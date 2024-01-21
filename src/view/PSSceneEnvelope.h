#pragma once
#include "PSScene.h"
#include "PSMEnvelope.h"

class PSSceneEnvelope : public PSScene
{
public:
    PSSceneEnvelope(const std::string &name) : PSScene(PSK::SCN_ENVELOPE, name) {}
    ~PSSceneEnvelope() override {}

    void drawModules() override
    {
        for (auto &module : _modules.items)
            if (PSMEnvelope *e = dynamic_cast<PSMEnvelope *>(module.second))
                printf("Envelope [%s] : (atk %7.2f)  (hld %7.2f)  (dec %7.2f)  (sus %2.2f)  (rel %7.2f)\n",
                       e->name.c_str(),
                       e->getAttack(), e->getHold(), e->getDecay(), e->getSustain(), e->getRelease());
        printf("\nButtons : (shift %0.0f)  (enter %0.0f)\n",
               Parameters.byKey(CTRL_BTN_Shift)->getValue(),
               Parameters.byKey(CTRL_BTN_DataG)->getValue());
    }
};