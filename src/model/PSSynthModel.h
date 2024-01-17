#pragma once
#include "../modules/PSModuleManager.h"
#include "../controllers/PSControllerManager.h"
#include "../view/PSSceneManager.h"

class PSSynthModel
{
public:
    PSModuleManager modules;
    PSControllerManager controllers;
    PSSceneManager scenes;

    PSSynthModel() {}

    void initialise()
    {
        initModules();
        initControllers();
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
        modules.update();
        controllers.endUpdate();
        scenes.render();
    }

private:
    void initModules()
    {
        modules.addItem(new PSCEnvelope(MOD_PENVa, "PENV_a")); // Voice part A : pitch env
        modules.addItem(new PSCEnvelope(MOD_AENVa, "AENV_a")); // v1 part A : amp env
        modules.addItem(new PSCEnvelope(MOD_FENVa, "FENV_a")); // v1 part A : filter env
        modules.addItem(new PSCEnvelope(MOD_PENVb, "PENV_b")); // v1 part B : pitch env
        modules.addItem(new PSCEnvelope(MOD_AENVb, "AENV_b")); // v1 part B : amp env
        modules.addItem(new PSCEnvelope(MOD_FENVb, "FENV_b")); // v1 part B : filter env
    }

    void initControllers()
    {
        controllers.addItem(new PSCPotentiometer(CTRL_POT1, "pot1"));
        controllers.addItem(new PSCPotentiometer(CTRL_POT2, "pot2"));
        controllers.addItem(new PSCPotentiometer(CTRL_POT3, "pot3"));
        controllers.addItem(new PSCPotentiometer(CTRL_POT4, "pot4"));
        controllers.addItem(new PSCPotentiometer(CTRL_POT5, "pot5"));
        controllers.addItem(new PSCPotentiometer(CTRL_POT6, "pot6"));
    }

    void initControllerMappings()
    {        
        modules.getEnvelope(MOD_PENVa)
            ->attachControllers(
                {{PARM_ENV_ATTACK, controllers.controller(CTRL_POT1)},                 
                 {PARM_ENV_HOLD, controllers.controller(CTRL_POT2)},
                 {PARM_ENV_DECAY, controllers.controller(CTRL_POT3)},
                 {PARM_ENV_SUSTAIN, controllers.controller(CTRL_POT4)},
                 {PARM_ENV_RELEASE, controllers.controller(CTRL_POT5)},
                 {PARM_ENV_AMOUNT, controllers.controller(CTRL_POT6)}});
    }

    void initScenes()
    {
    }

    void loadConfig()
    {
    }
} synth;
