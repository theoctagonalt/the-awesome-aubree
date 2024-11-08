#include "main.h"
#include "globals.h" 
#include "initialize.h"

int routine = 0;

void initialize() {
	pros::lcd::initialize();
  chassis.calibrate(true);
	master.clear();
}

void disabled() {}

void competition_initialize() {
	while(true){
		pros::lcd::set_text(0, "Autonomous selector");
		if(auton_selector.get_new_press()){
			if(routine != 5) routine++;
			else routine = -1;
		}
		std::string output = "";
		switch(routine){
			case NO_ROUTE:
				output = "NO ROUTE";
				break;
			case SOLO_RED:
				output = "SOLO RED";
				break;
			case NEG_RED:
				output = "NEG RED";
				break;
			case POS_RED:
				output = "POS RED";
				break;
			case SOLO_BLUE:
				output = "SOLO BLUE";
				break;
			case NEG_BLUE:
				output = "NEG BLUE";
				break;
			case POS_BLUE:
				output = "POS BLUE";
				break;
		}
		pros::lcd::set_text(1, output);
		pros::delay(100);
	}
}

int get_routine(){
	return routine;
}