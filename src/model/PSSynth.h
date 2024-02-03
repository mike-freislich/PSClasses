#pragma once
#include "AUMapping.h"
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
    //static void mapAudioUnitParameters();
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
    PSConfig config;    
    config.loadConfig("config.json");
    config.applyConfig();
    initModules();
    initScenes();
    printConfig();
}

void PSSynth::printConfig()
{
#ifdef DEBUG
    StringBuilder sb;
    sb.add("\n")->startElement()->add("\n");
    sb.add(Controllers.serialize());
    sb.add(",\n");
    sb.add(Parameters.serialize());
    sb.add("\n")->endElement()->add("\n");
    printf("%s", sb.toString().c_str());
#endif
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
    // TODO remove AU mapping to modules...
    Modules.add(MOD_PENVa, PSMEnvelope::create(MOD_PENVa, "PENV_a", PSMEnvelopeParameters(EPARMS_PENVa))); //->addAudioUnit(&auENV_PITCH_a);
    Modules.add(MOD_AENVa, PSMEnvelope::create(MOD_AENVa, "AENV_a", PSMEnvelopeParameters(EPARMS_AENVa))); //->addAudioUnit(&auENV_AMP_a);
    Modules.add(MOD_FENVa, PSMEnvelope::create(MOD_FENVa, "FENV_a", PSMEnvelopeParameters(EPARMS_FENVa))); //->addAudioUnit(&auENV_FILTER_a);
    Modules.add(MOD_PENVb, PSMEnvelope::create(MOD_PENVb, "PENV_b", PSMEnvelopeParameters(EPARMS_PENVb))); //->addAudioUnit(&osc2PENV);
    Modules.add(MOD_AENVb, PSMEnvelope::create(MOD_AENVb, "AENV_b", PSMEnvelopeParameters(EPARMS_AENVb))); //->addAudioUnit(&auENV_AMP_b);
    Modules.add(MOD_FENVb, PSMEnvelope::create(MOD_FENVb, "FENV_b", PSMEnvelopeParameters(EPARMS_FENVb))); //->addAudioUnit(&auENV_FILTER_b);
}

void PSSynth::initLFOs()
{
}

// void PSSynth::mapAudioUnitParameters()
// {
//     // AudioEffectEnvelope env1;\

//     // Lambda = [&env1](float value)
//     // {
//     //     env1.attack(value);
//     // };

//     // Parameters[PARM_AENVa_ATTACK]
//     //     ->setAudioUnitHandle(l);
// }

#pragma endregion