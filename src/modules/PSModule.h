#pragma once
#include "PSObject.h"
#include "PSObjectCollection.h"
#include "PSParameterManager.h"
#include "PSControllerConnection.h"

class PSModule : public PSObject, public PSObjectCollection
{
public:
    PSModule(const PSK &key, const std::string name) : PSObject(key, name), PSObjectCollection() {}
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

    void attachController(const PSK &key, PSController *controller)
    {   
        if (PSParameter *p = Parameters.byKey(key))
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