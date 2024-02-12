#pragma once
#include "Module.h"
#include "AUMapping.h"


#define PARAMS_NOISE PARM_NOISE_LEVEL, PARM_NOISE_TYPE

namespace PS
{
    enum NoiseType {
        NOISE_WHITE,
        NOISE_PINK
    };
    struct ModuleNoiseParameters
    {
        std::string level, noiseType;
        ModuleNoiseParameters(const std::string &level, const std::string &noiseType)
            : level(level), noiseType(noiseType) {}
    };

    class ModuleNoise : public Module
    {
    public:
        ModuleNoise()
        {
            typeName = "ModuleNoise";
            _mixer = &auMIXER_NOISE;
        }
        ~ModuleNoise() {}

        static ModuleNoise *create(const char *key, const char *displayName, const ModuleNoiseParameters &p)
        {
            ModuleNoise *newMod = Module::create<ModuleNoise>(key, displayName);
            newMod->addParameters(p);
            return newMod;
        }

        ObjectType getType() override { return ObjectType::TModuleNoise; }

        void addParameters(const ModuleNoiseParameters &p)
        {
            _level = addParameter(Parameters[p.level]);
            _noiseType = addParameter(Parameters[p.noiseType]);                
        }

        bool update() override
        {
            bool result;
            if (_noiseType->changed(true) || _level->changed(true)) 
            {
                uint8_t t = _noiseType->getValue();
                float level = _level->getValue();
                if (t == NOISE_WHITE)
                {
                    _mixer->gain(NOISE_WHITE, level);
                    _mixer->gain(NOISE_PINK, 0);
                }
                else    // pink noise
                {
                    _mixer->gain(NOISE_WHITE, 0);
                    _mixer->gain(NOISE_PINK, level);
                }
                result = true;
            }
            return result;
        }

    protected:
        Parameter *_level, *_noiseType;
        AudioMixer4 *_mixer;        
    };
}