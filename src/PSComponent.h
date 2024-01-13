#pragma once
#include "PSParameter.h"
#include <vector>

using namespace std;

class PSComponent
{
public:
    PSParameterVector values;

    PSComponent(string key)
    {
        _key = key;
    }

    PSParameter *addParameter(PSParameter *p)
    {                   
        values.push_back(p);
        return p;
    }

    void update()
    {        
        for (auto p : values)        
            p->update();        
    }

    string getKey()
    {
        return _key;
    }

    virtual string toString()
    {
        string result = "@" + _key + "{";
        for (auto p : values)
        {
            result += p->toString();            
        }
        result += "}";
        return result;
    }

protected:
    string _key;
    float min, max;
};

typedef vector<PSComponent *> PSComponentVector;