#pragma once
#include "AUMapping.h"
#include "PSModule.h"
#include "PSParameterManager.h"

// Envelope instance parameter mappings
#define EPARMS_PENV PARM_PENV_ATTACK, PARM_PENV_HOLD, PARM_PENV_DECAY, PARM_PENV_SUSTAIN, PARM_PENV_RELEASE, PARM_PENV_AMOUNT, PARM_PENV_INVERT
#define EPARMS_AENV PARM_AENV_ATTACK, PARM_AENV_HOLD, PARM_AENV_DECAY, PARM_AENV_SUSTAIN, PARM_AENV_RELEASE, PARM_AENV_AMOUNT, PARM_AENV_INVERT
#define EPARMS_FENV PARM_FENV_ATTACK, PARM_FENV_HOLD, PARM_FENV_DECAY, PARM_FENV_SUSTAIN, PARM_FENV_RELEASE, PARM_FENV_AMOUNT, PARM_FENV_INVERT

struct PSMEnvelopeParameters
{
    std::string attack, hold, decay, sustain, release, amount, invert;
    PSMEnvelopeParameters(std::string attack, std::string hold, std::string decay, std::string sustain, std::string release, std::string amount, std::string invert)
        : attack(attack), hold(hold), decay(decay), sustain(sustain), release(release), amount(amount), invert(invert) {}
};

class PSMEnvelope : public PSModule
{
public:
    PSMEnvelope() : PSModule() {}
    ~PSMEnvelope() override { moduleParameters.clear(); }

    static PSMEnvelope *create(const char *key, const char *displayName, const PSMEnvelopeParameters &ep)
    {
        PSMEnvelope *newMod = PSModule::create<PSMEnvelope>(key, displayName);
        newMod->attachParameters(ep);
        return newMod;
    }

    PSMEnvelope *attachParameters(const PSMEnvelopeParameters &ep)
    {
        _attack = addParameter(Parameters[ep.attack]);
        _hold = addParameter(Parameters[ep.hold]);
        _decay = addParameter(Parameters[ep.decay]);
        _sustain = addParameter(Parameters[ep.sustain]);
        _release = addParameter(Parameters[ep.release]);
        _amount = addParameter(Parameters[ep.amount]);
        _invert = addParameter(Parameters[ep.invert]);
        return this;
    }

    PSMEnvelope *setValue(const std::string &key, float value)
    {
        moduleParameters[key]->setValue(value);
        return this;
    }

    float getValue(const std::string &key) { return moduleParameters[key]->getValue(); }

    float getAttack() { return _attack->getValue(); }
    float getHold() { return _hold->getValue(); }
    float getDecay() { return _decay->getValue(); }
    float getSustain() { return _sustain->getValue(); }
    float getRelease() { return _release->getValue(); }
    float getAmount() { return _amount->getValue(); }

    bool update() override
    {
        if (_attack->changed(true))
            for (auto i : audioUnits)
                if (AudioEffectEnvelope *e = dynamic_cast<AudioEffectEnvelope *>(i))
                    e->attack(_attack->getValue());

        if (_hold->changed(true))
            for (auto i : audioUnits)
                if (AudioEffectEnvelope *e = dynamic_cast<AudioEffectEnvelope *>(i))
                    e->hold(_hold->getValue());

        if (_decay->changed(true))
            for (auto i : audioUnits)
                if (AudioEffectEnvelope *e = dynamic_cast<AudioEffectEnvelope *>(i))
                    e->decay(_decay->getValue());

        if (_sustain->changed(true))
            for (auto i : audioUnits)
                if (AudioEffectEnvelope *e = dynamic_cast<AudioEffectEnvelope *>(i))
                    e->sustain(_sustain->getValue());

        if (_release->changed(true))
            for (auto i : audioUnits)
                if (AudioEffectEnvelope *e = dynamic_cast<AudioEffectEnvelope *>(i))
                    e->release(_release->getValue());

        if (_amount->changed(true))
            for (auto i : audioUnits)
                if (AudioSynthWaveformDc *e = dynamic_cast<AudioSynthWaveformDc *>(i))
                    auDC_AMPENV.amplitude(_amount->getValue() * invertMultiplier());

        return true;
    }

    int8_t invertMultiplier() { return (isInverted()) ? -1 : 1; }

private:
    PSParameter *_attack, *_hold, *_decay, *_sustain, *_release, *_amount, *_invert;
    bool isInverted() { return (Controllers.button(CTRL_BTN_Invert)->isPressed()); }
};