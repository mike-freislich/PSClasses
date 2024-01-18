#pragma once
#include "PSParameter.h"
#include "../controllers/PSController.h"
#include <vector>

struct PSControllerConnection {
    PSKeys key;
    PSController *controller;
    PSControllerConnection(const PSKeys &k, PSController *c) : key(k), controller(c) {}
};

typedef std::vector<PSControllerConnection> PSControllerConnectionVector;