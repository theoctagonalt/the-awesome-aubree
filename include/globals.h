#include "main.h"
#include "lemlib/api.hpp"

#ifndef GLOBALS_H_
#define GLOBALS_H_

extern pros::Controller master;

extern pros::MotorGroup left_motors;
extern pros::MotorGroup right_motors;

extern pros::Motor arm_motor;
extern pros::Motor hooks_motor;
extern pros::Motor floating_motor;

extern pros::adi::DigitalOut mogo;
extern pros::adi::DigitalOut doinker;

extern pros::adi::DigitalIn intake_switch;
extern pros::Rotation arm_sensor;
extern pros::Distance arm_distance_sensor;

extern lemlib::ControllerSettings arm_controller;
extern lemlib::ControllerSettings angular_controller;
extern lemlib::Chassis chassis;



#endif