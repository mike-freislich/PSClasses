#pragma once
#include <string>
#include "PSModule.h"
#include "../model/PSParameter.h"

class PSMEnvelope : public PSModule
{
public:
    PSMEnvelope(const PSKeys &key, const std::string name) : PSModule(key, name)
    {
        addParameter((new PSParameter(PARM_ENV_ATTACK, "atk"))->setRange(0, 10000))->setTaper(PSParameter::TAPER::LOGARITHMIC); // PARM_ENV_ATTACK
        addParameter((new PSParameter(PARM_ENV_HOLD, "hld"))->setRange(0, 5000))->setTaper(PSParameter::TAPER::LOGARITHMIC);    // PARM_ENV_HOLD
        addParameter((new PSParameter(PARM_ENV_DECAY, "dec"))->setRange(0, 10000))->setTaper(PSParameter::TAPER::LOGARITHMIC);  // PARM_ENV_DECAY
        addParameter((new PSParameter(PARM_ENV_SUSTAIN, "sus"))->setRange(0, 1));                                               // PARM_ENV_SUSTAIN
        addParameter((new PSParameter(PARM_ENV_RELEASE, "rel"))->setRange(0, 5000))->setTaper(PSParameter::TAPER::LOGARITHMIC); // PARM_ENV_RELEASE
        addParameter((new PSParameter(PARM_ENV_AMOUNT, "amt"))->setRange(0, 1));                                                // PARM_ENV_AMOUNT
    }
    ~PSMEnvelope() override {}




    PSMEnvelope *setValues(float attack, float hold, float decay, float sustain, float release, float amount = 1.0f)
    {
        setValue(PARM_ENV_ATTACK, attack);
        setValue(PARM_ENV_HOLD, hold);
        setValue(PARM_ENV_DECAY, decay);
        setValue(PARM_ENV_SUSTAIN, sustain);
        setValue(PARM_ENV_RELEASE, release);
        setValue(PARM_ENV_AMOUNT, amount);

        return this;
    }

    PSMEnvelope *setValue(const PSKeys &key, float value)
    {
        getItem<PSParameter>(key)->setValue(value);
        return this;
    }

    float getValue(const PSKeys &key) { return getItem<PSParameter>(key)->getValue();}

    void attack(float value) { getItem<PSParameter>(PARM_ENV_ATTACK)->setValue(value); }
    float getAttack() { return getItem<PSParameter>(PARM_ENV_ATTACK)->getValue(); }

    void hold(float value) { getItem<PSParameter>(PARM_ENV_HOLD)->setValue(value); }
    float getHold() { return getItem<PSParameter>(PARM_ENV_HOLD)->getValue(); }

private:
};