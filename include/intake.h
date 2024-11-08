#ifndef INTAKE_H_
#define INTAKE_H_

namespace Intake{

  void toggle(int state = -1);
  void toggle_hooks(int state = -1);
  void toggle_floating(int state = -1);
  void reverse();

  int hooks_state();
  int floating_state();
}
#endif