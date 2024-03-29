using namespace vex;

extern brain Brain;

// VEXcode devices
extern motor FrontLeft;
extern motor FrontRight;
extern motor BackLeft;
extern motor BackRight;
extern controller Controller1;
extern motor Rollers;
extern motor Intake;
extern motor FlywheelNonSparkly;
extern motor FlywheelSparkly;
extern limit JumperA;
extern limit JumperB;
extern limit JumperC;
extern limit JumperD;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );