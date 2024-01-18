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
    PSMEnvelope *getEnvelope(const PSKeys &key) { return getItem<PSMEnvelope>(key); }    

private:
};