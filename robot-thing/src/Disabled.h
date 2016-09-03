#include "lib/JoystickHelper.h"

namespace frc973 {

void Robot::DisabledStart(void) {
    fprintf(stderr, "***disable start\n");

    m_shooter->SetFlywheelStop();
	m_intake->SetIntakeMode(Intake::IntakeMode::off);
	fprintf(stderr, "disable start end \n");
}

void Robot::DisabledStop(void) {

}

void Robot::DisabledContinuous(void) {
	switch(m_autoDistance) {
	case AutoDistance::reallyNear:
		DBStringPrintf(DBStringPos::DB_LINE0, "really near");
		break;
	case AutoDistance::near:
		DBStringPrintf(DBStringPos::DB_LINE0, "near");
		break;
	case AutoDistance::middle:
		DBStringPrintf(DBStringPos::DB_LINE0, "middle");
		break;
	case AutoDistance::far:
		DBStringPrintf(DBStringPos::DB_LINE0, "far");
		break;
	}

	switch(m_autoShooterHeight) {
	case AutoShooterHeight::high:
		DBStringPrintf(DBStringPos::DB_LINE1, "high");
		break;
	case AutoShooterHeight::low:
		DBStringPrintf(DBStringPos::DB_LINE1, "ow");
		break;
	}
}

void Robot::HandleDisabledButton(uint32_t port, uint32_t button,
		bool pressedP){
	m_buttonPresses->LogPrintf("Button event port %d button %d pressed %d", port, button, pressedP);
	if (port == DRIVER_JOYSTICK_PORT) {
		switch (button) {
		case DualAction::BtnA:
			if (pressedP) {
				m_autoDistance = AutoDistance::reallyNear;
			}
			break;
		case DualAction::BtnB:
			if (pressedP) {
				m_autoDistance = AutoDistance::near;
			}
			break;
		case DualAction::BtnX:
			if (pressedP) {
				m_autoDistance = AutoDistance::middle;
			}
			break;
		case DualAction::BtnY:
			if (pressedP) {
				m_autoDistance = AutoDistance::far;
			}
			break;
		case DualAction::DPadUpVirtBtn:
			if (pressedP) {
				m_autoShooterHeight = AutoShooterHeight::high;
			}
			break;
		case DualAction::DPadDownVirtBtn:
			if (pressedP) {
				m_autoShooterHeight = AutoShooterHeight::low;
			}
			break;
		}
	}
}

}
