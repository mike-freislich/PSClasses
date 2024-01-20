#pragma once

#include "PSObjectCollection.h"
#include "Parameters.h"
#include "Modules.h"
#include "Controllers.h"
#include "PSSceneManager.h"

class PSSynthModel
{
private:
public:
    PSCButton
        *btnShift,
        *btnNoiseColour,
        *btnEnvSelect,
        *btnFilterBand,
        *btnFilterMode,
        *btnDataGlobal;

    PSParameter *shiftMode;
    PSControllerManager controllers;
    PSSceneManager scenes;

    PSSynthModel() {}
    ~PSSynthModel() {}

    void initialise()
    {
        initControllers();
        initModules();
        initControllerMappings();
        initScenes();
        loadConfig();
    }

    /**
     * @brief updates controllers, modules and scenes
     */
    void update()
    {
        controllers.update();
        Modules.update();
        controllers.endUpdate();
        printf("SHIFT : %d\n", (int)btnShift->getValue());
        scenes.render();
    }

private:
    void initControllers()
    {
        // pots
        controllers.addItem(new PSCPotentiometer(CTRL_POT1, "pot1"));
        controllers.addItem(new PSCPotentiometer(CTRL_POT2, "pot2"));
        controllers.addItem(new PSCPotentiometer(CTRL_POT3, "pot3"));
        controllers.addItem(new PSCPotentiometer(CTRL_POT4, "pot4"));
        controllers.addItem(new PSCPotentiometer(CTRL_POT5, "pot5"));
        controllers.addItem(new PSCPotentiometer(CTRL_POT6, "pot6"));

        // buttons
        btnShift = controllers.addItem(new PSCButton(CTRL_BTN_Shift, "shift"));
        shiftMode = (new PSParameter(PSK::CTRL_BTN_Shift, "shift"))->attachController(btnShift);
        btnDataGlobal = controllers.addItem(new PSCButton(CTRL_BTN_DataG, "enter"));
    }

    void initControllerMappings()
    {
        Modules.envelope(MOD_PENVa)
            ->attachControllers(
                {{PARM_PENVa_ATTACK, controllers.controller(CTRL_POT1)},
                 {PARM_PENVa_HOLD, controllers.controller(CTRL_POT2)},
                 {PARM_PENVa_DECAY, controllers.controller(CTRL_POT3)},
                 {PARM_PENVa_SUSTAIN, controllers.controller(CTRL_POT4)},
                 {PARM_PENVa_RELEASE, controllers.controller(CTRL_POT5)},
                 {PARM_PENVa_AMOUNT, controllers.controller(CTRL_POT6)}});
    }

    void initScenes()
    {
        scenes.addItem((new PSSceneEnvelope("Scene Envelope"))->addModule(Modules.getItem<PSModule>(MOD_PENVa)));
        scenes.setActive(SCN_ENVELOPE);
    }

    void loadConfig()
    {
        
    }
} synth;
