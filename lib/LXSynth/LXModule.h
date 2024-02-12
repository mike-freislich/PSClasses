#pragma once
#include "CollectionLiteItem.h"
#include "ModKeys.h"
#include "LXParameterList.h"
#include "AUMapping.h"

class LXModule : public CollectionLiteItem<ModKeys>
{
public:
    LXModule(ModKeys key) : CollectionLiteItem(key) {}

    virtual ItemType getType() override { return ItemType::TLXModule; }

    template <typename ModuleType>
    ModuleType *attachParameters(const std::vector<ParmKeys> &parmKeys)
    {
        _parameters.clear();
        for (auto pkey : parmKeys)
        {
            printf("Module: %s -> Parameter : %s\n", this->typeName(), parmKey_cstr(pkey));
            _parameters.push_back(Parameters[pkey]);
        }
        afterAttachParameters();
        return (ModuleType *)this;
    }

    virtual void afterAttachParameters() {}

    LXModule *attachAudioUnits(const std::vector<AudioStream *> &audioUnits)
    {
        _audioUnits = audioUnits;
        return this;
    }

    LXParameter *findParameter(ParmKeys key)
    {
        for (auto &p : _parameters)
        {
            if (p->key == key)
                return p;
        }
        return nullptr; // not found
    }

protected:
    std::vector<LXParameter *> _parameters;
    std::vector<AudioStream *> _audioUnits;
};

class LXEnvModulatorBank : public LXModule
{
public:
    LXEnvModulatorBank(ModKeys key) : LXModule(key) {}
    ItemType getType() override { return ItemType::TLXModulatorBank; }

    LXEnvModulatorBank *attachEnvelopes(const std::vector<AudioEffectEnvelope *> &envelopes)
    {
        _envelopes = envelopes;
        return this;
    }
    LXEnvModulatorBank *attachAmountDC(AudioSynthWaveformDc *amountDC)
    {
        _amountDC = amountDC;
        return this;
    }
    LXEnvModulatorBank *attachBendDC(AudioSynthWaveformDc *bendDC)
    {
        _bendDC = bendDC;
        return this;
    }
    LXEnvModulatorBank *attachLFOWave(AudioSynthWaveformModulated *lfoWave)
    {
        _lfoWave = lfoWave;
        return this;
    }

    void update() override
    {
        // Envelope Amount / Invert
        if (_parameters[amount]->changed(true) || _parameters[invert]->changed(true))
        {
            int8_t inverMultiplier = _parameters[ModBankParamIndex::invert]->getValue() ? -1 : 1;
            _amountDC->amplitude(_parameters[amount]->getValue() * inverMultiplier);
        }

        // Envelope ADHSR
        if (LXParameter *p = _parameters[ModBankParamIndex::invert])
            if (p->changed(true))
                _amountDC->amplitude(p->getValue());

        if (_parameters[ModBankParamIndex::attack]->changed(true))
            for (auto e : _envelopes)
                e->attack(_parameters[ModBankParamIndex::attack]->getValue());

        if (_parameters[ModBankParamIndex::decay]->changed(true))
            for (auto e : _envelopes)
                e->decay(_parameters[ModBankParamIndex::decay]->getValue());

        if (_parameters[ModBankParamIndex::hold]->changed(true))
            for (auto e : _envelopes)
                e->hold(_parameters[ModBankParamIndex::hold]->getValue());

        if (_parameters[ModBankParamIndex::sustain]->changed(true))
            for (auto e : _envelopes)
                e->sustain(_parameters[ModBankParamIndex::sustain]->getValue());

        if (_parameters[ModBankParamIndex::release]->changed(true))
            for (auto e : _envelopes)
                e->release(_parameters[ModBankParamIndex::release]->getValue());

        // Bend
        if (_parameters[bend]->changed(true))
            if (_bendDC) // optional
                _bendDC->amplitude(_parameters[bend]->getValue());

        // LFO
        if (_parameters[lfo_shape]->changed(true))
        {
            _parameters[lfo_amount]->changed(true);
            _parameters[lfo_freq]->changed(true);
            _lfoWave->begin(
                _parameters[lfo_amount]->getValue(),
                _parameters[lfo_freq]->getValue(),
                _parameters[lfo_shape]->getValue());
        }
        else
        {
            if (_parameters[lfo_amount]->changed(true))
                _lfoWave->amplitude(_parameters[lfo_amount]->getValue());
            if (_parameters[lfo_freq]->changed(true))
                _lfoWave->frequency(_parameters[lfo_freq]->getValue());
        }
    }

private:
    enum ModBankParamIndex
    {
        attack,
        decay,
        hold,
        sustain,
        release,
        amount,
        invert,
        bend,
        lfo_amount,
        lfo_freq,
        lfo_shape
    };
    std::vector<AudioEffectEnvelope *> _envelopes;
    AudioSynthWaveformDc *_amountDC, *_bendDC;
    AudioSynthWaveformModulated *_lfoWave;
};

