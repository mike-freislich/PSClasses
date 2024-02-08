#pragma once
#include "AudioStub.h"
#include "ParameterManager.h"
#include "Controller.h"

namespace ps
{
    struct ControllerTarget
    {
        std::string key;
        Controller *controller;        
        ControllerTarget(const std::string &k, Controller *c) : key(k), controller(c) {}
    };

    typedef std::vector<ControllerTarget> PSControllerTargetVector;

    class Module : public CollectionItemBase
    {
    public:
        ParameterManager moduleParameters;

        Module() : CollectionItemBase() { typeName = "Module"; }
        ~Module() override {}

        Module *addAudioUnit(AudioStream *au)
        {
            audioUnits.push_back(au);
            return this;
        }

        template <typename T>
        static T *create(const char *key, const char *displayName)
        {
            static_assert(std::is_base_of<Module, T>::value, "T must be a derived class of Module");
            T *newMod = new T();
            newMod->key = key;
            newMod->displayName = displayName;
            return newMod;
        }

        Parameter *addParameter(Parameter *p)
        {
            moduleParameters.add(p->key, p);
            return p;
        }

        Parameter *getParameter(const std::string &key)
        {
            if (moduleParameters.contains(key))
                return moduleParameters[key];
            else
                return nullptr;
        }

        void attachController(const std::string &key, Controller *controller)
        {
            if (Parameters.contains(key))
            {
                if (Parameter *p = Parameters[key])
                {
                    if (controller)
                    {
                        std::cout << controller->displayName << "->" << displayName << "_" << p->displayName << ", ";
                        ParameterMode mode = (arc4random() % 2 == 0) ? SHIFT_PARM : STANDARD_PARM;
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

        Module *attachControllers(const PSControllerTargetVector &connections)
        {
            std::cout << "[" << displayName << "]: ";
            for (auto connection : connections)
                attachController(connection.key, connection.controller);
            printf("\n");
            return this;
        }

    protected:
        std::vector<AudioStream *> audioUnits;

        // handle units that have a function (float, float, short) e.g. AudioWaveFormDC
        template <typename T>
        void updateUnits(Parameter *p1, Parameter *p2, Parameter *p3, void (T::*func)(float, float, short), float multiplier = 1.0f)
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

        // handle units that have a function (float) e.g. AudioAmplifier.gain
        template <typename T, typename V>
        void updateUnits(Parameter *p, void (T::*func)(V), float multiplier = 1.0f)
        {
            if (p->changed(true))
            {
                for (auto i : audioUnits)
                    if (T *e = dynamic_cast<T *>(i))
                    {
                        auto f = [func, e, multiplier](V value)
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

        // handle audio unit with a single parameter e.g. AudioAmplifier.gain
        template <typename T, typename X>
        void updateUnit1(T *instance, Parameter *p, void (T::*func)(X), float multiplier = 1.0f)
        {
            if (p->changed(true))
            {
                auto f = [func, instance, multiplier](X value)
                {
                    (instance->*func)(value * multiplier);
                };
                f(p->getValue());
            }
        }
    };
}