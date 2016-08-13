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
	Turret(TaskMgr *scheduler);
	virtual ~Turret();

	/** Set turret position in degrees where 0 is forward and 90 is right */
	void SetTurretPosition(double pos);
	double GetTurretPosition();
	void SetTurretPower(double pow);
	bool TurretOnTarget();
	void SetTurretAutoTarget(bool autoTargetEnabled);

	void TaskPeriodic(RobotMode mode);
private:
	CANTalon *m_turretMotor;
	bool m_autoTargetEnabled;
public:
	AnalogInput *m_offsetInput;
private:
	DigitalInput *m_targetFoundInput;
	TaskMgr *m_scheduler;
};

}

#endif /* SRC_SUBSYSTEMS_TURRET_H_ */
