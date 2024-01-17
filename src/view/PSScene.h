#pragma once
#include "../model/PSParameter.h"
#include "../model/PSKeys.h"

using namespace std;

class PSScene : public PSObject
{
public:
    PSScene(const PSKeys &key, const std::string &name,  PSModule *module) : PSObject(key, name)
    {
        addModule(module);
    }

    ~PSScene() override {}

    void setDisplay()
    {
        // TODO - implement display
    }

    void activate() { _active = true; }
    void deactivate() { _active = false; }
    void addParameter(PSParameter *param) { _params.push_back(param); }
    void addModule(PSModule *c)
    {
        if (c)
            _modules.addItem(c);
    }

    virtual void render()
    {
        if (_active)
        {
            for (auto p : _params)
            {
                printf("%s : %0.2f\n", p->name.c_str(), p->getValue());
            }
        }
        printf("----------------------------------------\n");
    }

protected:
    PSParameterVector _params;
    PSObjectCollection _modules;
    bool _active;
};