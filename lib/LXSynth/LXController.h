#pragma once
#include "CollectionLiteItem.h"
#include "ContKeys.h"
#include "LXParameter.h"
#ifdef __ARM_ARCH_7EM__
#include "SimpleTimer.h"
#else
#include "timing.h"
#endif

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

    LXController *debounceMs(uint32_t durationMs)
    {
        _debounceTimer.duration(durationMs);
        return this;
    }

    /**
     * @brief
     * checks if the debounce duration has completed;
     * @return true
     * @return false
     */
    bool checkDebounce() { return _debounceTimer.update(); }

protected:
    std::vector<LXParameter *> _parameters;
    int _min = 0, _max = 1;

    float mapToParameterValue(LXParameter *p, int controllerValue)
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

class LXPotentiometer : public LXController
{
public:
    LXPotentiometer(ContKeys key) : LXController(key)
    {
        debounceMs(5); // default pot debounce
        _min = 10;
        _max = 1010;
    }
    ItemType getType() override { return ItemType::TLXPotentiometer; }

    // void updateController() override { LXController::updateController(); }

private:
    // int readValue() override { return LXController::readValue(); }
};

class LXButton : public LXController
{
public:
    LXButton(ContKeys key) : LXController(key)\
    {
        debounceMs(30); // default button debounce
        _min = 0;
        _max = 1;
    }
    ItemType getType() override { return ItemType::TLXButton; }

    // void updateController() override { LXController::updateController(); }

private:
    // int readValue() override { return LXController::readValue(); }
};

class LXRotary : public LXController
{
public:
    LXRotary(ContKeys key) : LXController(key)
    {
        debounceMs(5); // default Rotary debounce
        _min = -1;
        _max = 1;
    }
    ItemType getType() override { return ItemType::TLXRotary; }

    // void updateController() override { LXController::updateController(); }

private:
    // int readValue() override { return LXController::readValue(); }
};