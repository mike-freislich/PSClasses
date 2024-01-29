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
        // setValueRange(0, 1);
    }
    ~PSCButton() override {}

    static PSCButton *create(const char *key, int pin, const char *displayName)
    {
        PSCButton *newButton = PSController::create<PSCButton>(key, pin, displayName);
        newButton->debounceMS(30);
        return newButton;
    }

    void serializeCustomProperties(StringBuilder *sb) override
    {
        sb->addPair("state", isPressed())
            ->delimiter();
    }

    void buttonType(const PSCButtonType &bt) { _buttonType = bt; }

    bool isPressed() { return (_value); }

protected:
    PSCButtonType _buttonType = Momentary;

    virtual bool readValue() override
    {
        if (_readMode == PSControllerReadMode::PSCRandom)
        {
            float v = (float)((rand() % (int)(_range * 10000))) / 10000.0f;            
            v = (v <= 0.5f) ? 0 : 1;
            return setValue(v);
        }
        return false;
    }
};