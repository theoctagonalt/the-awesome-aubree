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
  if(routine == -1){
    pros::delay(9999);
  }else if(routine == 0){
    
  }
}