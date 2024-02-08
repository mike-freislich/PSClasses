#pragma once
// #include "Parameter.h"
#include "PSModuleManager.h"
#include "ParameterManager.h"
#include "ControllerManager.h"
#include "Keys.h"
#include "timing.h"

namespace ps
{

    class PSScene : public CollectionItemBase
    {

    private:
        SimpleTimer refreshTimer = SimpleTimer(0);
        bool shouldRender() { return _active && refreshTimer.update(); }

    protected:
        ParameterManager _params;
        PSModuleManager _modules;
        ControllerManager _controllers;
        bool _active;

    public:
        ~PSScene() override
        {
            _modules.clear();
            _params.clear();
            _controllers.clear();
        }

        template <typename T>
        static T *create(const char *key, const string &displayName)
        {
            static_assert(std::is_base_of<PSScene, T>::value, "T must be a derived class of PSScene");
            PSScene *scene = new T();
            scene->key = key;
            scene->refreshRateHz(120);
            scene->displayName = displayName;
            return dynamic_cast<T *>(scene);
        }

        void setDisplay()
        {
            // TODO - implement display
        }

        void activate()
        {
            _active = true;
            refreshTimer.start();
        }
        void deactivate()
        {
            _active = false;
            refreshTimer.stop();
        }

        void addParameter(Parameter *param) { _params.add(param->key, param); }

        PSScene *addModule(Module *c)
        {
            if (c)
            {
                _modules.add(c->key, c);
            }
            return this;
        }

        // void initParameters(Module *m)
        // {
        //     if (m)
        //     {
        //         printf("scene - adding parameters\n");
        //         for (auto &item : m->items)
        //         {
        //             Parameter *p = dynamic_cast<Parameter *>(item.second);
        //             if (p)
        //                 _params.addItem(p);
        //         }
        //     }
        // }

        void render()
        {
            if (shouldRender())
                onRenderScene();
        }

        virtual void onRenderScene()
        {
            clearDisplay();
            drawTitle();
            // drawParameters();
            drawModules();
            drawBorder();
            drawButtons();
            drawBorder();
        }

        virtual void drawModules()
        {
            for (auto &module : _modules.getData())
            {
                if (Module *m = dynamic_cast<Module *>(module.second))
                {
                    printf("MODULE [%s] : ", m->displayName.c_str());
                    for (auto &parameter : m->moduleParameters.getData())
                    {
                        if (Parameter *p = dynamic_cast<Parameter *>(parameter.second))
                        {
                            printf("%s : %0.2f\t", p->displayName.c_str(), p->getValue());
                        }
                    }
                    printf("\n");
                }
            }
            printf("\n");
        }

        virtual void drawParameters()
        {
            for (auto &item : _params.getData())
            {
                Parameter *p = dynamic_cast<Parameter *>(item.second);
                if (p)
                {
                    printf("%s : %0.2f\t", p->displayName.c_str(), p->getValue());
                }
            }
            printf("\n");
        }

        virtual void drawButtons()
        {
            printf("\nButtons : ");
            for (auto &button : Controllers.buttons)
            {
                if (Parameter *p = Parameters[button->key])
                {
                    if (button->isPressed())
                        printf("<<%s>>\t", p->displayName.c_str());
                    else
                        printf("..%s..\t", p->displayName.c_str());
                }
            }
        }

        std::string parmDisplay(Parameter *p) { return "(" + p->displayName + " " + std::to_string(p->getValue()) + ")"; }

        virtual void clearDisplay() { system("clear"); }
        virtual void drawTitle() { printf("******** SCENE: %s **********\n\n", displayName.c_str()); }
        virtual void drawBorder() { printf("\n----------------------------------------\n"); }
        void refreshRateHz(uint8_t freq) { refreshTimer.duration(1.0f / freq * 1000); }
    };

}