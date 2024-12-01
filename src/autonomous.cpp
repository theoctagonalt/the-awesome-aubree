#include "main.h"
#include "globals.h"
#include "initialize.h"
#include "./subsystems/intake.h"
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
			pros::delay(50);
	}
}


void autonomous() {
  int routine = get_routine();
	pros::Task screenTask(screen);
	pros::Task intakeTask(Intake::update_intake);
	if(routine == POS){
		pos_routine();
	}else if(routine == NEG){
		neg_routine();
	}else if(routine == SOLO){
		solo_routine();
	}else if(routine == DRIVE_FORWARD){
		chassis.setPose(0, 0, 90);
		chassis.moveToPoint(24, 0, 3000);
	}
}