#include "main.h"
#include "globals.h"

void opcontrol(){
	while(true){
    //get the y and x values of the left and right joysticks respectively
    int throttle = master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
    int turn = master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);

    //create a lemlib curvature function to control the drivetrain
    chassis.curvature(throttle, turn);
  }
}