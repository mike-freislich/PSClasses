#pragma once
#include "AUMapping.h"
#include "PSParameterManager.h"
#include "PSControllerManager.h"
#include "PSModuleManager.h"
#include "PSSceneManager.h"
#include "config.h"

float lastShiftState;

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

        bool shiftNow = Controllers.button(CTRL_BTN_Shift)->isPressed();
        if (shiftNow != lastShiftState)
        {
            lastShiftState = shiftNow;
            Scenes.nextScene();
        }

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
    // if (!Scenes.contains(SCN_ENVELOPE))
    if (PSScene *scene = Scenes.add(SCN_ENVELOPE, PSScene::create<PSSceneEnvelope>(SCN_ENVELOPE, "View Envelope")))
        scene->refreshRateHz(SCENE_REFRESH_RATE);

    Scenes.add(SCN_VOICEMIXER, PSScene::create<PSSceneStereoVoiceMixer>(SCN_VOICEMIXER, "Main Mix"));

    Scenes.setActive();
}

void PSSynth::initialise()
{
    PSConfig config;
    config.loadConfig("config.json");
    config.applyConfig();
    // connectParameterTargets();
    initModules();
    initScenes();
    lastShiftState = Controllers.button(CTRL_BTN_Shift)->isPressed();
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
    Modules.add(MOD_MIXER_MAIN, PSMStereoVoiceMixer::create(MOD_MIXER_MAIN, "Main Mix", PSMStereoVoiceMixerParameters(PARAMS_VOICEMIXER)));
    Modules.add(MOD_PWM_A, PSMPulseWidthMod::create(MOD_PWM_A, "PWM A", PSMPulseWidthModParameters(PARAMS_PWM_A), &auWAVE_PWM_a, &auAMP_PWM_a));
    Modules.add(MOD_PWM_B, PSMPulseWidthMod::create(MOD_PWM_B, "PWM B", PSMPulseWidthModParameters(PARAMS_PWM_B), &auWAVE_PWM_b, &auAMP_PWM_b));
}

void PSSynth::initEnvelopes()
{
    Modules.add(MOD_PENV, PSMEnvModulator::create(MOD_PENV, "PENV_a", PSMEnvelopeParameters(EPARMS_PENV), &auLFO_PITCH, &auDC_PITCHBEND, &auDC_PITCHENV));
    if (PSMEnvModulator *emod = dynamic_cast<PSMEnvModulator *>(Modules[MOD_PENV]))
    {
        emod->addAudioUnit(&auENV_PITCH_V1)
            ->addAudioUnit(&auENV_PITCH_V2)
            ->addAudioUnit(&auENV_PITCH_V3)
            ->addAudioUnit(&auENV_PITCH_V4);
    }

    Modules.add(MOD_AENV, PSMEnvModulator::create(MOD_AENV, "AENV_a", PSMEnvelopeParameters(EPARMS_AENV), &auLFO_AMP, nullptr, &auDC_AMPENV));
    if (PSMEnvModulator *emod = dynamic_cast<PSMEnvModulator *>(Modules[MOD_AENV]))
    {
        emod->addAudioUnit(&auENV_AMP_V1)
            ->addAudioUnit(&auENV_AMP_V2)
            ->addAudioUnit(&auENV_AMP_V3)
            ->addAudioUnit(&auENV_AMP_V4);
    }

    Modules.add(MOD_FENV, PSMEnvModulator::create(MOD_FENV, "FENV_a", PSMEnvelopeParameters(EPARMS_FENV), &auLFO_FILTER, nullptr, &auDC_FILTERENV));
    if (PSMEnvModulator *emod = dynamic_cast<PSMEnvModulator *>(Modules[MOD_FENV]))
    {
        emod->addAudioUnit(&auENV_FILTER_V1)
            ->addAudioUnit(&auENV_FILTER_V2)
            ->addAudioUnit(&auENV_FILTER_V3)
            ->addAudioUnit(&auENV_FILTER_V4);
    }
}

#pragma endregion