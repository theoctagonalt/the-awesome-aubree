#include "main.h"
#include "globals.h"
#include "initialize.h"

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
	chassis.moveToPoint(10, 0, 5000);
	while(chassis.isInMotion()){
		pros::lcd::print(0, "X: %f", chassis.getPose().x); // x
		pros::lcd::print(1, "Y: %f", chassis.getPose().y); // y
		pros::lcd::print(2, "Theta: %f", chassis.getPose().theta); // heading
		float error = 78 - chassis.getPose().x;
		fprintf(output_file, "%fin %fms \n", error, time);
		time+=40;
		pros::delay(250);
	}
	chassis.waitUntilDone();
	fclose(output_file);
}