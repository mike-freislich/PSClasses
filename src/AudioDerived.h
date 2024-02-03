#pragma once
#include "AudioMockObjects.h"
#include <string>
#include <iostream>

using FieldKey = std::string;

#define FK_ENV_ATTACK "attack"
#define FK_ENV_HOLD "hold"
#define FK_ENV_DECAY "decay"
#define FK_ENV_SUSTAIN "sustain"
#define FK_ENV_RELEASE "release"
#define FK_AMP_GAIN "gain"

//typedef std::function<void(FieldKey, float)> SetFloatFunction;

class MyAudioBase
{
public:
    virtual ~MyAudioBase() {}
    std::string unitName = "base";
    
    virtual void setFloat(const FieldKey &key, float value)
    {
        std::cout << "MyAudioBase: setting [" << unitName << "] " << key << ": " << value << std::endl;
    }
    
    virtual void setChannelFloat(const FieldKey &key, unsigned int channel, float value)
    {
        std::cout << "MyAudioBase: setting [" << unitName << "] " << key << ": " << value << "channel : " << channel << std::endl;
    }
};

class MyAudioEffectEnvelope : public AudioEffectEnvelope, public MyAudioBase
{
public:
    void setFloat(const FieldKey &key, float value) override
    {
        if (key == FK_ENV_ATTACK)
            this->attack(value);
        else if (key == FK_ENV_HOLD)
            this->hold(value);
        else if (key == FK_ENV_DECAY)
            this->decay(value);
        else if (key == FK_ENV_SUSTAIN)
            this->sustain(value);
        else if (key == FK_ENV_RELEASE)
            this->release(value);

        MyAudioBase::setFloat(key, value);
    }
};

class MyAudioAmplifier : public AudioAmplifier, public MyAudioBase
{
public:
    void setFloat(const FieldKey &key, float value) override
    {        
        if (key == FK_AMP_GAIN)
            this->gain(value);

        MyAudioBase::setFloat(key, value);
    }
};

class MyAudioAnalyzePeak : public AudioAnalyzePeak, public MyAudioBase
{
    // void setFloat(const FieldKey &key, float value) override
    // {
    //     this->
    //     // if (key == FK_AMP_GAIN)
    //     //     this->gain(value);
    //     MyAudioBase::setFloat(key, value);
    // }
};

class MyAudioMixer4 : public AudioMixer4, public MyAudioBase
{
    void setChannelFloat(const FieldKey &key, unsigned int channel, float value) override
    {        
        if (key == FK_AMP_GAIN)
            this->gain(channel, value);

        MyAudioBase::setChannelFloat(key, channel, value);
    }

    void setFloat(const FieldKey &key, float value) override
    {
        for (int i = 0; i < 4; i ++)    
            setChannelFloat(key, i, value);
    }
};

void testAudioDerived()
{
    MyAudioBase *base = new MyAudioEffectEnvelope();
    base->setFloat(FK_ENV_ATTACK, 12.23);
}
