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
        Controllers.update();
        Parameters.update();
        Controllers.endUpdate();
        scenes.render();
    }

private:
    void initControllerMappings()
    {
        printf("\nController Mappings:\n");
        Modules.envelope(MOD_PENVa)
            ->attachControllers(
                {{PARM_PENVa_ATTACK, Controllers.controller(CTRL_POT1)},
                 {PARM_PENVa_HOLD, Controllers.controller(CTRL_POT2)},
                 {PARM_PENVa_DECAY, Controllers.controller(CTRL_POT3)},
                 {PARM_PENVa_SUSTAIN, Controllers.controller(CTRL_POT4)},
                 {PARM_PENVa_RELEASE, Controllers.controller(CTRL_POT5)},
                 {PARM_PENVa_AMOUNT, Controllers.controller(CTRL_POT6)}});

        Modules.envelope(MOD_PENVb)
            ->attachControllers(
                {{PARM_PENVb_ATTACK, Controllers.controller(CTRL_POT6)},
                 {PARM_PENVb_HOLD, Controllers.controller(CTRL_POT5)},
                 {PARM_PENVb_DECAY, Controllers.controller(CTRL_POT4)},
                 {PARM_PENVb_SUSTAIN, Controllers.controller(CTRL_POT3)},
                 {PARM_PENVb_RELEASE, Controllers.controller(CTRL_POT2)},
                 {PARM_PENVb_AMOUNT, Controllers.controller(CTRL_POT1)}});

        Modules.envelope(MOD_AENVa)
            ->attachControllers(
                {{PARM_AENVa_ATTACK, Controllers.controller(CTRL_POT_DataA)},
                 {PARM_AENVa_HOLD, Controllers.controller(CTRL_POT_DataB)},
                 {PARM_AENVa_DECAY, Controllers.controller(CTRL_POT_DataC)},
                 {PARM_AENVa_SUSTAIN, Controllers.controller(CTRL_POT_DataD)},
                 {PARM_AENVa_RELEASE, Controllers.controller(CTRL_POT1)},
                 {PARM_AENVa_AMOUNT, Controllers.controller(CTRL_POT2)}});

        Modules.envelope(MOD_AENVb)
            ->attachControllers(
                {{PARM_AENVb_ATTACK, Controllers.controller(CTRL_POT2)},
                 {PARM_AENVb_HOLD, Controllers.controller(CTRL_POT3)},
                 {PARM_AENVb_DECAY, Controllers.controller(CTRL_POT4)},
                 {PARM_AENVb_SUSTAIN, Controllers.controller(CTRL_POT5)},
                 {PARM_AENVb_RELEASE, Controllers.controller(CTRL_POT1)},
                 {PARM_AENVb_AMOUNT, Controllers.controller(CTRL_POT2)}});

        Modules.envelope(MOD_FENVa)
            ->attachControllers(
                {{PARM_FENVa_ATTACK, Controllers.controller(CTRL_POT_DataC)},
                 {PARM_FENVa_HOLD, Controllers.controller(CTRL_POT_DataD)},
                 {PARM_FENVa_DECAY, Controllers.controller(CTRL_POT_DataB)},
                 {PARM_FENVa_SUSTAIN, Controllers.controller(CTRL_POT_DataA)},
                 {PARM_FENVa_RELEASE, Controllers.controller(CTRL_POT3)},
                 {PARM_FENVa_AMOUNT, Controllers.controller(CTRL_POT4)}});

        Modules.envelope(MOD_FENVb)
            ->attachControllers(
                {{PARM_FENVb_ATTACK, Controllers.controller(CTRL_POT_DataB)},
                 {PARM_FENVb_HOLD, Controllers.controller(CTRL_POT_DataC)},
                 {PARM_FENVb_DECAY, Controllers.controller(CTRL_POT_DataA)},
                 {PARM_FENVb_SUSTAIN, Controllers.controller(CTRL_POT_DataD)},
                 {PARM_FENVb_RELEASE, Controllers.controller(CTRL_POT5)},
                 {PARM_FENVb_AMOUNT, Controllers.controller(CTRL_POT6)}});
    }

    void initScenes()
    {
        scenes.addItem(new PSSceneEnvelope("Scene Envelope"))->refreshRateKHz(120);
        if (PSScene *scene = scenes.getItem<PSScene>(SCN_ENVELOPE))
        {
            scene->addModule(Modules.getItem<PSModule>(MOD_PENVa));
            scene->addModule(Modules.getItem<PSModule>(MOD_PENVb));
            scene->addModule(Modules.getItem<PSModule>(MOD_AENVa));
            scene->addModule(Modules.getItem<PSModule>(MOD_AENVb));
            scene->addModule(Modules.getItem<PSModule>(MOD_FENVa));
            scene->addModule(Modules.getItem<PSModule>(MOD_FENVb));           
        }

        scenes.setActive(SCN_ENVELOPE);
    }

    void loadConfig()
    {
    }
} synth;
