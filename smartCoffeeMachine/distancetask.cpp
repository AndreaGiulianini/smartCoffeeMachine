#include "distancetask.h"
#include "Arduino.h"

DistanceTask::DistanceTask( GlobalVar_t* gv ) {
  this->gv = gv;
}

void DistanceTask::Exec() {
  gv->hc_in_range = ( ( gv->state == ON || gv->state == READY )
                      && ( GetDistance() <= DIST1 ) )
                    || ( gv->state == TAKING_COFFEE && GetDistance() <= DIST2 );
}

float DistanceTask::GetDistance() {
  // Clears the trigPin
  digitalWrite( SP_TRIG_PIN, LOW );
  delayMicroseconds( 2 );
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite( SP_TRIG_PIN, HIGH );
  delayMicroseconds( 10 );
  digitalWrite( SP_TRIG_PIN, LOW );
  // Reads the echoPin, returns the sound wave travel time in microseconds
  int duration = pulseIn( SP_ECHO_PIN, HIGH );
  // Calculating the distance
  float distance = duration * 0.034 / 2;
  return distance / 100;
}
