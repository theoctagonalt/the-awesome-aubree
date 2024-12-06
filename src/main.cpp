#include "main.h"
#include "globals.h"
#include "autonomous.h"
#include "./subsystems/intake.h"
#include "./subsystems/arm.h"
#include "./subsystems/mogo.h"
#include "./subsystems/doinker.h"
#include "initialize.h"

int gameTime = 0;
int r1_hold = 0;
void opcontrol(){
  Intake::set_colour(get_colour());
	while(true){
    double current_hue = intake_colour.get_hue();
    pros::lcd::print(1, "%f", intake_colour.get_hue());
    if(current_hue < RED_HUE_MAX && current_hue > RED_HUE_MIN){
      Intake::set_last_colour(RED);
    }else if(current_hue < BLUE_HUE_MAX && current_hue > BLUE_HUE_MIN){
      Intake::set_last_colour(BLUE);
    }
    pros::lcd::print(0, "%i", Intake::get_last_colour());

    //get the y and x values of the left and right joysticks respectively
    int throttle = master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
    int turn = master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);

    //create a lemlib curvature function to control the drivetrain
    // chassis.curvature(throttle, turn);

    //intake functions
    
    if(master.get_digital_new_press(pros::controller_digital_e_t::E_CONTROLLER_DIGITAL_R1)){
      Intake::toggle(1);
    }else if(master.get_digital_new_press(pros::controller_digital_e_t::E_CONTROLLER_DIGITAL_R2)){
      Intake::toggle(-1);
    }
    Intake::update_intake();

    if(master.get_digital_new_press(pros::controller_digital_e_t::E_CONTROLLER_DIGITAL_A)){
      Intake::set_colour(!Intake::get_colour());
      master.rumble("..");
    }

    //mogo functions
    if(master.get_digital_new_press(pros::controller_digital_e_t::E_CONTROLLER_DIGITAL_RIGHT)){
      Mogo::toggle();
    }

    //doinker
    if(master.get_digital_new_press(pros::controller_digital_e_t::E_CONTROLLER_DIGITAL_Y)){
      Doinker::toggle();
    }
    //arm
    if(master.get_digital_new_press(pros::controller_digital_e_t::E_CONTROLLER_DIGITAL_L1)){
      Arm::next_state();
      if(Arm::get_state() == SCORING){
        hooks_motor.move_relative(-50, 50);
      }
    }else if(master.get_digital_new_press(pros::controller_digital_e_t::E_CONTROLLER_DIGITAL_L2)){
      Arm::last_state();
    }
    
    Arm::arm_pid();
    //game
    if(pros::competition::is_connected() && !pros::competition::is_autonomous()){
			gameTime++;
		} 
    if(gameTime == 4500){
      master.rumble("--");
    }
    pros::delay(20);
  }
}