#pragma once

#include <iostream>
#include <vector>
#include "PSController.h"
// #include "FastMath.h"

using namespace std;

class PSParameter
{
public:
    enum TAPER
    {
        LINEAR,
        LOGARITHMIC
    };

    PSParameter(string key) : _key(key) {}

    float getValue()
    {
        if (_taper == LINEAR)
            return _value;
        return getValueLog();
    }

    string getKey() { return _key; }
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
                if (c->getKey() == controller->getKey())
                {
                    _controllers.erase(_controllers.begin() + i);
                    break;
                }
            }
        }
    }

    bool update()
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

    string toString()
    {
        return "{" + _key + "," + to_string(_value) + "}";
    }

    PSParameter *setRange(float minV, float maxV)
    {
        _min = minV;
        _max = maxV;
        _range = _max - _min;
        _value = clamp(_value, _min, _max);
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
    string _key;
    PSControllerVector _controllers;

    float convertToAudio(float linearValue, float linearMin, float linearMax, float audioMin = 0, float audioMax = 0, float exponent = 2.0f)
    {
        if (audioMax == audioMin)
        {
            audioMax = linearMax;
            audioMin = linearMin;
        }
        // Ensure linearValue is within the specified range
        linearValue = max(min(linearValue, linearMax), linearMin);

        // Perform the conversion using the formula
        float audioValue = audioMin + (audioMax - audioMin) * std::pow((linearValue - linearMin) / (linearMax - linearMin), exponent);

        return audioValue;
    }

    float getValueLog() { return convertToAudio(_value, _min, _max); }
};

typedef vector<PSParameter *> PSParameterVector;