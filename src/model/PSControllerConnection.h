#pragma once
#include "PSParameter.h"
#include "PSController.h"
#include <vector>

struct PSControllerConnection {
    PSK key;
    PSController *controller;
    PSControllerConnection(const PSK &k, PSController *c) : key(k), controller(c) {}
};

typedef std::vector<PSControllerConnection> PSControllerConnectionVector;