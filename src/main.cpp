#include "ArduinoStub.h"
#include "AudioStub.h"
#include "init.h"


void setup()
{
    initParameters();
    initModules();
    initControllers();
}

void loop()
{
    Controllers.update();
    Modules.update();
}

void exiting()
{
}

