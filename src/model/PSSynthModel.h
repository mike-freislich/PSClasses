#pragma once
#include "../components/PSComponentManager.h"
#include "../controllers/PSControllerManager.h"
#include "../view/PSSceneManager.h"

class PSSynthModel
{
public:
    PSComponentManager components;
    PSControllerManager controllers;
    PSSceneManager scenes;

    PSSynthModel() {}

    void initialise()
    {
        initComponents();
        initControllers();
        initControllerMappings();
        initScenes();
        loadConfig();
    }

    /**
     * @brief updates controllers, components and scenes
     */
    void update()
    {
        controllers.update();
        components.update();
        controllers.endUpdate();
        scenes.render();
    }

private:
    void initComponents()
    {
        components.addItem(new PSCEnvelope(COMP_PENVa, "PENV_a")); // Voice part A : pitch env
        components.addItem(new PSCEnvelope(COMP_AENVa, "AENV_a")); // v1 part A : amp env
        components.addItem(new PSCEnvelope(COMP_FENVa, "FENV_a")); // v1 part A : filter env
        components.addItem(new PSCEnvelope(COMP_PENVb, "PENV_b")); // v1 part B : pitch env
        components.addItem(new PSCEnvelope(COMP_AENVb, "AENV_b")); // v1 part B : amp env
        components.addItem(new PSCEnvelope(COMP_FENVb, "FENV_b")); // v1 part B : filter env
    }

    void initControllers()
    {
        controllers.addItem(new PSCTPotentiometer(CTRL_POT1, "pot1"));
        controllers.addItem(new PSCTPotentiometer(CTRL_POT2, "pot2"));
        controllers.addItem(new PSCTPotentiometer(CTRL_POT3, "pot3"));
        controllers.addItem(new PSCTPotentiometer(CTRL_POT4, "pot4"));
        controllers.addItem(new PSCTPotentiometer(CTRL_POT5, "pot5"));
        controllers.addItem(new PSCTPotentiometer(CTRL_POT6, "pot6"));
    }

    void initControllerMappings()
    {        
        components.getEnvelope(COMP_PENVa)
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
