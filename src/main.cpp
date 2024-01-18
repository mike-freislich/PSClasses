#include "utils/ArduinoShard.h"
#include "model/PSSynthModel.h"

#define DEBUG

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
#ifdef DEBUG
        printf("%s\n", synth.modules.getItem<PSMEnvelope>(MOD_PENVa)->toString().c_str());
#endif
        loopCount++;
    }
    delay(10);
}
