#pragma once
#include <cstdio>
#include "timing.h"

#define LOOPDURATION 8000
#define REVIEWTIME 250

#define TICKTIME 5
#define SCENE_REFRESH_RATE 120

//#define TESTMODE
//#define DEBUG
#include "DebugLog.h"

#ifdef TESTMODE
#include "tests.h"
#endif

void runTests();
void setup();
void loop();
void beginLoop();
void exiting();
void pauseForReview(const std::string &reason, uint32_t delayMS = REVIEWTIME);


int main()
{
#ifdef TESTMODE
    printf("Running in TEST MODE\n");
    printf("--------------------\n\n");    
    runTests();
    printf("\n--------------------\n");
#else
    printf("Starting Main\n");
    srand(millis());
    setup();

    pauseForReview("Setup Complete");

    timer1.start(TICKTIME);
    beginLoop();
    exiting();
#endif
    return 0;
}

void beginLoop()
{
    timer2.duration(LOOPDURATION);
    timer2.start();

    while (!timer2.update())
    {
        loop();
        delay(1);
    }

    pauseForReview("Loop Test Complete");
}

void pauseForReview(const std::string &reason, uint32_t delayMS)
{
#ifdef DEBUG
    printf("\n>>>>> %s : pause for review <<<<<\n\n", reason.c_str());
    delay(delayMS);
#endif
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

float clampf(float value, float minValue, float maxValue) {
    return std::max(minValue, std::min(value, maxValue));
}
