#include "main.h"
#include "lemlib/api.hpp"

//TODO: ADD PORT NUMBERS

#define LEFT_FRONT_MOTOR -8
#define LEFT_BACK_MOTOR -9
#define LEFT_BACK_MOTOR_TOP 10

#define RIGHT_FRONT_MOTOR 17
#define RIGHT_BACK_MOTOR 16
#define RIGHT_BACK_MOTOR_TOP -15

#define HOOKS 12
#define FLOATING 13 
#define ARM 19

#define MOGO 8  
#define DOINKER 7

#define ARM_SENSOR 20  
#define INTAKE_COLOUR 18
#define INERTIAL_SENSOR 11
#define INTAKE_SWITCH 6


pros::Controller master (pros::E_CONTROLLER_MASTER);

//motors
pros::MotorGroup left_motors ({LEFT_FRONT_MOTOR, LEFT_BACK_MOTOR, LEFT_BACK_MOTOR_TOP}, pros::MotorGear::blue);
pros::MotorGroup right_motors ({RIGHT_FRONT_MOTOR, RIGHT_BACK_MOTOR, RIGHT_BACK_MOTOR_TOP}, pros::MotorGear::blue);

pros::Motor arm_motor (ARM, pros::MotorGear::green);
pros::Motor hooks_motor(HOOKS, pros::MotorGear::green);
pros::Motor floating_motor(FLOATING, pros::MotorGear::green);

//pistons
pros::adi::DigitalOut mogo (MOGO);
pros::adi::DigitalOut doinker (DOINKER);

//sensors
pros::Rotation arm_sensor (ARM_SENSOR);
pros::Optical intake_colour (INTAKE_COLOUR);
pros::adi::DigitalIn intake_switch (INTAKE_SWITCH);
pros::IMU inertial (INERTIAL_SENSOR);

//lemlib objects

lemlib::Drivetrain drivetrain (&left_motors, &right_motors, 11.705, lemlib::Omniwheel::NEW_275, 400, 2);

//================================================================= TODO
lemlib::ControllerSettings angular_controller(1.6, //kP
                                              0.01, //kI
                                              0, //kD
                                              7.5, //anti-windup
                                              1, //small error range (in)
                                              1000, //small error timeout (ms)
                                              0, //large error range (in)
                                              500, //large error timeout(ms)
                                              0  //maximum accel
                                              ); 

lemlib::ControllerSettings lateral_controller(3.5,
                                             0.1, 
                                             0.1, 
                                             5, 
                                             1, 
                                             100, 
                                             0, 
                                             500, 
                                             0 //TODO: TUNE SLEW
                                             );

lemlib::ControllerSettings arm_controller(0.03,
                                          0, 
                                          0.00001, 
                                          0, 
                                          0, 
                                          0, 
                                          50, 
                                          0, 
                                          30
                                          );

lemlib::TrackingWheel left_side_imes (&left_motors, lemlib::Omniwheel::NEW_325, -5.8525, 400);
lemlib::TrackingWheel right_side_imes (&right_motors, lemlib::Omniwheel::NEW_325, 5.8525, 400);

lemlib::OdomSensors sensors (&left_side_imes, &right_side_imes, nullptr, nullptr, &inertial);

lemlib::Chassis chassis (drivetrain, lateral_controller, angular_controller, sensors);