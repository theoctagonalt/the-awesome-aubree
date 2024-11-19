#include "main.h"
#include "globals.h"
#include "initialize.h"
#include "arm.h"
#include "intake.h"
#include "doinker.h"
#include "mogo.h"

void screen() {
	// loop forever
	while (true) {
			lemlib::Pose pose = chassis.getPose(); // get the current position of the robot
			pros::lcd::print(0, "x: %f", pose.x); // print the x position
			pros::lcd::print(1, "y: %f", pose.y); // print the y position
			pros::lcd::print(2, "heading: %f", pose.theta); // print the heading
			pros::delay(10);
	}
}


void autonomous() {
  int routine = get_routine();
	pros::Task screenTask(screen);
	FILE* output_file = fopen("/usd/lateral_pid_10.txt", "a");
	fputs("==============\n", output_file);
	float time = 0;
	chassis.setPose(0, 0, 90);
	chassis.turnToHeading(270, 5000);
	while(chassis.isInMotion()){
		// pros::lcd::print(0, "X: %f", chassis.getPose().x); // x
		// pros::lcd::print(1, "Y: %f", chassis.getPose().y); // y
		// pros::lcd::print(2, "Theta: %f", chassis.getPose().theta); // heading
		float theta = chassis.getPose().theta;
		fprintf(output_file, "%f\n",theta);
		time+=40;
		pros::delay(250);
	}
	chassis.waitUntilDone();
	fclose(output_file);
	if(routine == POS_RED){
		//set the starting pose to the accurate point and heading
		chassis.setPose(-52.8, -2.57, 162.664);
		//move to point 1 facing backwards
		chassis.moveToPoint(-11.28, -43.8, 3000, {.forwards=false});
		chassis.waitUntilDone();
		//when there, toggle the mobile goal clamp
		Mogo::toggle();
		//score our preload onto the goal
		hooks_motor.move_velocity(200);
		pros::delay(100);

		//turn on the floating motor
		floating_motor.move_velocity(200);
		//move towards the indicated ring
		chassis.moveToPoint(-24, -48, 500, {.forwards=true});
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
		chassis.moveToPose(-24, -34, 0, 500, {.forwards=false});
		chassis.waitUntilDone();
		//turn on the clamp
		Mogo::toggle();
		pros::delay(200);
		//score the stored mobile goal
		hooks_motor.move_velocity(200);
		floating_motor.move_velocity(200);
		pros::delay(200);

		//drive to the ladder
		chassis.moveToPoint(-13, -17.5, 500, {.forwards=true});
		chassis.waitUntilDone();
		//stop the intake
		hooks_motor.brake();
		floating_motor.brake();
		//raise the arm
	}else if(routine == POS_BLUE){
		//set the starting pose to the accurate point and heading
		chassis.setPose(52.8, -2.57, 17.336);
		//move to point 1 facing backwards
		chassis.moveToPoint(11.28, -43.8, 3000, {.forwards=false});
		chassis.waitUntilDone();
		//when there, toggle the mobile goal clamp
		Mogo::toggle();
		//score our preload onto the goal
		hooks_motor.move_velocity(200);
		pros::delay(100);

		//turn on the floating motor
		floating_motor.move_velocity(200);
		//move towards the indicated ring
		chassis.moveToPoint(24, -48, 500, {.forwards=true});
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
		chassis.moveToPose(24, -34, 0, 500, {.forwards=false});
		chassis.waitUntilDone();
		//turn on the clamp
		Mogo::toggle();
		pros::delay(200);
		//score the stored mobile goal
		hooks_motor.move_velocity(200);
		floating_motor.move_velocity(200);
		pros::delay(200);

		//drive to the ladder
		chassis.moveToPoint(13, -17.5, 500, {.forwards=true});
		chassis.waitUntilDone();
		//stop the intake
		hooks_motor.brake();
		floating_motor.brake();
		//raise the arm
	}
}