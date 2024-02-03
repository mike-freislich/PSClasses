#pragma once
#include "PSParameter.h"
#include "Collection.h"


class PSParameterManager : public CollectionBase<std::string, PSParameter *>
{
public:
    PSParameterManager() {}
    ~PSParameterManager() {}

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