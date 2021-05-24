# StepperTone
An Arduino library to play tones using one or multiple stepper motors.

The steppers must be driven by a driver with step/direction interface, such as the A4988 or the DRV8225.
The implementation is based on the *micros()* and *millis()* functions. The code inside the *loop()* must be non-blocking.

Tested with Arduino UNO but should work well in other platforms.

## Library usage
### Classes

**StepperTone** is the main class for controlling a single stepper motor.

### Constructor

**StepperTone(int *direction_pin*, int *step_pin*, int *enable_pin*)**

### Methods

**void setTone(int *pitch*, int *duration*)**

Plays a tone with a specific frequency _pitch_ in Hz and a duration _duration_ in milliseconds. Notes are specified on the file **pitches.h** with the following notation: **NOTE_C3**, **NOTE_C4**, **NOTE_GS4**...

**void play()**

Main routine to generate the tones. Must be placed in the **loop()** section with other non-blocking code.

**boolean isPlaying()**

Returns *true* if the stepper is playing a tone. Useful to know when to play the next note in a song.

**void setDirection(int *dir*)**

Sets the rotation direction of the stepper. Can be set to clockwise using **DIR_CLOCKW** or counterclockwise using **DIR_CNTCLOCKW**. By default the rotation is set to clockwise.

**void setActive(boolean *active*)**

To enable/disable the stepper. Some drivers reset the step table when disabling the motor and thismay cause undesired behaviours on startup, so use it with caution. The method **setTone()** always enables the stepper.
