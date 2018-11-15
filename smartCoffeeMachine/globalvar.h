#ifndef __GLOBAL_VAR__
#define __GLOBAL_VAR__

#include "WString.h"
#include "LinkedList.h"

#define BAUD_RATE 2000000 // se non invia i dati velocemente entra in sleep prima di aver finito

#define PIR_PIN 2
#define SP_TRIG_PIN 11
#define SP_ECHO_PIN 12
#define BUTTON_PIN 3
#define LED1_PIN 8
#define LED2_PIN 9
#define LED3_PIN 10
#define POT_PIN A5


#define NMAX_CAFFEE 10  // Max num of caffee
#define DIST1 0.3       // Engagement distance
#define DIST2 0.1       // Take coffee
#define DT1 1           // Min engagement time
#define DT2a 5          // Max time with no engagement
#define DT2b 5          // Max time with no presence
#define DT3 3           // Coffee making process duration
#define DT4 5           // Max time to remove coffee

typedef enum STATE {
  STAND_BY,
  ON,
  READY,
  MAKING_COFFEE,
  TAKING_COFFEE,
  MAINTENANCE
} State_t;

typedef struct GV {
  State_t state;
  bool pir_present;
  bool hc_in_range;
  bool time_elapsed;
  bool time_acquired;
  bool make_coffee;
  bool coffee_ready;
  int coffee_pods;
  LinkedList< String >msgs;
} GlobalVar_t;

#endif
