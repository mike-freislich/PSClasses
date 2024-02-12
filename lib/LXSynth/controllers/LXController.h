#pragma once
#include "CollectionLiteItem.h"
#include "ContKeys.h"
#include "LXParameter.h"
#include "timing.h"

class LXController : public CollectionLiteItem<ContKeys>
{
public:
    LXController(ContKeys key) : CollectionLiteItem(key) { _debounceTimer.start(); }
    virtual ItemType getType() override { return ItemType::TLXController; }

    template <typename ControllerType>
    ControllerType *attachParameters(const std::vector<ParmKeys> &parmKeys)
    {
        _parameters.clear();
        for (auto pkey : parmKeys)
        {
            printf("Controller: %s -> Parameter : %s\n", this->typeName(), parmKey_cstr(pkey));
            _parameters.push_back(Parameters[pkey]);
        }
        // afterAttachParameters();
        return (ControllerType *)this;
    }

    // virtual void afterAttachParameters() {}
    virtual void update() override
    {
        if (checkDebounce())
            updateController();
    }
    virtual void updateController()
    {
        int v = readValue();
        for (auto p : _parameters)
            p->setValue(mapToParameterValue(p, v));
    }

    template <typename T>
    T *setup(uint16_t pin, uint32_t debounceMS, int rangeMin, int rangeMax)
    {
        debounceMs(debounceMS);
        setPin(pin);
        setRange(rangeMin, rangeMax);
        return static_cast<T *>(this);
    }

    FLASHMEM LXController *debounceMs(uint32_t durationMs)
    {
        _debounceTimer.duration(durationMs);
        return this;
    }

    FLASHMEM void setPin(uint16_t pin) { _pin = pin; }

    FLASHMEM void setRange(int min, int max)
    {
        _min = min;
        _max = max;
    }

protected:
    std::vector<LXParameter *> _parameters;
    int _min = 0, _max = 1;
    uint16_t _pin = 0;

    /**
     * @brief
     * checks if the debounce duration has completed;
     * @return true
     * @return false
     */
    FLASHMEM bool checkDebounce() { return _debounceTimer.update(); }

    FLASHMEM float mapToParameterValue(LXParameter *p, int controllerValue)
    {
        float pmin, pmax;
        p->getRange(pmin, pmax);
        float v = map((float)controllerValue, (float)_min, (float)_max, pmin, pmax);
        return v;
    }

    virtual int readValue()
    {
        // TODO get the value from the controller
        return rand() % (_max - _min) + _min;
    }

private:
    SimpleTimer _debounceTimer;
};

