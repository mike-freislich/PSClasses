#include "utils/ArduinoShard.h"
#include "model/PSSynthModel.h"

/**
 * PSModule contains 1 or more PSParameter
 * PSParameter attaches 1 or more PSControllers
 * PSModule.update() calls update on all parameters which checks if any controllers have changed
 * PSController.update() reads new values from the input device and flags if the value has changed
 */

void setup()
{
    synth.initialise();
    timer1.start();
}

void loop()
{
    if (timer1.update())
    {

        synth.update();
        printf("%s\n", synth.components.getItem<PSCEnvelope>(MOD_PENVa)->toString().c_str());
        loopCount++;
    }
    delay(10);
}
