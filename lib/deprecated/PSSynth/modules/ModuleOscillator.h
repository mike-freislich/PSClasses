#pragma once
#include "Module.h"
#include "ParameterManager.h"

#define PARAMS_DCO_A PARM_DCO_A_AMP, PARM_DCO_A_FREQ, PARM_DCO_A_SHAPE, PARM_DCO_A_DETUNE
#define PARAMS_DCO_B PARM_DCO_B_AMP, PARM_DCO_B_FREQ, PARM_DCO_B_SHAPE, PARM_DCO_B_DETUNE

namespace PS
{
    struct ModuleOscillatorParameters
    {        
        std::string amp, shape, freq, detune;
        ModuleOscillatorParameters(
            const std::string &amp,
            const std::string &freq,
            const std::string &shape,
            const std::string &detune)
            : amp(amp), shape(shape), freq(freq), detune(detune)
        {
        }
    };

    class ModuleOscillator : public Module
    {
    public:
        ModuleOscillator() { typeName = "ModuleOscillator"; }
        ~ModuleOscillator() {}

        static ModuleOscillator *create(
            const char *key, const char *displayName,
            const ModuleOscillatorParameters &p,
            const std::vector<AudioSynthWaveformModulated *>& voices)
        {
            ModuleOscillator *newMod = Module::create<ModuleOscillator>(key, displayName);
            newMod->attachParameters(p);
            for (auto au : voices)
                newMod->addAudioUnit(au);
            return newMod;
        }

        ObjectType getType() override { return ObjectType::TModuleOscillator; }

        ModuleOscillator *attachParameters(const ModuleOscillatorParameters &p)
        {
            _amp = addParameter(Parameters[p.amp]);
            _freq = addParameter(Parameters[p.freq]);
            _shape = addParameter(Parameters[p.shape]);            
            _detune = addParameter(Parameters[p.detune]);
            return this;
        }

        bool update() override
        {            
            if (_shape->changed())
            {
                // update all parameters at once (and restart the wave generation)
                // TODO may require audio interrupts to halt for this
                updateUnits(_amp, _freq, _shape, &AudioSynthWaveformModulated::begin, 1.0f, _detune->getValue());
            }
            else
            {
                // shape didn't change so no need to restart wave generation
                if (_detune->changed(true) || _freq->changed())
                    updateUnits(_freq, &AudioSynthWaveformModulated::frequency, 1.0f, _detune->getValue());                
                updateUnits(_amp, &AudioSynthWaveformModulated::amplitude);                
            }
            return true;
        }

    private:
        Parameter *_amp, *_freq, *_shape, *_detune;
    };

}
