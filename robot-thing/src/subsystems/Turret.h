/*
 * Turret.h
 *
 *  Created on: Aug 12, 2016
 *      Author: Andrew
 */

#ifndef SRC_SUBSYSTEMS_TURRET_H_
#define SRC_SUBSYSTEMS_TURRET_H_

#include "WPILib.h"
#include "lib/CoopTask.h"

namespace frc973 {

class TaskMgr;

class Turret: public CoopTask {
public:

	enum class Flashlight{
		on,
		off
	};

	Turret(TaskMgr *scheduler);
	virtual ~Turret();

	/** Set turret position in degrees where 0 is forward and 90 is right */
	void SetTurretPosition(double pos);
	double GetTurretPosition();
	void SetTurretPower(double pow);
	bool TurretOnTarget();
	void SetTurretAutoTarget(bool autoTargetEnabled);
	void SetTurretMode(Flashlight newMode);

	void TaskPeriodic(RobotMode mode);
private:
	CANTalon *m_turretMotor;
	bool m_autoTargetEnabled;
public:
	AnalogInput *m_offsetInput;
private:
	DigitalInput *m_targetFoundInput;
	TaskMgr *m_scheduler;
	Solenoid *m_greenFlashlight;
	Solenoid *m_manualFlashlight;
	Flashlight m_flashlightMode;
	bool m_flashlightStarted;
};

}

#endif /* SRC_SUBSYSTEMS_TURRET_H_ */
