#pragma once
#include "PSParameter.h"
#include "PSController.h"
#include <vector>

struct PSControllerConnection {
    std::string key;
    PSController *controller;
    PSControllerConnection(const std::string &k, PSController *c) : key(k), controller(c) {}
};

typedef std::vector<PSControllerConnection> PSControllerConnectionVector;