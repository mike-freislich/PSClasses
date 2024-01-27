#pragma once
#include "PSObjectCollection.h"
#include "Parameters.h"
#include "Modules.h"
#include "Controllers.h"
#include "Modules.h"
#include "Controllers.h"
#include "PSSceneManager.h"
#include "config.h"

#define SCENE_REFRESH_RATE 120
#define DEBUG

class PSSynth
{
public:
    PSSynth() {}
    ~PSSynth() {}

    void initialise();

    void update()
    {
#ifdef DEBUG
        // printf("%dms elapsed since last update", elapsed());
#endif
        Controllers.update();
        Scenes.render();
    }

    uint32_t elapsed()
    {
        uint32_t now = millis();
        uint32_t result = now - _lastUpdate;
        _lastUpdate = now;
        return result;
    }
    static void printConfig();

private:
    uint32_t _lastUpdate = millis();
    static void initModules();
    static void initEnvelopes();
    static void initLFOs();
    static void initScenes();
} synth;

#pragma region--------------- PSSynthModel implementation

void PSSynth::initScenes()
{
    Scenes.add<PSSceneEnvelope>(SCN_ENVELOPE, "Envelope")->refreshRateHz(SCENE_REFRESH_RATE);
    if (PSScene *scene = Scenes.scene(SCN_ENVELOPE))
    {
        scene->addModule(Modules.getItem<PSModule>(MOD_PENVa));
        scene->addModule(Modules.getItem<PSModule>(MOD_PENVb));
        scene->addModule(Modules.getItem<PSModule>(MOD_AENVa));
        scene->addModule(Modules.getItem<PSModule>(MOD_AENVb));
        scene->addModule(Modules.getItem<PSModule>(MOD_FENVa));
        scene->addModule(Modules.getItem<PSModule>(MOD_FENVb));
    }
    Scenes.setActive(SCN_ENVELOPE);
}

void PSSynth::initialise()
{
    PSConfig config("./src/config/config.json");
    config.applyConfig();

    // Controllers.controller(PSK::CTRL_POT1)->setReadMode(PSCRandom);
    // Controllers.controller(PSK::CTRL_POT2)->setReadMode(PSCRandom);

    initModules();
    initScenes();
    printConfig();

    if (!dynamic_cast<PSCButton *>(Controllers.controller(PSK::CTRL_BTN_DataG)))
        printf("PROBLEM WITH CTRL_BTN_DATAG");
    if (!dynamic_cast<PSCButton *>(Controllers.controller(PSK::CTRL_BTN_Shift)))
        printf("PROBLEM WITH CTRL_BTN_SHIFT");
}

void PSSynth::printConfig()
{
    StringBuilder sb;
    sb.add("\n")->startElement()->add("\n");
    sb.add(Controllers.serialize());
    sb.add(",\n");
    sb.add(Parameters.serialize());
    sb.add("\n")->endElement()->add("\n");
    printf("%s", sb.toString().c_str());
}

#pragma endregion

#pragma region--------------- INIT: Controllers

// void PSSynth::initControllers()
// {
//     // pots
//     Controllers.add<PSCPotentiometer>(CTRL_POT1, "pot1");
//     Controllers.add<PSCPotentiometer>(CTRL_POT2, "pot2");
//     Controllers.add<PSCPotentiometer>(CTRL_POT3, "pot3");
//     Controllers.add<PSCPotentiometer>(CTRL_POT4, "pot4");
//     Controllers.add<PSCPotentiometer>(CTRL_POT5, "pot5");
//     Controllers.add<PSCPotentiometer>(CTRL_POT6, "pot6");
//     Controllers.add<PSCPotentiometer>(CTRL_POT_DataA, "potDA");
//     Controllers.add<PSCPotentiometer>(CTRL_POT_DataB, "potDB");
//     Controllers.add<PSCPotentiometer>(CTRL_POT_DataC, "potDC");
//     Controllers.add<PSCPotentiometer>(CTRL_POT_DataD, "potDD");

