#pragma once

/**
 * @brief PSKeys is an enum containing all key-identifier for modules, parameters, controllers and scenes
 * 
 */
enum PSKeys
{
#pragma region MODULES
    // ---------------------- MODULES ----------------------
    // Part A
    MOD_LFO1a,
    MOD_LFO2a,
    MOD_PENVa,
    MOD_AENVa,
    MOD_FENVa,
    MOD_VCFa,

    // Part B
    MOD_LFO1b,
    MOD_LFO2b,
    MOD_PENVb,
    MOD_AENVb,
    MOD_FENVb, 
    MOD_VCFb,       

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

    // Ring Modulation
    PARM_RING_LEVEL,
    PARM_RING_FREQ,
    PARM_RING_WAVE,
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