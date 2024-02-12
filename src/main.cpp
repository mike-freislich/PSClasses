#ifdef BUILD_FOR_TEENSY
#include <Ardunio>
#else
#include "ArduinoStub.h"
#endif
#include "LXSynth.h"

LXSynth synth;

void setup()
{
       
}

void loop()
{
    synth.update();
}

void exiting()
{
}

