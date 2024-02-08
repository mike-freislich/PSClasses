#pragma once
#include "ArduinoStub.h"
#include "AUMapping.h"
#include "ParameterManager.h"
#include "ControllerManager.h"
#include "ModuleManager.h"
#include "SceneManager.h"
#include "config.h"

namespace ps
{
    class Synth
    {
    public:
        Synth() {}
        ~Synth() {}

        void initialise(const char *filename);
        void update();

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
        static void initScenes();
        // static void mapAudioUnitParameters();
    };

#pragma region--------------- PSSynthModel implementation

    float lastShiftState;

    void Synth::update()
    {
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

    void Synth::initScenes()
    {
        // if (!Scenes.contains(SCN_ENVELOPE))
        if (Scene *scene = Scenes.add(SCN_ENVELOPE, Scene::create<SceneEnvelope>(SCN_ENVELOPE, "View Envelope")))
            scene->refreshRateHz(SCENE_REFRESH_RATE);

        Scenes.add(SCN_VOICEMIXER, Scene::create<SceneStereoVoiceMixer>(SCN_VOICEMIXER, "Main Mix"));

        Scenes.setActive();
    }

    void Synth::initialise(const char *filename)
    {
        PSConfig config;
        config.loadConfig(filename);
        config.applyConfig();
        // connectParameterTargets();
        initModules();
        initScenes();
        lastShiftState = Controllers.button(CTRL_BTN_Shift)->isPressed();
        printConfig();
    }

    void Synth::printConfig()
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

    void Synth::initModules()
    {
        initEnvelopes();
        Modules.add(MOD_MIXER_MAIN, ps::PSMStereoVoiceMixer::create(MOD_MIXER_MAIN, "Main Mix", ps::PSMStereoVoiceMixerParameters(PARAMS_VOICEMIXER)));
        Modules.add(MOD_PWM_A, PSMPulseWidthMod::create(MOD_PWM_A, "PWM A", PSMPulseWidthModParameters(PARAMS_PWM_A), &auWAVE_PWM_a, &auAMP_PWM_a));
        Modules.add(MOD_PWM_B, PSMPulseWidthMod::create(MOD_PWM_B, "PWM B", PSMPulseWidthModParameters(PARAMS_PWM_B), &auWAVE_PWM_b, &auAMP_PWM_b));
    }

    void Synth::initEnvelopes()
    {
        Modules.add(MOD_PENV, ps::PSMEnvModulator::create(MOD_PENV, "PENV_a", ps::PSMEnvelopeParameters(EPARMS_PENV), &auLFO_PITCH, &auDC_PITCHBEND, &auDC_PITCHENV));
        if (ps::PSMEnvModulator *emod = dynamic_cast<ps::PSMEnvModulator *>(Modules[MOD_PENV]))
        {
            emod->addAudioUnit(&auENV_PITCH_V1)
                ->addAudioUnit(&auENV_PITCH_V2)
                ->addAudioUnit(&auENV_PITCH_V3)
                ->addAudioUnit(&auENV_PITCH_V4);
        }

        Modules.add(MOD_AENV, ps::PSMEnvModulator::create(MOD_AENV, "AENV_a", ps::PSMEnvelopeParameters(EPARMS_AENV), &auLFO_AMP, nullptr, &auDC_AMPENV));
        if (ps::PSMEnvModulator *emod = dynamic_cast<ps::PSMEnvModulator *>(Modules[MOD_AENV]))
        {
            emod->addAudioUnit(&auENV_AMP_V1)
                ->addAudioUnit(&auENV_AMP_V2)
                ->addAudioUnit(&auENV_AMP_V3)
                ->addAudioUnit(&auENV_AMP_V4);
        }

        Modules.add(MOD_FENV, ps::PSMEnvModulator::create(MOD_FENV, "FENV_a", ps::PSMEnvelopeParameters(EPARMS_FENV), &auLFO_FILTER, nullptr, &auDC_FILTERENV));
        if (ps::PSMEnvModulator *emod = dynamic_cast<ps::PSMEnvModulator *>(Modules[MOD_FENV]))
        {
            emod->addAudioUnit(&auENV_FILTER_V1)
                ->addAudioUnit(&auENV_FILTER_V2)
                ->addAudioUnit(&auENV_FILTER_V3)
                ->addAudioUnit(&auENV_FILTER_V4);
        }
    }

#pragma endregion

}
