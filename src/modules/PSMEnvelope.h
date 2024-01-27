#pragma once
#include "PSModule.h"
#include "PSParameterManager.h"

struct PSMEnvelopeParameters
{    
    PSK attack, hold, decay, sustain, release, amount;
    PSMEnvelopeParameters(PSK attack, PSK hold, PSK decay, PSK sustain, PSK release, PSK amount) 
        : attack(attack), hold(hold), decay(decay), sustain(sustain), release(release), amount(amount) {}
};

struct PSMEnvelopeValues
{
    float attack, hold, decay, sustain, release, amount;
};

class PSMEnvelope : public PSModule
{
public:
    PSMEnvelope(const PSK &key, const std::string name, const PSMEnvelopeParameters &ep) : PSModule(key, name) 
    {
        attachParameters(ep);
    }

    ~PSMEnvelope() override { items.clear(); }

    PSMEnvelope *attachParameters(const PSMEnvelopeParameters &ep)
    {
        _attack = addParameter(Parameters.byKey(ep.attack));
        _hold = addParameter(Parameters.byKey(ep.hold));
        _decay = addParameter(Parameters.byKey(ep.decay));
        _sustain = addParameter(Parameters.byKey(ep.sustain));
        _release = addParameter(Parameters.byKey(ep.release));
        _amount = addParameter(Parameters.byKey(ep.amount));        
        return this;
    }

    // PSMEnvelope *setValues(PSMEnvelopeValues &values)
    // {
    //     attack(values.attack);
    //     hold(values.hold);
    //     decay(values.decay);
    //     sustain(values.sustain);
    //     release(values.release);
    //     amount(values.amount);
    //     return this;
    // }

    PSMEnvelope *setValue(const PSK &key, float value)
    {
        this->getItem<PSParameter>(key)->setValue(value);        
        return this;
    }

    void attack(float value) { _attack->setValue(value); }
    void hold(float value) { _hold->setValue(value); }
    void decay(float value) { _decay->setValue(value); }
    void sustain(float value) { _sustain->setValue(value); }
    void release(float value) { _release->setValue(value); }
    void amount(float value) { _amount->setValue(value); }

    float getValue(const PSK &key) { return getItem<PSParameter>(key)->getValue(); }

    float getAttack() { return _attack->getValue(); }
    float getHold() { return _hold->getValue(); }
    float getDecay() { return _decay->getValue(); }
    float getSustain() { return _sustain->getValue(); }
    float getRelease() { return _release->getValue(); }
    float getAmount() { return _amount->getValue(); }

private:
    PSParameter *_attack, *_hold, *_decay, *_sustain, *_release, *_amount;
};