#pragma once
#include <unordered_map>
#include <string>
#include "PSKeys.h"
#include "PSObject.h"
#include "PSMEnvelope.h"

class PSObjectCollection
{
protected:
public:
    std::unordered_map<PSKeys, PSObject *> items;
    void addItem(PSObject *obj)
    {
        if (obj)
        {
            const PSKeys &key = obj->key;
            items[key] = obj;
        }
    }

    template <typename T>
    T *getItem(const PSKeys &key)
    {
        auto item = items.find(key);
        if (item != items.end())
            return (T *)item->second;
        return nullptr;
    }

    virtual ~PSObjectCollection()
    {        
        for (auto entry : items)
        {
            if (entry.second)
                delete entry.second;
        }
    }
};