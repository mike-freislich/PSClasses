#pragma once
#include "Module.h"
#include "ModuleModulator.h"
#include "ModuleVoiceMixer.h"
#include "ModulePulseWidthMod.h"
#include "ModuleOscillator.h"
#include "ModuleXModulation.h"
#include "ModuleRingMod.h"
#include "ModuleNoise.h"



namespace ps
{
    class ModuleManager : public CollectionBase<std::string, Module *>
    {
    public:
        ~ModuleManager() override {}

    } Modules;
}