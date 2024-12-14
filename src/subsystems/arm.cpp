#include "main.h"
#include "globals.h"
#include "./subsystems/arm.h"

namespace Arm{
  double arm_state_values[] = {REST_DEG, READY_DEG, SCORING_DEG, MOGO_SCORING_DEG};
  bool arm_pid_activated = false;
  int target_arm_state = REST;
  int target_arm_state_value = 0;

  int accumulated_error = 0; 
  int last_error = 0;
  int error_timeout = 0;

  void next_state(){
    if(target_arm_state != SCORING) {
      set_state(target_arm_state+1);

    }
    else set_state(REST);
  }
  void last_state(){
    if(target_arm_state != REST) set_state(target_arm_state-1);  
  }

  void set_state(int state){
    arm_pid_activated = true;
    target_arm_state = state;
    target_arm_state_value = arm_state_values[state];
    accumulated_error = 0;
    last_error = 0;
  }

  int get_state(){
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
      int currentPos = arm_sensor.get_angle();
      int error = currentPos - target_arm_state_value;

      pros::lcd::print(1, "current pos: %i, error: %i", currentPos, error);

      if(std::abs(error) > arm_controller.largeError){
        error_timeout = 0;
        int p = error;
        int i = accumulated_error;
        int d = error - last_error;

        float vel = (arm_controller.kP*p) + (arm_controller.kI*i) + (arm_controller.kD*d);

        if(target_arm_state == SCORING && std::abs(vel) > 50){
          vel == (vel < 0 ? -1 : 1) * 50;
        }

        arm_motor.move_velocity(vel);

        accumulated_error+=error;
        last_error = error;
      }else{
        if(error_timeout >= arm_controller.largeErrorTimeout){
          if(target_arm_state != REST){
            arm_motor.set_brake_mode(pros::motor_brake_mode_e::E_MOTOR_BRAKE_HOLD);
          }else{
            arm_motor.set_brake_mode(pros::motor_brake_mode_e::E_MOTOR_BRAKE_COAST);
          }
          arm_motor.brake();
          reset_pid();
        }else{
          error_timeout++;
        }
      }
    }
  }
}