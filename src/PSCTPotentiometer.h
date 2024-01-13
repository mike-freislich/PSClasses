#pragma once
#include <string>
#include "PSController.h"
#include "ArduinoShard.h"

class PSCTPotentiometer : public PSController
{
public:
    PSCTPotentiometer(string key, uint8_t pin) : PSController(key, 10, 1010, true)
    {             
        setPin(pin);
    }

private:
};