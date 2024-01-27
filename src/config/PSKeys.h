#pragma once

#include <string>

/**
 * @brief PSKeys is an enum containing all key-identifier for modules, parameters, controllers and scenes
 *
 */

enum PSK
{
    // ---------------------- MODULES ----------------------
    // Part A
    MOD_LFO1a,
    MOD_LFO2a,
    MOD_PENVa,
    MOD_AENVa,
    MOD_FENVa,
    MOD_VCFa,
    MOD_VCOa,
    MOD_VCAa,
    MOD_NOISEa,
    MOD_RINGMODa,
    MOD_FOLDa,

    // Part B
    MOD_LFO1b,
    MOD_LFO2b,
    MOD_PENVb,
    MOD_AENVb,
    MOD_FENVb,
    MOD_VCFb,
    MOD_VCOb,
    MOD_VCAb,
    MOD_NOISEb,
    MOD_RINGMODb,
    MOD_FOLDb,
    // ---------------------- PARAMETERS ----------------------
    // Envelope
    PARM_AENVa_ATTACK,
    PARM_AENVa_HOLD,
    PARM_AENVa_DECAY,
    PARM_AENVa_SUSTAIN,
    PARM_AENVa_RELEASE,
    PARM_AENVa_AMOUNT,
    PARM_AENVb_ATTACK,
    PARM_AENVb_HOLD,
    PARM_AENVb_DECAY,
    PARM_AENVb_SUSTAIN,
    PARM_AENVb_RELEASE,
    PARM_AENVb_AMOUNT,

    PARM_PENVa_ATTACK,
    PARM_PENVa_HOLD,
    PARM_PENVa_DECAY,
    PARM_PENVa_SUSTAIN,
    PARM_PENVa_RELEASE,
    PARM_PENVa_AMOUNT,
    PARM_PENVb_ATTACK,
    PARM_PENVb_HOLD,
    PARM_PENVb_DECAY,
    PARM_PENVb_SUSTAIN,
    PARM_PENVb_RELEASE,
    PARM_PENVb_AMOUNT,

    PARM_FENVa_ATTACK,
    PARM_FENVa_HOLD,
    PARM_FENVa_DECAY,
    PARM_FENVa_SUSTAIN,
    PARM_FENVa_RELEASE,
    PARM_FENVa_AMOUNT,
    PARM_FENVb_ATTACK,
    PARM_FENVb_HOLD,
    PARM_FENVb_DECAY,
    PARM_FENVb_SUSTAIN,
    PARM_FENVb_RELEASE,
    PARM_FENVb_AMOUNT,

    // LFO
    PARM_LFO_SHAPE,
    PARM_LFO_FREQ,
    PARM_LFO_LEVEL,

    // Ring Modulation
    PARM_RING_LEVEL,
    PARM_RING_FREQ,
    PARM_RING_WAVE,

    // ---------------------- CONTROLLERS ----------------------
    CTRL_POT_DataA,
    CTRL_POT_DataB,
    CTRL_POT_DataC,
    CTRL_POT_DataD,
    CTRL_ROTARY_DataG_pA,
    CTRL_ROTARY_DataG_pB,
    CTRL_BTN_DataG,
    CTRL_BTN_Shift,
    CTRL_POT1,
    CTRL_POT2,
    CTRL_POT3,
    CTRL_POT4,
    CTRL_POT5,
    CTRL_POT6,

    // ---------------------- SCENES ----------------------
    SCN_ENVELOPE
};

#pragma region PSK LOOKUP MAPS

