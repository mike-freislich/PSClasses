// #define TEENSYDUINO 210
#include "ArduinoShard.h"
#include "timing.h"
#include "PSSynth.h"


//#define TESTMODE
#ifdef TESTMODE
#include "tests.h"
#endif


void setup()
{
#ifdef TESTMODE
    // testCollection();
    // testLoadConfig();
#else
    synth.initialise();
#endif
}

void loop()
{
#ifndef TESTMODE

    if (timer1.update())
    {
        synth.update();
    }
    delay(1);

#endif
}

void exiting()
{
    synth.printConfig();
}
