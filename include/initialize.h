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
#define SOLO 3


int get_routine();
int get_colour();
void initialize();
void competition_initialize();

#endif