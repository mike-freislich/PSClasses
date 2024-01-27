#pragma once

#include "Collection.h"
#include "PSCButton.h"
#include "PSCPotentiometer.h"


struct Mapping {
    int key1, key2;
    Mapping() {}
    Mapping(int k1, int k2) : key1(k1), key2(k2) {}
};

void testCollection()
{
    CollectionBase <int, Mapping>mappings;
    CollectionBase <PSK, PSController *>controllers;

    mappings.addItem(1, Mapping(1,2));
    controllers.addItem(PSK::CTRL_POT2, new PSCPotentiometer(PSK::CTRL_POT2, "pot2"));    
    mappings.displayItems();
    controllers.displayItems();

}