// ENUM LOOKUP : PSK TO STRING
const std::unordered_map<PSK, std::string> pskToString = {
    {MOD_LFO1a, "MOD_LFO1a"},
    {MOD_LFO2a, "MOD_LFO2a"},
    {MOD_PENVa, "MOD_PENVa"},
    {MOD_AENVa, "MOD_AENVa"},
    {MOD_FENVa, "MOD_FENVa"},
    {MOD_VCFa, "MOD_VCFa"},
    {MOD_VCOa, "MOD_VCOa"},
    {MOD_VCAa, "MOD_VCAa"},
    {MOD_NOISEa, "MOD_NOISEa"},
    {MOD_RINGMODa, "MOD_RINGMODa"},
    {MOD_FOLDa, "MOD_FOLDa"},

    {MOD_LFO1b, "MOD_LFO1b"},
    {MOD_LFO2b, "MOD_LFO2b"},
    {MOD_PENVb, "MOD_PENVb"},
    {MOD_AENVb, "MOD_AENVb"},
    {MOD_FENVb, "MOD_FENVb"},
    {MOD_VCFb, "MOD_VCFb"},
    {MOD_VCOb, "MOD_VCOb"},
    {MOD_VCAb, "MOD_VCAb"},
    {MOD_NOISEb, "MOD_NOISEb"},
    {MOD_RINGMODb, "MOD_RINGMODb"},
    {MOD_FOLDb, "MOD_FOLDb"},

    {PARM_AENVa_ATTACK, "PARM_AENVa_ATTACK"},
    {PARM_AENVa_HOLD, "PARM_AENVa_HOLD"},
    {PARM_AENVa_DECAY, "PARM_AENVa_DECAY"},
    {PARM_AENVa_SUSTAIN, "PARM_AENVa_SUSTAIN"},
    {PARM_AENVa_RELEASE, "PARM_AENVa_RELEASE"},
    {PARM_AENVa_AMOUNT, "PARM_AENVa_AMOUNT"},
    {PARM_AENVb_ATTACK, "PARM_AENVb_ATTACK"},
    {PARM_AENVb_HOLD, "PARM_AENVb_HOLD"},
    {PARM_AENVb_DECAY, "PARM_AENVb_DECAY"},
    {PARM_AENVb_SUSTAIN, "PARM_AENVb_SUSTAIN"},
    {PARM_AENVb_RELEASE, "PARM_AENVb_RELEASE"},
    {PARM_AENVb_AMOUNT, "PARM_AENVb_AMOUNT"},

    {PARM_PENVa_ATTACK, "PARM_PENVa_ATTACK"},
    {PARM_PENVa_HOLD, "PARM_PENVa_HOLD"},
    {PARM_PENVa_DECAY, "PARM_PENVa_DECAY"},
    {PARM_PENVa_SUSTAIN, "PARM_PENVa_SUSTAIN"},
    {PARM_PENVa_RELEASE, "PARM_PENVa_RELEASE"},
    {PARM_PENVa_AMOUNT, "PARM_PENVa_AMOUNT"},
    {PARM_PENVb_ATTACK, "PARM_PENVb_ATTACK"},
    {PARM_PENVb_HOLD, "PARM_PENVb_HOLD"},
    {PARM_PENVb_DECAY, "PARM_PENVb_DECAY"},
    {PARM_PENVb_SUSTAIN, "PARM_PENVb_SUSTAIN"},
    {PARM_PENVb_RELEASE, "PARM_PENVb_RELEASE"},
    {PARM_PENVb_AMOUNT, "PARM_PENVb_AMOUNT"},

    {PARM_FENVa_ATTACK, "PARM_FENVa_ATTACK"},
    {PARM_FENVa_HOLD, "PARM_FENVa_HOLD"},
    {PARM_FENVa_DECAY, "PARM_FENVa_DECAY"},
    {PARM_FENVa_SUSTAIN, "PARM_FENVa_SUSTAIN"},
    {PARM_FENVa_RELEASE, "PARM_FENVa_RELEASE"},
    {PARM_FENVa_AMOUNT, "PARM_FENVa_AMOUNT"},
    {PARM_FENVb_ATTACK, "PARM_FENVb_ATTACK"},
    {PARM_FENVb_HOLD, "PARM_FENVb_HOLD"},
    {PARM_FENVb_DECAY, "PARM_FENVb_DECAY"},
    {PARM_FENVb_SUSTAIN, "PARM_FENVb_SUSTAIN"},
    {PARM_FENVb_RELEASE, "PARM_FENVb_RELEASE"},
    {PARM_FENVb_AMOUNT, "PARM_FENVb_AMOUNT"},

    // LFO
    {PARM_LFO_SHAPE, "PARM_LFO_SHAPE"},
    {PARM_LFO_FREQ, "PARM_LFO_FREQ"},
    {PARM_LFO_LEVEL, "PARM_LFO_LEVEL"},

    // Ring Modulation
    {PARM_RING_LEVEL, "PARM_RING_LEVEL"},
    {PARM_RING_FREQ, "PARM_RING_FREQ"},
    {PARM_RING_WAVE, "PARM_RING_WAVE"},

    // CONTROLLERS
    {CTRL_POT_DataA, "CTRL_POT_DataA"},
    {CTRL_POT_DataB, "CTRL_POT_DataB"},
    {CTRL_POT_DataC, "CTRL_POT_DataC"},
    {CTRL_POT_DataD, "CTRL_POT_DataD"},
    {CTRL_ROTARY_DataG_pA, "CTRL_ROTARY_DataG_pA"},
    {CTRL_ROTARY_DataG_pB, "CTRL_ROTARY_DataG_pB"},
    {CTRL_BTN_DataG, "CTRL_BTN_DataG"},
    {CTRL_BTN_Shift, "CTRL_BTN_Shift"},
    {CTRL_POT1, "CTRL_POT1"},
    {CTRL_POT2, "CTRL_POT2"},
    {CTRL_POT3, "CTRL_POT3"},
    {CTRL_POT4, "CTRL_POT4"},
    {CTRL_POT5, "CTRL_POT5"},
    {CTRL_POT6, "CTRL_POT6"},

    // SCENES
    {SCN_ENVELOPE, "SCN_ENVELOPE"}};

