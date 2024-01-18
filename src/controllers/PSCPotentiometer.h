#pragma once
#include <string>
#include "PSController.h"

class PSCPotentiometer : public PSController
{
public:
    PSCPotentiometer(const PSKeys &key, const std::string &name) : PSController(key, name, 10, 1010)
    {             
        setPin(key);
    }

    ~PSCPotentiometer() override { 
        //PSController::~PSController(); 
        }

private:
};