#pragma once
#include "Module.h"
#include "AUMapping.h"

#define PARAMS_SHAPER PARM_SHAPER_PREGAIN, PARM_SHAPER_SHAPE, PARM_SHAPER_BYPASS

namespace PS
{
    struct ModuleWaveShaperParameters
    {
        std::string preGain, shape, bypass;
        ModuleWaveShaperParameters(const std::string &preGain, const std::string &shape, const std::string &bypass)
            : preGain(preGain), shape(shape), bypass(bypass) {}
    };

    class ModuleWaveShaper : public Module
    {
    public:
        enum BypassChannels
        {
            bypassThru = 0,
            bypassShaped = 1
        };
        ModuleWaveShaper()
        {
            typeName = "ModuleWaveShaper";
            _mixers = {&auMIXER_SHAPER_BYPASS_V1, &auMIXER_SHAPER_BYPASS_V2, &auMIXER_SHAPER_BYPASS_V3, &auMIXER_SHAPER_BYPASS_V4};
            _shapers = {&auSHAPER_V1, &auSHAPER_V2, &auSHAPER_V3, &auSHAPER_V4};
            _amps = {&auAMP_SHAPER_PREAMP_V1, &auAMP_SHAPER_PREAMP_V2, &auAMP_SHAPER_PREAMP_V3, &auAMP_SHAPER_PREAMP_V4};
        }
        ~ModuleWaveShaper() {}

        static ModuleWaveShaper *create(const char *key, const char *displayName, const ModuleWaveShaperParameters &p)
        {
            ModuleWaveShaper *newMod = Module::create<ModuleWaveShaper>(key, displayName);
            newMod->addParameters(p);
            return newMod;
        }
        ObjectType getType() override { return ObjectType::TModuleWaveShaper; }

        void addParameters(const ModuleWaveShaperParameters &p)
        {
            _preGain = addParameter(Parameters[p.preGain]);
            _shape = addParameter(Parameters[p.shape]);
            _bypass = addParameter(Parameters[p.bypass]);
        }

        bool update() override
        {
            bool result;
            if (_shape->changed(true))
            {
                for (auto shaper : _shapers)
                {
                    //TODO switch the shape data of the shaper                     
                    // shaper->shape(_shaper.getValue(), data);
                }
                result = true;
            }

            if (_preGain->changed(true))
            {
                for (auto amp : _amps)
                    amp->gain(_preGain->getValue());
                result = true;
            }

            if (_bypass->changed(true))
            {
                float bypass = _bypass->getValue();
                for (auto mixer : _mixers)
                {
                    if (bypass)
                    {
                        mixer->gain(bypassThru, 1);
                        mixer->gain(bypassShaped, 0);
                    }
                    else
                    {
                        mixer->gain(bypassThru, 0);
                        mixer->gain(bypassShaped, 1);
                    }
                }
                result = true;
            }        
            return result;
        }

    protected:
        Parameter *_preGain, *_shape, *_bypass;
        std::vector<AudioAmplifier *> _amps;
        std::vector<AudioEffectWaveshaper *> _shapers;
        std::vector<AudioMixer4 *> _mixers;
    };
}