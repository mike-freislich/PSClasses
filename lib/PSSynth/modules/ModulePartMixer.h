#pragma once
#include "Module.h"
#include "AUMapping.h"

#define PARAMS_PARTMIXER PARM_PAN_AB

namespace PS
{
    struct ModulePartMixerParameters : ModuleParametersBase
    {
        std::string pan;
        ModulePartMixerParameters(const std::string &pan) : pan(pan) {}
    };

    class ModulePartMixer : public Module
    {
    public:
        ModulePartMixer()
        {
            typeName = "ModulePartMixer";
            addAudioUnits({&auMIXER_PRESHAPE_V1, &auMIXER_PRESHAPE_V2,
                           &auMIXER_PRESHAPE_V3, &auMIXER_PRESHAPE_V4});
        }
        ~ModulePartMixer() {}

        static ModulePartMixer *create(const char *key, const char *displayName, const ModulePartMixerParameters &p)
        {
            ModulePartMixer *newMod = Module::create<ModulePartMixer>(key, displayName);
            newMod->addParameters(p);
            return newMod;
        }

        ObjectType getType() override { return ObjectType::TModulePartMixer; }

        void addParameters(const ModulePartMixerParameters &p)
        {
            _pan = addParameter(Parameters[p.pan]);
        }

        bool update() override
        {
            bool result;
            if (_pan->changed(true))
            {            
                float pan = _pan->getValue();
                for (auto m : _mixers)
                {
                    float a, b;
                    a = 1 - pan;
                    b = 1 - a;
                    m->gain(0, a);
                    m->gain(1, b);
                }
                result = true;
            }
            return result;
        }

    protected:
        Parameter *_pan;
        AudioMixer4 *_mixers[VOICES];
    };
}