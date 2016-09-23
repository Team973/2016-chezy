/*
 * Shooter.cpp
 *
 *  Created on: Oct 9, 2015
 *      Author: Andrew
 */

#include "subsystems/Shooter.h"
#include "RobotInfo.h"
#include "lib/util/Util.h"
#include "lib/WrapDash.h"
#include "lib/TaskMgr.h"
#include "lib/logging/LogSpreadsheet.h"

namespace frc973 {

static constexpr bool SOL_EXTENDED = true;
static constexpr bool SOL_RETRACTED = false;

Shooter::Shooter(TaskMgr *scheduler, LogSpreadsheet *logger) :
		m_topFlywheelMotor(new VictorSP(TOP_FLYWHEEL_PWM)),
		m_bottomFlywheelMotor(new VictorSP(BOTTOM_FLYWHEEL_PWM)),
		m_conveyor(new VictorSP(SHOOTER_CONVEYER_MOTOR_PWM)),
		m_flywheelEnabled(false),
		m_elevatorState(ShooterHeight::low),
		m_shooterHeightSol(new Solenoid(1, SHOOTER_ANGLE_SOL)),
		m_scheduler(scheduler)
{
	m_scheduler->RegisterTask("Shooter", this, TASK_PERIODIC);
}

Shooter::~Shooter() {
	m_scheduler->UnregisterTask(this);
}

void Shooter::SetFlywheelStart() {
	m_flywheelEnabled = true;
	printf("start flywheel\n");
}

void Shooter::SetFlywheelStop() {
	m_flywheelEnabled = false;
	printf("stop flywheel\n");
}

void Shooter::SetConveyorPower(double pow) {
	m_conveyor->Set(pow);
}

void Shooter::TaskPeriodic(RobotMode mode) {
	if (m_flywheelEnabled) {
		m_topFlywheelMotor->Set(FLYWHEEL_ENABLED_SPEED);
		m_bottomFlywheelMotor->Set(FLYWHEEL_ENABLED_SPEED);
	}
	else {
		m_topFlywheelMotor->Set(0.0);
		m_bottomFlywheelMotor->Set(0.0);
	}
}

void Shooter::SetShooterHeight(ShooterHeight newHeight) {
	if (newHeight != m_elevatorState) {
		m_elevatorState = newHeight;

		switch (m_elevatorState) {
		case ShooterHeight::high:
			m_shooterHeightSol->Set(SOL_EXTENDED);
			break;
		case ShooterHeight::low:
			m_shooterHeightSol->Set(SOL_RETRACTED);
			break;
		}
	}
}

}
