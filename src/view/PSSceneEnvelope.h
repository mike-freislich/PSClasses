#pragma once
#include "../view/PSScene.h"
#include "../modules/PSMEnvelope.h"

class PSSceneEnvelope : public PSScene
{
public:
    PSSceneEnvelope(const std::string &name, PSCEnvelope *e = nullptr) : PSScene(MOD_AENVa, name, e)
    {        
        _active = false;             
    }

    PSSceneEnvelope *setEnvelope(PSCEnvelope *e) 
    {         
        addComponent(e);            
        return this;
    }

private:
    //PSCEnvelope *envelope;
};