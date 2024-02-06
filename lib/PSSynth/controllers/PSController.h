#pragma once
#include <vector>
#include "PSKeys.h"
#include "timing.h"
#include "FastMath.h"
#include "PSParameterManager.h"
#include "Collection.h"
#include "CollectionItem.h"
#include "StringBuilder.h"

enum PSControllerReadMode
{
    PSCRandom,
    PSCHardware,
    PSCSine
};

class PSController : public CollectionItemBase
{
public:
    PSParameterManager params;
    PSParameterManager paramsShift;

    PSController() : CollectionItemBase()
    {
        typeName = "PSController";
        bounceTimer.start(0);
    }

    template <typename T>
    static T *create(const std::string &key, int pin, const std::string &displayName)
    {
        static_assert(std::is_base_of<PSController, T>::value, "T must be a derived class of Controller");
        
        T *c = CollectionItemBase::create<T>(key, displayName);    
        c->setPin(pin);
        c->displayName = displayName;    
        return c;
    }

    virtual ~PSController() override {}

    bool didChange() { return _changed; }

    float getValue() { return _value; }

    virtual bool update() override
    {
        if (readValue())
        {
            for (auto item : activeParameters()->getData())
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

    PSParameterManager *activeParameters() { return useShiftMode() ? &paramsShift : &params; }

    void clearParameters()
    {
        paramsShift.clear();
        params.clear();
    }

    bool useShiftMode() { return (isShiftPressed() && paramsShift.size() > 0); }

    bool isShiftPressed() { return (Parameters[CTRL_BTN_Shift]->getValue()); }

    virtual PSController *setPin(uint16_t pin)
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

        PSParameterManager *parameters = (parameterMode == SHIFT_PARM) ? &paramsShift : &params;
        if (!(parameters->contains(pAssign->key)))
        {
            printf("%s\t: %s -> %s\n",
                   (parameterMode == SHIFT_PARM) ? "shift" : "normal",
                   this->key.c_str(),
                   pAssign->key.c_str());
            parameters->add(pAssign->key, pAssign);
        }
        return this;
    }

    void debounceMS(uint32_t delay) { bounceTimer.start(delay); }

    uint32_t getDebounceMS() { return bounceTimer.getDuration(); }

    std::string serializeParamaterBank(PSParameterMode bank)
    {
        StringBuilder sb;
        std::string mode = (bank == STANDARD_PARM) ? "normal" : "shift";
        PSParameterManager *collection = (bank == STANDARD_PARM) ? &params : &paramsShift;

        sb.startElement()
            ->addPair("mode", mode)
            ->delimiter()
            ->startArray("assigned");

        int count = 0;
        for (auto &item : collection->getData())
        {
            if (PSParameter *p = dynamic_cast<PSParameter *>(item.second))
            {
                sb.startElement()
                    ->addPair("pkey", p->key)
                    ->endElement();
                count++;
                if (count < collection->size())
                    sb.add(",");
            }
        }

        sb.endArray()
            ->endElement();

        return sb.toString();
    }

    virtual void serialize(StringBuilder *sb) override
    {

        sb->begin()
            ->addPair("key", key)
            ->delimiter()
            ->addPair("type", typeName)
            ->delimiter()
            ->addPair("name", displayName)
            ->delimiter()
            ->addPair("pin", _pin)
            ->delimiter()
            ->addPair("debounce", (int)getDebounceMS())
            ->delimiter()
            ->addPair("min", _min)
            ->delimiter()
            ->addPair("max", _max)
            ->delimiter();
        
        serializeCustomProperties(sb);

        sb->startArray("PARMS")
            ->add(serializeParamaterBank(PSParameterMode::STANDARD_PARM))
            ->delimiter()
            ->add(serializeParamaterBank(PSParameterMode::SHIFT_PARM))
            ->endArray();
    }

    virtual void serializeCustomProperties(StringBuilder *sb) {}

    void setReadMode(const PSControllerReadMode &readMode) { _readMode = readMode; }

protected:
    PSControllerReadMode _readMode = PSCSine;
    bool _changed, _allowRandom;
    float _value, _min, _max, _range;
    uint16_t _pin;
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