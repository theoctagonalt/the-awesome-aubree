#include "globals.h"
#include "main.h"
#include "mogo.h"

namespace Mogo{
  int value = 0;
  void toggle(int state = -1){
    if(state == -1){
      toggle(!value);
      toggle(!value);
      return;
    }
    mogo_1.set_value(state);
    mogo_2.set_value(state);
    value = state;
  }
}