#pragma once

#include "PSParameter.h"
#include <vector>

class PSComponent
{
public:
    PSParameterVector values;

    PSComponent()
    {
    }

    PSParameter *addParameter(PSParameter *p)
    {
        values.push_back(p);
        return p;
    }

    void update()
    {
        for (auto p : values)
        {
            p->update();
        }
    }

    // void setValue(uint8_t value)
    // {
    //     this->value = value;
    // }
    // uint8_t getValue()
    // {
    //     return this->value;
    // }

protected:
};