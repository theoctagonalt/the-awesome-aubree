#include "./routines/neg.h"
#include "main.h"
#include "globals.h"
#include "initialize.h"
#include "./subsystems/arm.h"
#include "./subsystems/intake.h"
#include "./subsystems/doinker.h"
#include "./subsystems/mogo.h"

void neg_routine(){
  int colour = get_colour();
  int starting_dir = colour ? 0 : 0;
  int n = colour ? -1 : 1;
  int starting_x = colour ? -53 : 56;
  int starting_y = colour ? -8 : -8;
  //set the starting pose to the acucurate heading and point
  chassis.setPose(starting_x, starting_y, starting_dir);
  
  int alliance_stake_x = colour ? n*65 : n*68;

  chassis.moveToPoint(alliance_stake_x, 9, 750);
  chassis.waitUntilDone();
  Arm::set_state(SCORING);
  pros::delay(750);

  Arm::set_state(REST);
  chassis.moveToPoint(n*35, -8, 500, {.forwards=false});
  chassis.waitUntilDone();
  chassis.moveToPoint(n*23, -16, 1000, {.forwards=false});
  chassis.waitUntilDone();
  Mogo::toggle();

  chassis.moveToPoint(n*10, -20, 1000);
  chassis.waitUntilDone();

  Intake::toggle(1);
  chassis.moveToPoint(n*2, -34, 1000, {.maxSpeed=100});
  chassis.waitUntilDone();
  
  chassis.moveToPoint(n*5, -30, 1000, {.forwards=false});
  chassis.waitUntilDone();

  pros::delay(750);

  chassis.moveToPoint(n*29, -45, 1000);
  chassis.waitUntilDone();

  pros::delay(750);

  chassis.moveToPoint(0, -49, 1000);
  chassis.waitUntilDone();

  pros::delay(500);

  chassis.moveToPoint(n*15, -42, 1000, {.forwards=false});
  chassis.waitUntilDone();

  chassis.moveToPoint(0, -47, 1000);
  chassis.waitUntilDone();

  pros::delay(500);

  if(get_match() == QUALS){
    Intake::toggle();

    chassis.moveToPoint(n*24, -24, 1000, {.forwards=false});
    chassis.waitUntilDone();
    
    chassis.moveToPoint(n*18, -2, 1000, {.forwards=false});
    chassis.waitUntilDone();

    Doinker::toggle();

    int turn = colour ? n*45 : -340;

    chassis.turnToHeading(turn, 1000);
    chassis.waitUntilDone();
  }else{
    chassis.moveToPoint(n*46, 3, 1500);
    chassis.waitUntilDone();
    chassis.moveToPoint(n*46, 40, 1000);
    chassis.waitUntilDone();

    Doinker::toggle();
  }
  master.rumble("..");
  
}