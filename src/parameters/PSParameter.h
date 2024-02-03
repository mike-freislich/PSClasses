#pragma once
#include <vector>
#include <algorithm>
#include "StringBuilder.h"
#include "CollectionItem.h"
#include "AudioShard.h"

typedef std::function<void(float)> AUValueFunc;
typedef std::function<void(unsigned int, float)> AUChannelValueFunc;

template <typename T>
AUValueFunc mapValueFunc(T *audioUnitInstance, void (T::*func)(float))
{
    return [func, audioUnitInstance](float value)
    {
        if (auto derived = dynamic_cast<T *>(audioUnitInstance))
            (derived->*func)(value);
        else
            std::cerr << "Invalid cast!" << std::endl;
    };
}

template <typename T>
AUChannelValueFunc mapValueFunc(T *audioUnitInstance, void (T::*func)(unsigned int, float))
{
    return [func, audioUnitInstance](unsigned int channel, float value)
    {
        if (auto derived = dynamic_cast<T *>(audioUnitInstance))
        {
            (derived->*func)(channel, value);
            //derived->channel = channel;
        }
        else
            std::cerr << "Invalid cast!" << std::endl;
    };
}

enum PSParameterMode
{
    STANDARD_PARM,
    SHIFT_PARM
};

class PSParameter : public CollectionItemBase
{
public:
    unsigned int channel;
    enum TAPER
    {
        LINEAR,
        LOGARITHMIC
    };

    PSParameter() : CollectionItemBase() {}

    virtual ~PSParameter() override {}

    static PSParameter *create(const char *key, const char *displayName)
    {
        PSParameter *p = new PSParameter();
        p->key = key;
        p->displayName = displayName;
        return p;
    }

    float getValue()
    {
        if (_taper == LINEAR)
            return _value;
        return getValueLog();
    }

    void setValue(float val)
    {
        if (val != _value)
        {
            if (auSetValue)
                auSetValue(val); // TODO this is where AudioUnit values need to be set
            else if (auSetChannelValue)
                auSetChannelValue(channel, val);
        }
        _value = val;
    }

    void setValueFromController(float controllerValue) { setValue(controllerValue * _range + _min); }

    PSParameter *setRange(float minV, float maxV)
    {
        _min = minV;
        _max = maxV;
        _range = _max - _min;
        _value = std::clamp(_value, _min, _max);
        return this;
    }

    PSParameter *setTaper(PSParameter::TAPER taper)
    {
        _taper = taper;
        return this;
    }

    PSParameter *setAudioUnitHandle(AUValueFunc &func)
    {
        auSetValue = func;
        return this;
    }

    PSParameter *setAudioUnitHandle(AUChannelValueFunc &func, uint8_t channel)
    {
        auSetChannelValue = func;
        this->channel = channel;
        return this;
    }

    void serialize(StringBuilder *sb) override
    {
        sb->startElement()
            ->addPair("key", key)
            ->delimiter()
            ->addPair("name", displayName)
            ->delimiter()
            ->addPair("value", _value)
            ->delimiter()
            ->addPair("min", _min)
            ->delimiter()
            ->addPair("max", _max)
            ->delimiter()
            ->addPair("taper", (int)_taper)
            ->endElement();
    }

    static PSParameter *deserialize(const std::string &jsonData)
    {
        return nullptr;
    }

protected:
    AUValueFunc auSetValue;
    AUChannelValueFunc auSetChannelValue;
    float _value, _max, _min, _range;
    TAPER _taper = LINEAR;

    float convertToAudio(float linearValue, float linearMin, float linearMax, float audioMin = 0, float audioMax = 0, float exponent = 2.0f)
    {
        if (audioMax == audioMin)
        {
            audioMax = linearMax;
            audioMin = linearMin;
        }
        // Ensure linearValue is within the specified range
        linearValue = std::max(std::min(linearValue, linearMax), linearMin);

        // Perform the conversion using the formula
        float audioValue = audioMin + (audioMax - audioMin) * std::pow((linearValue - linearMin) / (linearMax - linearMin), exponent);

        return audioValue;
    }

    float getValueLog() { return convertToAudio(_value, _min, _max); }
};

typedef std::vector<PSParameter *> PSParameterVector;