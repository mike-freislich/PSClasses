#pragma once
#include "PSMEnvelope.h"

class PSModuleManager : public PSObjectCollection
{
public:
    ~PSModuleManager() override {}

    void update()
    {
        for (auto &entry : items)
            ((PSModule *)entry.second)->update();
    }

    PSController *controller(const PSKeys &key) { return getItem<PSController>(key); }

    PSCEnvelope *getEnvelope(const PSKeys &key) { return getItem<PSCEnvelope>(key); }
    //PSCEnvelope *getLFO(const PSKeys &key) { return getItem<PSCEnvelope>(key); }

private:
};