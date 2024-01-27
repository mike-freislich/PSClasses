#pragma once
#include "PSParameterManager.h"
#include "PSControllerConnection.h"

class PSModule : public PSObject, public PSObjectCollection
{
public:
    PSModule(const PSK &key, const std::string name) : PSObject(key, name), PSObjectCollection() {}
    ~PSModule() override {}

    PSParameter *addParameter(PSParameter *p)
    {
        addItem(p);
        return p;
    }

    PSParameter *getParameter(const PSK &key) { return getItem<PSParameter>(key); }

    // virtual std::string toString()
    // {
    //     std::string result = "@" + name + "{";
    //     for (auto i : items)
    //         result += ((PSParameter *)i.second)->toString();
    //     result += "}";
    //     return result;
    // }

    void attachController(const PSK &key, PSController *controller)
    {
        if (PSParameter *p = Parameters.byKey(key))
        {
            if (controller)
            {
                printf("%s->%s_%s, ", controller->name.c_str(), name.c_str(), p->name.c_str());
                PSParameterMode mode = (random() % 2 == 0) ? SHIFT_PARM : STANDARD_PARM;
                controller->assignParameter(p, mode);
            }            
            else {
                printf("unable to assign parameter to null controller\n");
            }
        }
        else
        {
            printf("unable to assign controller to null parameter\n");
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
    
};