#pragma once
#include "../model/PSParameter.h"
#include "../model/PSKeys.h"

using namespace std;

class PSScene : public PSObject
{
public:
    PSScene(const PSKeys &key, const std::string &name,  PSComponent *component) : PSObject(key, name)
    {
        addComponent(component);
    }

    ~PSScene() override {}

    void setDisplay()
    {
        // TODO - implement display
    }

    void activate() { _active = true; }
    void deactivate() { _active = false; }
    void addParameter(PSParameter *param) { _params.push_back(param); }
    void addComponent(PSComponent *c)
    {
        if (c)
            _components.addItem(c);
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
    PSObjectCollection _components;
    bool _active;
};