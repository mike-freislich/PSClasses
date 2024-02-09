#pragma once
#include "Collection.h"
#include "Scene.h"
#include "SceneEnvelope.h"
#include "SceneStereoVoiceMixer.h"
#include "ModuleManager.h"

namespace PS
{
    class SceneManager : public CollectionBase<std::string, Scene *>
    {
    public:
        ~SceneManager() override {}
        std::vector<Scene *> scenes;
        uint8_t sceneIndex = 0;

        Scene *scene(const std::string &key) { return collectionData[key]; }

        Scene *add(const std::string &key, Scene *scene) override
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

        void setActive(Scene *scene)
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

        Scene *active() { return _activeScene; }

    private:
        Scene *_activeScene;
    } Scenes;

}