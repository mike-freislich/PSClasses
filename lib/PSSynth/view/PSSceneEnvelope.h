#pragma once
#include "PSScene.h"
#include "PSMEnvModulator.h"

namespace ps
{

    class PSSceneEnvelope : public PSScene
    {
    public:
        PSSceneEnvelope() : PSScene()
        {
            typeName = "PSSceneEnvelope";
            addModule(Modules[MOD_PENV]);
            addModule(Modules[MOD_AENV]);
            addModule(Modules[MOD_FENV]);
        }
        ~PSSceneEnvelope() override {}

        void drawModules() override
        {
            for (auto &module : _modules.getData())
            {
                if (PSMEnvModulator *e = dynamic_cast<PSMEnvModulator *>(module.second))
                {
                    printf("Envelope [%s] : (atk %7.2f)  (hld %7.2f)  (dec %7.2f)  (sus %2.2f)  (rel %7.2f)  (amt %2.2f) (lfo-s %2.0f) (lfo-lvl %2.2f) (lfo-freq %2.2f) \n",
                           e->displayName.c_str(),
                           e->getAttack(), e->getHold(), e->getDecay(), e->getSustain(), e->getRelease(), e->getAmount() * e->invertMultiplier(), e->getLFOShape(), e->getLFOAmplitude(), e->getLFOFreq());
                }
            }
        }
    };

}