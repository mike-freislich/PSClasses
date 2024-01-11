#pragma once
#include <string>
#include "PSCTPotentiometer.h"
#include "PSController.h"

#define CC67 0
#define CC68 1

using namespace std;

class PSControllerManager
{
public:
    PSControllerVector controls;
    PSControllerManager() {}

    /**
     * @brief
     * Adds all the necessary hardware controllers to the manager
     */
    void setup()
    {
        // Add four pots
        addController(new PSCTPotentiometer("pot1", 1));
        addController(new PSCTPotentiometer("pot2", 2));
        addController(new PSCTPotentiometer("pot3", 3));
        addController(new PSCTPotentiometer("pot4", 4));
        // Controllers.addController(new PSController("CC67"));
        // Controllers.addController(new PSController("CC68"));
    }

    PSController *addController(PSController *controller)
    {
        if (byKey(controller->getKey()) != nullptr)
            return nullptr;

        controls.push_back(controller);
        return controller;
    }

    /**
     * @brief
     * Finds a PSController by "key" name, or returns null
     * @param key is a string containing the name of the controller
     * @return PSController*
     */
    PSController *byKey(string key)
    {
        for (auto c : controls)
        {
            if (c->getKey() == key)
                return c;
        }
        return nullptr;
    }

    /**
     * @brief
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
} Controllers;