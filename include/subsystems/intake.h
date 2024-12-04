#ifndef INTAKE_H_
#define INTAKE_H_

namespace Intake{

  void toggle(int state = 0);
  void toggle_hooks(int state);
  void toggle_floating(int state);
  void reverse();
  void set_colour(int new_colour);

  void set_last_colour(int new_colour);
  int hooks_state();
  int floating_state();
  void update_intake();
}
#endif