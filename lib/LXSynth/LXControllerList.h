#pragma once
#include "CollectionLite.h"
#include "LXController.h"
#include "ContKeys.h"

class LXControllerList : public CollectionLite<LXController, ContKeys>
{

};

LXControllerList Controllers;
