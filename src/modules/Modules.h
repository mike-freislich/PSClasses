#pragma once
#include "PSModuleManager.h"

// forward declarations
void initEnvelopes();
void initLFOs();


// declarations
void initModules()
{
    initEnvelopes();
}

void initEnvelopes()
{
    // Envelopes
    Modules.addItem(new PSMEnvelope(MOD_PENVa, "PENV_a",
                                    PSMEnvelopeParameters(
                                        PARM_PENVa_ATTACK, PARM_PENVa_HOLD, PARM_PENVa_DECAY, PARM_PENVa_SUSTAIN, PARM_PENVa_RELEASE, PARM_PENVa_AMOUNT)));
    Modules.addItem(new PSMEnvelope(MOD_AENVa, "AENV_a",
                                    PSMEnvelopeParameters(
                                        PARM_AENVa_ATTACK, PARM_AENVa_HOLD, PARM_AENVa_DECAY, PARM_AENVa_SUSTAIN, PARM_AENVa_RELEASE, PARM_AENVa_AMOUNT)));
    Modules.addItem(new PSMEnvelope(MOD_FENVa, "FENV_a",
                                    PSMEnvelopeParameters(
                                        PARM_FENVa_ATTACK, PARM_FENVa_HOLD, PARM_FENVa_DECAY, PARM_FENVa_SUSTAIN, PARM_FENVa_RELEASE, PARM_FENVa_AMOUNT)));
    Modules.addItem(new PSMEnvelope(MOD_PENVb, "PENV_b",
                                    PSMEnvelopeParameters(
                                        PARM_PENVb_ATTACK, PARM_PENVb_HOLD, PARM_PENVb_DECAY, PARM_PENVb_SUSTAIN, PARM_PENVb_RELEASE, PARM_PENVb_AMOUNT)));
    Modules.addItem(new PSMEnvelope(MOD_AENVb, "AENV_b",
                                    PSMEnvelopeParameters(
                                        PARM_AENVb_ATTACK, PARM_AENVb_HOLD, PARM_AENVb_DECAY, PARM_AENVb_SUSTAIN, PARM_AENVb_RELEASE, PARM_AENVb_AMOUNT)));
    Modules.addItem(new PSMEnvelope(MOD_FENVb, "FENV_b",
                                    PSMEnvelopeParameters(
                                        PARM_FENVb_ATTACK, PARM_FENVb_HOLD, PARM_FENVb_DECAY, PARM_FENVb_SUSTAIN, PARM_FENVb_RELEASE, PARM_FENVb_AMOUNT)));

    
}

void initLFOs()
{    
}