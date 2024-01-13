#pragma once

#include "PSComponent.h"
#include "PSParameter.h"

#define PARM_ENV_ATTACK 0
#define PARM_ENV_HOLD 1
#define PARM_ENV_DECAY 2
#define PARM_ENV_SUSTAIN 3
#define PARM_ENV_RELEASE 4
#define PARM_ENV_AMOUNT 5

class PSCEnvelope : public PSComponent
{
public:
    PSCEnvelope(string key) : PSComponent(key)
    {
        addParameter((new PSParameter("atk"))->setRange(0, 10000))->setTaper(PSParameter::TAPER::LOGARITHMIC); // PARM_ENV_ATTACK
        addParameter((new PSParameter("hld"))->setRange(0, 5000))->setTaper(PSParameter::TAPER::LOGARITHMIC);  // PARM_ENV_HOLD
        addParameter((new PSParameter("dec"))->setRange(0, 10000))->setTaper(PSParameter::TAPER::LOGARITHMIC); // PARM_ENV_DECAY
        addParameter((new PSParameter("sus"))->setRange(0, 1));                                                // PARM_ENV_SUSTAIN
        addParameter((new PSParameter("rel"))->setRange(0, 5000))->setTaper(PSParameter::TAPER::LOGARITHMIC);  // PARM_ENV_RELEASE
        addParameter((new PSParameter("amt"))->setRange(0, 1));                                                // PARM_ENV_AMOUNT
    }
    ~PSCEnvelope() {}

    void attachController(uint8_t parmIndex, PSController *controller)
    {
        values[parmIndex]->attachController(controller);
    }

    void setValues(float attack, float hold, float decay, float sustain, float release, float amount = 1.0f)
    {
        setValue(PARM_ENV_ATTACK, attack);
        setValue(PARM_ENV_HOLD, hold);
        setValue(PARM_ENV_DECAY, decay);
        setValue(PARM_ENV_SUSTAIN, sustain);
        setValue(PARM_ENV_RELEASE, release);
        setValue(PARM_ENV_AMOUNT, amount);
    }

    void setValue(uint8_t parmIndex, float value)
    {
        values[parmIndex]->setValue(value);
    }

    void attack(float value) { values[PARM_ENV_ATTACK]->setValue(value); }
    float getAttack() { return values[PARM_ENV_ATTACK]->getValue(); }

private:
};