#pragma once
#include <vector>
#include <algorithm>
#include "PSController.h"

class PSParameter: public PSObject
{
public:
    enum TAPER { LINEAR, LOGARITHMIC };

    PSParameter(const PSK &key, const std::string &name) : PSObject(key, name) {}
    virtual ~PSParameter() override {}        

    float getValue()
    {
        if (_taper == LINEAR)
            return _value;
        return getValueLog();
    }

    void setValue(float val) { _value = val; }

    PSParameter * attachController(PSController *controller)
    {
        _controllers.push_back(controller);
        return this;
    }

    void detachController(PSController *controller)
    {
        if (controller)
        {
            for (int i = 0; i < _controllers.size(); i++)
            {
                PSController *c = _controllers[i];        
                if (c->key == controller->key)
                {
                    _controllers.erase(_controllers.begin() + i);
                    break;
                }
            }
        }
    }

    bool update() override
    {
        bool changed = false;
        for (auto c : _controllers)
        {
            if (c->didChange())
            {
                _value = (c->getValue() * _range) + _min;
                changed = true;
                break;
            }
        }
        return changed;
    }

    std::string toString() { return "{" + name + "," + std::to_string(_value) + "}"; }

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

protected:
    float _value, _max, _min, _range;
    TAPER _taper = LINEAR;    
    PSControllerVector _controllers;

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