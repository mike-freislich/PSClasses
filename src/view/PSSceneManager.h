#pragma once
#include "Collection.h"
#include "PSScene.h"
#include "PSSceneEnvelope.h"
#include "PSModuleManager.h"

#define SCENE_SPLASH 0
#define SCENE_ENVELOPE 1

class PSSceneManager : public CollectionBase<std::string, PSScene *>
{
public:
    //PSSceneManager() : CollectionBase() {}
    ~PSSceneManager() override {}

    PSScene *scene(const std::string &key) { return collectionData[key]; }

    void setActive(const std::string &key)
    {
        setActive(collectionData[key]);        
    }

    void setActive(PSScene *scene)
    {
        _activeScene = scene;
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
} Scenes;