#pragma once
#include "AUMapping.h"
#include "PSModule.h"
#include "PSParameterManager.h"

#define VOICES 4

#define PARAMS_VOICEMIXER (std::string[VOICES]){PARM_VOICE_GAIN0, PARM_VOICE_GAIN1, PARM_VOICE_GAIN2, PARM_VOICE_GAIN3}, \
                          (std::string[VOICES]){PARM_VOICE_PAN0, PARM_VOICE_PAN1, PARM_VOICE_PAN2, PARM_VOICE_PAN3},     \
                          PARM_MASTER_GAIN, PARM_MASTER_PAN

struct PSMStereoVoiceMixerParameters
{
    std::string voiceGain[VOICES];
    std::string voicePan[VOICES];
    std::string masterGain, masterPan;
    PSMStereoVoiceMixerParameters(
        const std::string voiceGain[VOICES],
        const std::string voicePan[VOICES],
        const std::string &masterGain,
        const std::string &masterPan) : masterGain(masterGain), masterPan(masterPan)
    {
        for (uint8_t i = 0; i < VOICES; i++)
        {
            this->voiceGain[i] = voiceGain[i];
            this->voicePan[i] = voicePan[i];
        }
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
        for (uint8_t i = 0; i < VOICES; i++)
        {
            _voiceGain[i] = addParameter(Parameters[p.voiceGain[i]]);
            _voicePan[i] = addParameter(Parameters[p.voicePan[i]]);
        }
        _masterGain = addParameter(Parameters[p.masterGain]);
        _masterPan = addParameter(Parameters[p.masterPan]);

        return this;
    }

    /**
     * @brief
     * Pans a stereo channel to the relevant position.
     * @param channel 4 channels : 0-3
     * @param position  L<<0.0 <<0.5>> 1.0>>R
     */
    void voicePan(uint8_t voice, float position)
    {
        if (voice >= 0 && voice < 4)
        {
            position = clampf(position, 0, 1.0);
            _voicePan[voice]->setValue(position);
        }
    }

    void getStereoGainLR(float gain, float pan, float &left, float &right)
    {
        // float gain = _voiceGain[voice]->getValue();
        // float pan = _voicePan[voice]->getValue();
        left = (1 - pan) * gain;
        right = (1 - left) * gain;
    }

    void voiceGain(uint8_t voice, float value)
    {
        if (voice >= 0 && voice < VOICES)
        {
            value = clampf(value, 0, 1.0);
            _voiceGain[voice]->setValue(value);
        }
    }

    void masterPan(float value) { _masterPan->setValue(clampf(value, 0, 1.0f)); }
    void masterGain(float value) { _masterGain->setValue(clampf(value, 0, 1.5f)); }

    // void setValue(const std::string &key, float value)
    // {
    //     if (PSParameter *p = getParameter(key))
    //         p->setValue(value);
    // }

    bool update() override
    {
        float left, right;

        // set mixer channel levels
        for (uint8_t voice = 0; voice < VOICES; voice++)
        {
            if (_voicePan[voice]->changed(true) || _voiceGain[voice]->changed(true))
            {
                getStereoGainLR(
                    _voiceGain[voice]->getValue(),
                    _voicePan[voice]->getValue(),
                    left, right);
                _leftMix->gain(voice, left);
                _rightMix->gain(voice, right);
            }
        }

        // set output amp levels
        if (_masterPan->changed(true) || _masterGain->changed(true))
        {            
            getStereoGainLR(_masterGain->getValue(), _masterPan->getValue(), left, right);
            _leftAmp->gain(left);
            _rightAmp->gain(right);            
        }
        return true;
    }

protected:
    PSParameter *_voiceGain[VOICES], *_voicePan[VOICES], *_masterGain, *_masterPan;

    AudioMixer4 *_leftMix, *_rightMix;
    AudioAmplifier *_leftAmp, *_rightAmp;
};