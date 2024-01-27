#pragma once
#include <string>
#include "PSKeys.h"
#include "StringBuilder.h"

uint16_t PSObjectCount = 0;

class PSObject
{
public:
    PSK key;
    std::string name;

    PSObject(const PSK &key, const std::string &name) : key(key), name(name)
    {
        PSObjectCount++;
        printf("+%s [%s] (count %d)\n", name.c_str(), psk_tostr(key).c_str(), PSObjectCount);        
    }    

    virtual ~PSObject()
    {
        PSObjectCount--;
        printf("-%s [%s] (count %d)\n", name.c_str(), psk_tostr(key).c_str(), PSObjectCount);        
    }

    std::string keyString() { return psk_tostr(key); }

    virtual bool update() { return false; }

    virtual const char *typeName() { return "PSObject"; }

    virtual std::string serialize()
    {
        printf("DEBUG : serialized not implemented for [%s]\n", name.c_str());
        return "";
    }
};
