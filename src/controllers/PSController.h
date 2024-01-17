#pragma once
#include <vector>
#include "../model/PSKeys.h"

using namespace std;

class PSController : public PSObject
{
public:
    PSController(const PSKeys &key, const std::string &name, float minV = 0, float maxV = 127, bool allowRandom = false)
        : _allowRandom(allowRandom), PSObject(key, name)
    {        
        setValueRange(minV, maxV);
        _allowRandom = true;
        
    }

    bool didChange() { return _changed; }

    float getValue() { return _value; }

    virtual void update() { readValue(); }
    void endUpdate() { _changed = false; }

    virtual PSKeys getKey() { return key; }

    PSController *setPin(uint8_t pin)
    {
        _pin = pin;
        printf("hardware pin : %s to %d\n", name.c_str(), pin);
        // TODO hardware setup
        return this;
    }

    /**
     * @brief Set the Value Range object
     * The expected hardware min and max values from analogRead().
     * Values outside of this range will be clamped.
     * @param min
     * @param max
     * @return PSController*
     */
    PSController *setValueRange(float min, float max)
    {
        _min = min;
        _max = max;
        _range = _max - _min;
        return this;
    }

protected:
    bool _changed = false;
    float _value, _min, _max, _range;    
    uint8_t _pin = 0;

    virtual void readValue()
    {
        if (_allowRandom)
        {
            float v = (float)(rand() % (int)(_range * 10000)) / 10000.0f;
            setValue(v);
        }
    }

    virtual void setValue(float val)
    {
        float sval = val / _range;
        if (sval != _value)
        {
            _value = sval;
            _changed = true;
        }
    }

private:
    bool _allowRandom = false;    
};

typedef vector<PSController *> PSControllerVector;