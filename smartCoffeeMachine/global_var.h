#ifndef __GLOBAL_VAR__
#define __GLOBAL_VAR__

#define PIR_PIN 2

#define DIST1 0.3   // Engagement distance
#define DIST2 0.1   // Take coffee
#define DT1 1       // Min engagement time
#define DT2a 5      // Max time with no engagement
#define DT2b 5      // Max time with no presence
#define DT3 3       // Coffee making process duration
#define DT4 5       // Max time to remove coffee

extern enum STATE {
  STAND_BY,
  ON,
  READY,
  MAKING_COFFEE,
  MAINTENANCE
} state;
extern bool pir_present;
extern bool hc_in_range;
extern bool time_elapsed; // flag?
extern bool make_coffee;
extern bool coffee_ready;
extern int coffee_pods;

#endif
