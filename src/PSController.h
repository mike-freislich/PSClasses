#pragma once
#include <vector>

using namespace std;

enum Taper
{
    LINEAR,
    LOGARITHMIC
};

class PSController
{
public:
    PSController(string key, float minV = 0, float maxV = 127, Taper taper = Taper::LINEAR, bool allowRandom = false)
        : _key(key), _min(minV), _max(maxV), _taper(taper), _allowRandom(allowRandom){};

    bool didChange()
    {
        bool c = _changed;
        _changed = false;
        return c;
    }

    float getValue() { return _value; }

    virtual void update()
    {
        readValue();
    }

    virtual string getKey() { return _key; }

    void setPin(uint8_t pin)
    {
        _pin = pin;
        //TODO hardware setup
    }

protected:
    bool _changed = false;
    float _value, _min, _max;
    Taper _taper = LINEAR;
    uint8_t _pin = 0;

    virtual void readValue()
    {
        if (_allowRandom)
            setValue(rand() % 128);
    }

    virtual void setValue(float val)
    {
        if (val != _value)
        {
            _value = val;
            _changed = true;
        }
    }

private:
    bool _allowRandom = false;
    string _key;
};

typedef vector<PSController *> PSControllerVector;