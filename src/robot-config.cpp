#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
motor FrontLeft = motor(PORT1, ratio18_1, true);
motor FrontRight = motor(PORT3, ratio18_1, false);
motor BackLeft = motor(PORT2, ratio18_1, false);
motor BackRight = motor(PORT4, ratio18_1, true);
controller Controller1 = controller(primary);
motor Rollers = motor(PORT11, ratio36_1, false);
motor Intake = motor(PORT12, ratio18_1, false);
motor FlywheelNonSparkly = motor(PORT13, ratio6_1, false);
motor FlywheelSparkly = motor(PORT14, ratio6_1, true);
limit JumperA = limit(Brain.ThreeWirePort.A);
limit JumperB = limit(Brain.ThreeWirePort.B);
limit JumperC = limit(Brain.ThreeWirePort.C);
limit JumperD = limit(Brain.ThreeWirePort.D);

// VEXcode generated functions
// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}