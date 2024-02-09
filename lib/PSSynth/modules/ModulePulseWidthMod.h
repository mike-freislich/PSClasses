#pragma once
#include "Module.h"
#include "AudioStub.h"
#include "AUMapping.h"

#define PARAMS_PWM_A PARM_PWM_A_SHAPE, PARM_PWM_A_FREQ, PARM_PWM_A_GAIN
#define PARAMS_PWM_B PARM_PWM_B_SHAPE, PARM_PWM_B_FREQ, PARM_PWM_B_GAIN

namespace PS
{
    struct ModulePulseWidthModParameters
    {
        std::string shape, freq, gain;
        ModulePulseWidthModParameters(
            const std::string &shape,
            const std::string &freq,
            const std::string &gain) : shape(shape), freq(freq), gain(gain) {}
    };

    class ModulePulseWidthMod : public PS::Module
    {
    public:
        ModulePulseWidthMod() : Module() { typeName = "ModulePulseWidthMod"; }

        static ModulePulseWidthMod *create(
            const char *key,
            const char *displayName,
            const ModulePulseWidthModParameters &smp,
            AudioSynthWaveform *lfo, AudioAmplifier *amp)
        {
            ModulePulseWidthMod *newMod = Module::create<ModulePulseWidthMod>(key, displayName);
            newMod
                ->attachParameters(smp)
                ->addAudioUnits(lfo, amp);
            return newMod;
        }

        bool update() override
        {
            updateUnit1(_lfo, _shape, &AudioSynthWaveform::begin);
            updateUnit1(_lfo, _freq, &AudioSynthWaveform::frequency);
            updateUnit1(_amp, _gain, &AudioAmplifier::gain);
            return true;
        }

    protected:
        Parameter *_freq, *_gain, *_shape;
        AudioAmplifier *_amp;
        AudioSynthWaveform *_lfo;

        ModulePulseWidthMod *attachParameters(const ModulePulseWidthModParameters &p)
        {
            _freq = addParameter(Parameters[p.freq]);
            _gain = addParameter(Parameters[p.gain]);
            _shape = addParameter(Parameters[p.shape]);
            return this;
        }

        ModulePulseWidthMod *addAudioUnits(AudioSynthWaveform *lfo, AudioAmplifier *amp)
        {
            _lfo = lfo;
            addAudioUnit(lfo);
            _amp = amp;
            addAudioUnit(amp);
            return this;
        }
    };

}