#pragma once
#include "PSScene.h"
#include "PSSceneEnvelope.h"
#include "../modules/PSModuleManager.h"

#define SCENE_SPLASH 0
#define SCENE_ENVELOPE 1

class PSSceneManager : public PSObjectCollection
{
public:
    PSSceneManager() : PSObjectCollection() {}
    ~PSSceneManager() override {}

    void setActive(const PSKeys &key) { _activeScene = _scenes.getItem<PSScene>(key); }
    void nextScene() {}
    void prevScene() {}

    void render()
    {
        if (_activeScene)
            _activeScene->render();
    }

private:
    PSObjectCollection _scenes;
    PSScene *_activeScene;
};