#include "main.h"
#include "lemlib/api.hpp"

//TODO: ADD PORT NUMBERS

#define LEFT_FRONT_MOTOR 1
#define LEFT_BACK_MOTOR 2
#define LEFT_BACK_MOTOR_TOP 3

#define RIGHT_FRONT_MOTOR 4
#define RIGHT_BACK_MOTOR 5
#define RIGHT_BACK_MOTOR_TOP 6

#define HOOKS -99
#define FLOATING -99 
#define ARM -99

#define MOGO -99

#define ARM_SENSOR -99  
#define INERTIAL_SENSOR -99
#define AUTON_SELECTOR -99


pros::Controller master (pros::E_CONTROLLER_MASTER);

//motors
pros::MotorGroup left_motors ({LEFT_FRONT_MOTOR, LEFT_BACK_MOTOR, LEFT_BACK_MOTOR_TOP}, pros::MotorGear::blue);
pros::MotorGroup right_motors ({RIGHT_FRONT_MOTOR, RIGHT_BACK_MOTOR, RIGHT_BACK_MOTOR_TOP}, pros::MotorGear::blue);

pros::Motor arm_motor (ARM, pros::MotorGear::green);
pros::Motor hooks_motor(HOOKS, pros::MotorGear::green);
pros::Motor floating_motor(FLOATING, pros::MotorGear::green);

//pistons
pros::adi::DigitalOut mogo (MOGO);

//sensors
pros::Rotation arm_sensor (ARM_SENSOR);
pros::adi::DigitalIn auton_selector (AUTON_SELECTOR);
pros::IMU inertial (INERTIAL_SENSOR);

//lemlib objects

lemlib::Drivetrain drivetrain (&left_motors, &right_motors, 11.705, lemlib::Omniwheel::NEW_275, 400, 2);

//================================================================= TODO
lemlib::ControllerSettings angular_controller(-99, -99, -99, -99, -99, -99, -99, -99, -99); 
lemlib::ControllerSettings lateral_controller(-99, -99, -99, -99, -99, -99, -99, -99, -99);
lemlib::ControllerSettings arm_controller(-99, -99, -99, -99, -99, -99, -99, -99, -99);

lemlib::TrackingWheel left_side_imes (&left_motors, lemlib::Omniwheel::NEW_325, -5.8525, 400);
lemlib::TrackingWheel right_side_imes (&right_motors, lemlib::Omniwheel::NEW_325, 5.8525, 400);

lemlib::OdomSensors sensors (&left_side_imes, &right_side_imes, nullptr, nullptr, &inertial);

lemlib::Chassis chassis (drivetrain, lateral_controller, angular_controller, sensors);