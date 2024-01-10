#pragma once
#include <string>
#include "PSController.h"

#define CC67 0
#define CC68 1

using namespace std;

class PSControllerManager
{
public:
    PSControllerVector controls;
    PSControllerManager() {}

    PSController *addController(PSController *controller)
    {
        for (auto c : controls)
            if (c->getKey() == controller->getKey())
                return nullptr;
        
        controls.push_back(controller);
        return controller;
    }

    PSController *byKey(string key)
    {
        for (auto c : controls)
        {
            if (c->getKey() == key)
                return c;
        }
        return nullptr;
    }

    PSController *byIndex(int index)
    {
        if (index < controls.size())
            return controls[index];
        return nullptr;
    }

    /*
     * Reads and updates the values from physical controllers e.g. knobs etc.
     * NOTE:
     *   PSParamater.update() polls each of its attached PSController.didChange()
     *   to determine new input value to update the parameter with.
     */
    void update()
    {
        for (auto c : controls)
            c->update();
    }

private:
} controlsManager;