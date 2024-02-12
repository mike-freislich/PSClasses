#pragma once
#include "Module.h"
#include "AUMapping.h"

#define PARAMS_XMOD PARM_XMOD_AMOUNT

namespace PS
{
    struct ModuleXModulationParamaters
    {
        std::string xmodAmount;
        ModuleXModulationParamaters(const std::string &xmodAmount) : xmodAmount(xmodAmount) {}
    };

    class ModuleXModulation : public Module
    {
    public:
        ModuleXModulation()
        {
            typeName = "ModuleXModulation";
            _xmodA = &auDC_XMOD_a;
            _xmodB = &auDC_XMOD_b;
        }
        ~ModuleXModulation() {}

        static ModuleXModulation *create(const char *key, const char *name, const ModuleXModulationParamaters &p)
        {
            ModuleXModulation *newMod = Module::create<ModuleXModulation>(key, name);
            newMod->addParameters(p);
            return newMod;
        }

        ObjectType getType() override { return ObjectType::TModuleXModulation; }

        void addParameters(const ModuleXModulationParamaters &p)
        {
             _xmodAmount = addParameter(Parameters[p.xmodAmount]); 
        }

        bool update() override
        {
            if (_xmodAmount->changed(true))
            {   
                // pot centre = no xmod.... pot left = apply a -> b ... pot right = apply b -> a
                float pan = _xmodAmount->getValue();
                _xmodA->amplitude(pan <= 0.4 ? pan * 2.5 : 0);
                _xmodB->amplitude(pan >= 0.6 ? (pan-0.6) * 2.5 : 0);
            }
            return true;
        }

    protected:
        Parameter *_xmodAmount;
        AudioSynthWaveformDc *_xmodA, *_xmodB;
    };
}