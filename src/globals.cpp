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
#define ARM

#define MOGO_MECH_1
#define MOGO_MECH_2

#define TRACKING_WHEEL
#define INERTIAL_SENSOR

pros::Controller master (pros::E_CONTROLLER_MASTER);

//drivetrain motors
pros::MotorGroup left_motors ({LEFT_FRONT_MOTOR, LEFT_BACK_MOTOR, LEFT_BACK_MOTOR_TOP}, pros::MotorGear::blue);
pros::MotorGroup right_motors ({RIGHT_FRONT_MOTOR, RIGHT_BACK_MOTOR, RIGHT_BACK_MOTOR_TOP}, pros::MotorGear::blue);

//lemlib objects

lemlib::Drivetrain drivetrain (&left_motors, &right_motors, 11.705, lemlib::Omniwheel::NEW_275, 400, 2);

lemlib::ControllerSettings angular_controller;
lemlib::ControllerSettings lateral_controller;

lemlib::OdomSensors sensors;

lemlib::Chassis chassis (drivetrain, lateral_controller, angular_controller, sensors);
