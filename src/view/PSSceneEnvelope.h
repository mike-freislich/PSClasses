#pragma once
#include "PSScene.h"
#include "PSMEnvelope.h"

class PSSceneEnvelope : public PSScene
{
public:
    PSSceneEnvelope() : PSScene()
    {
        typeName = "PSSceneEnvelope";
        addModule(Modules[MOD_PENVa]);
        addModule(Modules[MOD_PENVb]);
        addModule(Modules[MOD_AENVa]);
        addModule(Modules[MOD_AENVb]);
        addModule(Modules[MOD_FENVa]);
        addModule(Modules[MOD_FENVb]);
    }
    ~PSSceneEnvelope() override {}

    void drawModules() override
    {
        for (auto &module : _modules.getData())
        {
            if (PSMEnvelope *e = dynamic_cast<PSMEnvelope *>(module.second))
            {
                printf("Envelope [%s] : (atk %7.2f)  (hld %7.2f)  (dec %7.2f)  (sus %2.2f)  (rel %7.2f)  (amt %2.2f)\n",
                       e->displayName.c_str(),
                       e->getAttack(), e->getHold(), e->getDecay(), e->getSustain(), e->getRelease(), e->getAmount());
            }
        }

        printf("\nButtons : ");
        for (auto &button : Controllers.buttons)
        {
            if (PSParameter *p = Parameters[button->key])
            {
                
                if (button->isPressed())
                    printf("<<%s>>\t", p->displayName.c_str());
                else
                    printf("..%s..\t", p->displayName.c_str());
            }
        }
    }
};