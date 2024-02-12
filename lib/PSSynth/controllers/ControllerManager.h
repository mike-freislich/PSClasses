#pragma once
// #include "PSObjectCollection.h"
#include "Collection.h"
#include "Controller.h"
#include "CPotentiometer.h"
#include "CButton.h"

namespace PS
{

    class ControllerManager : public CollectionLite<Controller> //CollectionBase<std::string, Controller *>
    {
    public:
        std::vector<CButton *> buttons;

        ~ControllerManager() override { buttons.clear(); }

        Controller *add(Controller *value) override
        {
            Controller *c = CollectionLite::add(value);
            if (c->getType() == ObjectType::TCButton)
            {
                CButton *b = static_cast<CButton *>(c);
                buttons.push_back(b);
            }
            return c;
        }

        bool isShiftPressed() { return button("CTRL_BTN_Shift")->getValue(); }

        CButton *button(const std::string &key)
        {
            Controller *c = collectionData[key];            
            if (c->getType() == ObjectType::TCButton)
                return static_cast<CButton *>(c);
            return nullptr;
        }

        CPotentiometer *potentiometer(const std::string &key)
        {        
            Controller *c = collectionData[key];
            if (c->getType() == ObjectType::TCPotentiometer)
                return (CPotentiometer *)(c);
            return nullptr;
        }

        std::string serialize() override
        {
            StringBuilder sb;
            sb.startArray("CONTROLLERS")->add("\n");
            size_t count = 0;
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