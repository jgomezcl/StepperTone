/*
  Example sketch for two stepper tone
  This is basic example of how to play a song with two melodies
  The steppers must be driven using a driver with STEP and DIRECTION pins, such as the DRV8225 or the A4988
  Implemented using micros() and millis() and tested on Arduino UNO
  Updated: Jan 2021 by Joan Gómez
*/

#include "pitches.h"
#include "stepperTone.h"

int melody1[] = {
  NOTE_F5, NOTE_F5, NOTE_F5, NOTE_F5, NOTE_F5, NOTE_F5, NOTE_F5, NOTE_F5,
  NOTE_F5, NOTE_F5, NOTE_F5, NOTE_F5, NOTE_F5, NOTE_F5, NOTE_F5, NOTE_F5,
  NOTE_F5, NOTE_F5, NOTE_F5, NOTE_FS5, NOTE_F5, NOTE_F5, NOTE_F5, NOTE_F5,

  NOTE_FS5, NOTE_F5, NOTE_F5, NOTE_FS5, NOTE_F5, NOTE_F5, NOTE_F5, NOTE_F5,
  NOTE_AS5, NOTE_AS5, NOTE_AS5, NOTE_AS5, NOTE_AS5, NOTE_AS5, NOTE_AS5, NOTE_AS5,
  NOTE_C6, NOTE_C6, NOTE_C6, NOTE_C6, NOTE_C6, NOTE_C6, NOTE_C6, NOTE_C6,

  NOTE_AS5, NOTE_CS6, NOTE_C6, NOTE_DS6, NOTE_GS5, NOTE_FS5, NOTE_F5,

  NOTE_CS5, NOTE_DS5, NOTE_C5,

  NOTE_AS5, NOTE_CS6, NOTE_C6, NOTE_DS6, NOTE_GS6, NOTE_FS6, NOTE_F6,
};

int durations1[] = {
  125, 125, 125, 125, 125, 125, 125, 125,
  125, 125, 125, 125, 125, 125, 125, 125,
  125, 125, 125, 125, 125, 125, 125, 125,

  125, 125, 125, 125, 125, 125, 125, 125,
  125, 125, 125, 125, 125, 125, 125, 125,
  125, 125, 125, 125, 125, 125, 125, 125,

  750, 250, 250, 250, 250, 250, 1000,

  1000, 1000, 1000,

  750, 250, 250, 250, 250, 250, 1000,
};

int melody2[] = {
  NOTE_F5, NOTE_F5, NOTE_F5, NOTE_F5, NOTE_F5, NOTE_F5, NOTE_F5, NOTE_F5,
  NOTE_F5, NOTE_F5, NOTE_F5, NOTE_F5, NOTE_F5, NOTE_F5, NOTE_F5, NOTE_F5,
  NOTE_F5, NOTE_F5, NOTE_F5, NOTE_FS5, NOTE_F5, NOTE_F5, NOTE_F5, NOTE_F5,

  NOTE_FS5, NOTE_F5, NOTE_F5, NOTE_FS5, NOTE_F5, NOTE_F5, NOTE_F5, NOTE_F5,
  NOTE_F5, NOTE_F5, NOTE_F5, NOTE_F5, NOTE_F5, NOTE_F5, NOTE_F5, NOTE_F5,
  NOTE_F5, NOTE_F5, NOTE_F5, NOTE_F5, NOTE_F5, NOTE_F5, NOTE_F5, NOTE_F5,

  NOTE_F5, NOTE_F5, NOTE_F5, NOTE_F5, NOTE_F5, NOTE_F5, NOTE_F5, NOTE_F5,
  NOTE_F5, NOTE_F5, NOTE_F5, NOTE_F5, NOTE_F5, NOTE_F5, NOTE_F5, NOTE_F5,
  NOTE_F5, NOTE_F5, NOTE_F5, NOTE_F5, NOTE_F5, NOTE_F5, NOTE_F5, NOTE_F5,

  NOTE_F5, NOTE_F5, NOTE_F5, NOTE_F5, NOTE_F5, NOTE_F5, NOTE_F5, NOTE_F5,
  NOTE_F5, NOTE_F5, NOTE_F5, NOTE_F5, NOTE_F5, NOTE_F5, NOTE_F5, NOTE_F5,
  NOTE_F5, NOTE_F5, NOTE_F5, NOTE_F5, NOTE_F5, NOTE_F5, NOTE_F5, NOTE_F5,

  NOTE_F5, NOTE_F5, NOTE_F5, NOTE_F5, NOTE_F5, NOTE_F5, NOTE_F5, NOTE_F5,
  NOTE_F5, NOTE_F5, NOTE_F5, NOTE_F5, NOTE_F5, NOTE_F5, NOTE_F5, NOTE_F5,
  NOTE_F5, NOTE_F5, NOTE_F5, NOTE_F5, NOTE_F5, NOTE_F5, NOTE_F5, NOTE_F5,
};

int durations2[] = {
  125, 125, 125, 125, 125, 125, 125, 125,
  125, 125, 125, 125, 125, 125, 125, 125,
  125, 125, 125, 125, 125, 125, 125, 125,

  125, 125, 125, 125, 125, 125, 125, 125,
  125, 125, 125, 125, 125, 125, 125, 125,
  125, 125, 125, 125, 125, 125, 125, 125,

  125, 125, 125, 125, 125, 125, 125, 125,
  125, 125, 125, 125, 125, 125, 125, 125,
  125, 125, 125, 125, 125, 125, 125, 125,

  125, 125, 125, 125, 125, 125, 125, 125,
  125, 125, 125, 125, 125, 125, 125, 125,
  125, 125, 125, 125, 125, 125, 125, 125,

  125, 125, 125, 125, 125, 125, 125, 125,
  125, 125, 125, 125, 125, 125, 125, 125,
  125, 125, 125, 125, 125, 125, 125, 125,
};

int songLength1 = sizeof(melody1) / sizeof(melody1[0]);
int currentNote1 = 0;

int songLength2 = sizeof(melody2) / sizeof(melody2[0]);
int currentNote2 = 0;

#define TIME_MULTIPLIER 1.3     //Use this to incrase/decrease the basic tempo

StepperTone s1(2, 3, 4);
StepperTone s2(5, 6, 7);

void setup()
{
  s1.setDirection(DIR_CLOCKW);  //Use this to change the direction to DIR_CLOCKW or DIR_CNTCLOCKW (default clockwise)
}

//DO NOT USE BLOCKING CODE INSIDE THE LOOP
void loop() {

  if (!s1.isPlaying())    //The next note is played when the stepper is idle
  {
    s1.setTone(melody1[currentNote1], durations1[currentNote1] * TIME_MULTIPLIER);
    currentNote1++;

    if (currentNote1 > songLength1)
    {
      s1.setActive(false);
      s2.setActive(false);
      while (1);
    }
  }

  if (!s2.isPlaying())
  {
    s2.setTone(melody2[currentNote2], durations2[currentNote2] * TIME_MULTIPLIER);
    currentNote2++;

    if (currentNote2 > songLength2)
    {
      s1.setActive(false);
      s2.setActive(false);
      while (1);
    }
  }

  s1.play();
  s2.play();
}
