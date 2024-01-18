#pragma once
#include "PSController.h"

class PSCButton : public PSController
{
public:
    PSCButton(const PSKeys &key, const std::string &name) : PSController(key, name, 10, 1010)
    {
        setPin(key);
        setValueRange(0, 1);
        debounceMS(30);
    }
    ~PSCButton() override {}

protected:
    virtual void readValue() override
    {
        if (_allowRandom)
        {                      
            float v = (float)(rand() % (int)(_range * 10000)) / 10000.0f;                   
            setValue(roundf(v));
        }
    }
};