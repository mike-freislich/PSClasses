#pragma once
#include "PSScene.h"
#include "PSMEnvelope.h"

class PSSceneEnvelope : public PSScene
{
public:
    PSSceneEnvelope(const std::string &name) : PSScene(SCN_ENVELOPE, name) {}
    ~PSSceneEnvelope() override {}

    void onRenderScene() override
    {
        if (_customDisplay)
        {
            clearDisplay();
            drawTitle();
            drawParameters();            
        }
        else
        {
            PSScene::onRenderScene();            
        }
    }

private:
    bool _customDisplay = false;
};