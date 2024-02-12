#pragma once
#include "Parameter.h"
#include "Collection.h"

namespace PS
{

    class ParameterManager : public CollectionBase<std::string, Parameter *>
    {
    public:
        ParameterManager() {}
        ~ParameterManager() {}

        bool setValue(const std::string &key, float value)
        {
            if (Parameter *p = collectionData[key])
            {
                p->setValue(value);
                return true;
            }
            return false;
        }

        float getValue(const std::string &key)
        {
            if (Parameter *p = collectionData[key])
                return p->getValue();
            return 0;
        }

        bool update() override { return CollectionBase::update(); }

        std::string serialize() override
        {
            StringBuilder sb;
            sb.startArray("PARAMETERS")->add("\n");
            size_t count = 0;
            for (auto i : collectionData)
            {
                if (Parameter *c = i.second)
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

}