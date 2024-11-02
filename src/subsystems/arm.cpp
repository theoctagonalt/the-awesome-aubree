#include "main.h"
#include "globals.h"
#include "arm.h"

namespace Arm{
  int arm_state_values[] = {1, 2, 3}; //TODO: SET ROTATION SENSOR VALUES
  bool arm_pid_activated = false;
  ArmState target_arm_state;
  int target_arm_state_value = 0;

  int accumulated_error = 0; 
  int last_error = 0;
  int error_timeout = 0;

  void next_state(){
    set_state(ArmState(target_arm_state+1));
  }
  void last_state(){
    set_state(ArmState(target_arm_state-1));  
  }

  void set_state(ArmState state){
    arm_pid_activated = true;
    target_arm_state = state;
    target_arm_state_value = arm_state_values[state];
    accumulated_error = 0;
    last_error = 0;
  }

  ArmState get_state(){
    return target_arm_state; 
  }
  void reset_pid(){
    accumulated_error = 0;
    last_error = 0;
    error_timeout = 0;
    arm_pid_activated = false;
  }
  void arm_pid(){
    if(arm_pid_activated){
      int currentPos = arm_sensor.get_position();
      int error = currentPos - target_arm_state_value;

      if(error > arm_controller.largeError){
        error_timeout = 0;
        int p = error;
        int i = accumulated_error;
        int d = error - last_error;

        float vel = (arm_controller.kP*p) + (arm_controller.kI*i) + (arm_controller.kD*d);

        arm_motor.move_velocity(vel);

        accumulated_error+=error;
        last_error = error;
      }else{
        if(error_timeout >= arm_controller.largeErrorTimeout){
          reset_pid();
        }else{
          error_timeout++;
        }
      }
    }
  }
}