#include "ArduinoShard.h"
#include "PSControllerManager.h"
#include "PSComponentManager.h"

/**
 * PSComponent contains 1 or more PSParameter
 * PSParameter attaches 1 or more PSControllers
 * PSComponent.update() calls update on all parameters which checks if any controllers have changed
 * PSController.update() reads new values from the input device and flags if the value has changed
 */

void setup()
{
    PSCEnvelope *penv = Components.getEnv("P-ENV1a");
    penv->setValues(5, 0, 150, 1.0, 30, 1.0);
    printf("%s\n", penv->toString().c_str());

    Controllers.setup();
    penv->attack->attachController(Controllers.byKey("pot1"));

    srand(millis());
    timer1.start();
}

void loop()
{
    if (timer1.update())
    {
        Controllers.update();
        Components.update();

        PSCEnvelope *penv = Components.getEnv("P-ENV1a");        

        printf("%s : %0.0f\n", penv->getKey().c_str(), penv->attack->getValue());
        loopCount++;
    }
    delay(10, true);
}
