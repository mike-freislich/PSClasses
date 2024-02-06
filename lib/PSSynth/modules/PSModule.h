#pragma once
#include "AudioStub.h"
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
                    PSParameterMode mode = (arc4random() % 2 == 0) ? SHIFT_PARM : STANDARD_PARM;
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

    // handle units that have a function (float, float, short)
    template <typename T>
    void updateUnits(PSParameter *p1, PSParameter *p2, PSParameter *p3, void (T::*func)(float, float, short), float multiplier = 1.0f)
    {
        if (p1->changed(true) || p2->changed(true) || p3->changed(true))
        {
            for (auto i : audioUnits)
                if (T *e = dynamic_cast<T *>(i))
                {
                    auto callFunc = [func, e, multiplier](float t_amp, float t_freq, short t_type)
                    {
                        if (auto derived = dynamic_cast<T *>(e))
                            (derived->*func)(t_amp * multiplier, t_freq, t_type);
                        else
                            LOG("Invalid cast!");
                    };
                    callFunc(p1->getValue(), p2->getValue(), p3->getValue());
                }
        }
    }

    // handle units that have a function (float, float, short)
    template <typename T>
    void updateUnits(PSParameter *p, void (T::*func)(float), float multiplier = 1.0f)
    {
        if (p->changed(true))
        {
            for (auto i : audioUnits)
                if (T *e = dynamic_cast<T *>(i))
                {
                    auto f = [func, e, multiplier](float value)
                    {
                        if (auto derived = dynamic_cast<T *>(e))
                            (derived->*func)(value * multiplier);
                        else
                            LOG("Invalid cast!");
                    };
                    f(p->getValue());
                }
        }
    }


};