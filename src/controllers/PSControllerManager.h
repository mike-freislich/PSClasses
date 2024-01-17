#pragma once
#include <string>
#include "PSCTPotentiometer.h"
#include "PSController.h"

#define CC67 0
#define CC68 1

using namespace std;

class PSControllerManager : public PSObjectCollection
{
public:
    PSControllerManager() {}
    ~PSControllerManager() override {}

    PSController *add(PSController *controller)
    {
        this->addItem(controller);        
        return controller;
    }

    PSController *controller(const PSKeys &key) { return getItem<PSController>(key); }

    // /**
    //  * @brief
    //  * Finds a PSController by "key" name, or returns null
    //  * @param key is a string containing the name of the controller
    //  * @return PSController*
    //  */
    // PSController *byKey(string key)
    // {
    //     controls.getItem<PSController>
    //     for (auto c : controls)
    //         if (c->getKey() == key)
    //             return c;
    //     return nullptr;
    // }

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

    void endUpdate() {
        for (auto c : items)
            ((PSController *)c.second)->endUpdate();
    }

private:
};