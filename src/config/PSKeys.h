#pragma once

// -- Voice A Modules ---
#define MOD_LFO1a "MOD_LFO1a"
#define MOD_LFO2a "MOD_LFO2a"
#define MOD_PENVa "MOD_PENVa"
#define MOD_AENVa "MOD_AENVa"
#define MOD_FENVa "MOD_FENVa"
#define MOD_VCFa "MOD_VCFa"
#define MOD_VCOa "MOD_VCOa"
#define MOD_VCAa "MOD_VCAa"
#define MOD_NOISEa "MOD_NOISEa"
#define MOD_RINGMODa "MOD_RINGMODa"
#define MOD_FOLDa "MOD_FOLDa"

// -- Voice B Modules ---
#define MOD_LFO1b "MOD_LFO1b"
#define MOD_LFO2b "MOD_LFO2b"
#define MOD_PENVb "MOD_PENVb"
#define MOD_AENVb "MOD_AENVb"
#define MOD_FENVb "MOD_FENVb"
#define MOD_VCFb "MOD_VCFb"
#define MOD_VCOb "MOD_VCOb"
#define MOD_VCAb "MOD_VCAb"
#define MOD_NOISEb "MOD_NOISEb"
#define MOD_RINGMODb "MOD_RINGMODb"
#define MOD_FOLDb "MOD_FOLDb"

// -- Mixers -- 
#define MOD_MIXER_MAIN "MOD_MIXER_MAIN"

// -- Attack Envelopes A / B --
#define PARM_AENVa_ATTACK "PARM_AENVa_ATTACK"
#define PARM_AENVa_HOLD "PARM_AENVa_HOLD"
#define PARM_AENVa_DECAY "PARM_AENVa_DECAY"
#define PARM_AENVa_SUSTAIN "PARM_AENVa_SUSTAIN"
#define PARM_AENVa_RELEASE "PARM_AENVa_RELEASE"
#define PARM_AENVa_AMOUNT "PARM_AENVa_AMOUNT"
#define PARM_AENVb_ATTACK "PARM_AENVb_ATTACK"
#define PARM_AENVb_HOLD "PARM_AENVb_HOLD"
#define PARM_AENVb_DECAY "PARM_AENVb_DECAY"
#define PARM_AENVb_SUSTAIN "PARM_AENVb_SUSTAIN"
#define PARM_AENVb_RELEASE "PARM_AENVb_RELEASE"
#define PARM_AENVb_AMOUNT "PARM_AENVb_AMOUNT"

// -- Pitch Envelopes A / B --
#define PARM_PENVa_ATTACK "PARM_PENVa_ATTACK"
#define PARM_PENVa_HOLD "PARM_PENVa_HOLD"
#define PARM_PENVa_DECAY "PARM_PENVa_DECAY"
#define PARM_PENVa_SUSTAIN "PARM_PENVa_SUSTAIN"
#define PARM_PENVa_RELEASE "PARM_PENVa_RELEASE" 
#define PARM_PENVa_AMOUNT "PARM_PENVa_AMOUNT"
#define PARM_PENVb_ATTACK "PARM_PENVb_ATTACK"
#define PARM_PENVb_HOLD "PARM_PENVb_HOLD"
#define PARM_PENVb_DECAY "PARM_PENVb_DECAY"
#define PARM_PENVb_SUSTAIN "PARM_PENVb_SUSTAIN"
#define PARM_PENVb_RELEASE "PARM_PENVb_RELEASE"
#define PARM_PENVb_AMOUNT "PARM_PENVb_AMOUNT"

// -- Filter Envelopes A / B --
#define PARM_FENVa_ATTACK "PARM_FENVa_ATTACK"
#define PARM_FENVa_HOLD "PARM_FENVa_HOLD"
#define PARM_FENVa_DECAY "PARM_FENVa_DECAY"
#define PARM_FENVa_SUSTAIN "PARM_FENVa_SUSTAIN"
#define PARM_FENVa_RELEASE "PARM_FENVa_RELEASE"
#define PARM_FENVa_AMOUNT "PARM_FENVa_AMOUNT"
#define PARM_FENVb_ATTACK "PARM_FENVb_ATTACK"
#define PARM_FENVb_HOLD "PARM_FENVb_HOLD"
#define PARM_FENVb_DECAY "PARM_FENVb_DECAY"
#define PARM_FENVb_SUSTAIN "PARM_FENVb_SUSTAIN"
#define PARM_FENVb_RELEASE "PARM_FENVb_RELEASE"
#define PARM_FENVb_AMOUNT "PARM_FENVb_AMOUNT"

// LFO
#define PARM_LFO_SHAPE "PARM_LFO_SHAPE"
#define PARM_LFO_FREQ "PARM_LFO_FREQ"
#define PARM_LFO_LEVEL "PARM_LFO_LEVEL"

// Ring Modulation
#define PARM_RING_LEVEL "PARM_RING_LEVEL"
#define PARM_RING_FREQ "PARM_RING_FREQ"
#define PARM_RING_WAVE "PARM_RING_WAVE"

// ---------------------- CONTROLLERS ----------------------
#define CTRL_POT_DataA "CTRL_POT_DataA"
#define CTRL_POT_DataB "CTRL_POT_DataB"
#define CTRL_POT_DataC "CTRL_POT_DataC"
#define CTRL_POT_DataD "CTRL_POT_DataD"
#define CTRL_ROTARY_DataG_pA "CTRL_ROTARY_DataG_pA"
#define CTRL_ROTARY_DataG_pB "CTRL_ROTARY_DataG_pB"
#define CTRL_BTN_DataG "CTRL_BTN_DataG"
#define CTRL_BTN_Shift "CTRL_BTN_Shift"
#define CTRL_BTN_VoiceSelect "CTRL_BTN_VoiceSelect"
#define CTRL_POT1 "CTRL_POT1"
#define CTRL_POT2 "CTRL_POT2"
#define CTRL_POT3 "CTRL_POT3"
#define CTRL_POT4 "CTRL_POT4"
#define CTRL_POT5 "CTRL_POT5"
#define CTRL_POT6 "CTRL_POT6"


// ---------------------- SCENES ----------------------
#define SCN_ENVELOPE "SCN_ENVELOPE"


struct Range
{
    Range(float min, float max) : min(min), max(max) {}
    float min;
    float max;
};


