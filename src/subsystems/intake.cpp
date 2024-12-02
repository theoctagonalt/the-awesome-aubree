#include "./subsystems/intake.h"
#include "main.h"
#include "globals.h"
#include "./subsystems/arm.h"
#include "initialize.h"

namespace Intake{
  int hooks = 0;
  int floating = 0;
  int timeout = 0;
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

  void update_intake(int colour){
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
      double current_hue = intake_colour.get_hue();
      int current_colour = -1;
      if(intake_switch.get_value()){
        if(timeout == 0 && hooks == 1){
          if(current_hue < RED_HUE_MAX && current_hue > RED_HUE_MIN){
            current_colour = RED;
          }else if(current_hue < BLUE_HUE_MAX && current_hue > BLUE_HUE_MIN){
            current_colour = BLUE;
          }
          if(current_colour != colour){
            Intake::toggle_hooks(-1);
          }
        }else if(timeout > 0){
          if(timeout == 38){
            Intake::toggle_hooks(1);
          }else{
            timeout++;
          }
        }
        //TODO
      }
    }
  }

  int hooks_state(){
    return hooks;
  }
  int floating_state(){
    return floating;
  }
}
