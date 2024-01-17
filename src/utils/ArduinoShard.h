#pragma once
#include <cstdio>
#include "timing.h"

void setup();
void loop();
void beginLoop();

int main()
{    
    printf("Starting Main\n");
    srand(millis());
    setup();
    if (timer1.isRunning())    
        beginLoop();    
    return 0;
}

int loopCount = 0;
void beginLoop()
{   
    while (loopCount < 10)
        loop();      

    // printf("DONE : pause for review\n");
    // delay(5000);
}

long map(long x, long in_min, long in_max, long out_min, long out_max) {
    // Ensures that 'x' is within the input range
    if (x < in_min) {
        x = in_min;
    } else if (x > in_max) {
        x = in_max;
    }

    // Calculates and returns the mapped value
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

