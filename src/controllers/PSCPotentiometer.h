#pragma once
#include "PSController.h"
#include "StringBuilder.h"

class PSCPotentiometer : public PSController
{
public:
    PSCPotentiometer() : PSController()
    {
        typeName = "PSCPotentiometer";
    }
    ~PSCPotentiometer() override {}

    static PSCPotentiometer *create(const char *key, int pin, const char *displayName)
    {
        PSCPotentiometer *newPot = PSController::create<PSCPotentiometer>(key, pin, displayName);
        newPot->debounceMS(5);
        newPot->setValueRange(10,1010);
        newPot->setReadMode(PSControllerReadMode::PSCSine);        
        return newPot;
    }
};