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
        Modules.update();
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
    // static void mapAudioUnitParameters();
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
    //connectParameterTargets();
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
    Modules.add(MOD_MIXER_MAIN, PSMStereoVoiceMixer::create(MOD_MIXER_MAIN, "Main Mix", PSMStereoVoiceMixerParameters(PARAMS_MASTER)));
    initEnvelopes();    
}

void PSSynth::initEnvelopes()
{    
    Modules.add(MOD_PENV, PSMEnvModulator::create(MOD_PENV, "PENV_a", PSMEnvelopeParameters(EPARMS_PENV)));

    if (PSMEnvModulator *emod = dynamic_cast<PSMEnvModulator *>(Modules[MOD_PENV]))
    {
        emod->addAudioUnit(&auENV_PITCH_V1)
            ->addAudioUnit(&auENV_PITCH_V2)
            ->addAudioUnit(&auENV_PITCH_V3)
            ->addAudioUnit(&auENV_PITCH_V4)
            ->addAudioUnit(&auDC_PITCHENV)
            ->addAudioUnit(&auLFO_PITCH);
    }
    Modules.add(MOD_AENV, PSMEnvModulator::create(MOD_AENV, "AENV_a", PSMEnvelopeParameters(EPARMS_AENV)));
    if (PSMEnvModulator *emod = dynamic_cast<PSMEnvModulator *>(Modules[MOD_AENV]))
    {
        emod->addAudioUnit(&auENV_AMP_V1)
            ->addAudioUnit(&auENV_AMP_V2)
            ->addAudioUnit(&auENV_AMP_V3)
            ->addAudioUnit(&auENV_AMP_V4)
            ->addAudioUnit(&auDC_AMPENV)
            ->addAudioUnit(&auLFO_AMP);
    }

    Modules.add(MOD_FENV, PSMEnvModulator::create(MOD_FENV, "FENV_a", PSMEnvelopeParameters(EPARMS_FENV)));
    if (PSMEnvModulator *emod = dynamic_cast<PSMEnvModulator *>(Modules[MOD_FENV]))
    {
        emod->addAudioUnit(&auENV_FILTER_V1)
            ->addAudioUnit(&auENV_FILTER_V2)
            ->addAudioUnit(&auENV_FILTER_V3)
            ->addAudioUnit(&auENV_FILTER_V4)
            ->addAudioUnit(&auDC_FILTERENV)
            ->addAudioUnit(&auLFO_FILTER);
    }
}

#pragma endregion