//     // buttons
//     Controllers.add<PSCButton>(CTRL_BTN_Shift, "shift");
//     //->assignParameter(Parameters.add(CTRL_BTN_Shift, "shift")->setRange(0, 1), STANDARD_PARM)
//     //->debounceMS(1000);

//     Controllers.add<PSCButton>(CTRL_BTN_DataG, "enter");
//     //->assignParameter(Parameters.add(CTRL_BTN_DataG, "enter")->setRange(0, 1), STANDARD_PARM);
// }

#pragma endregion

#pragma region--------------- INIT: Controller / Parameter assignments

// void PSSynth::initControllerMappings()
// {
//     printf("\nController Mappings:\n");
//     Modules.envelope(MOD_PENVa)
//         ->attachControllers({{PARM_PENVa_ATTACK, Controllers.controller(CTRL_POT1)},
//                              {PARM_PENVa_HOLD, Controllers.controller(CTRL_POT2)},
//                              {PARM_PENVa_DECAY, Controllers.controller(CTRL_POT3)},
//                              {PARM_PENVa_SUSTAIN, Controllers.controller(CTRL_POT4)},
//                              {PARM_PENVa_RELEASE, Controllers.controller(CTRL_POT5)},
//                              {PARM_PENVa_AMOUNT, Controllers.controller(CTRL_POT6)}});

//     Modules.envelope(MOD_PENVb)
//         ->attachControllers({{PARM_PENVb_ATTACK, Controllers.controller(CTRL_POT6)},
//                              {PARM_PENVb_HOLD, Controllers.controller(CTRL_POT5)},
//                              {PARM_PENVb_DECAY, Controllers.controller(CTRL_POT4)},
//                              {PARM_PENVb_SUSTAIN, Controllers.controller(CTRL_POT3)},
//                              {PARM_PENVb_RELEASE, Controllers.controller(CTRL_POT2)},
//                              {PARM_PENVb_AMOUNT, Controllers.controller(CTRL_POT1)}});

//     Modules.envelope(MOD_AENVa)
//         ->attachControllers({{PARM_AENVa_ATTACK, Controllers.controller(CTRL_POT_DataA)},
//                              {PARM_AENVa_HOLD, Controllers.controller(CTRL_POT_DataB)},
//                              {PARM_AENVa_DECAY, Controllers.controller(CTRL_POT_DataC)},
//                              {PARM_AENVa_SUSTAIN, Controllers.controller(CTRL_POT_DataD)},
//                              {PARM_AENVa_RELEASE, Controllers.controller(CTRL_POT1)},
//                              {PARM_AENVa_AMOUNT, Controllers.controller(CTRL_POT2)}});

//     Modules.envelope(MOD_AENVb)
//         ->attachControllers({{PARM_AENVb_ATTACK, Controllers.controller(CTRL_POT2)},
//                              {PARM_AENVb_HOLD, Controllers.controller(CTRL_POT3)},
//                              {PARM_AENVb_DECAY, Controllers.controller(CTRL_POT4)},
//                              {PARM_AENVb_SUSTAIN, Controllers.controller(CTRL_POT5)},
//                              {PARM_AENVb_RELEASE, Controllers.controller(CTRL_POT1)},
//                              {PARM_AENVb_AMOUNT, Controllers.controller(CTRL_POT2)}});

//     Modules.envelope(MOD_FENVa)
//         ->attachControllers({{PARM_FENVa_ATTACK, Controllers.controller(CTRL_POT_DataC)},
//                              {PARM_FENVa_HOLD, Controllers.controller(CTRL_POT_DataD)},
//                              {PARM_FENVa_DECAY, Controllers.controller(CTRL_POT_DataB)},
//                              {PARM_FENVa_SUSTAIN, Controllers.controller(CTRL_POT_DataA)},
//                              {PARM_FENVa_RELEASE, Controllers.controller(CTRL_POT3)},
//                              {PARM_FENVa_AMOUNT, Controllers.controller(CTRL_POT4)}});

