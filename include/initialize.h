#ifndef INITIALIZE_H_
#define INITIALIZE_H_

#define RED 0
#define BLUE 1

#define RED_HUE_MIN 0
#define RED_HUE_MAX 30
#define BLUE_HUE_MIN 150
#define BLUE_HUE_MAX 230

#define NO_ROUTE -1
#define DRIVE_FORWARD 0
#define NEG 1
#define POS 2
#define SKILLS 3

#define QUALS 0
#define ELIMS 1


int get_routine();
int get_colour();
int get_match();
void initialize();
void competition_initialize();

#endif