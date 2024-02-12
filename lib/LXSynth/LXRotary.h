#pragma once
#include "LXController.h"

class LXRotary : public LXController
{
public:
    LXRotary(ContKeys key) : LXController(key)
    {
        debounceMs(5); // default Rotary debounce
        _min = -1;
        _max = 1;
    }
    ItemType getType() override { return ItemType::TLXRotary; }

    void setPins(uint16_t pinA, uint16_t pinB)
    {
        _pin = pinA;
        _pin2 = pinB;
    }

    void updateController() override
    {
        if (_moved != 0)
        {
            for (auto &p : _parameters)
                p->setValue(p->getValue() + _moved);
        }
    }

private:
    // int readValue() override { return LXController::readValue(); }
    int8_t _moved = 0;
    uint16_t _pin2 = 0;
};