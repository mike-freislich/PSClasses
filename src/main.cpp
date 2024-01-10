#include "ArduinoShard.h"
#include "PSControllerManager.h"
#include "PSComponentManager.h"

/**
 * PSComponent contains 1 or more PSParameter
 * PSParameter attaches 1 or more PSControllers
 * PSComponent.update() calls update on all parameters which checks if any controllers have changed
 * PSController.update() reads new values from the input device and flags if the value has changed
 */
PSComponent comp = PSComponent("std comp");

void setup()
{
    PSCEnvelope *penv = componentManager.getEnv("P-ENV1a");
    penv->setValues(5, 0, 150, 1.0, 30, 1.0);
    printf("%s\n", penv->toString().c_str());

    controlsManager.addController(new PSController("CC67", false));
    controlsManager.addController(new PSController("CC68", true));
    srand(millis());
    PSParameter *p = new PSParameter("param1");
    for (auto c : controlsManager.controls)
        p->attachController(c);

    comp.addParameter(p);

    timer1.start();    
}

void loop()
{
    if (timer1.update())
    {
        controlsManager.update();
        comp.update();
        PSParameter *p = comp.values[0];
        printf("%s : %0.0f\n", p->getKey().c_str(), p->getValue());
        loopCount++;
    }
    delay(10, true);
}
