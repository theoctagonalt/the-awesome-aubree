#ifndef SUBSYSTEMS_H_
#define SUBSYSTEMS_H_

namespace Arm{
  enum ArmState{ //todo: set the values for enum to the rotation values
    REST = 0,
    READY,
    SCORING
  };

  void next_state();
  void last_state();

  ArmState get_state();
  void set_state(ArmState state);
  void arm_pid();
}
#endif