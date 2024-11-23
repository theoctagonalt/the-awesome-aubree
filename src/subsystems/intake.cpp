#include "./subsystems/intake.h"
#include "main.h"
#include "globals.h"
#include "./subsystems/arm.h"

namespace Intake{
  int hooks = 0;
  int floating = 0;
  int intake_timeout = 0;
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
      if(arm_distance_sensor.get_distance() < 50){
        pros::lcd::print(0, "hiahsdij");
        if(intake_timeout == 25){
          toggle_hooks(1);
          arm_ready = true;
        }else{
          intake_timeout++;
        }
      }else{
        intake_timeout = 0;
        arm_ready = false;
      }
    }else{
      arm_ready = false;
    }
  }

  int hooks_state(){
    return hooks;
  }
  int floating_state(){
    return floating;
  }
}