class LXFilterBank : public LXModule
{
public:
    LXFilterBank(ModKeys key) : LXModule(key)
    {
        _filtersLadder = {&auFILTER_LADDER_V1, &auFILTER_LADDER_V2, &auFILTER_LADDER_V3, &auFILTER_LADDER_V4};
        _filtersSV = {&auFILTER_SV_V1, &auFILTER_SV_V2, &auFILTER_SV_V3, &auFILTER_SV_V4};
        _amps = {&auAMP_POST_FILTER_V1, &auAMP_POST_FILTER_V2, &auAMP_POST_FILTER_V3, &auAMP_POST_FILTER_V4};
        _mixers = {&auMIXER_FILTER_BLOCK_V1, &auMIXER_FILTER_BLOCK_V2, &auMIXER_FILTER_BLOCK_V3, &auMIXER_FILTER_BLOCK_V4};

        _filterType = Parameters[filter_type];
        _filterFreq = Parameters[filter_freq];
        _filterRes = Parameters[filter_res];
        _filterOctave = Parameters[filter_octaves];
        _filterPostGain = Parameters[filter_postgain];
    }

    ItemType getType() override { return ItemType::TLXFilterBank; }

    void update() override
    {
        // TODO update the AudioUnits
    }

private:
    LXParameter *_filterRes, *_filterFreq, *_filterOctave, *_filterType, *_filterPostGain;
    std::vector<AudioAmplifier *> _amps;
    std::vector<AudioMixer4 *> _mixers;
    std::vector<AudioFilterStateVariable *> _filtersSV;
    std::vector<AudioFilterLadder *> _filtersLadder;
};

class LXPulseWidthMod : public LXModule
{
public:
    LXPulseWidthMod(ModKeys key) : LXModule(key) {}

    ItemType getType() override { return ItemType::TLXPulseWidthMod; }

    LXPulseWidthMod *attachPWMWave(AudioSynthWaveform *wave)
    {
        _wave = wave;
        return this;
    }

    LXPulseWidthMod *attachAmp(AudioAmplifier *amp)
    {
        _amp = amp;
        return this;
    }

    void update() override
    {
        if (_parameters[shape]->changed(true))
        {
            _parameters[gain]->changed(true);
            _parameters[freq]->changed(true);
            _wave->begin(
                _parameters[gain]->getValue(),
                _parameters[freq]->getValue(),
                _parameters[shape]->getValue());
        }
        else
        {
            if (_parameters[gain]->changed(true))
                _wave->amplitude(_parameters[gain]->getValue());
            if (_parameters[freq]->changed(true))
                _wave->frequency(_parameters[freq]->getValue());
        }
    }

private:
    enum PWMParamIndex
    {
        freq,
        gain,
        shape
    };
    AudioSynthWaveform *_wave;
    AudioAmplifier *_amp;
};

class LXCrossModulation : public LXModule
{
public:
    LXCrossModulation(ModKeys key) : LXModule(key) { _xmodAmount = Parameters[xmod_amount]; }
    ItemType getType() override { return ItemType::TLXCrossModulation; }

    void update() override
    {
        if (_xmodAmount->changed(true))
        {
            // pot centre = no xmod.... pot left = apply a -> b ... pot right = apply b -> a
            float pan = _xmodAmount->getValue();
            auDC_XMOD_a.amplitude(pan <= 0.4 ? pan * 2.5 : 0);
            auDC_XMOD_b.amplitude(pan >= 0.6 ? (pan - 0.6) * 2.5 : 0);
        }
    }

private:
    LXParameter *_xmodAmount;
};

class LXRingModulation : public LXModule
{
public:
    LXRingModulation(ModKeys key) : LXModule(key)
    {
        _ringFreq = Parameters[ring_freq];
        _ringLevel = Parameters[ring_level];
        _ringShape = Parameters[ring_shape];
    }
    ItemType getType() override { return ItemType::TLXRingModulation; }

