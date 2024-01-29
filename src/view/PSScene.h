#pragma once
// #include "Parameter.h"
#include "PSModuleManager.h"
#include "PSParameterManager.h"
#include "PSControllerManager.h"
#include "PSKeys.h"
#include "timing.h"

using namespace std;

class PSScene : public CollectionItemBase
{

private:
    SimpleTimer refreshTimer = SimpleTimer(0);
    bool shouldRender() { return _active && refreshTimer.update(); }

protected:
    PSParameterManager _params;
    PSModuleManager _modules;
    PSControllerManager _controllers;
    bool _active;

public:
    ~PSScene() override
    {
        _modules.clear();
        _params.clear();
        _controllers.clear();
    }

    template <typename T>
    static T *create(const char * key, const char *displayName)
    {
        static_assert(std::is_base_of<PSScene, T>::value, "T must be a derived class of PSScene");
        PSScene *scene = new T();
        scene->key = key;
        scene->refreshRateHz(120);
        return dynamic_cast<T *>(scene);
    }

    void setDisplay()
    {
        // TODO - implement display
    }

    void activate()
    {
        _active = true;
        refreshTimer.start();
    }
    void deactivate()
    {
        _active = false;
        refreshTimer.stop();
    }

    void addParameter(PSParameter *param) { _params.add(param->key, param); }

    PSScene *addModule(PSModule *c)
    {
        if (c)
        {
            _modules.add(c->key, c);            
        }
        return this;
    }

    // void initParameters(PSModule *m)
    // {
    //     if (m)
    //     {
    //         printf("scene - adding parameters\n");
    //         for (auto &item : m->items)
    //         {
    //             PSParameter *p = dynamic_cast<PSParameter *>(item.second);
    //             if (p)
    //                 _params.addItem(p);
    //         }
    //     }
    // }

    void render()
    {
        if (shouldRender())
            onRenderScene();
    }

    virtual void onRenderScene()
    {
        clearDisplay();
        drawTitle();
        // drawParameters();
        drawModules();
        drawBorder();
    }

    virtual void drawModules()
    {
        for (auto &module : _modules.getData())
        {
            if (PSModule *m = dynamic_cast<PSModule *>(module.second))
            {                
                printf("MODULE [%s] : ", m->displayName.c_str());
                for (auto &parameter : m->parms.getData())
                {
                    if (PSParameter *p = dynamic_cast<PSParameter *>(parameter.second))
                    {
                        printf("%s : %0.2f\t", p->displayName.c_str(), p->getValue());
                    }
                }
                printf("\n");
            }
        }
        printf("\n");
    }

    void drawParameters()
    {
        for (auto &item : _params.getData())
        {
            PSParameter *p = dynamic_cast<PSParameter *>(item.second);
            if (p)
            {
                printf("%s : %0.2f\t", p->displayName.c_str(), p->getValue());
            }
        }
        printf("\n");
    }

    virtual void clearDisplay() { system("clear"); }
    virtual void drawTitle() { printf("******** SCENE: %s **********\n\n", displayName.c_str()); }
    virtual void drawBorder() { printf("\n----------------------------------------\n"); }
    void refreshRateHz(uint8_t freq) { refreshTimer.duration(1.0f / freq * 1000); }
};