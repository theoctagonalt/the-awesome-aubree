#include "./subsystems/intake.h"
#include "main.h"
#include "globals.h"
#include "./subsystems/arm.h"
#include "initialize.h"

namespace Intake{
  int hooks = 0;
  int floating = 0;
  int timeout = 0;
  int colour;
  int last_colour = -1;
  // bool arm_ready = false;


  //this method overrides all other ones
  void toggle(int state){
    if(hooks != floating){
      toggle_hooks(state);  
    }else{
      toggle_hooks(state);
      toggle_floating(state);
    }
  }
  
  void toggle_hooks(int state){ //1 = forward, -1 = reverse
    if(hooks == state){
      hooks_motor.brake();
      hooks = 0;
    }else{
      hooks_motor.move_velocity(state * 200);
      hooks = state;
    }
  }
  void toggle_floating(int state){
    if(floating == state){
      floating_motor.brake();
      floating = 0;
    }else{
      floating_motor.move_velocity(state * 200);
      floating = state;
    }
  }

  void reverse(){
    floating_motor.move_velocity(-200);
    hooks_motor.move_velocity(-200);
  }

  void set_colour(int new_colour){
    colour = new_colour;
  }

  void update_intake(){
    if(Arm::get_state() == READY){
      if(intake_switch.get_value()){
        if(timeout == 25){
          toggle_hooks(1);
        }else{
          timeout++;
        }
      }else{
        timeout = 0;
      }
    }else{
      if(intake_switch.get_value()){
        pros::lcd::print(3, "toggle");
        if(timeout == 0 && hooks == 1){
          if(last_colour != colour && last_colour != -1){
            Intake::toggle_hooks(-1);
            timeout++;
          }
        }
      }
      if(timeout > 0){
        if(timeout == 25 && hooks == -1){
          Intake::toggle_hooks(1);
          timeout=0;
        }else{
          timeout++;
        }
      }
    }
  }
  void set_last_colour(int new_colour){
    last_colour = new_colour;
  }
  int hooks_state(){
    return hooks;
  }
  int floating_state(){
    return floating;
  }
}
