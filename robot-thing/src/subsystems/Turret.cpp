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

namespace frc973 {

constexpr double CLICKS_PER_DEGREE = 14.0;

Turret::Turret(TaskMgr *scheduler)
		: m_turretMotor(new CANTalon(SHOOTER_TURRET_CAN_ID))
		, m_autoTargetEnabled(false)
		, m_offsetInput(new AnalogInput(PIXY_CAM_ANALOG_PORT))
		, m_targetFoundInput(new DigitalInput(PIXY_CAM_DIGITAL_PORT))
		, m_scheduler(scheduler)
{
	m_scheduler->RegisterTask("Shooter", this, TASK_PERIODIC);
	m_turretMotor->SetFeedbackDevice(CANTalon::FeedbackDevice::QuadEncoder);
	m_turretMotor->SetSensorDirection(true);
	m_turretMotor->ConfigForwardLimit(80.0 * CLICKS_PER_DEGREE);
	m_turretMotor->ConfigReverseLimit(-80.0 * CLICKS_PER_DEGREE);
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

void Turret::TaskPeriodic(RobotMode mode) {
	if (m_autoTargetEnabled) {
		if (m_targetFoundInput->Get()) {
			double offset = -(m_offsetInput->GetVoltage() - (3.3 / 2));
			m_turretMotor->Set(offset * -0.5);
			printf("Setting speed setpoint on turret\n");
		}
	}
}

}
