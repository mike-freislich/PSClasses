#pragma once
#include "PSParameter.h"
#include "PSKeys.h"
#include "timing.h"

using namespace std;

class PSScene : public PSObject
{

private:
    SimpleTimer refreshTimer = SimpleTimer(0);
    bool shouldRender() { return _active && refreshTimer.update(); }

protected:
    PSObjectCollection _params;
    PSObjectCollection _modules;
    PSObjectCollection _controllers;
    bool _active;

public:
    PSScene(const PSK &key, const std::string &name) : PSObject(key, name) { refreshRateHz(20); }

    ~PSScene() override
    {
        _modules.items.clear();
        _params.items.clear();
        _controllers.items.clear();
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

    void addParameter(PSParameter *param) { _params.addItem(param); }

    PSScene *addModule(PSModule *c)
    {
        if (c)
        {
            _modules.addItem(c);
            initParameters(c);
        }
        return this;
    }

    void initParameters(PSModule *m)
    {
        if (m)
        {
            printf("scene - adding parameters\n");
            for (auto &item : m->items)
            {
                PSParameter *p = dynamic_cast<PSParameter *>(item.second);
                if (p)
                    _params.addItem(p);
            }
        }
    }

    void render()
    {
        if (shouldRender())
            onRenderScene();
    }

    virtual void onRenderScene()
    {
        clearDisplay();
        drawTitle();
        //drawParameters();
        drawModules();
        drawBorder();
    }

    virtual void drawModules()
    {
        for (auto &module : _modules.items)
        {
            if (PSModule *m = dynamic_cast<PSModule *>(module.second))
            {
                printf("MODULE [%s] : ", m->name.c_str());
                for (auto &parameter : m->items)
                {
                    if (PSParameter *p = dynamic_cast<PSParameter *>(parameter.second))
                    {
                        printf("%s : %0.2f\t", p->name.c_str(), p->getValue());
                    }
                }
                printf("\n");
            }
        }
        printf("\n");
    }

    void drawParameters()
    {
        for (auto &item : _params.items)
        {
            PSParameter *p = dynamic_cast<PSParameter *>(item.second);
            if (p)
            {
                printf("%s : %0.2f\t", p->name.c_str(), p->getValue());
            }
        }
        printf("\n");
    }

    virtual void clearDisplay() { system("clear"); }
    virtual void drawTitle() { printf("******** SCENE: %s **********\n\n", name.c_str()); }
    virtual void drawBorder() { printf("\n----------------------------------------\n"); }    
    void refreshRateHz(uint8_t freq) { refreshTimer.duration(1.0f / freq * 1000); }
};