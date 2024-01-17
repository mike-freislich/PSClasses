#pragma once
#include "PSParameter.h"
#include "../controllers/PSController.h"
#include <vector>

struct PSControllerMap {
    PSKeys key;
    PSController *controller;
    PSControllerMap(const PSKeys &k, PSController *c) : key(k), controller(c) {}
};

typedef std::vector<PSControllerMap> PSControllerMapVector;