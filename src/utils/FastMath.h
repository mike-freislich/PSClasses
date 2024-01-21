#pragma once
#include <iostream>
#include <cmath>

using namespace std;

// Number of entries in the logarithm table
const int TABLE_SIZE = 64;

// Function to create a static logarithm table
const float *createStaticLogTable(float min, float max, int size)
{
    static float logTable[TABLE_SIZE];

    float step = (max - min) / static_cast<float>(size - 1);

    for (int i = 0; i < size; ++i)
    {
        float value = min + step * static_cast<float>(i);
        logTable[i] = std::log(value);
    }

    return logTable;
}

// Function to perform a logarithmic lookup with linear interpolation
float fastLogLookup(float x, const float *logTable, float min, float max, int size)
{
    if (x <= 0.0f)
        return -std::numeric_limits<float>::infinity();
    if (x >= max)
        return logTable[size - 1];

    float indexFloat = (x - min) / (max - min) * (size - 1);
    int indexLow = static_cast<int>(indexFloat);
    int indexHigh = indexLow + 1;

    // Perform linear interpolation
    float frac = indexFloat - indexLow;
    float logLow = logTable[indexLow];
    float logHigh = logTable[indexHigh];
    return (1.0f - frac) * logLow + frac * logHigh;
}

float convertToAudio(float linearValue, float linearMin, float linearMax, float audioMin = 0, float audioMax = 0, float exponent = 2.0f)
{
    if (audioMax == audioMin)
    {
        audioMax = linearMax;
        audioMin = linearMin;
    }
    // Ensure linearValue is within the specified range
    linearValue = max(min(linearValue, linearMax), linearMin);

    // Perform the conversion using the formula
    float audioValue = audioMin + (audioMax - audioMin) * std::pow((linearValue - linearMin) / (linearMax - linearMin), exponent);

    return audioValue;
}


float sineWavePoint(float amplitude, float frequency, float phaseOffset, uint32_t numMilliseconds) {
    const float twoPi = 2.0f * 3.14159f;
    float timeInSeconds = static_cast<float>(numMilliseconds) / 1000.0f;
    float phase = twoPi * frequency * timeInSeconds + twoPi * phaseOffset;
    return amplitude * std::sin(phase);
}
