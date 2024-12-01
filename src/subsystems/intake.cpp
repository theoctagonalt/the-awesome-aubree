#include "./subsystems/intake.h"
#include "main.h"
#include "globals.h"
#include "./subsystems/arm.h"

namespace Intake{
  int hooks = 0;
  int floating = 0;
  int timeout = 0;
  bool arm_ready = false;



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

  void update_intake(){
    if(Arm::get_state() == READY){
      if(intake_switch.get_value()){
        if(timeout == 25){
          toggle_hooks(1);
          arm_ready = true;
        }else{
          timeout++;
        }
      }else{
        timeout = 0;
        arm_ready = false;
      }
    }else{
      arm_ready = false;
      if(intake_switch.get_value() && hooks == 1){
        toggle_hooks(-1);
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
