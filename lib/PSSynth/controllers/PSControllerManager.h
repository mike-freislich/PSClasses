#pragma once
// #include "PSObjectCollection.h"
#include "Collection.h"
#include "PSController.h"
#include "PSCPotentiometer.h"
#include "PSCButton.h"

class PSControllerManager : public CollectionBase<std::string, PSController *>
{
public:
    std::vector<PSCButton *> buttons;

    ~PSControllerManager() override { buttons.clear(); }

    PSController *add(const std::string &key, PSController *value) override
    {
        PSController *c = CollectionBase::add(key, value);
        if (PSCButton *b = dynamic_cast<PSCButton *>(c))
            buttons.push_back(b);
        return c;
    }

    bool isShiftPressed() { return button("CTRL_BTN_Shift")->getValue(); }

    PSCButton *button(const std::string &key) { return dynamic_cast<PSCButton *>(collectionData[key]); }
    PSCPotentiometer *potentiometer(const std::string &key) { return dynamic_cast<PSCPotentiometer *>(collectionData[key]); }

    std::string serialize() override
    {
        StringBuilder sb;
        sb.startArray("CONTROLLERS")->add("\n");
        int count = 0;
        for (auto &pair : collectionData)
        {
            sb.startElement();
            if (PSController *c = pair.second)
            {
                c->serialize(&sb);
                count++;                
            }
            sb.endElement();
            if (count < collectionData.size())
                sb.delimiter()->add("\n");
        }
        sb.add("\n")
            ->endArray();
        return sb.toString();
    }

} Controllers;