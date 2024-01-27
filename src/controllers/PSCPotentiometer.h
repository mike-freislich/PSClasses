#pragma once
#include "PSController.h"
#include "StringBuilder.h"

class PSCPotentiometer : public PSController
{
public:
    PSCPotentiometer(const PSK &key, const std::string &name) : PSController(key, name, 10, 1010)
    {
        //setPin(key);
    }
    ~PSCPotentiometer() override {}

    const char *typeName() override { return "PSCPotentiometer"; }
};