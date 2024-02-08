#pragma once
#include "Controller.h"

namespace ps
{

    // TODO implement momentary / latching button type
    enum CButtonType
    {
        Momentary,
        Latching
    };

    class CButton : public Controller
    {
    public:
        CButton() : Controller()
        {
            typeName = "CButton";
            _readMode = ControllerReadMode::PSCRandom;
        }
        ~CButton() override {}

        static CButton *create(const std::string &key, int pin, const std::string &displayName)
        {
            CButton *newButton = Controller::create<CButton>(key, pin, displayName);
            newButton->debounceMS(30);
            return newButton;
        }

        void buttonType(const CButtonType &bt) { _buttonType = bt; }

        bool isPressed() { return (_value); }

    protected:
        CButtonType _buttonType = Momentary;

        virtual bool readValue() override
        {
            if (_readMode == ControllerReadMode::PSCRandom)
            {
                float v = (float)((arc4random() % (int)(_range * 10000))) / 10000.0f;
                v = (v <= 0.5f) ? 0 : 1;
                return setValue(v);
            }
            return false;
        }

        void serializeCustomProperties(StringBuilder *sb) override
        {
            sb->addPair("state", isPressed())
                ->delimiter();
        }
    };

}