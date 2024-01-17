#pragma once
#include "PSCEnvelope.h"

class PSComponentManager : public PSObjectCollection
{
public:
    ~PSComponentManager() override {}

    void update()
    {
        for (auto &entry : items)
            ((PSComponent *)entry.second)->update();
    }

    PSController *controller(const PSKeys &key) { return getItem<PSController>(key); }

    PSCEnvelope *getEnvelope(const PSKeys &key) { return getItem<PSCEnvelope>(key); }
    //PSCEnvelope *getLFO(const PSKeys &key) { return getItem<PSCEnvelope>(key); }

private:
};