#include "ArduinoShard.h"
#include "PSControllerManager.h"
#include "PSComponentManager.h"
#include "FastMath.h"

/**
 * PSComponent contains 1 or more PSParameter
 * PSParameter attaches 1 or more PSControllers
 * PSComponent.update() calls update on all parameters which checks if any controllers have changed
 * PSController.update() reads new values from the input device and flags if the value has changed
 */

void mapControllerParameters(PSCEnvelope *penv);

void setup()
{
    PSCEnvelope *penv = Components.getEnv("P-ENV1a");
    penv->setValues(5, 0, 150, 1.0f, 30, 1.0f);
    //Controllers.setup();
    mapControllerParameters(penv);

    srand(millis());
    timer1.start();
}

void mapControllerParameters(PSCEnvelope *penv)
{
    penv->values[PARM_ENV_ATTACK]->attachController(Controllers.byKey("pot1"));
    penv->values[PARM_ENV_HOLD]->attachController(Controllers.byKey("pot1"));
    penv->values[PARM_ENV_DECAY]->attachController(Controllers.byKey("pot1"));
    penv->values[PARM_ENV_SUSTAIN]->attachController(Controllers.byKey("pot1"))->setTaper(PSParameter::TAPER::LOGARITHMIC);
    penv->values[PARM_ENV_RELEASE]->attachController(Controllers.byKey("pot1"));
    penv->values[PARM_ENV_AMOUNT]->attachController(Controllers.byKey("pot1"));
}

void loop()
{
    if (timer1.update())
    {
        Controllers.update();       // polls the hardware controllers
        Components.update();        // updates the synth parameters from controllers
        Controllers.endUpdate();    // resets controller changed state before next poll

        PSCEnvelope *env = Components.getEnv("P-ENV1a");
        float a = env->values[PARM_ENV_ATTACK]->getValue(),
              h = env->values[PARM_ENV_HOLD]->getValue(),
              d = env->values[PARM_ENV_DECAY]->getValue(),
              s = env->values[PARM_ENV_SUSTAIN]->getValue(),
              r = env->values[PARM_ENV_RELEASE]->getValue(),
              amt = env->values[PARM_ENV_AMOUNT]->getValue();

        printf("%s : atk %07.2f, hld %07.2f, dec %07.2f, sus %0.2f, rel %07.2f, amt %0.2f\n",
               env->getKey().c_str(),
               a, h, d, s, r, amt);

        loopCount++;
    }
    delay(10);
}
