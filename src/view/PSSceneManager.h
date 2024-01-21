#pragma once
#include "PSScene.h"
#include "PSSceneEnvelope.h"
#include "PSModuleManager.h"

#define SCENE_SPLASH 0
#define SCENE_ENVELOPE 1

class PSSceneManager : public PSObjectCollection
{
public:
    PSSceneManager() : PSObjectCollection() {}
    ~PSSceneManager() override {}

    void setActive(const PSK &key)
    {

        _activeScene = getItem<PSScene>(key);
        if (_activeScene)
            _activeScene->activate();
        else
            printf("no active scene to render\n");
    }
    void nextScene() {}
    void prevScene() {}

    void render()
    {
        if (_activeScene)
            _activeScene->render();
    }

    PSScene *active() { return _activeScene; }

private:
    PSScene *_activeScene;
};