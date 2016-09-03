namespace frc973 {

static constexpr double POS_2_TURN = 30.0;
static constexpr double POS_3_TURN = 5.0;
static constexpr double POS_4_TURN = -16.0;
static constexpr double POS_5_TURN = -23.22;

static constexpr double POS_2_DIST = 3.0 * 12.0;
static constexpr double POS_3_DIST = 0.0;
static constexpr double POS_4_DIST = 0.0;
static constexpr double POS_5_DIST = 0.0 * 12.0;

static constexpr int GO_BACK_START = 1001;
static constexpr int POST_BALL_SNATCH = 30;

static double headingBeforeTurn = 0.0;

double AutonomousDistance(Robot::AutoDistance autoDist){
	double dist = 0.0;
	switch(autoDist) {
	case Robot::AutoDistance::far:
		dist = 136;
		break;
	case Robot::AutoDistance::middle:
		dist = 124;
		break;
	case Robot::AutoDistance::near:
		dist = 112;
		break;
	case Robot::AutoDistance::reallyNear:
		dist = 100;
		break;
	}
	return dist;
}

void Robot::AutonomousStart(void) {
    printf("***auto start\n");

    m_shooter->SetFlywheelStop();
	m_intake->SetIntakeMode(Intake::IntakeMode::off);

	m_drive->Zero();

	m_autoState = 0;
}

void Robot::AutonomousStop(void) {
	printf("***auto stop\n");
}

void Robot::AutonomousContinuous(void) {
	switch(m_autoState) {
	case 0:
		//first argument is the distance to drive, second argument is what to drive relative to
		// (usually the first should be relative to now and the rest should be relative to setpoint)
		//third argument is the power scalar
		m_drive->PIDDrive(AutonomousDistance(m_autoDistance), Drive::RelativeTo::Now, 0.8);
		m_turret->SetTurretAutoTarget(true);
		m_autoTimer = GetMsecTime();
		if (m_autoShooterHeight == AutoShooterHeight::low) {
			m_shooter->SetShooterHeight(Shooter::ShooterHeight::low);
		}
		else {
			m_shooter->SetShooterHeight(Shooter::ShooterHeight::high);
		}
		m_autoState++;
		break;
	case 1:
		if (GetMsecTime() - m_autoTimer > 3000){
			m_autoState++;
		}
		break;
	case 2:
		m_shooter->SetFlywheelStart();
		m_autoTimer = GetMsecTime();
		m_autoState++;
		break;
	case 3:
		if ((m_drive->OnTarget() && GetMsecTime() - m_autoTimer >= 3000)
				|| GetMsecTime() - m_autoTimer > 6000){
			m_shooter->SetConveyorPower(1.0);
			m_shooter->SetFlywheelStop();
			m_autoState++;
		}
		break;
	default:
		break;
	}
	DBStringPrintf(DBStringPos::DB_LINE2, "auto %d", m_autoState);
}

}
