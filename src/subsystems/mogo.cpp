#include "globals.h"
#include "main.h"
#include "mogo.h"

namespace Mogo{
  int value = 0;
  void toggle(int state = -1){
    if(state == -1){
      toggle(!value);
      return;
    }
    mogo.set_value(state);
    value = state;
  }
}