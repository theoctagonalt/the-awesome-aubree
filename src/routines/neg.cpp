#include "./routines/neg.h"
#include "main.h"
#include "globals.h"
#include "initialize.h"
#include "./subsystems/arm.h"
#include "./subsystems/intake.h"
#include "./subsystems/doinker.h"
#include "./subsystems/mogo.h"

void neg_routine(int alliance_colour){
  int starting_dir = alliance_colour ? 66 : 294;
  int n = alliance_colour ? 1 : -1;
  int starting_y = alliance_colour ? 45 : 41;
  //set the starting pose to the acucurate heading and point
  chassis.setPose(n*55, starting_y, starting_dir);
  //move towards the alliance stake, backwards
  chassis.moveToPoint(n*29, 26, 1500, {.forwards=false});
  chassis.waitUntilDone();
  Mogo::toggle();
  int second_dir = alliance_colour ? 355 : 5;
  pros::delay(50);
  chassis.moveToPoint(n*30, 21, 1000, {.forwards=false});
  chassis.waitUntilDone();
  pros::delay(50);
  Intake::toggle(1);
  chassis.moveToPoint(n*31, 37, 500);
  chassis.waitUntilDone();
  chassis.moveToPoint(n*25, 52, 1500);
  chassis.waitUntilDone();
  int third_dir = alliance_colour ? 240 : 120;
  chassis.turnToHeading(third_dir, 500);
  chassis.waitUntilDone();
  chassis.moveToPoint(n*19, 50, 1500);
  chassis.waitUntilDone();
  chassis.moveToPoint(n*8, 48, 1500); 
  chassis.waitUntilDone();
  chassis.moveToPoint(n*25, 45, 1500, {.forwards=false});
  chassis.waitUntilDone();
  chassis.moveToPoint(n*8, 55, 1500); 
  chassis.waitUntilDone();
  chassis.moveToPoint(n*25, 45, 1500, {.forwards=false});
  chassis.waitUntilDone();
  chassis.moveToPoint(n*6, 33, 1500);
  chassis.waitUntilDone();
}