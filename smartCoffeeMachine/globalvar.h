#ifndef __GLOBAL_VAR__
#define __GLOBAL_VAR__

#define PIR_PIN 2

#define NMAX_CAFFEE 10  // Max num of caffee
#define DIST1 0.3       // Engagement distance
#define DIST2 0.1       // Take coffee
#define DT1 1           // Min engagement time
#define DT2a 5          // Max time with no engagement
#define DT2b 5          // Max time with no presence
#define DT3 3           // Coffee making process duration
#define DT4 5           // Max time to remove coffee

enum STATE {
  STAND_BY,
  ON,
  READY,
  MAKING_COFFEE,
  MAINTENANCE
};

typedef struct GV {
  enum STATE state;
  bool pir_present;
  bool hc_in_range;
  bool time_elapsed; // flag?
  bool make_coffee;
  bool coffee_ready;
  int coffee_pods;
} GlobalVar_t;

#endif
