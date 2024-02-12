#pragma once

#ifndef BUILD_FOR_TEENSY

#include <thread>
#include <chrono>

uint32_t millis();
void delay(uint32_t durationMS, bool allowYield = false);

void delay(uint32_t durationMS, bool allowYield)
{
    uint32_t start = millis();
    while (millis() - start < durationMS)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
        if (allowYield)
            std::this_thread::yield();
    }
}

uint32_t millis()
{
    auto currentTime = std::chrono::system_clock::now();
    auto now = std::chrono::time_point_cast<std::chrono::milliseconds>(currentTime);
    return now.time_since_epoch().count();
}

#endif

class SimpleTimer
{
public:
    SimpleTimer() { this->duration(1); }

    SimpleTimer(uint32_t d) { this->duration(d); }

    void duration(uint32_t d) { _duration = d; }

    uint32_t getDuration() { return _duration; }

    void start()
    {
        _start = millis();
        _running = true;
    }

    void start(uint32_t duration)
    {
        this->duration(duration);
        this->start();
    }
    bool isRunning() { return _running; }

    void stop() { _running = false; }    

    bool update()
    {
        if (_running)
        {
            uint32_t now = millis();
            if (now - _start > _duration)
            {
                _start = now;
                return true;
            }
        }
        return false;
    }
    
private:
    uint32_t _start;
    uint32_t _duration;
    bool _running = false;

}; 

#ifndef __ARM_ARCH_7EM__
SimpleTimer timer1(10), timer2(10), timer3(10);
#endif