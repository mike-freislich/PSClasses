#pragma once
#include <vector>

using namespace std;

class PSController
{
public:
    PSController(string key, bool allowRandom = false)
    {
        _key = key;
        _allowRandom = allowRandom;
    };

    bool didChange()
    {
        bool c = _changed;
        _changed = false;
        return c;
    }

    float getValue() { return _value; }

    void update()
    {
        readValue();
    }

    string getKey() { return _key; }

protected:
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
    bool _changed = false;
    bool _allowRandom = false;
    string _key;
    float _value;
};

typedef vector<PSController *> PSControllerVector;