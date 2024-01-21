#pragma once
#include <vector>
#include "PSKeys.h"
#include "PSObject.h"
#include "timing.h"
#include "FastMath.h"

class PSController : public PSObject
{
public:
    PSController(const PSK &key, const std::string &name, float minV = 0, float maxV = 127, bool allowRandom = false)
        : _allowRandom(allowRandom), PSObject(key, name)
    {
        setValueRange(minV, maxV);
        _allowRandom = true;
        bounceTimer.start(0);
    }

    virtual ~PSController() override
    {
        // PSObject::~PSObject();
    }

    bool didChange() { return _changed; }

    float getValue() { return _value; }

    virtual bool update() override { return readValue(); }
    void endUpdate() { _changed = false; }

    virtual PSK getKey() { return key; }

    virtual PSController *setPin(uint8_t pin)
    {
        // TODO implement hardware setup

        _pin = pin;
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

    void debounceMS(uint32_t delay)
    {
        bounceTimer.start(delay);
    }

protected:
    bool _changed, _allowRandom;
    float _value, _min, _max, _range;
    uint8_t _pin;
    SimpleTimer bounceTimer = SimpleTimer(0);
    float _randPhase = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);

    virtual bool readValue()
    {
        if (_allowRandom)
        {            
            //float v = (float)(rand() % (int)(_range * 10000)) / 10000.0f;            
            
            float v = (sineWavePoint(0.5f, 1.5f, _randPhase, millis()) + 0.5f) * _range;
            return setValue(v);
        }
        return false;
    }

    virtual bool setValue(float val)
    {
        float sval = val / _range;
        if (sval != _value)
        {
            if (bounceTimer.update())
            {
                _value = sval;
                _changed = true;
            }
        }
        return _changed;
    }
};

typedef std::vector<PSController *> PSControllerVector;