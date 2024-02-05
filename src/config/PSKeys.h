#pragma once

// -- Voice A Modules ---
#define MOD_LFO1a "MOD_LFO1a"
#define MOD_LFO2a "MOD_LFO2a"
#define MOD_PENV "MOD_PENV"
#define MOD_AENV "MOD_AENV"
#define MOD_FENV "MOD_FENV"
#define MOD_VCFa "MOD_VCFa"
#define MOD_VCOa "MOD_VCOa"
#define MOD_VCAa "MOD_VCAa"
#define MOD_NOISEa "MOD_NOISEa"
#define MOD_RINGMODa "MOD_RINGMODa"
#define MOD_FOLDa "MOD_FOLDa"

// -- Voice B Modules ---
#define MOD_LFO1b "MOD_LFO1b"
#define MOD_LFO2b "MOD_LFO2b"
#define MOD_VCFb "MOD_VCFb"
#define MOD_VCOb "MOD_VCOb"
#define MOD_VCAb "MOD_VCAb"
#define MOD_NOISEb "MOD_NOISEb"
#define MOD_RINGMODb "MOD_RINGMODb"
#define MOD_FOLDb "MOD_FOLDb"

// -- Mixers -- 
#define MOD_MIXER_MAIN "MOD_MIXER_MAIN"

// -- Attack Envelopes A / B --
#define PARM_AENV_ATTACK "PARM_AENV_ATTACK"
#define PARM_AENV_HOLD "PARM_AENV_HOLD"
#define PARM_AENV_DECAY "PARM_AENV_DECAY"
#define PARM_AENV_SUSTAIN "PARM_AENV_SUSTAIN"
#define PARM_AENV_RELEASE "PARM_AENV_RELEASE"
#define PARM_AENV_AMOUNT "PARM_AENV_AMOUNT"
#define PARM_AENV_INVERT "PARM_AENV_INVERT" 
// -- Pitch Envelopes A / B --
#define PARM_PENV_ATTACK "PARM_PENV_ATTACK"
#define PARM_PENV_HOLD "PARM_PENV_HOLD"
#define PARM_PENV_DECAY "PARM_PENV_DECAY"
#define PARM_PENV_SUSTAIN "PARM_PENV_SUSTAIN"
#define PARM_PENV_RELEASE "PARM_PENV_RELEASE" 
#define PARM_PENV_AMOUNT "PARM_PENV_AMOUNT"
#define PARM_PENV_INVERT "PARM_AENV_INVERT" 
// -- Filter Envelopes A / B --
#define PARM_FENV_ATTACK "PARM_FENV_ATTACK"
#define PARM_FENV_HOLD "PARM_FENV_HOLD"
#define PARM_FENV_DECAY "PARM_FENV_DECAY"
#define PARM_FENV_SUSTAIN "PARM_FENV_SUSTAIN"
#define PARM_FENV_RELEASE "PARM_FENV_RELEASE"
#define PARM_FENV_AMOUNT "PARM_FENV_AMOUNT"
#define PARM_FENV_INVERT "PARM_FENV_INVERT" 


// LFO
#define PARM_LFO_SHAPE "PARM_LFO_SHAPE"
#define PARM_LFO_FREQ "PARM_LFO_FREQ"
#define PARM_LFO_LEVEL "PARM_LFO_LEVEL"

// Ring Modulation
#define PARM_RING_LEVEL "PARM_RING_LEVEL"
#define PARM_RING_FREQ "PARM_RING_FREQ"
#define PARM_RING_WAVE "PARM_RING_WAVE"

// Output stage
#define PARM_MASTER_GAIN_A "PARM_MASTER_GAIN_A"
#define PARM_MASTER_GAIN_B "PARM_MASTER_GAIN_B"

// ---------------------- CONTROLLERS ----------------------
#define CTRL_POT1 "CTRL_POT1"
#define CTRL_POT2 "CTRL_POT2"
#define CTRL_POT3 "CTRL_POT3"
#define CTRL_POT4 "CTRL_POT4"
#define CTRL_POT5 "CTRL_POT5"
#define CTRL_POT6 "CTRL_POT6"
#define CTRL_POT_DataA "CTRL_POT_DataA"
#define CTRL_POT_DataB "CTRL_POT_DataB"
#define CTRL_POT_DataC "CTRL_POT_DataC"
#define CTRL_POT_DataD "CTRL_POT_DataD"
#define CTRL_ROTARY_DataG_pA "CTRL_ROTARY_DataG_pA"
#define CTRL_ROTARY_DataG_pB "CTRL_ROTARY_DataG_pB"
#define CTRL_BTN_DataG "CTRL_BTN_DataG"
#define CTRL_BTN_Shift "CTRL_BTN_Shift"
#define CTRL_BTN_VoiceSelect "CTRL_BTN_VoiceSelect"
#define CTRL_BTN_Invert "CTRL_BTN_Invert"



// ---------------------- SCENES ----------------------
#define SCN_ENVELOPE "SCN_ENVELOPE"


struct Range
{
    Range(float min, float max) : min(min), max(max) {}
    float min;
    float max;
};


