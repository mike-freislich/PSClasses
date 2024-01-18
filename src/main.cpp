#define TEENSYDUINO 210

#include "ArduinoShard.h"
#include "timing.h"
#include "PSSynthModel.h"

#define DEBUG

/**
 * PSModule contains 1 or more PSParameter
 * PSParameter attaches 1 or more PSControllers
 * PSModule.update() calls update on all parameters which checks if any controllers have changed
 * PSController.update() reads new values from the input device and flags if the value has changed
 */

void setup()
{
    synth.initialise();    
}

void loop()
{
    if (timer1.update())
        synth.update();

    delay(1);
}
