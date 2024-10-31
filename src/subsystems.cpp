#include "main.h"
#include "globals.h"
#include "subsystems.h"

namespace Arm{
  bool arm_pid_activated = false;
  ArmState target_arm_state;

  int accumulated_error = 0; 
  int last_error = 0;
  int error_timeout = 0;


  void set_state(ArmState state){
    arm_pid_activated = true;
    target_arm_state = state;
    accumulated_error = 0;
    last_error = 0;
  }

  ArmState get_state(){
    return target_arm_state; 
  }
  void arm_pid(ArmState state){
    if(arm_pid_activated){
      int currentPos = arm_sensor.get_position();
      int error = currentPos - state;

      if(error > arm_controller.largeError){
        error_timeout = 0;
        int p = error;
        int i = accumulated_error;
        int d = error - last_error;

        float vel = (arm_controller.kP*p) + (arm_controller.kI*i) + (arm_controller.kD*d);

        arm_motor.move_velocity(vel);

        accumulated_error+=error;
      }else{
        if(error_timeout >= arm_controller.largeErrorTimeout){
          accumulated_error = 0;
          last_error = 0;
          error_timeout = 0;
          arm_pid_activated = false;
        }else{
          error_timeout++;
        }
      }
    }
  }
}

namespace Intake{
  bool hooks = false;
  bool floating = false;

  //state -1 = switch to opposite
  //state 0 = turn off
  //state 1 = turn on
  void toggle(int state = -1){
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
  void toggle_hooks(int state = -1){
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
  void toggle_floating(int state = -1){
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
}