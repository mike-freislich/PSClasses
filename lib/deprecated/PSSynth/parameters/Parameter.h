#pragma once
#include <vector>
#include <algorithm>
#include "StringBuilder.h"
#include "CollectionItem.h"
#include "AudioStub.h"

namespace PS
{

    typedef std::function<void(float)> AUValueFunc;
    typedef std::function<void(unsigned int, float)> AUChannelValueFunc;

    template <typename T>
    AUValueFunc mapValueFunc(T *audioUnitInstance, void (T::*func)(float))
    {
        return [func, audioUnitInstance](float value)
        {
            auto derived = audioUnitInstance;
            (derived->*func)(value);
        };
    }

    template <typename T>
    AUChannelValueFunc mapValueFunc(T *audioUnitInstance, void (T::*func)(unsigned int, float))
    {
        return [func, audioUnitInstance](unsigned int channel, float value)
        {
            auto derived = audioUnitInstance;
            (derived->*func)(channel, value);            
        };
    }

    enum ParameterMode
    {
        STANDARD_PARM,
        SHIFT_PARM
    };

    class Parameter : public CollectionItemBase
    {
    public:
        enum TAPER
        {
            LINEAR,
            LOGARITHMIC
        };

        Parameter() : CollectionItemBase() {}

        virtual ~Parameter() override {}

        static Parameter *create(const char *key, const char *displayName)
        {
            Parameter *p = new Parameter();
            p->key = key;
            p->displayName = displayName;
            return p;
        }

        float getValue()
        {
            if (_integerValue)
            {
                if (_taper == LINEAR)
                    return (int)_value;
                return (int)getValueLog();
            }
            if (_taper == LINEAR)
                return _value;
            return getValueLog();
        }

        void setValue(float val)
        {
            if (_integerValue)
                val = (int)val;

            if (val != _value)
            {
                _changed = true;
                _value = val;
            }
        }

        bool changed(bool reset = false)
        {
            bool result = _changed;
            if (result && reset)
                _changed = false;
            return result;
        }

        void setValueFromController(float controllerValue) { setValue(controllerValue * _range + _min); }

        Parameter *setRange(float minV, float maxV)
        {
            _min = minV;
            _max = maxV;
            _range = _max - _min;
            _value = clampf<float>(_value, _min, _max);
            return this;
        }

        Parameter *setTaper(Parameter::TAPER taper)
        {
            _taper = taper;
            return this;
        }

        /**
         * @brief
         * If set will cause values returned from this->getValue() to be truncated to an integer
         * @param isInteger - true or false
         * @return Parameter*
         */
        Parameter *integerValue(bool isInteger)
        {
            _integerValue = isInteger;
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
                ->delimiter()
                ->addPair("integervalue", (bool)_integerValue)
                ->endElement();
        }

        static Parameter *deserialize(const std::string &jsonData)
        {
            // TODO move code from config LoadParameters to here
            return nullptr;
        }

    protected:
        AUValueFunc auSetValue;
        AUChannelValueFunc auSetChannelValue;
        float _value, _max, _min, _range;
        bool _changed, _integerValue;
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

    typedef std::vector<Parameter *> PSParameterVector;

}