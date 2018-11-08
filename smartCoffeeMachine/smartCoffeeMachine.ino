#include "definition.h"     // enum, struct, ...
#include "state_task.h"
#include "presence_task.h"
#include "distance_task.h"
#include "timer_task.h"
#include "comunication_task.h"

typedef enum STATE {
  STAND_BY,
  ON,
  READY,
  MAINTENANCE,
  MAKING_COFFEE
} State_t * variables;

struct VARIABLES {
  State_t state;
  bool pir_present;
  bool hc_in_range;
  unsigned long time_elapsed;
  int coffee_pods;
}

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}
