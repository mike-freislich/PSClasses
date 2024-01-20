#pragma once
#include "PSCPotentiometer.h"
#include "PSCButton.h"

class PSControllerManager : public PSObjectCollection
{
public:
    PSControllerManager() : PSObjectCollection() {}
    ~PSControllerManager() override {}

    PSController *controller(const PSK &key) { return getItem<PSController>(key); }

    /**
     * @brief
     * Reads and updates the values from physical controllers e.g. knobs etc.
     * NOTE:
     *   PSParamater.update() polls each of its attached PSController.didChange()
     *   to determine new input value to update the parameter with.
     */
    void update()
    {
        for (auto c : items)
            ((PSController *)c.second)->update();
    }

    /**
     * @brief Resets all the controllers changed values to "not changed"
     * Called after modules have checked to see if their parameters have changed.
     */
    void endUpdate()
    {
        for (auto c : items)
            ((PSController *)c.second)->endUpdate();
    }

private:
} Controllers;