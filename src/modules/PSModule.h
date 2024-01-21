#pragma once
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
            printf("%s->%s_%s, ", controller->name.c_str(), name.c_str(), p->name.c_str());
            p->attachController(controller);
        }
        else
        {
            printf("unable to attach controller to null parameter\n");
        }
    }

    PSModule *attachControllers(const PSControllerConnectionVector &connections)
    {
        printf("[%s]: ", name.c_str());
        for (auto connection : connections)
            attachController(connection.key, connection.controller);            
        printf("\n");
        return this;
    }

protected:
    float min, max;
};