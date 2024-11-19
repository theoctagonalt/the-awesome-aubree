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
  chassis.setPose(n*61, 11, starting_dir);
  chassis.moveToPoint(n*66, 6.5, 500, {.forwards=false});
  chassis.waitUntilDone();
  Intake::toggle_hooks(1);
  pros::delay(500);

  chassis.moveToPoint(n*50, 11.3, 500, {.forwards=true});
  chassis.waitUntilDone();
  chassis.moveToPoint(n*35.5, 18, 500, {.forwards=false});
  chassis.waitUntilDone();
  Mogo::toggle();
  pros::delay(250);

  chassis.moveToPoint(n*15, 30.5, 500, {.forwards=false});
  chassis.waitUntilDone();
  Intake::toggle(1);
  chassis.moveToPoint(n*3, 45, 500, {.forwards=true});
  chassis.waitUntilDone();

  chassis.moveToPoint(n*3, 53, 500);
  chassis.waitUntilDone();

  chassis.moveToPoint(n*25, 48, 500);
  chassis.waitUntilDone();

  chassis.moveToPoint(n*58, 62, 1000);
  chassis.waitUntilDone();
  Doinker::toggle();
  int currentTheta = chassis.getPose().theta;
  chassis.turnToHeading(alliance_colour ? 10 : 270, 500);
  chassis.waitUntilDone();
  chassis.turnToHeading(currentTheta, 500);
  chassis.waitUntilDone();
  chassis.moveToPoint(n*67, 67, 250);

  chassis.waitUntilDone();
  chassis.moveToPoint(n*17, 12, 2000);
  //raise arm up

  
}