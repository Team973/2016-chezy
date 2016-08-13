##Chezy champs 2016 student bot code

Copied from 2016-inseason code.  Will strip things down and make adjustments to account for difference in robot.

###Where stuff is

Robot code is in robot-thing/src.

Autonomous routines are defined in robot-thing/src/Autonomous.h

Teleop controls are defined in robot-thing/src/Teleop.h

Selecting an autonomous routine is done via the joystick in disabled mode so those controls are defined in robot-thing/src/Disabled.h

Pin mappings are defined in robot-thing/src/RobotInfo.h

Initialization code is in robot-thing/src/Robot.{cpp,h}

Each subsystem has its own class defined in robot-thing/src/subsystems.  Usually these get instantiated in robot-thing/src/Robot.{cpp,h}
