#pragma once

#include "PSComponent.h"
#include "PSParameter.h"

class PSCEnvelope : PSComponent
{
public:
    PSParameter *attack, *hold, *decay, *sustain, *release, *amount;
    PSCEnvelope()
    {
        attack = this->addParameter(new PSParameter("atk"));
        hold = this->addParameter(new PSParameter("hld"));
        decay = this->addParameter(new PSParameter("dec"));
        sustain = this->addParameter(new PSParameter("sus"));
        release = this->addParameter(new PSParameter("rel"));
        amount = this->addParameter(new PSParameter("amt"));
    }
    ~PSCEnvelope() {}

    void attachController(PSParameter *parameter, PSController *controller)
    {
        parameter->attachController(controller);
    }

    void setValues(float attack, float hold, float decay, float sustain, float release, float amount)
    {
        this->attack->setValue(attack);
        this->hold->setValue(hold);
        this->decay->setValue(decay);
        this->sustain->setValue(sustain);
        this->release->setValue(release);
        this->amount->setValue(amount);
    }

private:
};