#pragma once

#include <iostream>
#include <vector>
#include "PSController.h"

using namespace std;

class PSParameter
{
public:
    PSParameter(string key) : _key(key) {}

    float getValue() { return _value; }
    string getKey() { return _key; }
    void setValue(float val) { _value = val; }

    void attachController(PSController *controller)
    {        
        _controllers.push_back(controller);
    }

    void detachController(PSController *controller)
    {
        if (controller)
        {
            for (int i = 0; i < _controllers.size(); i++)
            {
                PSController *c = _controllers[i];
                if (c->getKey() == controller->getKey())
                {
                    _controllers.erase(_controllers.begin() + i);
                    break;
                }
            }
        }
    }

    bool update()
    {
        bool changed = false;

        for (auto c : _controllers)
        {
            if (c->didChange())
            {
                _value = c->getValue();
                changed = true;
                break;
            }
        }

        return changed;
    }

    string toString()
    {
        return "{" + _key + "," + to_string(_value) + "}";
    }

protected:
    float _value, _max, _min;
    string _key;
    PSControllerVector _controllers;
};

typedef vector<PSParameter *> PSParameterVector;

/*
void printVerify(PSParameter *p)
{
    if (p->isInt())
        printf("Integer : %d\n", p->asInt());
    else if (p->isUInt())
        printf("Unsigned Integer : %d\n", p->asUint());
    else if (p->isFloat())
        printf("float : %f\n", p->asFloat());
}

void testParams()
{
    PSParameter p = PSParameter(999999999);
    printVerify(&p);

    p.setValue(20.5f);
    printVerify(&p);
}
*/