#pragma once
#include "AudioShard.h"
#include <iostream>

class AUMockObject : public AudioStream
{
public:
    AUMockObject() : AudioStream(1, NULL) {}
    virtual void update(void) {}
};

class AudioEffectEnvelope : public AudioStream
{
public:
    AudioEffectEnvelope() : AudioStream(1, NULL) {}
    void noteOn() {}
    void noteOff() {}
    void delay(float milliseconds) { std::cout << "delay set to : " << milliseconds << std::endl; }
    void attack(float milliseconds) { std::cout << "attack set to : " << milliseconds << std::endl; }
    void hold(float milliseconds) { std::cout << "hold set to : " << milliseconds << std::endl; }
    void decay(float milliseconds) { std::cout << "decay set to : " << milliseconds << std::endl; }
    void sustain(float level) { std::cout << "sustain set to : " << level << std::endl; }
    void release(float milliseconds) { std::cout << "release set to : " << milliseconds << std::endl; }
    void releaseNoteOn(float milliseconds) {}
    bool isActive() {return false; }
    bool isSustain() { return false; }
    virtual void update(void) {}
};

class AudioSynthWaveformDc : public AudioStream
{
public:
    AudioSynthWaveformDc() : AudioStream(0, NULL) {}
    void amplitude(float n) {}
    void amplitude(float n, float milliseconds) {}
    float read(void) { return 0; }
    virtual void update(void) {}
};

class AudioMixer4 : public AudioStream
{
public:
    AudioMixer4(void) : AudioStream(4, NULL) {}
    virtual void update(void) {}
    void gain(unsigned int channel, float gain) { std::cout << "mixer channel: " << channel <<  ", set to : " << gain << std::endl; }
};

class AudioAmplifier : public AudioStream
{
public:
    AudioAmplifier(void) : AudioStream(1, NULL) {}
    virtual void update(void) {}
    void gain(float n) {std::cout << "gain set to : " << n << std::endl;}
private:
};

class AudioSynthWaveformModulated : public AudioStream
{
public:
    AudioSynthWaveformModulated(void) : AudioStream(2, NULL) {}
    void frequency(float freq) {}
    void amplitude(float n) {}
    void offset(float n) {}
    void begin(short t_type) {}
    void begin(float t_amp, float t_freq, short t_type) {}
    void arbitraryWaveform(const int16_t *data, float maxFreq) {}
    void frequencyModulation(float octaves) {}
    void phaseModulation(float degrees) {}
    virtual void update(void) {}
};

class AudioEffectMultiply : public AudioStream
{
public:
    AudioEffectMultiply() : AudioStream(2, NULL) {}
    virtual void update(void) {}
};

class AudioSynthWaveform : public AudioStream
{
public:
    AudioSynthWaveform(void) : AudioStream(0, NULL) {}
    void frequency(float freq) {}
    void phase(float angle) {}
    void amplitude(float n) {}
    void offset(float n) {}   
    void pulseWidth(float n) {}
    void begin(short t_type) {}
    void begin(float t_amp, float t_freq, short t_type) {}
    void arbitraryWaveform(const int16_t *data, float maxFreq) {}
    virtual void update(void) {}
};

class AudioSynthNoiseWhite : public AudioStream
{
public:
	AudioSynthNoiseWhite() : AudioStream(0, NULL) {}
	void amplitude(float n) {}	
	virtual void update(void) {}
};

class AudioSynthNoisePink : public AudioStream
{
public:
	AudioSynthNoisePink() : AudioStream(0, NULL) {}	
	void amplitude(float n) {}
	virtual void update(void) {}
};

class AudioEffectWaveshaper : public AudioStream
{
  public:
    AudioEffectWaveshaper(void): AudioStream(1, NULL) {}
    ~AudioEffectWaveshaper() {}
    virtual void update(void) {}
    void shape(float* waveshape, int length) {}
};

class AudioFilterStateVariable: public AudioStream
{
public:
	AudioFilterStateVariable() : AudioStream(2, NULL) {}
	void frequency(float freq) {}
	void resonance(float q) {}
	void octaveControl(float n) {}
	virtual void update(void) {}
};

enum AudioFilterLadderInterpolation {
	LADDER_FILTER_INTERPOLATION_LINEAR,
	LADDER_FILTER_INTERPOLATION_FIR_POLY
};
class AudioFilterLadder: public AudioStream
{
public:
	AudioFilterLadder() : AudioStream(3, NULL) { };
	void frequency(float FC) {}
	void resonance(float reson) {}
	void octaveControl(float octaves) {}
	void passbandGain(float passbandgain) {}
	void inputDrive(float drv) {}
	void interpolationMethod(AudioFilterLadderInterpolation im) {}
	virtual void update(void) {}
};

class AudioAnalyzePeak : public AudioStream
{
public:
	AudioAnalyzePeak(void) : AudioStream(1, NULL) {}
	bool available(void) { return false; }
	float read(void) { return 0; }
	float readPeakToPeak(void) {return 0;}
	virtual void update(void) {}
};

class AudioOutputUSB : public AudioStream
{
public:
	AudioOutputUSB(void) : AudioStream(2, NULL) {  }
	virtual void update(void) {}
	void begin(void) {}
	friend unsigned int usb_audio_transmit_callback(void) { return 0;}
};