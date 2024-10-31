#include "main.h"
#include "globals.h"
#include "arm.h"

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