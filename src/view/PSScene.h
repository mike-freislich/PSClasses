#pragma once
#include "../model/PSParameter.h"
#include "../model/PSKeys.h"
#include "../utils/timing.h"

using namespace std;

class PSScene : public PSObject
{
public:
    PSScene(const PSKeys &key, const std::string &name, PSModule *module) : PSObject(key, name)
    {
        addModule(module);
    }

    ~PSScene() override {
        _modules.items.clear();
        _params.items.clear();
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
    
    PSScene * addModule(PSModule *c)
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

    virtual void render()
    {
        if (_active)
        {
            if (refreshTimer.update())
            {
                system("clear");
                printf("******** SCENE: %s **********\n", name.c_str());
                for (auto item : _params.items)
                {
                    PSParameter *p = dynamic_cast<PSParameter *>(item.second);
                    if (p)
                    {
                        printf("%s : %0.2f\t", p->name.c_str(), p->getValue());
                    }
                }                
                printf("\n----------------------------------------\n");
            }            
        }
    }

protected:
    SimpleTimer refreshTimer = SimpleTimer(50);
    PSObjectCollection _params;
    PSObjectCollection _modules;
    bool _active;
};