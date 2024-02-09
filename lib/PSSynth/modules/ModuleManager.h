#pragma once
#include "Module.h"
#include "ModuleModulator.h"
#include "ModuleVoiceMixer.h"
#include "ModulePulseWidthMod.h"
#include "ModuleOscillator.h"
#include "ModuleXModulation.h"
#include "ModuleRingMod.h"
#include "ModuleNoise.h"
#include "ModulePartMixer.h"
#include "ModuleWaveShaper.h"
#include "ModuleFilterBlock.h"

namespace PS
{
    class ModuleManager : public CollectionBase<std::string, Module *>
    {
    public:
        ~ModuleManager() override {}

    } Modules;
}