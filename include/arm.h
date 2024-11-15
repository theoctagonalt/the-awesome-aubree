#ifndef SUBSYSTEMS_H_
#define SUBSYSTEMS_H_

#define REST 0
#define READY 1
#define SCORING 3

//TODO: SET ROTATION SENSOR VALUES
#define REST_DEG 360
#define READY_DEG 326
#define SCORING_DEG 220

namespace Arm{
  void next_state();
  void last_state();

  int get_state();
  void set_state(int state);
  void arm_pid();
}
#endif