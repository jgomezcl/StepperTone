
/*
  StepperTone library
  The steppers must be driven using a driver with STEP and DIRECTION pins, such as the DRV8225 or the A4988
  Implemented using micros() and millis() and tested on Arduino UNO
  Updated: Jan 2021 by Joan Gómez
*/

#ifndef stepperTone_h
#define stepperTone_h

#include "Arduino.h"

#define NOTE_SILENCE 0.75    //the ratio between note duration and total time (ie. 0.8 is 80% note and 20% silence)

#define DIR_CLOCKW 0          //to set the turn direction (default clockwise)
#define DIR_CNTCLOCKW 1

class StepperTone
{
  public:
    StepperTone(int dirPin, int stepPin, int enablePin);
    void setTone(int pitch, int duration);    //sets the tone in hertz and the duration in ms
    void setDirection(int dir);       //sets direction clockwise or counterclockwise
    void setActive(boolean active);   //enables/disables the stepper
    void play();        //the tone routine
    boolean isPlaying();  //true if the stepper is still playing a tone

  private:
    int _dirPin, _stepPin, _enablePin, _pitchT, _duration;
    boolean _isPlaying, _soundOn;
    unsigned long _toneStart, _freqCounter;
};

#endif
