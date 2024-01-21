#pragma once
#include "PSParameterManager.h"

void initParameters()
{
    // Parameters.add(PARM_AENVa_AMOUNT, "level")->setRange(0, 1);
    // Parameters.add(PARM_AENVa_ATTACK, "attack")->setRange(0, 10000);
    // Parameters.add(PARM_AENVa_HOLD, "hold")->setRange(0, 10000);
    // Parameters.add(PARM_AENVa_DECAY, "decay")->setRange(0, 10000);
    // Parameters.add(PARM_AENVa_SUSTAIN, "sustain")->setRange(0, 1);
    // Parameters.add(PARM_AENVa_RELEASE, "release")->setRange(0, 10000);



    Parameters.add(PARM_LFO_FREQ, "freq")->setRange(0, 5000)->setValue(1);
    Parameters.add(PARM_LFO_SHAPE, "shape")->setRange(0, 10)->setValue(0);
    Parameters.add(PARM_LFO_LEVEL, "level")->setRange(0, 1)->setValue(1);
}