    void update() override
    {
        if (_ringShape->changed(true))
        {
            _ringFreq->changed(true);
            _ringLevel->changed(true);
            auWAVE_RINGMOD.begin(_ringLevel->getValue(), _ringFreq->getValue(), _ringShape->getValue());
        }
        else
        {
            if (_ringFreq->changed(true))
                auWAVE_RINGMOD.frequency(_ringFreq->getValue());
            if (_ringLevel->changed(true))
                auWAVE_RINGMOD.amplitude(_ringLevel->getValue());
        }
    }

private:
    LXParameter *_ringFreq, *_ringLevel, *_ringShape;
};

class LXNoiseGen : public LXModule
{
public:
    LXNoiseGen(ModKeys key) : LXModule(key)
    {
        _noiseType = Parameters[noise_type];
        _noiseLevel = Parameters[noise_level];
    }
    ItemType getType() override { return ItemType::TLXNoiseGen; }

    void update() override
    {
        if (_noiseType->changed(true) || _noiseLevel->changed(true))
        {
            uint8_t t = _noiseType->getValue();
            float level = _noiseLevel->getValue();
            if (t == NOISE_WHITE)
            {
                auMIXER_NOISE.gain(NOISE_WHITE, level);
                auMIXER_NOISE.gain(NOISE_PINK, 0);
            }
            else // pink noise
            {
                auMIXER_NOISE.gain(NOISE_WHITE, 0);
                auMIXER_NOISE.gain(NOISE_PINK, level);
            }
        }
    }

private:
    enum NoiseType
    {
        NOISE_WHITE,
        NOISE_PINK
    };
    LXParameter *_noiseType, *_noiseLevel;
};

class LXPartMixer : public LXModule
{
public:
    LXPartMixer(ModKeys key) : LXModule(key)
    {
        _partPan = Parameters[ParmKeys::partpan_ab];
        attachAudioUnits({&auMIXER_PRESHAPE_V1, &auMIXER_PRESHAPE_V2, &auMIXER_PRESHAPE_V3, &auMIXER_PRESHAPE_V4});
    }
    ItemType getType() override { return ItemType::TLXPartMixer; }

    void update() override
    {
        if (_partPan->changed(true))
        {
            float pan = _partPan->getValue();
            for (auto m : _audioUnits)
            {
                AudioMixer4 *mixer = static_cast<AudioMixer4 *>(m);
                float a, b;
                a = 1 - pan;
                b = 1 - a;
                mixer->gain(0, a);
                mixer->gain(1, b);
            }
        }
    }

private:
    LXParameter *_partPan;
};

class LXWaveShaper : public LXModule
{
public:
    LXWaveShaper(ModKeys key) : LXModule(key)
    {
        _bypass = Parameters[shaper_bypass];
        _curve = Parameters[shaper_curve];
        _pregain = Parameters[shaper_pregain];
        _shapers = {&auSHAPER_V1, &auSHAPER_V2, &auSHAPER_V3, &auSHAPER_V4};
        _amps = {&auAMP_SHAPER_PREAMP_V1, &auAMP_SHAPER_PREAMP_V2, &auAMP_SHAPER_PREAMP_V3, &auAMP_SHAPER_PREAMP_V4};
        _mixers = {&auMIXER_SHAPER_BYPASS_V1, &auMIXER_SHAPER_BYPASS_V2, &auMIXER_SHAPER_BYPASS_V3, &auMIXER_SHAPER_BYPASS_V4};
    }
    ItemType getType() override { return ItemType::TLXWaveShaper; }

    void update() override
    {
        if (_curve->changed(true))
        {
            // for (auto shaper : _shapers)
            // {
            //     //TODO switch the shape data of the shaper
            //     // shaper->shape(_shaper.getValue(), data);
            // }
        }
        if (_pregain->changed(true))
            for (auto amp : _amps)
                amp->gain(_pregain->getValue());

        if (_bypass->changed(true))
        {
            float bypass = _bypass->getValue();
            for (auto mixer : _mixers)
            {
                if (bypass)
                {
                    mixer->gain(bypassThru, 1);
                    mixer->gain(bypassShaped, 0);
                }
                else
                {
                    mixer->gain(bypassThru, 0);
                    mixer->gain(bypassShaped, 1);
                }
            }
        }
    }

private:
    enum BypassChannels
    {
        bypassThru = 0,
        bypassShaped = 1
    };
    LXParameter *_bypass, *_curve, *_pregain;
    std::vector<AudioEffectWaveshaper *> _shapers;
    std::vector<AudioAmplifier *> _amps;
    std::vector<AudioMixer4 *> _mixers;
};

class LXOscillator : public LXModule
{
public:
    LXOscillator(ModKeys key) : LXModule(key) {}
    ItemType getType() override { return ItemType::TLXOscillator; }

