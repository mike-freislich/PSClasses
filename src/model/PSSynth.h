#pragma once
#include "PSParameterManager.h"
#include "PSControllerManager.h"
#include "PSModuleManager.h"
#include "PSSceneManager.h"
#include "config.h"

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
    if (!Scenes.contains(SCN_ENVELOPE))
        Scenes.add(SCN_ENVELOPE, PSScene::create<PSSceneEnvelope>(SCN_ENVELOPE, "View Envelope"));

    if (PSScene *scene = Scenes["SCN_ENVELOPE"])
    {
        scene->refreshRateHz(SCENE_REFRESH_RATE);        
    }
    Scenes.setActive("SCN_ENVELOPE");
}

void PSSynth::initialise()
{
    PSConfig config("./src/config/config.json");
    config.applyConfig();


    Controllers[CTRL_POT1]->setReadMode(PSCRandom);
    Controllers[CTRL_POT2]->setReadMode(PSCRandom);

    initModules();
    initScenes();
    printConfig();
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


#pragma region--------------- INIT: modules

void PSSynth::initModules()
{
    initEnvelopes();
    initLFOs();
}

void PSSynth::initEnvelopes()
{    
    Modules.add(MOD_PENVa, PSMEnvelope::create(MOD_PENVa, "PENV_a", PSMEnvelopeParameters(EPARMS_PENVa)));    
    Modules.add(MOD_AENVa, PSMEnvelope::create(MOD_AENVa, "AENV_a", PSMEnvelopeParameters(EPARMS_AENVa)));
    Modules.add(MOD_FENVa, PSMEnvelope::create(MOD_FENVa, "FENV_a", PSMEnvelopeParameters(EPARMS_FENVa)));
    Modules.add(MOD_PENVb, PSMEnvelope::create(MOD_PENVb, "PENV_b", PSMEnvelopeParameters(EPARMS_PENVb)));
    Modules.add(MOD_AENVb, PSMEnvelope::create(MOD_AENVb, "AENV_b", PSMEnvelopeParameters(EPARMS_AENVb)));
    Modules.add(MOD_FENVb, PSMEnvelope::create(MOD_FENVb, "FENV_b", PSMEnvelopeParameters(EPARMS_FENVb)));
}

void PSSynth::initLFOs()
{
}

#pragma endregion