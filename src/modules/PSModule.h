#pragma once
#include "../model/PSObject.h"
#include "../model/PSParameter.h"
#include "../model/PSObjectCollection.h"

class PSModule : public PSObject, public PSObjectCollection
{
public:
    PSModule(const PSKeys &key, const std::string name) : PSObject(key, name), PSObjectCollection() {}
    ~PSModule() override {}

    PSParameter *addParameter(PSParameter *p)
    {        
        addItem(p);
        return p;
    }

    void update()
    {
        for (auto i : items)
            ((PSParameter *)i.second)->update();
    }

    virtual std::string toString()
    {
        std::string result = "@" + name + "{";
        
        for (auto i : items)
            result += ((PSParameter *)i.second)->toString();

        result += "}";
        return result;
    }

protected:
    float min, max;
};