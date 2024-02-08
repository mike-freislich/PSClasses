// #define TEENSYDUINO 210
#include "ArduinoStub.h"
#include "timing.h"
#include "Synth.h"

ps::Synth *synth;

void setup()
{
    synth = new ps::Synth();
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
