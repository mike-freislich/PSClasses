#pragma once
#include "PSParameter.h"
#include "Collection.h"


class PSParameterManager : public CollectionBase<std::string, PSParameter *>
{
public:
    PSParameterManager() {}
    ~PSParameterManager() override {}

    bool setValue(const std::string &key, float value)
    {
        if (PSParameter *p = collectionData[key])
        {
            p->setValue(value);
            return true;
        }
        return false;
    }

    float getValue(const std::string &key)
    {
        if (PSParameter *p = collectionData[key])
            return p->getValue();
        return 0;
    }

    // const char *c_str(const std::string &key)
    // {
    //     if (PSParameter *p = collectionData[key])
    //         return p->displayName.c_str();
    //     return nullptr;
    // }    
    
    bool update() override { return CollectionBase::update(); }

    std::string serialize() override
    {
        StringBuilder sb;
        sb.startArray("PARAMETERS")->add("\n");
        int count = 0;
        for (auto i : collectionData)
        {
            if (PSParameter *c = dynamic_cast<PSParameter *>(i.second))
            {
                c->serialize(&sb);
                count++;
                if (count < collectionData.size())
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