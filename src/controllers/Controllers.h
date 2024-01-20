#pragma once
#include "PSControllerManager.h"

void initControllers()
{
    // pots
    Controllers.add<PSCPotentiometer>(CTRL_POT1, "pot1");
    Controllers.add<PSCPotentiometer>(CTRL_POT1, "pot1");
    Controllers.add<PSCPotentiometer>(CTRL_POT2, "pot2");
    Controllers.add<PSCPotentiometer>(CTRL_POT3, "pot3");
    Controllers.add<PSCPotentiometer>(CTRL_POT4, "pot4");
    Controllers.add<PSCPotentiometer>(CTRL_POT5, "pot5");
    Controllers.add<PSCPotentiometer>(CTRL_POT6, "pot6");

    // buttons
    Controllers.add<PSCButton>(CTRL_BTN_Shift, "shift");
    Parameters.add(CTRL_BTN_Shift, "shift")
        ->attachController(Controllers.button(CTRL_BTN_Shift))->setRange(0,1);
    
    Controllers.add<PSCButton>(CTRL_BTN_DataG, "enter");
}