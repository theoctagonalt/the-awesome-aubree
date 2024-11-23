#include "main.h"
#include "globals.h"
#include "initialize.h"
#include "./routines/pos.h"
#include "./routines/neg.h"
#include "./routines/solo.h"

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
	if(routine == POS_RED || routine == POS_BLUE){
		pos_routine(routine == POS_BLUE);
	}else if(routine == NEG_RED || routine == NEG_BLUE){
		neg_routine(routine == NEG_BLUE);
	}else if(routine == SOLO_RED || routine == SOLO_BLUE){
		solo_routine(routine == SOLO_BLUE);
	}
}