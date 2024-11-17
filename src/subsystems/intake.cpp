#include "intake.h"
#include "main.h"
#include "globals.h"
#include "arm.h"

namespace Intake{
  int hooks = 0;
  int floating = 0;

  //this method overrides all other ones
  void toggle(int state){
    toggle_hooks(state);
    toggle_floating(state);
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
