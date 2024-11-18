#include "doinker.h"
#include "globals.h"
#include "main.h"

namespace Doinker{
  int value = 0;
  void toggle(int state){
    if(state == -1){
      toggle(!value);
      return;
    }
    doinker.set_value(state);
    value = state;
  }
}