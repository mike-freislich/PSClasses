#pragma once
#include "../model/PSObject.h"
#include "../model/PSParameter.h"
#include "../model/PSObjectCollection.h"
#include "../model/PSControllerConnection.h"

class PSModule : public PSObject, public PSObjectCollection
{
public:
    PSModule(const PSKeys &key, const std::string name) : PSObject(key, name), PSObjectCollection() {}
    ~PSModule() override { }

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

    void attachController(const PSKeys &key, PSController *controller)
    {
        PSParameter *p = getItem<PSParameter>(key);
        if (p)
        {
            printf("attaching controller %s to parameter %s\n", controller->name.c_str(), p->name.c_str());
            p->attachController(controller);
        }
        else
        {
            printf("unable to attach controller to null parameter\n");
        }
    }

    PSModule *attachControllers(const PSControllerConnectionVector &connections)
    {
        printf("attaching %zu controllers\n", connections.size());

        for (auto connection : connections)
            attachController(connection.key, connection.controller);

        return this;
    }

protected:
    float min, max;
};