#include "./subsystems/mogo.h"
#include "globals.h"
#include "main.h"

namespace Mogo{
  int value = 0;
  void toggle(int state){
    if(state == -1){
      toggle(!value);
      return;
    }
    mogo.set_value(state);
    value = state;
  }
}