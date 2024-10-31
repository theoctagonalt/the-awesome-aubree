#include "main.h"
#include "globals.h"
#include "subsystems.h"

void opcontrol(){
	while(true){
    Arm::arm_pid();
    //get the y and x values of the left and right joysticks respectively
    int throttle = master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
    int turn = master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);

    //create a lemlib curvature function to control the drivetrain
    chassis.curvature(throttle, turn);
    

    pros::delay(20);
  }
}