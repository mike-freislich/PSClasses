#pragma once
#include "PSModule.h"
#include "PSMEnvelope.h"
#include "PSMLFO.h"
#include "PSMVCO.h"
#include "PSMWaveFolder.h"
#include "PSMMultiModeFilter.h"
#include "PSMRingMod.h"
#include "PSMNoiseGen.h"
#include "PSMStereoAmp.h"

class PSModuleManager : public PSObjectCollection
{
public:
    ~PSModuleManager() override {}

    void update()
    {
        for (auto &entry : items)
            ((PSModule *)entry.second)->update();
    }

    PSController *controller(const PSK &key) { return getItem<PSController>(key); }
    PSMEnvelope *envelope(const PSK &key) { return getItem<PSMEnvelope>(key); }    
} Modules;