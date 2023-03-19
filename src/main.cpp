/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       VEX                                                       */
/*    Created:      Thu Sep 26 2019                                           */
/*    Description:  Competition Template                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// FrontLeft            motor         1               
// FrontRight           motor         3               
// BackLeft             motor         2               
// BackRight            motor         4               
// Controller1          controller                    
// Rollers              motor         11              
// Intake               motor         12              
// FlywheelNonSparkly   motor         13              
// FlywheelSparkly      motor         14              
// JumperA              limit         A               
// JumperB              limit         B               
// JumperC              limit         C               
// JumperD              limit         D               
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;

// define your global instances of motors and other devices here

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

// ~~~~~~~~~~~~ helper functions below ~~~~~~~~~~~~
float CHASSIS_GEAR_RATIO = 1;

int ROLLER_SPEED = 30;
int INTAKE_SPEED = 200;
int FLYWHEEL_SPEED = 375; 

float const PI = 2 * acos(0.0);
int WHEEL_DIAMETER = 4;
float WHEEL_CIRCUMFERENCE = WHEEL_DIAMETER * PI;

float TURNING_DIAMETER = 17; // TO BE ALTERED!

void spinRollers() {
  if (Controller1.ButtonB.pressing()) {
    Rollers.spin(forward, ROLLER_SPEED, rpm);
  } else if (Controller1.ButtonX.pressing()) {
    Rollers.spin(reverse, ROLLER_SPEED, rpm);
  } else {
    Rollers.stop(hold);
  }
}

// void spinIntakeAndRollers() {
//     if (Controller1.ButtonA.pressing()) {
//       Intake.spin(forward, intakeSpeed, rpm);
//     } else if (Controller1.ButtonY.pressing()) {
//       Intake.spin(reverse, intakeSpeed, rpm);
//     } else if (Controller1.ButtonR1.pressing()) {
//       FlywheelSparkly.spin(forward, flywheelSpeed, rpm);
//       FlywheelNonSparkly.spin(forward, flywheelSpeed, rpm);
//       Intake.spin(forward, intakeSpeed, rpm);
//     } else {
//       FlywheelSparkly.stop();
//       FlywheelNonSparkly.stop();
//       Intake.stop(hold);
//     }
// }

bool spinFlywheel = false;

void doSpinFlywheel() {
  spinFlywheel = true;
}
void dontSpinFlywheel() {
  spinFlywheel = false;
}

void spinIntakeAndFlywheel() {
    if (Controller1.ButtonA.pressing()) {
      Intake.spin(forward, INTAKE_SPEED, rpm);
    } else if (Controller1.ButtonY.pressing()) {
      Intake.spin(reverse, INTAKE_SPEED, rpm);
    } else if (Controller1.ButtonR1.pressing()) {
      Intake.spin(forward, INTAKE_SPEED, rpm);
    } else {
      Intake.stop(hold);
    }

    Controller1.ButtonR1.pressed(doSpinFlywheel);
    Controller1.ButtonR2.pressed(dontSpinFlywheel);
}

// void shootDisks() {
//   if (Controller1.ButtonR1.pressing()) {
//     FlywheelSparkly.spin(forward, flywheelSpeed, rpm);
//     FlywheelNonSparkly.spin(forward, flywheelSpeed, rpm);
//     Intake.spin(forward, intakeSpeed, rpm);

//   } else {
//     FlywheelSparkly.stop();
//     FlywheelNonSparkly.stop();
//     Intake.stop(hold);
//   }
// }

  // [RESOURCE FOR THESE HELPER FUNCTIONS: https://medium.com/thefloatingpoint/autonomous-driving-tutorial-for-vex-v5-robots-774703ca2d3c]
  void driveDistanceInches(int distance) { // distance in inches
    float INCHES_PER_DEGREE = WHEEL_CIRCUMFERENCE / 360;
    float degreesSpin = distance / INCHES_PER_DEGREE * CHASSIS_GEAR_RATIO;
    //int degreesSpin = distance * 360; // to be altered!
    FrontLeft.spinFor(forward, degreesSpin, degrees, false); 
    FrontRight.spinFor(forward, degreesSpin, degrees, false);
    BackLeft.spinFor(forward, degreesSpin, degrees, false);
    BackRight.spinFor(forward, degreesSpin, degrees);

  }

  void turnAngle(int angle) { // sussy
    float turningRatio = 2.5*TURNING_DIAMETER / WHEEL_DIAMETER;
    float turnDegrees = turningRatio * angle;
    FrontLeft.spinFor(forward, turnDegrees * CHASSIS_GEAR_RATIO / 2, degrees, false); 
    FrontRight.spinFor(reverse, turnDegrees * CHASSIS_GEAR_RATIO / 2, degrees, false);
    BackLeft.spinFor(forward, turnDegrees * CHASSIS_GEAR_RATIO / 2, degrees, false);
    BackRight.spinFor(reverse, turnDegrees * CHASSIS_GEAR_RATIO / 2, degrees);
  }

  void setChassisSpeed(int speed) {
    FrontLeft.setVelocity(speed, percent);
    FrontRight.setVelocity(speed, percent);
    BackLeft.setVelocity(speed, percent); 
    BackRight.setVelocity(speed, percent); 
  }

  void setIntakeSpeed(int speed) {
    Intake.setVelocity(speed, percent); 
  }

  void setFlywheelSpeed(int speed) {
    FlywheelNonSparkly.setVelocity(speed, percent);
    FlywheelSparkly.setVelocity(speed, percent); 
  }

  double driveVel = 1.25;

  // turn all autons into functions that can be called in jumper code
  
  void AutonA() {
    setChassisSpeed(15);
    driveDistanceInches(4);
    Rollers.spinFor(forward, 90, degrees);
    driveDistanceInches(-3);
  }
  void AutonB() {
    setChassisSpeed(75);
    driveDistanceInches(24);
    turnAngle(110);
    setChassisSpeed(15);
    driveDistanceInches(5);
    Rollers.spinFor(forward, 90, degrees);
    driveDistanceInches(-3);
  }
  void AutonC() {
    //roll rollers
    setChassisSpeed(15);
    driveDistanceInches(4);
    Rollers.spinFor(forward, 90, degrees);
    driveDistanceInches(-3);
    setChassisSpeed(75);
    wait(500, msec);
    turnAngle(100); //back is towards low-goal

    //prepare low-goal scoring
    setFlywheelSpeed(75);
    FlywheelNonSparkly.spin(forward);
    FlywheelSparkly.spin(forward);
    driveDistanceInches(-24);
    wait(500, msec);

    //shoot pre-loads
    setIntakeSpeed(75);
    Intake.spinFor(forward, 4, turns);

    //stop flywheel
    FlywheelNonSparkly.stop();
    FlywheelSparkly.stop();
  }
  void AutonD() {
    //roll rollers
    setChassisSpeed(75);
    driveDistanceInches(24);
    turnAngle(110);
    setChassisSpeed(15);
    driveDistanceInches(6); //go against rollers
    Rollers.spinFor(forward, 90, degrees);
    driveDistanceInches(-3); //back away from rollers
    setChassisSpeed(75);
    wait(500, msec);
    turnAngle(100); //front is towards low-goal

    //prepare low-goal scoring
    driveDistanceInches(55);
    wait(500, msec);

    //shoot pre-loads
    setIntakeSpeed(75);
    Intake.spinFor(reverse, 6, turns);
  }

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

 void autonomous(void) {
  
  if (JumperA.pressing()) {
    AutonA();
  } else if (JumperB.pressing()) {
    AutonB();
  } else if (JumperC.pressing()) {
    AutonC();
  } else if (JumperD.pressing()) {
    AutonD();
  } else AutonA();

  //reset all velocities to 100% speed
  setChassisSpeed(100);
  setFlywheelSpeed(100); 
  setIntakeSpeed(100);

}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/



void driverControl() {
  // 4 motors: upper left (1), upper right (2), lower left (3), lower right (4)
  // left joystick: forward and backward + sideways (axes 3 and 4)
  // right joystick: turning (axes 1)

  int forwardVal = Controller1.Axis3.position(percent);
  int sidewaysVal = Controller1.Axis4.position(percent);
  int turnVal = Controller1.Axis1.position(percent);

  int deadband = 3;

  if (abs(forwardVal) < deadband && abs(sidewaysVal) < deadband && abs(turnVal) < deadband) {
    FrontLeft.stop(hold);
    FrontRight.stop(hold);
    BackLeft.stop(hold);
    BackRight.stop(hold);
    
  } else {
    FrontLeft.spin(forward, (forwardVal + sidewaysVal + turnVal) * driveVel, percent);
    FrontRight.spin(forward, (forwardVal - sidewaysVal - turnVal) * driveVel, percent);
    BackLeft.spin(forward, (forwardVal - sidewaysVal + turnVal) * driveVel, percent);
    BackRight.spin(forward, (forwardVal + sidewaysVal - turnVal) * driveVel, percent);
    // 12/08 negated turnVal because axis 1 was coded backwards. hope it works lol
    // update ehehe it works !!! i (julia) am so smart :D
  }

}

void usercontrol(void) {
  // User control code here, inside the loop
  while (1) {
    // This is the main execution loop for the user control program.
    // Each time through the loop your program should update motor + servo
    // values based on feedback from the joysticks.

    // ........................................................................
    // Insert user code here. This is where you use the joystick values to
    // update your motors, etc.
    // ........................................................................
    driverControl();

    //roller motor movement
    spinRollers();

    spinIntakeAndFlywheel();

    if (spinFlywheel) {
      FlywheelSparkly.spin(forward, FLYWHEEL_SPEED, rpm);
      FlywheelNonSparkly.spin(forward, FLYWHEEL_SPEED, rpm);
    } else {
      FlywheelSparkly.stop();
      FlywheelNonSparkly.stop();
    }

    //shootDisks();

    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }
}


//
// Main will set up the competition functions and callbacks.
//
int main() {
  // Set up callbacks for autonomous and driver control periods.
  //Competition.autonomous(autonomous);

  Competition.drivercontrol(usercontrol);
  // THIS IS THE CHANGE IM MAKING!

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}