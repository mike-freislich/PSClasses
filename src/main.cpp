// #define TEENSYDUINO 210
#include "ArduinoShard.h"
#include "timing.h"
#include "PSSynth.h"


void setup()
{
    synth.initialise();
}

void loop()
{
    if (timer1.update())
    {
        synth.update();
    }    
}

void exiting()
{
    synth.printConfig();
}
