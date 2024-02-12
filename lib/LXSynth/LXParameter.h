#pragma once
#include "CollectionLiteItem.h"

class LXParameter : public CollectionLiteItem<ParmKeys>
{
public:
    LXParameter(ParmKeys key) : CollectionLiteItem(key) {}
    ItemType getType() override { return ItemType::TLXParameter; }

    LXParameter *setValue(float v)
    {
        v = clampf(v, min_, max_);

        if (v != value_)
        {
            changed_ = true;
            value_ = v;
        }

        return this;
    }

    LXParameter *setValue(float v, float originMin, float originMax)
    {
        setValue(map(v, originMin, originMax, min_, max_));
        return this;
    }

    float getValue() { return value_; }

    LXParameter *setRange(float min, float max)
    {
        min_ = min;
        max_ = max;
        value_ = clampf(value_, min_, max_);
        return this;
    }
    void getRange(float &min, float &max)
    {
        min = min_;
        max = max_;
    }

    float getMin() { return min_; }
    float getMax() { return max_; }

    bool changed(bool clearFlag)
    {
        bool result = changed_;

        if (clearFlag)
            changed_ = false;

        return result;
    }

    void update() override { printf("updating %s\n", ItemTypeToName(getType())); }

private:
    float value_, min_, max_;
    bool changed_;
};