    void afterAttachParameters() override
    {
        _amp = _parameters[0];
        _detune = _parameters[1];
        _freq = _parameters[2];
        _shape = _parameters[3];
    }

    void update() override
    {
        if (_shape->changed(true))
        {
            _amp->changed(true);
            _detune->changed(true);
            _freq->changed(true);
            for (auto au : _audioUnits)
            {
                AudioSynthWaveformModulated *wave = static_cast<AudioSynthWaveformModulated *>(au);
                // TODO may require audio interrupts to halt for this
                wave->begin(_amp->getValue(), _freq->getValue() + _detune->getValue(), _shape->getValue());
            }
        }
        else
        {
            if (_detune->changed(true) || _freq->changed(true))
            {
                float freq = _freq->getValue() + _detune->getValue();
                for (auto au : _audioUnits)
                {
                    AudioSynthWaveformModulated *wave = static_cast<AudioSynthWaveformModulated *>(au);
                    wave->frequency(freq);
                }
            }
            if (_amp->changed(true))
            {
                for (auto au : _audioUnits)
                {
                    AudioSynthWaveformModulated *wave = static_cast<AudioSynthWaveformModulated *>(au);
                    wave->frequency(_amp->getValue());
                }
            }
        }
    }

private:
    LXParameter *_amp, *_detune, *_freq, *_shape;
};

class LXVoiceMixer : public LXModule
{
public:
    LXVoiceMixer(ModKeys key) : LXModule(key)
    {
        _voiceGains = {Parameters[voice_gain0], Parameters[voice_gain1], Parameters[voice_gain2], Parameters[voice_gain3]};
        _voicePans = {Parameters[voice_pan0], Parameters[voice_pan1], Parameters[voice_pan2], Parameters[voice_pan3]};
        _masterGain = Parameters[master_gain];
        _masterPan = Parameters[master_pan];
    }
    ItemType getType() override { return ItemType::TLXVoiceMixer; }

    void getStereoGainLR(float gain, float pan, float &left, float &right)
    {
        left = (1 - pan) * gain;
        right = (1 - left) * gain;
    }

    float getVoicePan(uint8_t voice)
    {
        voice = clampf<uint8_t>(voice, 0, _voicePans.size());
        return _voicePans[voice]->getValue();
    }

    float getVoiceGain(uint8_t voice)
    {
        voice = clampf<uint8_t>(voice, 0, _voiceGains.size());
        return _voiceGains[voice]->getValue();
    }

    float getMasterPan() { return _masterPan->getValue(); }
    float getMasterGain() { return _masterGain->getValue(); }

    /**
     * @brief
     * Pans a stereo channel to the relevant position.
     * @param channel 4 channels : 0-3
     * @param position  L<<0.0 <<0.5>> 1.0>>R
     */
    void voicePan(uint8_t voice, float position)
    {
        if (voice >= 0 && voice < _voicePans.size())
        {
            position = clampf<uint8_t>(position, 0, 1.0);
            _voicePans[voice]->setValue(position);
        }
    }

    void voiceGain(uint8_t voice, float value)
    {
        if (voice >= 0 && voice < _voiceGains.size())
        {
            value = clampf<uint8_t>(value, 0, 1.0);
            _voiceGains[voice]->setValue(value);
        }
    }

    void masterPan(float value) { _masterPan->setValue(clampf<float>(value, 0, 1.0f)); }
    void masterGain(float value) { _masterGain->setValue(clampf<float>(value, 0, 1.5f)); }

    void update() override
    {
        float left, right;
        // set mixer channel levels
        
        for (uint8_t voice = 0; voice < _voicePans.size(); voice++)
        {
            if (_voicePans[voice]->changed(true) || _voiceGains[voice]->changed(true))
            {
                getStereoGainLR(
                    _voiceGains[voice]->getValue(),
                    _voicePans[voice]->getValue(),
                    left, right);
                _voiceMixL->gain(voice, left);
                _voiceMixR->gain(voice, right);
            }
        }
        // set output amp levels
        if (_masterPan->changed(true) || _masterGain->changed(true))
        {
            getStereoGainLR(_masterGain->getValue(), _masterPan->getValue(), left, right);
            _masterAmpL->gain(left);
            _masterAmpR->gain(right);
        }
    }

private:
    LXParameter *_masterGain, *_masterPan;
    AudioMixer4 *_voiceMixL, *_voiceMixR;
    AudioAmplifier *_masterAmpL, *_masterAmpR;
    std::vector<LXParameter *> _voiceGains;
    std::vector<LXParameter *> _voicePans;
};
