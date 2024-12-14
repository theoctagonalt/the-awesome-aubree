#include "./routines/pos.h"
#include "main.h"
#include "globals.h"
#include "initialize.h"
#include "./subsystems/arm.h"
#include "./subsystems/intake.h"
#include "./subsystems/doinker.h"
#include "./subsystems/mogo.h"

void pos_routine(){
		int colour = get_colour();
		int n = colour ? 1 : -1;
		int starting_x = colour ? 60 : -60;
		int starting_theta = colour ? 215: 135;
		chassis.setPose(starting_x, -20, starting_theta);

		Intake::toggle(1);

		chassis.moveToPoint(n*24, -46, 750);
		chassis.waitUntilDone();

		chassis.moveToPoint(n*12, -47, 750);
		chassis.waitUntilDone();

		Arm::set_state(MOGO_SCORING);

		pros::delay(100);
		Intake::toggle(1);

		pros::delay(500);

		Doinker::toggle();
		chassis.moveToPoint(n*20, -40, 500);
		chassis.waitUntilDone();

		int knock_over = colour ? 10 : 350;

		chassis.turnToHeading(knock_over, 1000, {.maxSpeed=100});
		chassis.waitUntilDone();

		Doinker::toggle();
		pros::delay(500);

		chassis.moveToPoint(n*20, -60, 1000, {.forwards=false});
		chassis.waitUntilDone();

		chassis.turnToHeading(175, 1000);
		chassis.waitUntilDone();

		Arm::set_state(REST);

		int mogo_2_heading = colour ? 0 : 90;

		chassis.turnToHeading(mogo_2_heading, 1000);
		chassis.waitUntilDone();

		chassis.moveToPoint(n*35, -40, 500, {.forwards=false});
		chassis.waitUntilDone();

		chassis.moveToPoint(n*32, -20, 1000, {.forwards=false});
		chassis.waitUntilDone();

		Mogo::toggle();
		pros::delay(100);
		Intake::toggle(1);
}