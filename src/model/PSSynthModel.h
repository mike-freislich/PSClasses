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

        btnShift = Controllers.button(CTRL_BTN_Shift);
    }

    /**
     * @brief updates controllers, modules and scenes
     */
    void update()
    {
        Controllers.update();
        Modules.update();
        Controllers.endUpdate();
        //printf("SHIFT : %d\n", (int)btnShift->getValue());
        scenes.render();
    }

private:


    void initControllerMappings()
    {
        Modules.envelope(MOD_PENVa)
            ->attachControllers(
                {{PARM_PENVa_ATTACK, Controllers.controller(CTRL_POT1)},
                 {PARM_PENVa_HOLD, Controllers.controller(CTRL_POT2)},
                 {PARM_PENVa_DECAY, Controllers.controller(CTRL_POT3)},
                 {PARM_PENVa_SUSTAIN, Controllers.controller(CTRL_POT4)},
                 {PARM_PENVa_RELEASE, Controllers.controller(CTRL_POT5)},
                 {PARM_PENVa_AMOUNT, Controllers.controller(CTRL_POT6)}});
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
