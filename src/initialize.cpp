#include "main.h"
#include "globals.h" 

int routine = 0;

void initialize() {
	pros::lcd::initialize();
  // chassis.calibrate(true);
	// master.clear();
}

void disabled() {}

void competition_initialize() {
	while(true){
		pros::lcd::set_text(0, "Autonomous selector");
		if(auton_selector.get_new_press()){
			if(routine != 3) routine++;
			else routine = 0;
		}
		pros::lcd::set_text(1, routine == 0 ? "no auto" : (routine == 1 ? "right side" : routine == 2 ? "left side" : "skills"));
		pros::delay(100);
	}
}

int get_routine(){
	return routine;
}