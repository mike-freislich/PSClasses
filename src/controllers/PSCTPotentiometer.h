#pragma once
#include <string>
#include "PSController.h"

class PSCTPotentiometer : public PSController
{
public:
    PSCTPotentiometer(const PSKeys &key, const std::string &name) : PSController(key, name, 10, 1010)
    {             
        setPin(key);
    }

    ~PSCTPotentiometer() override {}

private:
};