#pragma once
#include "AUMapping.h"
#include "PSModule.h"
#include "PSParameterManager.h"

// Envelope instance parameter mappings
#define EPARMS_PENVa PARM_PENVa_ATTACK, PARM_PENVa_HOLD, PARM_PENVa_DECAY, PARM_PENVa_SUSTAIN, PARM_PENVa_RELEASE, PARM_PENVa_AMOUNT
#define EPARMS_AENVa PARM_AENVa_ATTACK, PARM_AENVa_HOLD, PARM_AENVa_DECAY, PARM_AENVa_SUSTAIN, PARM_AENVa_RELEASE, PARM_AENVa_AMOUNT
#define EPARMS_FENVa PARM_FENVa_ATTACK, PARM_FENVa_HOLD, PARM_FENVa_DECAY, PARM_FENVa_SUSTAIN, PARM_FENVa_RELEASE, PARM_FENVa_AMOUNT
#define EPARMS_PENVb PARM_PENVb_ATTACK, PARM_PENVb_HOLD, PARM_PENVb_DECAY, PARM_PENVb_SUSTAIN, PARM_PENVb_RELEASE, PARM_PENVb_AMOUNT
#define EPARMS_AENVb PARM_AENVb_ATTACK, PARM_AENVb_HOLD, PARM_AENVb_DECAY, PARM_AENVb_SUSTAIN, PARM_AENVb_RELEASE, PARM_AENVb_AMOUNT
#define EPARMS_FENVb PARM_FENVb_ATTACK, PARM_FENVb_HOLD, PARM_FENVb_DECAY, PARM_FENVb_SUSTAIN, PARM_FENVb_RELEASE, PARM_FENVb_AMOUNT

struct PSMEnvelopeParameters
{
    std::string attack, hold, decay, sustain, release, amount;
    PSMEnvelopeParameters(std::string attack, std::string hold, std::string decay, std::string sustain, std::string release, std::string amount)
        : attack(attack), hold(hold), decay(decay), sustain(sustain), release(release), amount(amount) {}
};

// struct PSMEnvelopeValues
// {
//     float attack, hold, decay, sustain, release, amount;
// };

class PSMEnvelope : public PSModule
{
public:
    PSMEnvelope() : PSModule() {}
    ~PSMEnvelope() override { parms.clear(); }

    static PSMEnvelope *create(const char *key, const char *displayName, const PSMEnvelopeParameters &ep)
    {
        PSMEnvelope *newMod = PSModule::create<PSMEnvelope>(key, displayName);
        newMod->attachParameters(ep);
        return newMod;
    }

    // template <typename T>
    // T *getAudioUnit()
    // {
    //     for (auto au : audioUnits)
    //     {
    //         // TODO is there a different way to up-cast the from AudioStream to AudioUnit since AudioStream is not polymorphic
    //         if (T *audioUnit = dynamic_cast<T *>(au))
    //             return audioUnit;
    //     }
    //     std::cout << "Module has no audio unit attached" << std::endl;
    //     return nullptr; // throw std::out_of_range("Module has no audio unit attached\n");
    // }

    // AudioEffectEnvelope *envelope()
    // {
    //     _envelope = (_envelope) ? _envelope : getAudioUnit<AudioEffectEnvelope>();
    //     return _envelope;
    // }

    // AudioAmplifier *amplifier()
    // {
    //     _amp = (_amp) ? _amp : getAudioUnit<AudioAmplifier>();
    //     return _amp;
    // }

    PSMEnvelope *attachParameters(const PSMEnvelopeParameters &ep)
    {
        _attack = addParameter(Parameters[ep.attack]);
        _hold = addParameter(Parameters[ep.hold]);
        _decay = addParameter(Parameters[ep.decay]);
        _sustain = addParameter(Parameters[ep.sustain]);
        _release = addParameter(Parameters[ep.release]);
        _amount = addParameter(Parameters[ep.amount]);
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

    PSMEnvelope *setValue(const std::string &key, float value)
    {
        parms[key]->setValue(value);
        return this;
    }

    void attack(float value)
    {
        _attack->setValue(value);
        //envelope()->attack(value);
    }
    void hold(float value)
    {
        _hold->setValue(value);
        //envelope()->hold(value);
    }
    void decay(float value)
    {
        _decay->setValue(value);
        //envelope()->decay(value);
    }
    void sustain(float value)
    {
        _sustain->setValue(value);
        //envelope()->sustain(value);
    }
    void release(float value)
    {
        _release->setValue(value);
        //envelope()->release(value);
    }
    void amount(float value)
    {
        _amount->setValue(value);
        // if (amplifier())
        // {
        //     std::cout << "setting amp amount: " << value << std::endl;
        //     _amp->gain(value);
        // }
    }

    float getValue(const std::string &key) { return parms[key]->getValue(); }

    float getAttack() { return _attack->getValue(); }
    float getHold() { return _hold->getValue(); }
    float getDecay() { return _decay->getValue(); }
    float getSustain() { return _sustain->getValue(); }
    float getRelease() { return _release->getValue(); }
    float getAmount() { return _amount->getValue(); }

private:
    PSParameter *_attack, *_hold, *_decay, *_sustain, *_release, *_amount;
    AudioEffectEnvelope *_envelope;
    AudioAmplifier *_amp;
};