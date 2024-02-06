#pragma once
#include "PSController.h"

// TODO implement momentary / latching button type
enum PSCButtonType
{
    Momentary,
    Latching
};

class PSCButton : public PSController
{
public:
    PSCButton() : PSController()
    {
        typeName = "PSCButton";
        _readMode = PSControllerReadMode::PSCRandom;
    }
    ~PSCButton() override {}

    static PSCButton *create(const std::string &key, int pin, const std::string &displayName)
    {
        PSCButton *newButton = PSController::create<PSCButton>(key, pin, displayName);
        newButton->debounceMS(30);    
        return newButton;
    }

    void buttonType(const PSCButtonType &bt) { _buttonType = bt; }

    bool isPressed() { return (_value); }

protected:
    PSCButtonType _buttonType = Momentary;

    virtual bool readValue() override
    {
        if (_readMode == PSControllerReadMode::PSCRandom)
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