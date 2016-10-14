/*
 * Hanger.cpp
 *
 *  Created on: Apr 17, 2016
 *      Author: Andrew
 */

#include <subsystems/Hanger.h>
#include "subsystems/Drive.h"
#include "subsystems/Shooter.h"
#include "lib/WrapDash.h"

#include "WPILib.h"
#include "RobotInfo.h"
#include "subsystems/Turret.h"

namespace frc973 {

static constexpr double DEFAULT_HANG_POWER = -1.0;

Hanger::Hanger(TaskMgr *scheduler, Drive *drive, Shooter *shooter, Turret *turret)
		 : CoopTask()
		 , m_scheduler(scheduler)
		 , m_drive(drive)
		 , m_ptoRelease(new DoubleSolenoid(POWER_TAKEOFF_SOL_A, POWER_TAKEOFF_SOL_B))
		 , m_crankMotor(new CANTalon(HANGER_CRANK_CAN_ID))
		 , m_leftHookSensor(new DigitalInput(LEFT_HOOK_HALL_DIN))
		 , m_rightHookSensor(new DigitalInput(RIGHT_HOOK_HALL_DIN))
		 , m_hooksReleased(false)
		 , m_everSeenSwitch(false)
		 , m_turret()
		 , m_shooter()
		 , m_state(HangerState::stop) {
	m_scheduler->RegisterTask("Hanger", this, TASK_PERIODIC);

	m_ptoRelease->Set(DoubleSolenoid::Value::kReverse);
}

Hanger::~Hanger() {
	m_scheduler->UnregisterTask(this);
}

void Hanger::SetHangerState(HangerState state) {
	if (state == autohangprefire || state == autohang){
		//Do nothing. Thous shall not pass.
	}
	else if (m_state == stop || m_state == down || m_state == up || m_state == autohang){
		m_state = state;
	}
}

void Hanger::TryReleaseHooks() {
	if (m_hooksReleased != true){
		m_ptoRelease->Set(DoubleSolenoid::Value::kForward);
		m_hooksReleased = true;
	}
	else {
	}
}

void Hanger::TaskPeriodic(RobotMode mode) {
	DBStringPrintf(DBStringPos::DB_LINE6,
			"left %s, right %s\n",
			(!m_leftHookSensor->Get()? "hit" : "mis"),
			(!m_rightHookSensor->Get()? "hit" : "mis"));

	switch (m_state) {
	case HangerState::up:
		m_crankMotor->Set(DEFAULT_HANG_POWER);
		break;
	case HangerState::down:
		m_crankMotor->Set(-DEFAULT_HANG_POWER);
		break;
	case HangerState::stop:
		m_crankMotor->Set(0.0);
		break;
	case HangerState::autohang:
		m_crankMotor->Set(DEFAULT_HANG_POWER);
		if (m_leftHookSensor->Get() == true || m_rightHookSensor->Get() == true){
			m_crankMotor->Set(0.0);
			m_state = autohangprefire;
		}
		break;
	case HangerState::autohangprefire:
		m_turret->SetTurretAutoTarget(false);
		m_turret->SetTurretPosition(0.0);
		m_shooter->SetFlywheelStart();
		if (m_shooter->IsFlywheelReady() == true){
			m_state = autohangfire;
		}
		break;
	case HangerState::autohangfire:
		m_shooter->SetConveyorPower(1.0);
		break;
	}
}

} /* namespace frc973 */
