#include "./routines/skills.h"
#include "main.h"
#include "globals.h"
#include "initialize.h"
#include "./subsystems/arm.h"
#include "./subsystems/intake.h"
#include "./subsystems/doinker.h"
#include "./subsystems/mogo.h"

void skills(){
  int colour = get_colour();
  chassis.setPose(0, 0, 90);
  Arm::set_state(SCORING);
  pros::delay(1000);
  chassis.moveToPoint(-10, 0, 1000, {.forwards=false});
  chassis.waitUntilDone();
  chassis.moveToPoint(-16, -24, 1000, {.forwards=false});
  chassis.waitUntilDone();
  pros::delay(150);
  Mogo::toggle();
  pros::delay(150);
  Intake::toggle(1);
  chassis.moveToPoint(-16, -70, 2000);
  chassis.waitUntilDone();
  chassis.moveToPoint(0, -70, 1000, {.forwards=false});
  chassis.waitUntilDone();
  pros::delay(500);
  Mogo::toggle();
}