#pragma once
#include "../model/PSObject.h"
#include "../model/PSParameter.h"
#include "../model/PSObjectCollection.h"

class PSComponent : public PSObject
{
public:
    PSObjectCollection parameters;
    PSComponent(const PSKeys &key, const std::string name) : PSObject(key, name) {}
    ~PSComponent() override {}

    PSParameter *addParameter(PSParameter *p)
    {        
        parameters.addItem(p);
        return p;
    }

    void update()
    {
        for (auto i : parameters.items)
            ((PSParameter *)i.second)->update();
    }

    virtual std::string toString()
    {
        std::string result = "@" + name + "{";
        
        for (auto i : parameters.items)
            result += ((PSParameter *)i.second)->toString();

        result += "}";
        return result;
    }

protected:
    float min, max;
};