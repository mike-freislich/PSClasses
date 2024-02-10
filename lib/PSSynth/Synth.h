#pragma once
#include "ArduinoStub.h"
#include "AUMapping.h"
#include "ParameterManager.h"
#include "ControllerManager.h"
#include "ModuleManager.h"
#include "SceneManager.h"
#include "config.h"

namespace PS
{
    class Synth
    {
    public:
        Synth() {}
        ~Synth() {}

        void initialise(const char *filename);
        void update();
        uint32_t elapsed();
        static void printConfig();

    private:
        uint32_t _lastUpdate = millis();
        static void initModules();        
        static void initScenes();        
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
        initModules();
        initScenes();
        if (CButton *b = Controllers.button(CTRL_BTN_Shift))
            lastShiftState = b->isPressed();
        printConfig();
    }

    void Synth::printConfig()
    {
        StringBuilder sb;
        sb.add("\n")->startElement()->add("\n");
        sb.add(Controllers.serialize());
        sb.add(",\n");
        sb.add(Parameters.serialize());
        sb.add("\n")->endElement()->add("\n");
        LOG(sb.toString());
    }

    void Synth::initModules()
    {        
        Modules.add(MOD_PENV, PS::ModuleModulator::create(MOD_PENV, "PENV_a", PS::ModuleModulatorParameters(EPARMS_PENV), &auLFO_PITCH, &auDC_PITCHBEND, &auDC_PITCHENV));        
        if (PS::ModuleModulator *emod = static_cast<PS::ModuleModulator *>(Modules[MOD_PENV]))
            emod->addAudioUnits({&auENV_PITCH_V1, &auENV_PITCH_V2, &auENV_PITCH_V3, &auENV_PITCH_V4});
        Modules.add(MOD_AENV, PS::ModuleModulator::create(MOD_AENV, "AENV_a", PS::ModuleModulatorParameters(EPARMS_AENV), &auLFO_AMP, nullptr, &auDC_AMPENV));
        if (PS::ModuleModulator *emod = static_cast<PS::ModuleModulator *>(Modules[MOD_AENV]))
            emod->addAudioUnits({&auENV_AMP_V1, &auENV_AMP_V2, &auENV_AMP_V3, &auENV_AMP_V4});
        Modules.add(MOD_FENV, PS::ModuleModulator::create(MOD_FENV, "FENV_a", PS::ModuleModulatorParameters(EPARMS_FENV), &auLFO_FILTER, nullptr, &auDC_FILTERENV));
        if (PS::ModuleModulator *emod = static_cast<PS::ModuleModulator *>(Modules[MOD_FENV]))
            emod->addAudioUnits({&auENV_FILTER_V1, &auENV_FILTER_V2, &auENV_FILTER_V3, &auENV_FILTER_V4});

        Modules.add(MOD_PWM_A, ModulePulseWidthMod::create(MOD_PWM_A, "PWM A", ModulePulseWidthModParameters(PARAMS_PWM_A), &auWAVE_PWM_a, &auAMP_PWM_a));
        Modules.add(MOD_PWM_B, ModulePulseWidthMod::create(MOD_PWM_B, "PWM B", ModulePulseWidthModParameters(PARAMS_PWM_B), &auWAVE_PWM_b, &auAMP_PWM_b));
        Modules.add(MOD_DCO_A, ModuleOscillator::create(MOD_DCO_A, "OSC A", ModuleOscillatorParameters(PARAMS_DCO_A), {&auDCO_V1a, &auDCO_V2a, &auDCO_V3a, &auDCO_V4a}));
        Modules.add(MOD_DCO_B, ModuleOscillator::create(MOD_DCO_B, "OSC B", ModuleOscillatorParameters(PARAMS_DCO_B), {&auDCO_v1b, &auDCO_v2b, &auDCO_v3b, &auDCO_v4b}));
        Modules.add(MOD_XMOD, ModuleXModulation::create(MOD_XMOD, "X-Mod", ModuleXModulationParamaters(PARAMS_XMOD)));
        Modules.add(MOD_RINGMOD, ModuleRingMod::create(MOD_RINGMOD, "Ring Mod", ModuleRingModParamaters(PARAMS_RINGMOD)));
        Modules.add(MOD_NOISE, ModuleNoise::create(MOD_NOISE, "Noise", ModuleNoiseParameters(PARAMS_NOISE)));
        Modules.add(MOD_WAVESHAPER, ModuleWaveShaper::create(MOD_WAVESHAPER, "wave shaper", ModuleWaveShaperParameters(PARAMS_SHAPER)));
        Modules.add(MOD_FILTER, ModuleFilterBlock::create(MOD_FILTER, "filter", ModuleFilterBlockParameters(PARAMS_FILTERBLOCK)));
        Modules.add(MOD_PARTMIXER, ModulePartMixer::create(MOD_PARTMIXER, "Part A/B Mix", ModulePartMixerParameters(PARAMS_PARTMIXER)));
        Modules.add(MOD_MIXER_MAIN, ModuleVoiceMixer::create(MOD_MIXER_MAIN, "Main Mix", ModuleVoiceMixerParameters(PARAMS_VOICEMIXER)));
    }

    uint32_t Synth::elapsed()
    {
        uint32_t now = millis();
        uint32_t result = now - _lastUpdate;
        _lastUpdate = now;
        return result;
    }

#pragma endregion

}
