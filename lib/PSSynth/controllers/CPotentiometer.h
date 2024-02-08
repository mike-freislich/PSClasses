#pragma once
#include "Controller.h"
#include "StringBuilder.h"

namespace ps
{

    class CPotentiometer : public Controller
    {
    public:
        CPotentiometer() : Controller()
        {
            typeName = "CPotentiometer";
        }
        ~CPotentiometer() override {}

        static CPotentiometer *create(const char *key, int pin, const char *displayName)
        {
            CPotentiometer *newPot = Controller::create<CPotentiometer>(key, pin, displayName);
            newPot->debounceMS(5);
            newPot->setValueRange(10, 1010);
            newPot->setReadMode(ControllerReadMode::PSCSine);
            return newPot;
        }

    protected:
        void serializeCustomProperties(StringBuilder *sb) override
        {
        }
    };

}