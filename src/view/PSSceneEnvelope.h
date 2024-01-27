#pragma once
#include "PSScene.h"
#include "PSMEnvelope.h"

class PSSceneEnvelope : public PSScene
{
public:
    PSSceneEnvelope(const PSK &key, const std::string &name) : PSScene(key, name)
    {
        addModule(Modules.getItem<PSModule>(MOD_PENVa));
        addModule(Modules.getItem<PSModule>(MOD_PENVb));
        addModule(Modules.getItem<PSModule>(MOD_AENVa));
        addModule(Modules.getItem<PSModule>(MOD_AENVb));
        addModule(Modules.getItem<PSModule>(MOD_FENVa));
        addModule(Modules.getItem<PSModule>(MOD_FENVb));
    }
    ~PSSceneEnvelope() override {}

    void drawModules() override
    {
        for (auto &module : _modules.items)
        {
            if (PSMEnvelope *e = dynamic_cast<PSMEnvelope *>(module.second))
            {
                printf("Envelope [%s] : (atk %7.2f)  (hld %7.2f)  (dec %7.2f)  (sus %2.2f)  (rel %7.2f)\n",
                       e->name.c_str(),
                       e->getAttack(), e->getHold(), e->getDecay(), e->getSustain(), e->getRelease());
            }
        }
        
        printf("\nButtons : (shift %d)  (enter %0.0f)\n",
              Controllers.isShiftPressed(),
              Parameters.byKey(CTRL_BTN_DataG)->getValue());
    }
};