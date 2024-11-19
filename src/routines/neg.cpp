#include "./routines/neg.h"
#include "main.h"
#include "globals.h"
#include "initialize.h"
#include "./subsystems/arm.h"
#include "./subsystems/intake.h"
#include "./subsystems/doinker.h"
#include "./subsystems/mogo.h"

void neg_routine(int alliance_colour){
  int starting_dir = alliance_colour ? 48.0128 : 318.0128;
  int n = alliance_colour ? 1 : -1;
  //set the starting pose to the acucurate heading and point
  chassis.setPose(n*61, 11, starting_dir);
  //move towards the alliance stake, backwards
  chassis.moveToPoint(n*66, 6.5, 500, {.forwards=false});
  chassis.waitUntilDone();
  //score our preload
  Intake::toggle_hooks(1);
  pros::delay(500);

  //move to halfway to the mobile goal, forward
  chassis.moveToPoint(n*50, 11.3, 500, {.forwards=true});
  chassis.waitUntilDone();
  Intake::toggle_hooks(1);
  //when halfway there, flip around and go backwards
  chassis.moveToPoint(n*35.5, 18, 500, {.forwards=false});
  chassis.waitUntilDone();
  //when there, toggle the mogo mech
  Mogo::toggle();
  pros::delay(250);

  //move to the indicated ring
  chassis.moveToPoint(n*15, 30.5, 500, {.forwards=false});
  chassis.waitUntilDone();
  //turn on the intake, inatke the ring
  Intake::toggle(1);
  chassis.moveToPoint(n*3, 45, 500, {.forwards=true});
  chassis.waitUntilDone();

  //move to the second ring
  chassis.moveToPoint(n*3, 53, 500);
  chassis.waitUntilDone();

  //move to the third ring
  chassis.moveToPoint(n*25, 48, 500);
  chassis.waitUntilDone();

  //move to the corner
  chassis.moveToPoint(n*58, 62, 1000);
  chassis.waitUntilDone();
  //toggle our corner clearning mech
  Doinker::toggle();
  int currentTheta = chassis.getPose().theta;
  //turn to either 10 degrees or 270 degrees
  chassis.turnToHeading(alliance_colour ? 10 : 270, 500);
  chassis.waitUntilDone();
  //when done, toggle our corner clearing mech to retract
  Doinker::toggle();
  //turn back to the original heading
  chassis.turnToHeading(currentTheta, 500);
  chassis.waitUntilDone();
  //move to the corner to intake the corner ring
  chassis.moveToPoint(n*67, 67, 250);

  chassis.waitUntilDone();
  pros::delay(100);
  Intake::toggle(1);
  //stop the intake
  //move to the ladder
  chassis.moveToPoint(n*17, 12, 2000);
  //raise arm up

  
}