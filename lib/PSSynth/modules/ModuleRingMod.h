#pragma once
#include "Module.h"
#include "AUMapping.h"


#define PARAMS_RINGMOD PARM_RING_LEVEL, PARM_RING_FREQ, PARM_RING_SHAPE

namespace PS
{
    struct ModuleRingModParamaters
    {
        std::string level, freq, shape;
        ModuleRingModParamaters(const std::string &level, const std::string &freq, const std::string &shape)
            : level(level), freq(freq), shape(shape) {}
    };

    class ModuleRingMod : public Module
    {
    public:
        ModuleRingMod()
        {
            typeName = "ModuleRingMod";
            _wave = &auWAVE_RINGMOD;
        }
        ~ModuleRingMod() {}

        static ModuleRingMod *create(const char *key, const char *displayName, const ModuleRingModParamaters &p)
        {
            ModuleRingMod *newMod = Module::create<ModuleRingMod>(key, displayName);
            newMod->addParameters(p);
            return newMod;
        }

        void addParameters(const ModuleRingModParamaters &p)
        {
            _level = addParameter(Parameters[p.level]);
            _freq = addParameter(Parameters[p.freq]);
            _shape = addParameter(Parameters[p.shape]);            
        }

        bool update() override
        {
            bool result;
            if (_shape->changed(true))
            {
                _level->changed(true);
                _freq->changed(true);
                result &= updateUnits(_level, _freq, _shape, &AudioSynthWaveform::begin);
            }
            else
            {
                result &= updateUnit1(_wave, _level, &AudioSynthWaveform::amplitude);
                result &= updateUnit1(_wave, _freq, &AudioSynthWaveform::frequency);
            }
            return result;
        }

    protected:
        Parameter *_level, *_shape, *_freq;
        AudioSynthWaveform *_wave;
    };
}