//     Modules.envelope(MOD_FENVb)
//         ->attachControllers({{PARM_FENVb_ATTACK, Controllers.controller(CTRL_POT_DataB)},
//                              {PARM_FENVb_HOLD, Controllers.controller(CTRL_POT_DataC)},
//                              {PARM_FENVb_DECAY, Controllers.controller(CTRL_POT_DataA)},
//                              {PARM_FENVb_SUSTAIN, Controllers.controller(CTRL_POT_DataD)},
//                              {PARM_FENVb_RELEASE, Controllers.controller(CTRL_POT5)},
//                              {PARM_FENVb_AMOUNT, Controllers.controller(CTRL_POT6)}});

//     // if (PSController * c = Controllers.controller(CTRL_POT_DataA))
//     //     c->clearParameters();
//     // if (PSController * c = Controllers.controller(CTRL_POT_DataB))
//     //     c->clearParameters();
//     // if (PSController * c = Controllers.controller(CTRL_POT_DataC))
//     //     c->clearParameters();
//     // if (PSController * c = Controllers.controller(CTRL_POT1))
//     //     c->clearParameters();
//     // if (PSController * c = Controllers.controller(CTRL_POT2))
//     //     c->clearParameters();
// }

#pragma endregion

#pragma region--------------- INIT: modules

void PSSynth::initModules()
{
    initEnvelopes();
    initLFOs();
}

void PSSynth::initEnvelopes()
{
    // Envelopes
    Modules.addItem(new PSMEnvelope(MOD_PENVa, "PENV_a", PSMEnvelopeParameters(PARM_PENVa_ATTACK, PARM_PENVa_HOLD, PARM_PENVa_DECAY, PARM_PENVa_SUSTAIN, PARM_PENVa_RELEASE, PARM_PENVa_AMOUNT)));
    Modules.addItem(new PSMEnvelope(MOD_AENVa, "AENV_a", PSMEnvelopeParameters(PARM_AENVa_ATTACK, PARM_AENVa_HOLD, PARM_AENVa_DECAY, PARM_AENVa_SUSTAIN, PARM_AENVa_RELEASE, PARM_AENVa_AMOUNT)));
    Modules.addItem(new PSMEnvelope(MOD_FENVa, "FENV_a", PSMEnvelopeParameters(PARM_FENVa_ATTACK, PARM_FENVa_HOLD, PARM_FENVa_DECAY, PARM_FENVa_SUSTAIN, PARM_FENVa_RELEASE, PARM_FENVa_AMOUNT)));
    Modules.addItem(new PSMEnvelope(MOD_PENVb, "PENV_b", PSMEnvelopeParameters(PARM_PENVb_ATTACK, PARM_PENVb_HOLD, PARM_PENVb_DECAY, PARM_PENVb_SUSTAIN, PARM_PENVb_RELEASE, PARM_PENVb_AMOUNT)));
    Modules.addItem(new PSMEnvelope(MOD_AENVb, "AENV_b", PSMEnvelopeParameters(PARM_AENVb_ATTACK, PARM_AENVb_HOLD, PARM_AENVb_DECAY, PARM_AENVb_SUSTAIN, PARM_AENVb_RELEASE, PARM_AENVb_AMOUNT)));
    Modules.addItem(new PSMEnvelope(MOD_FENVb, "FENV_b", PSMEnvelopeParameters(PARM_FENVb_ATTACK, PARM_FENVb_HOLD, PARM_FENVb_DECAY, PARM_FENVb_SUSTAIN, PARM_FENVb_RELEASE, PARM_FENVb_AMOUNT)));
}

void PSSynth::initLFOs()
{
}

#pragma endregion