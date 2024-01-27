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
            return getItem<T>(key);
        }
        return addItem(new T(key, name));
    }

    auto collectionItems() { return PSObjectCollection::items; }

    bool isShiftPressed() { return button(CTRL_BTN_Shift)->getValue(); }

    /**
     * @brief
     * Reads and updates the values from physical controllers e.g. knobs etc.
     * NOTE:
     *   PSParamater.update() polls each of its attached PSController.didChange()
     *   to determine new input value to update the parameter with.
     */
    bool update() override { return PSObjectCollection::update(); }

    PSCButton *button(const PSK &key) { return getItem<PSCButton>(key); }
    PSCPotentiometer *potentiometer(const PSK &key) { return getItem<PSCPotentiometer>(key); }

    const std::string serialize()
    {
        StringBuilder sb;
        sb.startArray("CONTROLLERS")->add("\n");
        int count = 0;
        for (auto i : items)
        {
            if (PSController *c = dynamic_cast<PSController *>(i.second))
            {
                sb.add(c->serialize());
                count++;
                if (count < items.size())
                    sb.add(", \n");
            }
        }
        sb.add("\n")->endArray();
        return sb.toString();
    }
} Controllers;