#pragma once
#include <string>
#include "PSModule.h"
#include "../model/PSParameter.h"
#include "../model/PSControllerMap.h"

class PSCEnvelope : public PSModule
{
public:
    PSCEnvelope(const PSKeys &key, const std::string name) : PSModule(key, name)
    {
        addParameter((new PSParameter(PARM_ENV_ATTACK, "atk"))->setRange(0, 10000))->setTaper(PSParameter::TAPER::LOGARITHMIC);                                                                        // PARM_ENV_ATTACK
        addParameter((new PSParameter(PARM_ENV_HOLD, "hld"))->setRange(0, 5000))->setTaper(PSParameter::TAPER::LOGARITHMIC);    // PARM_ENV_HOLD
        addParameter((new PSParameter(PARM_ENV_DECAY, "dec"))->setRange(0, 10000))->setTaper(PSParameter::TAPER::LOGARITHMIC);  // PARM_ENV_DECAY
        addParameter((new PSParameter(PARM_ENV_SUSTAIN, "sus"))->setRange(0, 1));                                               // PARM_ENV_SUSTAIN
        addParameter((new PSParameter(PARM_ENV_RELEASE, "rel"))->setRange(0, 5000))->setTaper(PSParameter::TAPER::LOGARITHMIC); // PARM_ENV_RELEASE
        addParameter((new PSParameter(PARM_ENV_AMOUNT, "amt"))->setRange(0, 1));                                                // PARM_ENV_AMOUNT
    }
    ~PSCEnvelope() {}

    void attachController(const PSKeys &key, PSController *controller)
    {
        PSParameter *p = getItem<PSParameter>(key);
        if (p)
        {
            printf("attaching controller %s to parameter %s\n", controller->name.c_str(), p->name.c_str());
            p->attachController(controller);
        }
        else
        {
            printf("unable to attach controller to null parameter\n");
        }
    }

    PSCEnvelope *attachControllers(const PSControllerMapVector &mappings)
    {
        printf("attaching %zu controllers\n", mappings.size());

        for (auto mapping : mappings)
            attachController(mapping.key, mapping.controller);

        return this;
    }

    PSCEnvelope *setValues(float attack, float hold, float decay, float sustain, float release, float amount = 1.0f)
    {
        setValue(PARM_ENV_ATTACK, attack);
        setValue(PARM_ENV_HOLD, hold);
        setValue(PARM_ENV_DECAY, decay);
        setValue(PARM_ENV_SUSTAIN, sustain);
        setValue(PARM_ENV_RELEASE, release);
        setValue(PARM_ENV_AMOUNT, amount);

        return this;
    }

    PSCEnvelope *setValue(const PSKeys &key, float value)
    {
        getItem<PSParameter>(key)->setValue(value);
        return this;
    }

    void attack(float value) { getItem<PSParameter>(PARM_ENV_ATTACK)->setValue(value); }
    float getAttack() { return getItem<PSParameter>(PARM_ENV_ATTACK)->getValue(); }

private:
};