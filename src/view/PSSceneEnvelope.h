#pragma once
#include "../view/PSScene.h"
#include "../modules/PSMEnvelope.h"

class PSSceneEnvelope : public PSScene
{
public:
    PSSceneEnvelope(const std::string &name) : PSScene(SCN_ENVELOPE, name) { }
    ~PSSceneEnvelope() override {}
private:    
};