#include "main.h"
#include "lemlib/api.hpp"

//TODO: ADD PORT NUMBERS

#define LEFT_FRONT_MOTOR 1
#define LEFT_BACK_MOTOR 2
#define LEFT_BACK_MOTOR_TOP 3

#define RIGHT_FRONT_MOTOR 4
#define RIGHT_BACK_MOTOR 5
#define RIGHT_BACK_MOTOR_TOP 6

#define HOOKS 
#define INTAKE 
#define ARM 3 //FIX LATER

#define MOGO_MECH_1
#define MOGO_MECH_2

#define ARM_SENSOR 2 //FIX LATER 
#define INERTIAL_SENSOR


pros::Controller master (pros::E_CONTROLLER_MASTER);

//drivetrain motors
pros::MotorGroup left_motors ({LEFT_FRONT_MOTOR, LEFT_BACK_MOTOR, LEFT_BACK_MOTOR_TOP}, pros::MotorGear::blue);
pros::MotorGroup right_motors ({RIGHT_FRONT_MOTOR, RIGHT_BACK_MOTOR, RIGHT_BACK_MOTOR_TOP}, pros::MotorGear::blue);

pros::Motor arm_motor (ARM, pros::MotorGear::green);
pros::Rotation arm_sensor (ARM_SENSOR);

//lemlib objects

lemlib::Drivetrain drivetrain (&left_motors, &right_motors, 11.705, lemlib::Omniwheel::NEW_275, 400, 2);

//================================================================= TODO
lemlib::ControllerSettings angular_controller; 
lemlib::ControllerSettings lateral_controller;
lemlib::ControllerSettings arm_controller;

lemlib::OdomSensors sensors;

lemlib::Chassis chassis (drivetrain, lateral_controller, angular_controller, sensors);

//subsystem functions

enum ArmState { //TODO: SET THE ENUM VALUES TO ROTATION SENSOR VALUES
  REST,
  READY,
  SCORING
};

void arm_to_state(ArmState state){
  arm_pid_activated = true;
  target_arm_state = state;
  accumulated_error = 0;
  last_error = 0;
}

bool arm_pid_activated = false;
ArmState target_arm_state;

int accumulated_error = 0; 
int last_error = 0;
int error_timeout = 0;

void arm_pid(ArmState state){
  while(true){
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
    pros::delay(1);
  } 
}
