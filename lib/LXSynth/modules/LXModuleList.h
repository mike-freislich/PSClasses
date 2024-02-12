#pragma once
#include "LXModule.h"
#include "CollectionLite.h"

class LXModuleList : public CollectionLite<LXModule, ModKeys>
{
public:
};

LXModuleList Modules;
