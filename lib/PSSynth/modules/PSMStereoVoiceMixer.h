#pragma once
#include "AUMapping.h"
#include "PSModule.h"
#include "PSParameterManager.h"

#define PARAMS_MASTER PARM_MASTER_L1, PARM_MASTER_L2, PARM_MASTER_L3, PARM_MASTER_L4, \
                      PARM_MASTER_R1, PARM_MASTER_R2, PARM_MASTER_R3, PARM_MASTER_R4, \
                      PARM_MASTER_GAINL, PARM_MASTER_GAINR

struct PSMStereoVoiceMixerParameters
{
    std::string chanL1, chanL2, chanL3, chanL4, chanR1, chanR2, chanR3, chanR4, gainL, gainR;
    PSMStereoVoiceMixerParameters(
        const std::string &chanL1,
        const std::string &chanL2,
        const std::string &chanL3,
        const std::string &chanL4,
        const std::string &chanR1,
        const std::string &chanR2,
        const std::string &chanR3,
        const std::string &chanR4,
        const std::string &gainL,
        const std::string &gainR)
        : chanL1(chanL1),
          chanL2(chanL2),
          chanL3(chanL3),
          chanL4(chanL4),
          chanR1(chanR1),
          chanR2(chanR2),
          chanR3(chanR3),
          chanR4(chanR4),
          gainL(gainL),
          gainR(gainR)
    {
    }
};

class PSMStereoVoiceMixer : public PSModule
{
public:
    PSMStereoVoiceMixer()
    {
        _leftMix = &auMIXER_FINAL_L;
        _rightMix = &auMIXER_FINAL_R;
        _leftAmp = &auAMP_MASTER_GAIN_L;
        _rightAmp = &auAMP_MASTER_GAIN_R;
        addAudioUnit(_leftMix);
        addAudioUnit(_rightMix);
        addAudioUnit(_leftAmp);
        addAudioUnit(_rightAmp);
    }

    static PSMStereoVoiceMixer *create(const char *key, const char *displayName, const PSMStereoVoiceMixerParameters &smp)
    {
        PSMStereoVoiceMixer *newMod = PSModule::create<PSMStereoVoiceMixer>(key, displayName);
        newMod->attachParameters(smp);
        return newMod;
    }

    PSMStereoVoiceMixer *attachParameters(const PSMStereoVoiceMixerParameters &p)
    {
        _chanL[0] = addParameter(Parameters[p.chanL1]);
        _chanR[0] = addParameter(Parameters[p.chanR1]);
        _chanL[1] = addParameter(Parameters[p.chanL2]);
        _chanR[1] = addParameter(Parameters[p.chanR2]);
        _chanL[2] = addParameter(Parameters[p.chanL3]);
        _chanR[2] = addParameter(Parameters[p.chanR3]);
        _chanL[3] = addParameter(Parameters[p.chanL4]);
        _chanR[3] = addParameter(Parameters[p.chanR4]);
        _gainL = addParameter(Parameters[p.gainL]);
        _gainR = addParameter(Parameters[p.gainR]);
        return this;
    }

    /**
     * @brief
     * Pans a stereo channel to the relevant position.
     * @param channel 4 channels : 0-3
     * @param position  L<<0.0 <<0.5>> 1.0>>R
     */
    void pan(uint8_t channel, float position)
    {
        if (channel >= 0 && channel < 4)
        {
            position = clampf(position, 0, 1.0);
            float leftPos = 1.0f - position;
            float rightPos = 1.0f - leftPos;
            _chanL[channel]->setValue(leftPos);
            _chanR[channel]->setValue(rightPos);
        }
    }

    void setValue(const std::string &key, float value)
    {
        if (PSParameter *p = getParameter(key))
            p->setValue(value);
    }

    bool update() override
    {
        // set mixer channels
        for (uint i = 0; i < 4; i++)
        {
            if (_chanL[i]->changed(true))
                _leftMix->gain(i, _chanL[i]->getValue());
            if (_chanR[i]->changed(true))
                _rightMix->gain(i, _chanR[i]->getValue());
        }

        // set gain
        if (_gainL->changed(true))
            _leftAmp->gain(_gainL->getValue());
        if (_gainR->changed(true))
            _rightAmp->gain(_gainL->getValue());

        return true;
    }

protected:
    PSParameter *_chanL[4];
    PSParameter *_chanR[4];
    PSParameter *_gainL, *_gainR;
    AudioMixer4 *_leftMix, *_rightMix;
    AudioAmplifier *_leftAmp, *_rightAmp;
};