// #define TEENSYDUINO 210
#include "ArduinoStub.h"
#include "timing.h"
#include "Synth.h"

PS::Synth *synth;

void setup()
{
    synth = new PS::Synth();
    synth->initialise("config.json");
}

void loop()
{
    if (timer1.update())
        synth->update();
}

void exiting()
{
    synth->printConfig();    
    delete synth;    
}
