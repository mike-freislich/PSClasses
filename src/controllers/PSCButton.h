#pragma once
#include "PSController.h"

enum PSCButtonType
{
    Momentary,
    Latching
};

// TODO implement momentary / latching button type
class PSCButton : public PSController
{
public:
    PSCButton(const PSK &key, const std::string &name) : PSController(key, name)
    {
        setPin(key);
        setValueRange(0, 1);
        debounceMS(30);
    }
    ~PSCButton() override {}

    const char *typeName() override { return "PSCButton"; }

    void buttonType(const PSCButtonType &bt) { _buttonType = bt; } 

    bool isPressed() { return _value == 1; }

protected:
    PSCButtonType _buttonType = Momentary;
    virtual bool readValue() override
    {
        if (_allowRandom)
        {
            float v = (float)(rand() % (int)(_range * 10000)) / 10000.0f;
            v = (v <= 0.5f) ? 0 : 1;      
            return setValue(v);
        }
        return false;
    }
};