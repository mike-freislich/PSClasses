#pragma once
#include "LXController.h"

class LXPotentiometer : public LXController
{
public:
    LXPotentiometer(ContKeys key) : LXController(key) { setup<LXPotentiometer>(0, 5, 10, 1010); }
    ItemType getType() override { return ItemType::TLXPotentiometer; }

private:
    int readValue() override
    {
        return LXController::readValue();
    }
};