#include "main.h"
#include "globals.h"
#include "initialize.h"
#include "autonomous.h"
#include "./subsystems/arm.h"
#include "./subsystems/intake.h"
#include "./routines/pos.h"
#include "./routines/neg.h"
#include "./routines/skills.h"

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
void update_subsystems(){
	while(pros::competition::is_autonomous()){
		double current_hue = intake_colour.get_hue();
    if(current_hue < RED_HUE_MAX && current_hue > RED_HUE_MIN){
      Intake::set_last_colour(RED);
    }else if(current_hue < BLUE_HUE_MAX && current_hue > BLUE_HUE_MIN){
      Intake::set_last_colour(BLUE);
    }
		Intake::update_intake();
		Arm::arm_pid();
		pros::delay(20);
	}
}

void autonomous() {
  int routine = get_routine();
	pros::Task screenTask(screen);
	pros::Task subsystemTask(update_subsystems);
	if(routine == POS){
		pos_routine();
	}else if(routine == NEG){
		neg_routine();
	}else if(routine == SKILLS){
		skills();
	}else if(routine == DRIVE_FORWARD){
		chassis.setPose(0, 0, 90);
		chassis.moveToPoint(24, 0, 3000);
	}
}