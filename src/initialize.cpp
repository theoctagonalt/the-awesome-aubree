#include "main.h"
#include "globals.h" 
#include "initialize.h"
#include "subsystems/intake.h"

int routine = NEG;
int colour = BLUE;

void initialize() {
	pros::lcd::initialize();
  chassis.calibrate(true);
	master.clear();
	intake_colour.set_led_pwm(50);
}

void disabled() {}

void competition_initialize() {
	while(true){
		pros::lcd::set_text(0, "Autonomous selector");
		if(intake_switch.get_new_press()){
			if(colour != 1) colour++;
			else {
				colour = 0;
				if(routine != 3) routine ++;
				else routine = -1;				
			}
		}
		std::string output = "";
		switch(routine){
			case NO_ROUTE:
				output = "No Route";
				break;
			case NEG:
				output = "Neg";
				break;
			case POS:
				output = "Pos";
				break;
			case SOLO:
				output = "Solo";
				break;
			case DRIVE_FORWARD:
				output = "Drive Forward";
				break;
		}
		switch(colour){
			case RED:
				output += " Red";
				break;
			case BLUE:
				output += " Blue";
				break;
		}
		Intake::set_colour(colour);
		pros::lcd::set_text(1, output);
		pros::delay(100);
	}
}

int get_routine(){
	return routine;
}
int get_colour(){
	return colour;
}