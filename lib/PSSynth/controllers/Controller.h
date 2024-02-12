#pragma once
#include <vector>
#include "Keys.h"
#include "timing.h"
#include "FastMath.h"
#include "ParameterManager.h"
#include "CollectionLite.h"
// #include "CollectionItem.h"
#include "StringBuilder.h"

namespace PS
{
    enum ControllerReadMode
    {
        PSCRandom,
        PSCHardware,
        PSCSine
    };

    class Controller : public CollectionLiteItem
    {
    public:
        ParameterManager params;
        ParameterManager paramsShift;
        const char * displayName;

        Controller(const char *key) : CollectionLiteItem(key)
        {
            bounceTimer.start(0);
        }
        ItemType getType() override { return ItemType::TController; }

        template <typename T>
        static T *create(const char *key, int pin, const std::string &displayName)
        {
            static_assert(std::is_base_of<Controller, T>::value, "T must be a derived class of Controller");            
            T *c = new T(key);
            c->setPin(pin);
            c->displayName = displayName;
            return c;
        }

        virtual ~Controller() override {}

        bool didChange() { return _changed; }

        float getValue() { return _value; }

        virtual bool update() override
        {
            if (readValue())
            {
                for (auto item : activeParameters()->getData())
                {
                    if (Parameter *p = item.second)
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

        ParameterManager *activeParameters() { return useShiftMode() ? &paramsShift : &params; }

        void clearParameters()
        {
            paramsShift.clear();
            params.clear();
        }

        bool useShiftMode() { return (isShiftPressed() && paramsShift.size() > 0); }

        bool isShiftPressed() { return (Parameters[CTRL_BTN_Shift]->getValue()); }

        virtual Controller *setPin(uint16_t pin)
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
         * @return Controller*
         */
        Controller *setValueRange(float min, float max)
        {
            _min = min;
            _max = max;
            _range = _max - _min;
            return this;
        }

        Controller *assignParameter(Parameter *pAssign, const ParameterMode &parameterMode)
        {
            if (!pAssign)
                return this;

            ParameterManager *parameters = (parameterMode == SHIFT_PARM) ? &paramsShift : &params;
            if (!(parameters->contains(pAssign->key)))
            {
                printf("%s\t: %s -> %s\n",
                       (parameterMode == SHIFT_PARM) ? "shift" : "normal",
                       this->key,
                       pAssign->key.c_str());
                parameters->add(pAssign->key, pAssign);
            }
            return this;
        }

        void debounceMS(uint32_t delay) { bounceTimer.start(delay); }

        uint32_t getDebounceMS() { return bounceTimer.getDuration(); }

        std::string serializeParamaterBank(ParameterMode bank)
        {
            StringBuilder sb;
            std::string mode = (bank == STANDARD_PARM) ? "normal" : "shift";
            ParameterManager *collection = (bank == STANDARD_PARM) ? &params : &paramsShift;

            sb.startElement()
                ->addPair("mode", mode)
                ->delimiter()
                ->startArray("assigned");

            size_t count = 0;
            for (auto &item : collection->getData())
            {
                if (Parameter *p = item.second)
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
                ->addPair("type", typeName())
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
                ->add(serializeParamaterBank(ParameterMode::STANDARD_PARM))
                ->delimiter()
                ->add(serializeParamaterBank(ParameterMode::SHIFT_PARM))
                ->endArray();
        }

        virtual void serializeCustomProperties(StringBuilder *sb) {}

        void setReadMode(const ControllerReadMode &readMode) { _readMode = readMode; }

    protected:
        ControllerReadMode _readMode = PSCSine;
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
                v = (float)(arc4random() % (int)(_range * 10000)) / 10000.0f;
                return setValue(v);
                break;
            case PSCSine:
                v = (sineWavePoint(0.5f, 0.05f, _randPhase, millis()) + 0.5f) * _range;
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

}