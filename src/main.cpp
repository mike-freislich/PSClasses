#include <iostream>
#include <cstdio>
#include "timing.h"
#include "PSControllerManager.h"
#include "PSComponent.h"
#include "PSCEnvelope.h"

/**
 * PSComponent contains 1 or more PSParameter
 * PSParameter attaches 1 or more PSControllers
 * PSComponent.update() calls update on all parameters which checks if any controllers have changed
 * PSController.update() reads new values from the input device and flags if the value has changed
 */

using namespace std;
void setup();
void loop();

PSComponent comp = PSComponent();
PSCEnvelope env = PSCEnvelope();

int main()
{
    printf("Starting Main\n");
    setup();
    loop();
    return 0;
}

void setup()
{    
    env.setValues(5, 0, 150, 1.0, 30, 1.0);

    controlsManager.addController(new PSController("CC67", false));
    controlsManager.addController(new PSController("CC68", true));
    srand(millis());
    PSParameter *p = new PSParameter("param1");
    for (auto c : controlsManager.controls)
        p->attachController(c);

    comp.addParameter(p);
    timer1.duration(300);
    timer1.start();
}

void loop()
{
    int loopCount = 0;
    while (loopCount < 10)
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
}
