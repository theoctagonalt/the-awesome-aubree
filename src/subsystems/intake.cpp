#include "intake.h"
#include "main.h"
#include "globals.h"
#include "arm.h"

namespace Intake{
  bool hooks = false;
  bool floating = false;

  //this method overrides all other ones
  void toggle(int state){
    if(state == 0){
      toggle_hooks(0);
      toggle_floating(0);
    }else if(state == 1){
      toggle_hooks(1);
      toggle_floating(1);
    }else{
      toggle_floating();
      toggle_hooks();
    }
  }
  
  void toggle_hooks(int state){
    if(state == 0){
      hooks_motor.brake();
      hooks = false;
    }else if(state == 1){
      hooks_motor.move_velocity(200);
      hooks = true;
    }else{
      toggle_hooks(!hooks);
    }
  }
  void toggle_floating(int state){
    if(state == 0){
      floating_motor.brake();
      floating = false;
    }else if(state == 1){
      floating_motor.move_velocity(200);
      floating = true;
    }else{
      toggle_floating(!floating);
    }
  }

  void reverse(){
    floating_motor.move_velocity(-200);
    hooks_motor.move_velocity(-200);
  }

  void update_intake(){
    if(Arm::get_state() == READY){
      //TODO: ADD LOGIC FOR DISTANCE SENSOR DETECTING AND AUTOMATIC TURNOFF
    }
  }

  int hooks_state(){
    return hooks;
  }
  int floating_state(){
    return floating;
  }
}
