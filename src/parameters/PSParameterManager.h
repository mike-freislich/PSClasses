#pragma once
#include "PSParameter.h"
#include "PSObjectCollection.h"

class PSParameterManager : PSObjectCollection
{
public:
    PSParameterManager() {}
    ~PSParameterManager() override {}

    PSParameter *add(const PSK &key, const std::string &name)
    {
        if (exists(key))
        {
            printf("Error adding parameter %s : already exists!\n", name.c_str());
            return byKey(key); // already exists!
        }
        PSParameter *p = new PSParameter(key, name);
        this->addItem(p);
        return p;
    }

    bool setValue(const PSK &key, float value)
    {
        if (PSParameter *p = byKey(key))
        {
            p->setValue(value);
            return true;
        }
        return false;
    }

    float getValue(const PSK &key)
    {
        if (PSParameter *p = byKey(key))
            return p->getValue();
        return 0;
    }

    // bool exists(const PSK &key) { return byKey(key); }

    const char *c_str(const PSK &key)
    {
        if (PSParameter *p = byKey(key))
            return p->name.c_str();
        return nullptr;
    }

    auto collectionItems() { return PSObjectCollection::items; }

    PSParameter *byKey(const PSK &key) { return getItem<PSParameter>(key); }

    bool update() override { return PSObjectCollection::update(); }

    // bool update() override
    // {
    //     for (auto item : items) {
    //         if (PSParameter *p = dynamic_cast<PSParameter *>(item.second))
    //             p->update();
    //     }
    //     return true;
    // }

    const std::string serialize()
    {
        StringBuilder sb;
        sb.startArray("PARAMETERS")->add("\n");
        int count = 0;
        for (auto i : items)
        {
            if (PSParameter *c = dynamic_cast<PSParameter *>(i.second))
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
} Parameters;

// void testParmManager()
// {
//     Parameters.add(PSK::PARM_AENVa_AMOUNT, "level");
//     Parameters.setValue(PARM_AENVa_AMOUNT, 1.0f);
//     float f = Parameters.getValue(PARM_AENVa_AMOUNT);
//     if (PSParameter *p = Parameters.byKey(PARM_AENVa_AMOUNT))
//         p->attachController(nullptr)->setRange(0, 1);
// }