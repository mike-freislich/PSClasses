#pragma once
#include "CollectionLite.h"
#include "LXParameter.h"
#include "ParmKeys.h"

#define PARM_BYTES 60

using CallbackFuncPtr = void(*)(const char *);
typedef std::vector<LXParameter *>LXParameterVector;

class LXParameterList : public CollectionLite<LXParameter, ParmKeys>
{
public:    
    FLASHMEM void serialize(CallbackFuncPtr storeItem)
    {
        for (auto &p : items)
        {
            char *buffer = new char[PARM_BYTES];
            snprintf(buffer, PARM_BYTES,
                     "key:%d, value:%11.3f, min:%11.3f, max:%11.3f",
                     p->key,
                     p->getValue(),
                     p->getMin(),
                     p->getMax());            
            storeItem(buffer);
            delete[] buffer;
        }
    }    
};

LXParameterList Parameters;
