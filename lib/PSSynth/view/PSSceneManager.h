#pragma once
#include "Collection.h"
#include "PSScene.h"
#include "PSSceneEnvelope.h"
#include "PSSceneStereoVoiceMixer.h"

#include "PSModuleManager.h"
// #define SCENE_SPLASH 0
// #define SCENE_ENVELOPE 1

class PSSceneManager : public CollectionBase<std::string, PSScene *>
{
public:
    ~PSSceneManager() override {}
    std::vector<PSScene *> scenes;
    uint8_t sceneIndex = 0;

    PSScene *scene(const std::string &key) { return collectionData[key]; }

    PSScene *add(const std::string &key, PSScene *scene) override
    {
        scenes.push_back(scene);
        return CollectionBase::add(key, scene);
    }

    void setActive(const std::string &key) { setActive(collectionData[key]); }

    void setActive()
    {
        sceneIndex = 0;
        setActive(scenes[sceneIndex]);
    }

    void setActive(PSScene *scene)
    {
        if (_activeScene)
            _activeScene->deactivate();

        if ((_activeScene = scene))
            _activeScene->activate();
        else
            printf("no active scene to render\n");
    }

    void nextScene()
    {
        sceneIndex = ++sceneIndex % scenes.size();
        setActive(scenes[sceneIndex]);
    }

    void prevScene()
    {
        sceneIndex = --sceneIndex % scenes.size();
        setActive(scenes[sceneIndex]);
    }

    void render()
    {
        if (_activeScene)
            _activeScene->render();
    }

    PSScene *active() { return _activeScene; }

protected:
    void drawButtons()
    {
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

private:
    PSScene *_activeScene;
} Scenes;