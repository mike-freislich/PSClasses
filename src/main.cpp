#include "ArduinoStub.h"
#include "AudioStub.h"
#include "init.h"


void setup()
{
    initParameters();
    initModules();
}

void loop()
{
    Modules.update();
}

void exiting()
{
}

