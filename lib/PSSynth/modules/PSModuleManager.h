#pragma once
#include "Module.h"
#include "PSMEnvModulator.h"
#include "PSMStereoVoiceMixer.h"
#include "PSMPulseWidthMod.h"
// #include "PSMLFO.h"
// #include "PSMVCO.h"
// #include "PSMWaveFolder.h"
// #include "PSMMultiModeFilter.h"
// #include "PSMRingMod.h"
// #include "PSMNoiseGen.h"
// #include "PSMStereoAmp.h"

namespace ps
{
    class PSModuleManager : public CollectionBase<std::string, Module *>
    {
    public:
        ~PSModuleManager() override {}

    } Modules;
}