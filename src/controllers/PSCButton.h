#pragma once
#include "PSController.h"

enum PSCButtonType
{
    Momentary,
    Latching
};

//TODO implement momentary / latching button type
class PSCButton : public PSController
{
public:
    PSCButton(const PSK &key, const std::string &name) : PSController(key, name, 10, 1010)
    {
        setPin(key);
        setValueRange(0, 1);
        debounceMS(100);
    }
    ~PSCButton() override {}

    void buttonType(const PSCButtonType &bt) { _buttonType = bt; }

protected:
    PSCButtonType _buttonType = Momentary;
    virtual bool readValue() override
    {
        if (_allowRandom)
        {
            float v = (float)(rand() % (int)(_range * 10000)) / 10000.0f;
            return setValue(roundf(v));
        }
        return false;
    }
};