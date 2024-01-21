#pragma once
#include "PSCPotentiometer.h"
#include "PSCButton.h"

class PSControllerManager : PSObjectCollection
{
public:
    PSControllerManager() : PSObjectCollection() {}
    ~PSControllerManager() override {}

    PSController *controller(const PSK &key) { return getItem<PSController>(key); }

    template <typename T>
    T *add(const PSK &key, const std::string &name)
    {        
        if (exists(key))
        {
            printf("Error adding controller %s : already exists!\n", name.c_str());
            return nullptr;
        }        
        return addItem(new T(key, name));        
    }

    /**
     * @brief
     * Reads and updates the values from physical controllers e.g. knobs etc.
     * NOTE:
     *   PSParamater.update() polls each of its attached PSController.didChange()
     *   to determine new input value to update the parameter with.
     */
    bool update() override { return PSObjectCollection::update(); }

    /**
     * @brief Resets all the controllers changed values to "not changed"
     * Called after modules have checked to see if their parameters have changed.
     */
    void endUpdate()
    {
        for (auto item : items)
            if (PSController *c = dynamic_cast<PSController *>(item.second))
                c->endUpdate();            
    }
    
    PSCButton *button(const PSK &key) { return this->getItem<PSCButton>(key); }
    PSCPotentiometer *potentiometer(const PSK &key) { return this->getItem<PSCPotentiometer>(key); }    
    
} Controllers;