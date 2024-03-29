/*
 * Turret.cpp
 *
 *  Created on: Aug 12, 2016
 *      Author: Andrew
 */

#include <subsystems/Turret.h>
#include "RobotInfo.h"
#include "lib/TaskMgr.h"
#include "lib/util/Util.h"
#include <subsystems/Drive.h>

namespace frc973 {

constexpr double CLICKS_PER_DEGREE = 14.0;

Turret::Turret(TaskMgr *scheduler, Drive *drive)
		: m_turretMotor(new CANTalon(SHOOTER_TURRET_CAN_ID))
		, m_autoTargetEnabled(false)
		, m_offsetInput(new AnalogInput(PIXY_CAM_ANALOG_PORT))
		, m_targetFoundInput(new DigitalInput(PIXY_CAM_DIGITAL_PORT))
		, m_scheduler(scheduler)
		, m_greenFlashlight(new Solenoid(1, GREEN_FLASHLIGHT))
		, m_manualFlashlight(new Solenoid(1, MANUAL_FLASHLIGHT))
		, m_flashlightMode (Flashlight::on)
		, m_flashlightStarted(false)
		, m_drive(drive)
{
	m_scheduler->RegisterTask("Shooter", this, TASK_PERIODIC);
	m_turretMotor->SetFeedbackDevice(CANTalon::FeedbackDevice::QuadEncoder);
	m_turretMotor->SetSensorDirection(true);
	m_turretMotor->ConfigForwardLimit(80.0 * CLICKS_PER_DEGREE);
	m_turretMotor->ConfigReverseLimit(-80.0 * CLICKS_PER_DEGREE);
	m_greenFlashlight->Set(true);
}

Turret::~Turret() {
	m_scheduler->UnregisterTask(this);
}

void Turret::SetTurretPosition(double pos) {
	m_turretMotor->SetControlMode(CANTalon::ControlMode::kPosition);
	m_turretMotor->Set(pos * CLICKS_PER_DEGREE);
}

double Turret::GetTurretPosition() {
	return m_turretMotor->GetEncPosition();
}

void Turret::SetTurretPower(double pow) {
	m_autoTargetEnabled = false;
	m_turretMotor->SetControlMode(CANTalon::ControlMode::kPercentVbus);
	m_turretMotor->Set(pow);
}

bool Turret::TurretOnTarget() {
	return Util::abs(m_offsetInput->GetVoltage() - (3.3 / 2)) < 0.25 &&
			Util::abs(m_turretMotor->GetEncVel()) < 0.25;
}

void Turret::SetTurretAutoTarget(bool autoTargetEnabled) {
	m_autoTargetEnabled = autoTargetEnabled;

	if (m_autoTargetEnabled) {
		m_turretMotor->SetControlMode(CANTalon::ControlMode::kPercentVbus);
		m_turretMotor->Set(0.0);

		}
	else {
		m_turretMotor->SetControlMode(CANTalon::ControlMode::kPercentVbus);
		m_turretMotor->Set(0.0);
	}
}

void Turret::SetTurretMode(Flashlight newMode) {
	if (newMode != m_flashlightMode) {
		switch (newMode) {
		case Flashlight::off:
			m_manualFlashlight->Set(false);
			break;
		case Flashlight::on:
			m_manualFlashlight->Set(true);
			break;
		}
	}

	m_flashlightMode = newMode;
}

void Turret::TaskPeriodic(RobotMode mode) {
	if (!m_flashlightStarted) {
		m_flashlightStarted = true;
		m_greenFlashlight->Set(true);
	}
	if (m_autoTargetEnabled) {
		if (m_targetFoundInput->Get()) {
			double offset = (m_offsetInput->GetVoltage() - (3.3 / 2));
			double power = Util::signedIncrease(offset * 0.6, 0.055);
			double feedForward = m_drive->GetAngularRate() * -1.0;
			m_turretMotor->Set(power + feedForward);
			printf("turr offset %f pow %f\n", offset, power);
		}
	}
}

}