// ENUM REVERSE LOOKUP : STRING to PSK
const std::unordered_map<std::string, PSK> stringToPSK = {
    {"MOD_LFO1a", MOD_LFO1a},
    {"MOD_LFO2a", MOD_LFO2a},
    {"MOD_PENVa", MOD_PENVa},
    {"MOD_AENVa", MOD_AENVa},
    {"MOD_FENVa", MOD_FENVa},
    {"MOD_VCFa", MOD_VCFa},
    {"MOD_VCOa", MOD_VCOa},
    {"MOD_VCAa", MOD_VCAa},
    {"MOD_NOISEa", MOD_NOISEa},
    {"MOD_RINGMODa", MOD_RINGMODa},
    {"MOD_FOLDa", MOD_FOLDa},

    {"MOD_LFO1b", MOD_LFO1b},
    {"MOD_LFO2b", MOD_LFO2b},
    {"MOD_PENVb", MOD_PENVb},
    {"MOD_AENVb", MOD_AENVb},
    {"MOD_FENVb", MOD_FENVb},
    {"MOD_VCFb", MOD_VCFb},
    {"MOD_VCOb", MOD_VCOb},
    {"MOD_VCAb", MOD_VCAb},
    {"MOD_NOISEb", MOD_NOISEb},
    {"MOD_RINGMODb", MOD_RINGMODb},
    {"MOD_FOLDb", MOD_FOLDb},

    {"PARM_AENVa_ATTACK", PARM_AENVa_ATTACK},
    {"PARM_AENVa_HOLD", PARM_AENVa_HOLD},
    {"PARM_AENVa_DECAY", PARM_AENVa_DECAY},
    {"PARM_AENVa_SUSTAIN", PARM_AENVa_SUSTAIN},
    {"PARM_AENVa_RELEASE", PARM_AENVa_RELEASE},
    {"PARM_AENVa_AMOUNT", PARM_AENVa_AMOUNT},
    {"PARM_AENVb_ATTACK", PARM_AENVb_ATTACK},
    {"PARM_AENVb_HOLD", PARM_AENVb_HOLD},
    {"PARM_AENVb_DECAY", PARM_AENVb_DECAY},
    {"PARM_AENVb_SUSTAIN", PARM_AENVb_SUSTAIN},
    {"PARM_AENVb_RELEASE", PARM_AENVb_RELEASE},
    {"PARM_AENVb_AMOUNT", PARM_AENVb_AMOUNT},

    {"PARM_PENVa_ATTACK", PARM_PENVa_ATTACK},
    {"PARM_PENVa_HOLD", PARM_PENVa_HOLD},
    {"PARM_PENVa_DECAY", PARM_PENVa_DECAY},
    {"PARM_PENVa_SUSTAIN", PARM_PENVa_SUSTAIN},
    {"PARM_PENVa_RELEASE", PARM_PENVa_RELEASE},
    {"PARM_PENVa_AMOUNT", PARM_PENVa_AMOUNT},
    {"PARM_PENVb_ATTACK", PARM_PENVb_ATTACK},
    {"PARM_PENVb_HOLD", PARM_PENVb_HOLD},
    {"PARM_PENVb_DECAY", PARM_PENVb_DECAY},
    {"PARM_PENVb_SUSTAIN", PARM_PENVb_SUSTAIN},
    {"PARM_PENVb_RELEASE", PARM_PENVb_RELEASE},
    {"PARM_PENVb_AMOUNT", PARM_PENVb_AMOUNT},

    {"PARM_FENVa_ATTACK", PARM_FENVa_ATTACK},
    {"PARM_FENVa_HOLD", PARM_FENVa_HOLD},
    {"PARM_FENVa_DECAY", PARM_FENVa_DECAY},
    {"PARM_FENVa_SUSTAIN", PARM_FENVa_SUSTAIN},
    {"PARM_FENVa_RELEASE", PARM_FENVa_RELEASE},
    {"PARM_FENVa_AMOUNT", PARM_FENVa_AMOUNT},
    {"PARM_FENVb_ATTACK", PARM_FENVb_ATTACK},
    {"PARM_FENVb_HOLD", PARM_FENVb_HOLD},
    {"PARM_FENVb_DECAY", PARM_FENVb_DECAY},
    {"PARM_FENVb_SUSTAIN", PARM_FENVb_SUSTAIN},
    {"PARM_FENVb_RELEASE", PARM_FENVb_RELEASE},
    {"PARM_FENVb_AMOUNT", PARM_FENVb_AMOUNT},

    // LFO
    {"PARM_LFO_SHAPE", PARM_LFO_SHAPE},
    {"PARM_LFO_FREQ", PARM_LFO_FREQ},
    {"PARM_LFO_LEVEL", PARM_LFO_LEVEL},

    // Ring Modulation
    {"PARM_RING_LEVEL", PARM_RING_LEVEL},
    {"PARM_RING_FREQ", PARM_RING_FREQ},
    {"PARM_RING_WAVE", PARM_RING_WAVE},

    // CONTROLLERS
    {"CTRL_POT_DataA", CTRL_POT_DataA},
    {"CTRL_POT_DataB", CTRL_POT_DataB},
    {"CTRL_POT_DataC", CTRL_POT_DataC},
    {"CTRL_POT_DataD", CTRL_POT_DataD},
    {"CTRL_ROTARY_DataG_pA", CTRL_ROTARY_DataG_pA},
    {"CTRL_ROTARY_DataG_pB", CTRL_ROTARY_DataG_pB},
    {"CTRL_BTN_DataG", CTRL_BTN_DataG},
    {"CTRL_BTN_Shift", CTRL_BTN_Shift},
    {"CTRL_POT1", CTRL_POT1},
    {"CTRL_POT2", CTRL_POT2},
    {"CTRL_POT3", CTRL_POT3},
    {"CTRL_POT4", CTRL_POT4},
    {"CTRL_POT5", CTRL_POT5},
    {"CTRL_POT6", CTRL_POT6},

    // SCENES
    {"SCN_ENVELOPE", SCN_ENVELOPE}};

#pragma endregion

#pragma region PSK LOOKUP FUNCTIONS

std::string psk_tostr(const PSK &key)
{
    const auto &pair = pskToString.find(key);
    if (pair != pskToString.end())
        return pair->second;
    throw std::runtime_error("unable to convert PSK to string... PSK key not available in lookup table");
}

PSK str_topsk(const std::string &key)
{
    const auto &pair = stringToPSK.find(key);
    if (pair != stringToPSK.end())
        return pair->second;
    throw std::runtime_error("unable to string to PSK... string key (" + key + ") not available in reverse lookup table");
}

#pragma endregion

struct Range
{
    Range(float min, float max) : min(min), max(max) {}
    float min;
    float max;
};

#ifdef TESTMODE
void testPSKmap()
{
    psk_tostr(MOD_AENVa);
    str_topsk("MOD_LFO1a");
}
#endif
