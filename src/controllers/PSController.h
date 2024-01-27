#pragma once
#include <vector>
#include "PSKeys.h"
#include "PSObject.h"
#include "timing.h"
#include "FastMath.h"
#include "PSParameter.h"
#include "StringBuilder.h"

enum PSParameterMode
{
    STANDARD_PARM,
    SHIFT_PARM
};

enum PSControllerReadMode
{
    PSCRandom,
    PSCHardware,
    PSCSine
};

class PSController : public PSObject
{
public:
    PSObjectCollection params;
    PSObjectCollection paramsShift;

    PSController(const PSK &key, const std::string &name, float minV = 0, float maxV = 127, bool allowRandom = false)
        : _allowRandom(allowRandom), PSObject(key, name)
    {
        setValueRange(minV, maxV);
        _allowRandom = true;
        bounceTimer.start(0);
    }

    virtual ~PSController() override
    {
        params.items.clear();
        paramsShift.items.clear();
    }

    bool didChange() { return _changed; }

    float getValue() { return _value; }

    virtual bool update() override
    {
        if (readValue())
        {
            for (auto item : activeParameters()->items)
            {
                if (PSParameter *p = dynamic_cast<PSParameter *>(item.second))
                {
                    p->setValueFromController(_value);
                    p->update();
                    _changed = false;
                }
            }
            return true;
        }
        return false;
    }

    PSObjectCollection *activeParameters() { return useShiftMode() ? &paramsShift : &params; }

    void clearParameters()
    {
        paramsShift.items.clear();
        params.items.clear();
    }

    bool useShiftMode() { return (isShiftPressed() && paramsShift.items.size() > 0); }

    bool isShiftPressed() { return (Parameters.byKey(CTRL_BTN_Shift)->getValue()); }

    virtual PSK getKey() { return key; }

    virtual PSController *setPin(uint8_t pin)
    {
        // TODO implement hardware setup
        _pin = pin;
        return this;
    }

    /**
     * @brief Set the Value Range object
     * The expected hardware min and max values from analogRead().
     * Values outside of this range will be clamped.
     * @param min
     * @param max
     * @return PSController*
     */
    PSController *setValueRange(float min, float max)
    {
        _min = min;
        _max = max;
        _range = _max - _min;
        return this;
    }

    PSController *assignParameter(PSParameter *pAssign, const PSParameterMode &parameterMode)
    {
        if (!pAssign)
            return this;

        PSObjectCollection *parameters = (parameterMode == SHIFT_PARM) ? &paramsShift : &params;
        if (!(parameters->exists(pAssign->key)))
        {
            printf("%s\t: %s -> %s\n",
                   (parameterMode == SHIFT_PARM) ? "shift" : "normal",
                   psk_tostr(this->key).c_str(),
                   psk_tostr(pAssign->key).c_str());
            parameters->addItem(pAssign);
        }
        return this;
    }

    void debounceMS(uint32_t delay) { bounceTimer.start(delay); }

    uint32_t getDebounceMS() { return bounceTimer.getDuration(); }

    std::string serializeParamaterBank(PSParameterMode bank)
    {
        StringBuilder sb;
        std::string mode = (bank == STANDARD_PARM) ? "normal" : "shift";
        PSObjectCollection *collection = (bank == STANDARD_PARM) ? &params : &paramsShift;

        sb.startElement()
            ->addPair("mode", mode)
            ->add(", ")
            ->startArray("assigned");

        int count = 0;
        for (auto &item : collection->items)
        {
            if (PSParameter *p = dynamic_cast<PSParameter *>(item.second))
            {
                sb.startElement()
                    ->addPair("pkey", psk_tostr(p->key))
                    ->endElement();
                count++;
                if (count < collection->items.size())
                    sb.add(",");
            }
        }

        sb.endArray()
            ->endElement();

        return sb.toString();
    }

    virtual std::string serialize() override
    {
        StringBuilder sb;

        sb.startElement()
            ->addPair("name", typeName())
            ->add(", ")
            ->addPair("key", psk_tostr(key))
            ->add(", ")
            ->addPair("pin", std::to_string(_pin))
            ->add(", ")
            ->addPair("debounce", std::to_string(getDebounceMS()))
            ->add(", ");
        sb.startArray("PARMS");
        sb.add(serializeParamaterBank(PSParameterMode::STANDARD_PARM))->add(", ");
        sb.add(serializeParamaterBank(PSParameterMode::SHIFT_PARM));
        sb.endArray()
            ->endElement();

        return sb.toString();
    }

    virtual const char *typeName() override { return "PSController"; }

    void setReadMode(const PSControllerReadMode &readMode) { _readMode = readMode; }

protected:
    PSControllerReadMode _readMode = PSCSine;
    bool _changed, _allowRandom;
    float _value, _min, _max, _range;
    uint8_t _pin;
    SimpleTimer bounceTimer = SimpleTimer(0);
    float _randPhase = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);

    virtual bool readValue()
    {
        float v = 0;
        switch (_readMode)
        {
        case PSCRandom:
            v = (float)(rand() % (int)(_range * 10000)) / 10000.0f;
            return setValue(v);
            break;
        case PSCSine:
            v = (sineWavePoint(0.5f, 2.0f, _randPhase, millis()) + 0.5f) * _range;
            return setValue(v);
            break;
        case PSCHardware:
            break;
        };
        return false;
    }

    virtual bool setValue(float val)
    {
        float sval = val / _range;
        if (sval != _value)
        {
            if (bounceTimer.update())
            {
                _value = sval;
                _changed = true;
            }
        }
        return _changed;
    }
};