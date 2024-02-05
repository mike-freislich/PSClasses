#pragma once
#include "PSParameterManager.h"
#include "PSControllerConnection.h"

class PSModule : public CollectionItemBase
{
public:
    PSParameterManager moduleParameters;

    PSModule() : CollectionItemBase() { typeName = "PSModule"; }
    ~PSModule() override {}

    PSModule *addAudioUnit(AudioStream *au)
    {
        audioUnits.push_back(au);
        return this;
    }

    template <typename T>
    static T *create(const char *key, const char *displayName)
    {
        static_assert(std::is_base_of<PSModule, T>::value, "T must be a derived class of PSModule");
        T *newMod = new T();
        newMod->key = key;
        newMod->displayName = displayName;
        return newMod;
    }

    PSParameter *addParameter(PSParameter *p)
    {
        moduleParameters.add(p->key, p);
        return p;
    }

    PSParameter *getParameter(const std::string &key)
    {
        if (moduleParameters.contains(key))
            return moduleParameters[key];
        else
            return nullptr;
    }

    void attachController(const std::string &key, PSController *controller)
    {
        if (Parameters.contains(key))
        {
            if (PSParameter *p = Parameters[key])
            {
                if (controller)
                {
                    std::cout << controller->displayName << "->" << displayName << "_" << p->displayName << ", ";
                    PSParameterMode mode = (random() % 2 == 0) ? SHIFT_PARM : STANDARD_PARM;
                    controller->assignParameter(p, mode);
                }
                else
                {
                    printf("unable to assign parameter to null controller\n");
                }
            }
        }
        else
        {
            printf("unable to assign controller to null parameter\n");
        }
    }

    PSModule *attachControllers(const PSControllerConnectionVector &connections)
    {
        std::cout << "[" << displayName << "]: ";
        for (auto connection : connections)
            attachController(connection.key, connection.controller);
        printf("\n");
        return this;
    }

protected:
    std::vector<AudioStream *> audioUnits;
};