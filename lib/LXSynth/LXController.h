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
        afterAttachParameters();
        return (ControllerType *)this;
    }

    virtual void afterAttachParameters() {}
    virtual void update() override { if (checkDebounce()) willUpdate();}
    virtual void willUpdate() {}

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

private:
    SimpleTimer _debounceTimer;
};

class LXPotentiometer : public LXController
{
public:
    LXPotentiometer(ContKeys key) : LXController(key)
    {
        debounceMs(5); // default pot debounce
    }
    ItemType getType() override { return ItemType::TLXPotentiometer; }

    void willUpdate() override
    {
    }
};

class LXButton : public LXController
{
public:
    LXButton(ContKeys key) : LXController(key)
    {
        debounceMs(30); // default button debounce
    }
    ItemType getType() override { return ItemType::TLXButton; }

    void willUpdate() override
    {
    }
};

class LXRotary : public LXController
{
public:
    LXRotary(ContKeys key) : LXController(key)
    {
        debounceMs(5); // default Rotary debounce
    }
    ItemType getType() override { return ItemType::TLXRotary; }

    void willUpdate() override
    {
    }
};