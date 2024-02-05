#pragma once
#include <stdio.h>
#include <iostream>
#include <functional>

typedef std::function<void(float)> AUValueLamda;

class TestAudioUnit
{
public:
    float _gain, _slope, _wave;
    void gain(float value) { _gain = value; }
    void slope(float value) { _slope = value; }
    void wave(float value) { _wave = value; }

protected:
    
};

TestAudioUnit auA;
TestAudioUnit auB;
TestAudioUnit auC;

class TestParameter
{
private:
    float _value;
    TestAudioUnit *_unit;

public:    
    void setValue(float value)
    {
        if (setAUValue)
            setAUValue(value);
        _value = value;
    }
    AUValueLamda setAUValue;    
};

void testL()
{
    TestParameter p;
    TestParameter b;

    std::cout << " before GAIN = " << auA._gain << std::endl;        

    b.setAUValue = [](float value){ auB.gain(value); };
    p.setAUValue = [](float value){ auA.gain(value); };    
    p.setValue(999);
    b.setValue(333);

    std::cout << " after GAIN = " << auA._gain << std::endl;
}