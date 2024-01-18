#pragma once
#include <cstdio>
#include "timing.h"

#define REVIEWTIME 2000
#define LOOPDURATION 8000

void setup();
void loop();
void beginLoop();
void pauseForReview(const std::string &reason, uint32_t delayMS = REVIEWTIME);

int main()
{
    printf("Starting Main\n");
    srand(millis());
    setup();

    pauseForReview("Setup Complete");    

    timer1.start(5);
    beginLoop();

    return 0;
}

void beginLoop()
{
    timer2.duration(LOOPDURATION);
    timer2.start();

    while (!timer2.update())
        loop();

    pauseForReview("Loop Test Complete");
}

void pauseForReview(const std::string &reason, uint32_t delayMS)
{
    printf("\n>>>>> %s : pause for review <<<<<\n\n", reason.c_str());
    delay(delayMS);
}

long map(long x, long in_min, long in_max, long out_min, long out_max)
{
    // Ensures that 'x' is within the input range
    if (x < in_min)
    {
        x = in_min;
    }
    else if (x > in_max)
    {
        x = in_max;
    }

    // Calculates and returns the mapped value
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
