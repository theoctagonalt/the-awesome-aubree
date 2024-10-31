#include "main.h"
#include "lemlib/api.hpp"

#ifndef GLOBALS_H_
#define GLOBALS_H_

extern pros::Controller master;

extern pros::Motor arm_motor;
extern pros::Motor hooks_motor;
extern pros::Motor floating_motor;

extern pros::adi::DigitalOut mogo_1;
extern pros::adi::DigitalOut mogo_2;

extern pros::adi::DigitalIn auton_selector;
extern pros::Rotation arm_sensor;

extern lemlib::ControllerSettings arm_controller;
extern lemlib::Chassis chassis;

#endif