#include "lib/JoystickHelper.h"
#include "lib/WrapDash.h"

namespace frc973 {

void Robot::TeleopStart(void) {
	m_teleopTimeSec = GetSecTime();
	m_drive->ArcadeDrive(0.0, 0.0);
	m_shooter->SetConveyorPower(0.0);
    printf("***teleop start\n");
}

void Robot::TeleopStop(void) {
    printf("***teleop stop\n");
}

static bool teleopDrive = true;
static bool conveyorNeedsStop = false;
static bool intakeNeedsStop = false;
static bool turretManualControl = true;

void Robot::TeleopContinuous(void) {
	double intakePower = m_operatorJoystick->GetRawAxisWithDeadband(
			DualAction::LeftYAxis, 0.2);
	if (intakePower != 0.0) {
		m_intake->SetIntakePower(intakePower);
		intakeNeedsStop = true;
	}
	else if (intakeNeedsStop) {
		m_intake->SetIntakePower(0.0);
		intakeNeedsStop = false;
	}


	double conveyorPower = m_operatorJoystick->GetRawAxisWithDeadband(
			DualAction::LeftXAxis, 0.2);
	if (conveyorPower != 0.0) {
		m_shooter->SetConveyorPower(conveyorPower);
		conveyorNeedsStop = true;
	}
	else if (conveyorNeedsStop) {
		m_shooter->SetConveyorPower(0.0);
		conveyorNeedsStop = false;
	}
	/*
	m_drive->CheesyDrive(m_driverJoystick->GetRawAxis(DualAction::LeftYAxis),
			-m_driverJoystick->GetRawAxis(DualAction::RightXAxis), false,
			m_driverJoystick->GetRawButton(DualAction::RightBumper));
			*/

	double turretControlPower = m_operatorJoystick->GetRawAxisWithDeadband(
			DualAction::RightXAxis, 0.2);
	if (Util::abs(turretControlPower) > 0.5) {
		turretManualControl = true;
		m_turret->SetTurretAutoTarget(false);
	}
	if (turretManualControl  == true){
		m_turret->SetTurretPower(turretControlPower * 0.5);
	}

	double y = m_driverJoystick->GetRawAxis(DualAction::LeftYAxis);
	double x = -m_driverJoystick->GetRawAxis(DualAction::RightXAxis);

	if (teleopDrive) {
		if (m_driverJoystick->GetRawButton(DualAction::LeftBumper)) {
			y *= 0.4;
			x *= 0.4;
		}

		m_drive->ArcadeDrive(y, x);
	}

 	/*
	printf("gyro reading %lf... raw counts %d\n", m_gyroEncoder->GetDistance(),
			m_gyroEncoder->GetRaw());
			*/
}

static double closeGoal = 5500.0;

void Robot::HandleTeleopButton(uint32_t port, uint32_t button,
		bool pressedP) {
	if (port == DRIVER_JOYSTICK_PORT) {
		switch (button) {
		case DualAction::BtnA:
			if (pressedP) {
			}
			break;
		case DualAction::BtnB:
			if (pressedP) {
				//m_drive->PIDTurn(-5.0, Drive::RelativeTo::Now);
				m_drive->ArcadeDrive(0.0, 0.0);
				teleopDrive = true;
			}
			break;
		case DualAction::BtnX:
			if (pressedP) {
				teleopDrive = false;
				//m_drive->SetVisionTargeting();
				//m_drive->VelocityPIDTurn(1.0, DriveBase::RelativeTo::Now);
				//closeGoal -= 50.0;
				//m_shooter->SetBackFlywheelSSShoot(closeGoal);
			}
			break;
		case DualAction::BtnY:
			if (pressedP) {
				teleopDrive = true;
				m_drive->ArcadeDrive(0.0, 0.0);
				//m_drive->VelocityPIDTurn(10.0, DriveBase::RelativeTo::SetPoint);
				//closeGoal += 50.0;
				//m_shooter->SetBackFlywheelSSShoot(closeGoal);
			}
			break;
		case DualAction::LeftBumper:
			if (pressedP) {
				m_drive->SetGearing(Drive::DriveGearing::LowGear);
			}
			break;
		case DualAction::LeftTrigger:
			if (pressedP) {
				m_drive->SetGearing(Drive::DriveGearing::HighGear);
			}
			break;
		case DualAction::RightBumper:
			if (pressedP) {
				//m_poseManager->AssumePose();
			}
			break;
		case DualAction::RightTrigger:
			if (pressedP) {
				m_intake->SetIntakeMode(Intake::IntakeMode::forward);
				m_shooter->SetConveyorPower(0.8);
				m_compressor->Disable();
			}
			else {
				m_intake->SetIntakeMode(Intake::IntakeMode::off);
				m_shooter->SetConveyorPower(0.0);
				m_compressor->Enable();
			}
			break;
		case DualAction::Start:
			//m_hanger->TryReleaseHooks();
			break;
		case DualAction::Back:
			if (pressedP) {
			}
			break;
		}
	}
	else if (port == OPERATOR_JOYSTICK_PORT) {
		switch (button) {
		case DualAction::BtnY:
			if (pressedP) {
				m_shooter->SetShooterHeight(Shooter::ShooterHeight::low);
				m_turret->SetTurretPosition(0.0);
				m_shooter->SetFlywheelStart();
				m_turret->SetTurretAutoTarget(true);
				turretManualControl = false;
			}
			break;
		case DualAction::BtnA:
			if (pressedP) {
				m_shooter->SetShooterHeight(Shooter::ShooterHeight::high);
				m_turret->SetTurretPosition(0.0);
				m_shooter->SetFlywheelStart();
				m_turret->SetTurretAutoTarget(true);
				turretManualControl = false;
			}
			break;
		case DualAction::BtnX:
			if (pressedP) {
				m_shooter->SetShooterHeight(Shooter::ShooterHeight::low);
				m_turret->SetTurretPosition(75.0);
				m_shooter->SetFlywheelStart();
				m_turret->SetTurretAutoTarget(true);
				turretManualControl = false;
			}
			break;
		case DualAction::BtnB:
			if (pressedP) {
				m_shooter->SetShooterHeight(Shooter::ShooterHeight::low);
				m_turret->SetTurretPosition(-75.0);
				m_shooter->SetFlywheelStart();
				m_turret->SetTurretAutoTarget(true);
				m_turret->SetTurretMode(Turret::Flashlight::on);
				turretManualControl = false;
			}
			break;
		case DualAction::RYAxisVirtButton:
			if (pressedP == false) {
				m_turret->SetTurretAutoTarget(false);
			}
			else {
				m_turret->SetTurretAutoTarget(false);
			}
			break;
		case DualAction::LeftBumper:
			if (pressedP) {
				m_intake->SetIntakePosition(Intake::IntakePosition::extended);
			}
			break;
		case DualAction::LeftTrigger:
			if (pressedP) {
				m_intake->SetIntakePosition(Intake::IntakePosition::retracted);
			}
			break;
		case DualAction::RightBumper:
			if (pressedP) {
				m_intake->SetIntakeMode(Intake::IntakeMode::forward);
			}
			else {
				m_intake->SetIntakeMode(Intake::IntakeMode::off);
			}
			break;
		case DualAction::RightTrigger:
			if (pressedP) {
				m_intake->SetIntakeMode(Intake::IntakeMode::reverse);
				m_shooter->SetConveyorPower(-0.8);
			}
			else {
				m_intake->SetIntakeMode(Intake::IntakeMode::off);
				m_shooter->SetConveyorPower(0.0);
			}
			break;
		case DualAction::DPadUpVirtBtn:
			if (pressedP) {
				m_shooter->SetFlywheelStart();
				DBStringPrintf(DBStringPos::DB_LINE0, "shooter enabled");
			}
			break;
		case DualAction::DPadDownVirtBtn:
			if (pressedP) {
				m_shooter->SetFlywheelStop();
				DBStringPrintf(DBStringPos::DB_LINE0, "shooter disabled");
			}
			break;
		case DualAction::DPadLeftVirtBtn:
			m_intake->SetIntakePosition(Intake::IntakePosition::extended);
			break;
		case DualAction::DPadRightVirtBtn:
			m_intake->SetIntakePosition(Intake::IntakePosition::retracted);
			break;
		case DualAction::Back:
			m_hanger->SetManualHang(pressedP);
			break;
		case DualAction::Start:
			m_hanger->SetAutoHang(pressedP);
			break;
		}
	}

	DBStringPrintf(DBStringPos::DB_LINE4,
			"front p %lf", closeGoal);
	}
}
