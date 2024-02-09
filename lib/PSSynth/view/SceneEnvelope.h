#pragma once
#include "Scene.h"
#include "ModuleModulator.h"

namespace PS
{
    class SceneEnvelope : public Scene
    {
    public:
        SceneEnvelope() : Scene()
        {
            typeName = "SceneEnvelope";
            addModule(Modules[MOD_PENV]);
            addModule(Modules[MOD_AENV]);
            addModule(Modules[MOD_FENV]);
        }
        ~SceneEnvelope() override {}

        void drawModules() override
        {
            for (auto &module : _modules.getData())
            {
                if (ModuleModulator *e = dynamic_cast<ModuleModulator *>(module.second))
                {
                    printf("Envelope [%s] : (atk %7.2f)  (hld %7.2f)  (dec %7.2f)  (sus %2.2f)  (rel %7.2f)  (amt %2.2f) (lfo-s %2.0f) (lfo-lvl %2.2f) (lfo-freq %2.2f) \n",
                           e->displayName.c_str(),
                           e->getAttack(), e->getHold(), e->getDecay(), e->getSustain(), e->getRelease(), e->getAmount() * e->invertMultiplier(), e->getLFOShape(), e->getLFOAmplitude(), e->getLFOFreq());
                }
            }
        }
    };

}