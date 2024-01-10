#pragma once
#include "PSCEnvelope.h"

class PSComponentManager
{
public:
    PSComponentVector components;
    PSComponentManager()
    {
        setup();
    }
    ~PSComponentManager() {}

    void setup()
    {
        add((PSComponent *)(new PSCEnvelope("P-ENV1a")));
        add((PSComponent *)(new PSCEnvelope("A-ENV1a")));
        add((PSComponent *)(new PSCEnvelope("F-ENV1a")));
        add((PSComponent *)(new PSCEnvelope("P-ENV1b")));
        add((PSComponent *)(new PSCEnvelope("A-ENV1b")));
        add((PSComponent *)(new PSCEnvelope("F-ENV1b")));
    }

    PSComponent *add(PSComponent *component)
    {
        components.push_back(component);
        return component;
    }

    PSComponent *byKey(string key)
    {
        for (auto c : components)
        {
            if (c->getKey() == key)            
                return c;            
        }
        return nullptr;
    }

    PSCEnvelope *getEnv(string key)
    {
        PSComponent *c = this->byKey(key);
        if (c == nullptr) 
            return nullptr;
        
        return (PSCEnvelope *)c;
    }

private:
} componentManager;