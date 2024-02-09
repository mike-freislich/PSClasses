#pragma once
// #include "PSObjectCollection.h"
#include "Collection.h"
#include "Controller.h"
#include "CPotentiometer.h"
#include "CButton.h"

namespace PS
{

    class ControllerManager : public CollectionBase<std::string, Controller *>
    {
    public:
        std::vector<CButton *> buttons;

        ~ControllerManager() override { buttons.clear(); }

        Controller *add(const std::string &key, Controller *value) override
        {
            Controller *c = CollectionBase::add(key, value);
            if (CButton *b = dynamic_cast<CButton *>(c))
                buttons.push_back(b);
            return c;
        }

        bool isShiftPressed() { return button("CTRL_BTN_Shift")->getValue(); }

        CButton *button(const std::string &key) { return dynamic_cast<CButton *>(collectionData[key]); }
        CPotentiometer *potentiometer(const std::string &key) { return dynamic_cast<CPotentiometer *>(collectionData[key]); }

        std::string serialize() override
        {
            StringBuilder sb;
            sb.startArray("CONTROLLERS")->add("\n");
            int count = 0;
            for (auto &pair : collectionData)
            {
                sb.startElement();
                if (Controller *c = pair.second)
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

}