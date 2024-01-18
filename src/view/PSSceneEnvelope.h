#pragma once
#include "../view/PSScene.h"
#include "../modules/PSMEnvelope.h"

class PSSceneEnvelope : public PSScene
{
public:
    PSSceneEnvelope(const std::string &name, PSMEnvelope *e = nullptr) : PSScene(SCN_ENVELOPE, name, e) { }
    ~PSSceneEnvelope() override {}

private:    
};