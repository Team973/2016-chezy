/*
 * Hanger.h
 *
 *  Created on: Apr 17, 2016
 *      Author: Andrew
 */

#ifndef SRC_SUBSYSTEMS_HANGER_H_
#define SRC_SUBSYSTEMS_HANGER_H_

class DoubleSolenoid;
class CANTalon;
class DigitalInput;

#include "lib/CoopTask.h"
#include "lib/TaskMgr.h"

namespace frc973 {

class Drive;
class Shooter;
class Turret;

class Hanger : public CoopTask {
public:
	enum HangerState {
		up,
		down,
		stop
	};

	Hanger(TaskMgr *scheduler, Drive *drive, Shooter *shooter, Turret *turret);
	virtual ~Hanger();

	void SetHangerState(HangerState state);

	/**
	 * Release the hooks if they haven't already been released
	 * If they have been released, just do nothing (don't spam them)
	 */
	void TryReleaseHooks();
private:

	void TaskPeriodic(RobotMode mode);

	TaskMgr *m_scheduler;
	Drive *m_drive;
	Shooter *m_shooter;
	Turret *m_turret;

	DoubleSolenoid *m_ptoRelease;
	CANTalon *m_crankMotor;

	DigitalInput *m_leftHookSensor;
	DigitalInput *m_rightHookSensor;

	bool m_hooksReleased;
	bool m_everSeenSwitch;

	HangerState m_state;
};

} /* namespace frc973 */

#endif /* SRC_SUBSYSTEMS_HANGER_H_ */
