#pragma once
#include "AUMapping.h"
#include "PSModule.h"
#include "PSParameterManager.h"

// Envelope instance parameter mappings
#define EPARMS_PENV PARM_PENV_ATTACK, PARM_PENV_HOLD, PARM_PENV_DECAY, PARM_PENV_SUSTAIN, PARM_PENV_RELEASE, PARM_PENV_AMOUNT, PARM_PENV_INVERT, PARM_PLFO_SHAPE, PARM_PLFO_FREQ, PARM_PLFO_AMOUNT, PARM_PITCH_BEND
#define EPARMS_AENV PARM_AENV_ATTACK, PARM_AENV_HOLD, PARM_AENV_DECAY, PARM_AENV_SUSTAIN, PARM_AENV_RELEASE, PARM_AENV_AMOUNT, PARM_AENV_INVERT, PARM_ALFO_SHAPE, PARM_ALFO_FREQ, PARM_ALFO_AMOUNT, PARM_AMP_BEND
#define EPARMS_FENV PARM_FENV_ATTACK, PARM_FENV_HOLD, PARM_FENV_DECAY, PARM_FENV_SUSTAIN, PARM_FENV_RELEASE, PARM_FENV_AMOUNT, PARM_FENV_INVERT, PARM_FLFO_SHAPE, PARM_FLFO_FREQ, PARM_FLFO_AMOUNT, PARM_FILTER_BEND

// #define PARMS_LFO_
// struct LFOParameters
// {
//     std::string lfoShape, lfoFreq, lfoAmplitude;
//     LFOParameters(
//         const std::string &lfoShape,
//         const std::string &lfoFreq,
//         const std::string &lfoAmplitude)
//         : lfoShape(lfoShape), lfoFreq(lfoFreq), lfoAmplitude(lfoAmplitude)
//         {}
// };

struct PSMEnvelopeParameters
{
    std::string attack, hold, decay, sustain, release, amount, invert, lfoShape, lfoFreq, lfoAmplitude, bend;
    PSMEnvelopeParameters(
        const std::string &attack,
        const std::string &hold,
        const std::string &decay,
        const std::string &sustain,
        const std::string &release,
        const std::string &amount,
        const std::string &invert,
        const std::string &lfoShape,
        const std::string &lfoFreq,
        const std::string &lfoAmplitude,
        const std::string &bend)
        : attack(attack),
          hold(hold),
          decay(decay),
          sustain(sustain),
          release(release),
          amount(amount),
          invert(invert),
          lfoShape(lfoShape),
          lfoFreq(lfoFreq),
          lfoAmplitude(lfoAmplitude),
          bend(bend)
    {
    }
};

class PSMEnvModulator : public PSModule
{
private:
    PSParameter *_attack, *_hold, *_decay, *_sustain, *_release, *_amount, *_invert, *_lfoShape, *_lfoFreq, *_lfoAmplitude, *_bend;
    AudioSynthWaveformDc *_bendUnit, *_amountUnit;
    AudioSynthWaveformModulated *_lfoUnit;
    bool isInverted() { return (Controllers.button(CTRL_BTN_Invert)->isPressed()); }

public:
    PSMEnvModulator() : PSModule() {}
    ~PSMEnvModulator() override { moduleParameters.clear(); }

    static PSMEnvModulator *create(const char *key, const char *displayName,
                                   const PSMEnvelopeParameters &ep,
                                   AudioSynthWaveformModulated *lfoUnit,
                                   AudioSynthWaveformDc *amountDC,
                                   AudioSynthWaveformDc *bendDC)
    {
        PSMEnvModulator *newMod = PSModule::create<PSMEnvModulator>(key, displayName);
        newMod->attachParameters(ep);
        newMod->addExtraUnits(lfoUnit, bendDC, amountDC);
        return newMod;
    }

    PSMEnvModulator *attachParameters(const PSMEnvelopeParameters &ep)
    {
        _attack = addParameter(Parameters[ep.attack]);
        _hold = addParameter(Parameters[ep.hold]);
        _decay = addParameter(Parameters[ep.decay]);
        _sustain = addParameter(Parameters[ep.sustain]);
        _release = addParameter(Parameters[ep.release]);
        _amount = addParameter(Parameters[ep.amount]);
        _invert = addParameter(Parameters[ep.invert]);
        _lfoShape = addParameter(Parameters[ep.lfoShape]);
        _lfoFreq = addParameter(Parameters[ep.lfoFreq]);
        _lfoAmplitude = addParameter(Parameters[ep.lfoAmplitude]);
        _bend = addParameter(Parameters[ep.bend]);
        return this;
    }

    PSMEnvModulator *setValue(const std::string &key, float value)
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
    float getLFOShape() { return _lfoShape->getValue(); }
    float getLFOAmplitude() { return _lfoAmplitude->getValue(); }
    float getLFOFreq() { return _lfoFreq->getValue(); }

    bool update() override
    {
        updateUnits(_attack, &AudioEffectEnvelope::attack);
        updateUnits(_hold, &AudioEffectEnvelope::hold);
        updateUnits(_decay, &AudioEffectEnvelope::decay);
        updateUnits(_sustain, &AudioEffectEnvelope::sustain);
        updateUnits(_release, &AudioEffectEnvelope::release);

        updateUnit1(_amountUnit, _amount, &AudioSynthWaveformDc::amplitude, invertMultiplier());
        updateUnit1(_bendUnit, _bend, &AudioSynthWaveformDc::amplitude);

        if (!_lfoShape->changed())
        {
            updateUnit1(_lfoUnit, _lfoAmplitude, &AudioSynthWaveformModulated::amplitude);
            updateUnit1(_lfoUnit, _lfoFreq, &AudioSynthWaveformModulated::frequency);
        }
        else
            updateUnits<AudioSynthWaveformModulated>(_lfoAmplitude, _lfoFreq, _lfoShape, &AudioSynthWaveformModulated::begin);

        return true;
    }

    float invertMultiplier() { return (isInverted()) ? -1 : 1; }

protected:
    void addExtraUnits(AudioSynthWaveformModulated *lfo, AudioSynthWaveformDc *bend, AudioSynthWaveformDc *amount)
    {
        _bendUnit = bend;
        _amountUnit = amount;
        _lfoUnit = lfo;
    }
};