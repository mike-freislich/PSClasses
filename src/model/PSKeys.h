#pragma once

enum PSKeys
{
#pragma region COMPONENTS
    // ---------------------- COMPONENTS ----------------------
    // Part A
    COMP_LFO1a,
    COMP_LFO2a,
    COMP_PENVa,
    COMP_AENVa,
    COMP_FENVa,

    // Part B
    COMP_LFO1b,
    COMP_LFO2b,
    COMP_PENVb,
    COMP_AENVb,
    COMP_FENVb,

#pragma endregion

#pragma region parameters
    // ---------------------- PARAMETERS ----------------------
    // Envelope
    PARM_ENV_ATTACK,
    PARM_ENV_HOLD,
    PARM_ENV_DECAY,
    PARM_ENV_SUSTAIN,
    PARM_ENV_RELEASE, 
    PARM_ENV_AMOUNT,   

    // LFO
    PARM_LFO_SHAPE,
    PARM_LFO_FREQ,
    PARM_LFO_LEVEL,
#pragma endregion

#pragma region CONTROLLERS
    // ---------------------- CONTROLLERS ----------------------
    // USAGE : name = pinNumber
    CTRL_POT1 = 71,
    CTRL_POT2 = 2,
    CTRL_POT3 = 32,
    CTRL_POT4 = 4,
    CTRL_POT5 = 5,
    CTRL_POT6 = 6

#pragma endregion
};