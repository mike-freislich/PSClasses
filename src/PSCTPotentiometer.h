#pragma once

#include "PSController.h"
#include <string>
#include "ArduinoShard.h"

class PSCTPotentiometer : public PSController
{
public:
    PSCTPotentiometer(string key, uint8_t pin) : PSController(key)
    {
        _min = 10;
        _max = 1000;
        _taper = LINEAR;
        PSController::setPin(pin);
    }

    void readValue()
    {       
        float rv = rand() % (int)((_max - _min) + _min);        
        float nv = map(rv, _min, _max, 0, 127);   
        if (nv != _value)
            setValue(nv);     
    }

    void setValue(float v)
    {
        if (!_changed)
        {
            PSController::setValue(v);            
        }                
    }

private:
};