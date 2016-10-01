/*
 * Shooter.h
 *
 *  Created on: Oct 9, 2015
 *      Author: Andrew
 */

#ifndef SRC_SUBSYSTEMS_SHOOTER_H_
#define SRC_SUBSYSTEMS_SHOOTER_H_

#include "WPILib.h"
#include "lib/CoopTask.h"

namespace frc973 {

class TaskMgr;
class CascadingFilter;
class MovingAverageFilter;
class DelaySwitch;
class PID;
class LogSpreadsheet;
class MedianFilter;
class StateSpaceFlywheelController;
class LogCell;
class LogSpreadsheet;

/**
 * Open loop control on flywheel at the moment... will do fine tuning
 * once it's shown that everything else works
 */
class Shooter : public CoopTask
{
public:
	enum ShooterHeight {
		high,
		low
	};

	Shooter(TaskMgr *scheduler, LogSpreadsheet *logger, PowerDistributionPanel *pdp);
	virtual ~Shooter();

	bool IsFlywheelReady();

	void SetFlywheelStart();
	void SetFlywheelStop();

	void SetConveyorPower(double pow);

	void TaskPeriodic(RobotMode mode);

	void SetShooterHeight(ShooterHeight newHeight);
private:
	VictorSP *m_topFlywheelMotor;
	VictorSP *m_bottomFlywheelMotor;
	VictorSP *m_conveyor;

	bool m_flywheelEnabled;

	ShooterHeight m_elevatorState;
	Solenoid *m_shooterHeightSol;

	TaskMgr *m_scheduler;
	PowerDistributionPanel *m_pdp;

	static constexpr double FLYWHEEL_ENABLED_SPEED = 1.0;
};

}

#endif /* SRC_SUBSYSTEMS_SHOOTER_H_ */
