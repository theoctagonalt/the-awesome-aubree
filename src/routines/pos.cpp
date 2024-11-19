#include "./routines/pos.h"
#include "main.h"
#include "globals.h"
#include "initialize.h"
#include "./subsystems/arm.h"
#include "./subsystems/intake.h"
#include "./subsystems/doinker.h"
#include "./subsystems/mogo.h"

void pos_routine(int alliance_colour){ //0 = red, 1 = blue
    int starting_dir = alliance_colour ? 17.336 : 162.664;
    int n = alliance_colour ? 1 : -1;

    //set the starting pose to the accurate point and heading
		chassis.setPose(n*52.8, -2.57, starting_dir);
		//move to point 1 facing backwards
		chassis.moveToPoint(n*11.28, -43.8, 3000, {.forwards=false});
		chassis.waitUntilDone();
		//when there, toggle the mobile goal clamp
		Mogo::toggle();
		//score our preload onto the goal
		hooks_motor.move_velocity(200);
		pros::delay(100);

		//turn on the floating motor
		floating_motor.move_velocity(200);
		//move towards the indicated ring
		chassis.moveToPoint(n*24, -48, 500, {.forwards=true});
		//wait until we're 12 inches down
		chassis.waitUntil(12);
		//let go of our mobile goal, stop the hooks
		Mogo::toggle();
		hooks_motor.brake();
		chassis.waitUntilDone();
		//wait 200 ms, for the ring to be finished intaked
		pros::delay(200);
		//stop the floating motor
		floating_motor.brake();

		//move to the second mobile goal
		chassis.moveToPose(n*24, -34, 0, 500, {.forwards=false});
		chassis.waitUntilDone();
		//turn on the clamp
		Mogo::toggle();
		pros::delay(200);
		//score the stored mobile goal
		hooks_motor.move_velocity(200);
		floating_motor.move_velocity(200);
		pros::delay(200);

		//drive to the ladder
		chassis.moveToPoint(n*13, -17.5, 500, {.forwards=true});
		chassis.waitUntilDone();
		//stop the intake
		hooks_motor.brake();
		floating_motor.brake();
		//raise the arm
}