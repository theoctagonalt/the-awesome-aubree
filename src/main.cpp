#include "main.h"
#include "globals.h"
#include "intake.h"
#include "arm.h"
#include "mogo.h"

int gameTime = 0;
void opcontrol(){
	while(true){
    //get the y and x values of the left and right joysticks respectively
    int throttle = master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
    int turn = master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);

    //create a lemlib curvature function to control the drivetrain
    chassis.curvature(throttle, turn);

    //intake functions
    
    int r1_hold = 0;
    int hooks_prev_state = 0;
    int floating_prev_state = 0;
    if(master.get_digital_new_press(pros::controller_digital_e_t::E_CONTROLLER_DIGITAL_R1)){
      Intake::toggle();
    }else if(master.get_digital(pros::controller_digital_e_t::E_CONTROLLER_DIGITAL_R1)){
      r1_hold++;
      if(r1_hold == 20){
        hooks_prev_state = Intake::hooks_state();
        floating_prev_state = Intake::floating_state();
        Intake::reverse();
      }
    }else if(r1_hold > 20){
      r1_hold = 0;
      Intake::toggle_hooks(hooks_prev_state);
      Intake::toggle_floating(floating_prev_state);
    }

    //mogo functions
    if(master.get_digital_new_press(pros::controller_digital_e_t::E_CONTROLLER_DIGITAL_X)){ //TODO:CHANGE BUTTONS
      Mogo::toggle();
    }

    //arm
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