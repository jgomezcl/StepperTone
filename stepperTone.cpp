
#include "Arduino.h"
#include "stepperTone.h"
#include "pitches.h"

StepperTone::StepperTone(int dirPin, int stepPin, int enablePin)
{
  _dirPin = dirPin;
  _stepPin = stepPin;
  _enablePin = enablePin;
  _isPlaying = false;

  pinMode(_dirPin, OUTPUT);
  pinMode(_stepPin, OUTPUT);
  pinMode(_enablePin, OUTPUT);

  digitalWrite(_dirPin, LOW);
  digitalWrite(_enablePin, LOW);
}

void StepperTone::setTone(int pitch, int duration)
{
  digitalWrite(_enablePin, HIGH);
  _duration = duration;
  if (pitch == SILENCE)
  {
    _soundOn = false;
  }
  else
  {
    _pitchT = 1000000 / pitch; //conversion from freq to period in us
    _soundOn = true;
  }
  _isPlaying = true;
  _toneStart = millis();
  _freqCounter = micros();
}

void StepperTone::play()
{
  if (_isPlaying)
  {
    if (micros() - _freqCounter >= _pitchT && _soundOn)
    {
      _freqCounter = micros();
      digitalWrite(_stepPin, !digitalRead(_stepPin));
    }

    if (millis() - _toneStart <  _duration * NOTE_SILENCE) {

    }
    else if (millis() - _toneStart <  _duration)
    {
      _soundOn = false;
      //digitalWrite(_enablePin, LOW); //causes errors on re-enable because it resets the step table
    }
    else
    {
      _isPlaying = false;
    }
  }
}


boolean StepperTone::isPlaying()
{
  return _isPlaying;
}

void StepperTone::setDirection(int dir)
{
  digitalWrite(_dirPin, dir);
}

void StepperTone::setActive(boolean active)
{
  digitalWrite(_enablePin, active);
}
