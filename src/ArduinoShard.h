#pragma once
#include <cstdio>
#include "timing.h"


using namespace std;
void setup();
void loop();
void beginLoop();

int main()
{
    printf("Starting Main\n");
    setup();
    beginLoop();    
    return 0;
}

int loopCount = 0;
void beginLoop()
{
    
    while (loopCount < 10)
    {
        loop();        
    }
}