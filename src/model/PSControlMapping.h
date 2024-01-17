#pragma once
#include "PSParameter.h"
#include "../controllers/PSController.h"
#include <vector>

using namespace std;

struct PSControllerMap {
    PSKeys key;
    PSController *controller;
    PSControllerMap(const PSKeys &k, PSController *c) : key(k), controller(c) {}
};

typedef vector<PSControllerMap> PSControllerMapVector;