#pragma once
#include <functional>
#include <iostream>
#include <map>
#include <memory>
#include <sstream>
#include <fstream>
#include <vector>
#include "AudioDerived.h"

#define AUDIO_UNIT_ENVELOPE "envelope"
#define AUDIO_UNIT_AMPLIFIER "amplifier"
#define AUDIO_UNIT_MIXER "mixer"

// typedef std::function<void(AudioStream *, float)> AUPropertyFunction;
// typedef std::map<std::string, AUPropertyFunction> AUPropertyFunctionMap;

typedef std::function<void(MyAudioBase *, const std::string &, float)> AUValueFunction;
typedef std::map<std::string, AUValueFunction> AUValueFunctionMap;

typedef std::function<void(MyAudioBase *, const std::string &, unsigned int, float)> AUChannelValueFunction;
typedef std::map<std::string, AUChannelValueFunction> AUChannelValueFunctionMap;

class AudioUnitFactory
{
public:
    virtual ~AudioUnitFactory() {}
    virtual std::unique_ptr<AudioStream> createInstance() const = 0;
};

template <typename T>
class TypedAudioUnitFactory : public AudioUnitFactory
{
public:
    std::unique_ptr<AudioStream> createInstance() const override { return std::make_unique<T>(); }
};

class AudioUnitManager
{
public:
    void registerFactory(const std::string &typeName, std::unique_ptr<AudioUnitFactory> factory)
    {
        factories[typeName] = std::move(factory);
    }

    std::unique_ptr<AudioStream> createInstance(const std::string &typeName, const std::string &unitName) const
    {
        auto it = factories.find(typeName);
        if (it != factories.end())
        {
            auto instance = it->second->createInstance();
            if (MyAudioBase *ab = dynamic_cast<MyAudioBase *>(instance.get()))
            {
                ab->unitName = unitName;
            }
            return instance;
        }
        else
        {
            std::cerr << "Unknown audio stream type: " << typeName << std::endl;
            return nullptr;
        }
    }

    template <typename T>
    AUValueFunction mapValueFunction(void (T::*func)(const std::string &, float), T *audioUnitInstance)
    {
        return [func, audioUnitInstance](MyAudioBase *audioBase, const std::string &fieldName, float value)
        {
            if (auto derived = dynamic_cast<T *>(audioBase))
            {
                (derived->*func)(fieldName, value);
            }
            else
            {
                std::cerr << "Invalid cast!" << std::endl;
            }
        };
    }

    template <typename T>
    AUChannelValueFunction mapValueFunction(void (T::*func)(const std::string &, const unsigned int, float), T *audioUnitInstance)
    {
        return [func, audioUnitInstance](MyAudioBase *audioBase, const std::string &fieldName, unsigned int channel, float value)
        {
            if (auto derived = dynamic_cast<T *>(audioBase))
            {
                (derived->*func)(fieldName, channel, value);
            }
            else
            {
                std::cerr << "Invalid cast!" << std::endl;
            }
        };
    }

    void registerValueFunction(const std::string &propertyGlobalKey, AUValueFunction func) { valueFunctions[propertyGlobalKey] = func; }
    void registerChannelValueFunction(const std::string &propertyGlobalKey, AUChannelValueFunction func) { channelValueFunctions[propertyGlobalKey] = func; }

protected:
    std::map<std::string, std::unique_ptr<AudioUnitFactory>> factories;     
    AUValueFunctionMap valueFunctions;
    AUChannelValueFunctionMap channelValueFunctions;
};

class AudioUnits : public AudioUnitManager
{
public:
    AudioUnits()
    {
        registerAudioUnits();
    }

    // template <typename T>
    // void set(std::unique_ptr<AudioStream> &stream, AUPropertyFunction &func, float value)
    // {
    //     if (T *audioUnit = dynamic_cast<T *>(stream.get()))
    //         func(audioUnit, value);
    // }
    // void setEnvelope(std::unique_ptr<AudioStream> &audioUnit, std::string propertyName, float value)
    // {
    //     if (audioUnit)
    //     {
    //         if (AUPropertyFunction &func = propertyFunctions[propertyName])
    //             set<AudioEffectEnvelope>(audioUnit, func, value);
    //         else
    //             std::cerr << "property function not found : " << propertyName << std::endl;
    //     }
    //     else
    //     {
    //         std::cerr << "AudioUnit unknown" << std::endl;
    //     }
    // }

    template <typename T>
    T *unit(std::unique_ptr<AudioStream> &audioUnit) { return dynamic_cast<T *>(audioUnit.get()); }

    void set(std::unique_ptr<AudioStream> &audioUnit, const std::string fieldName, float value)
    {
        if (MyAudioBase *base = dynamic_cast<MyAudioBase *>(audioUnit.get()))
        {
            if (AUValueFunction func = valueFunctions["setFloat"])
                func(base, fieldName, value);
            else
                std::cout << "Error: unable to find [" << fieldName << "]" << std::endl;
        }
        else
            std::cout << "Error: invalid cast" << std::endl;
    }

    void set(std::unique_ptr<AudioStream> &audioUnit, const std::string fieldName, unsigned int channel, float value)
    {
        if (MyAudioBase *base = dynamic_cast<MyAudioBase *>(audioUnit.get()))
        {
            if (AUChannelValueFunction func = channelValueFunctions["setChannelFloat"])
                func(base, fieldName, channel, value);
            else
                std::cout << "Error: unable to find [" << fieldName << "]" << std::endl;
        }
        else
            std::cout << "Error: invalid cast" << std::endl;
    }

protected:
    // AUPropertyFunctionMap propertyFunctions;
    //  void readConfigFile(const std::string &filename)
    //  {
    //      std::ifstream configFile(filename);
    //      if (!configFile.is_open())
    //      {
    //          std::cerr << "Failed to open config file: " << filename << std::endl;
    //          return;
    //      }
    //      std::string line;
    //      while (std::getline(configFile, line))
    //      {
    //          std::istringstream iss(line);
    //          std::string propertyGlobalKey, audioUnitType, propertyName;
    //          if (iss >> propertyGlobalKey >> audioUnitType >> propertyName)
    //          {
    //              if (propertyGlobalKey != "#")
    //              {
    //                  if (auto instance = createInstance(audioUnitType))
    //                      propertyFunctions[propertyName] = mapPropertyFunction(audioUnitType, propertyGlobalKey);
    //              }
    //          }
    //      }
    //  }

    void registerAudioUnits()
    {
        registerFactories();
        registerPropertyFunctions();
    }

    void registerFactories()
    {
        // create factories for the various types of AudioUnit
        registerFactory(AUDIO_UNIT_ENVELOPE, std::make_unique<TypedAudioUnitFactory<MyAudioEffectEnvelope>>());
        registerFactory(AUDIO_UNIT_AMPLIFIER, std::make_unique<TypedAudioUnitFactory<MyAudioAmplifier>>());
    }

    void registerPropertyFunctions()
    {
        registerValueFunction("setFloat", mapValueFunction(&MyAudioBase::setFloat, static_cast<MyAudioBase *>(nullptr)));
        registerChannelValueFunction("setChannelFloat", mapValueFunction(&MyAudioBase::setChannelFloat, static_cast<MyAudioBase *>(nullptr)));
    }
} AU;

// --------------------------------------------------------------------------------

auto amp_env_a = AU.createInstance(AUDIO_UNIT_ENVELOPE, MOD_AENVa);
auto amp_env_b = AU.createInstance(AUDIO_UNIT_ENVELOPE, MOD_AENVb);
auto flt_env_a = AU.createInstance(AUDIO_UNIT_ENVELOPE, MOD_FENVa);
auto flt_env_b = AU.createInstance(AUDIO_UNIT_ENVELOPE, MOD_FENVb);
auto pit_env_a = AU.createInstance(AUDIO_UNIT_ENVELOPE, MOD_PENVa);
auto pit_env_b = AU.createInstance(AUDIO_UNIT_ENVELOPE, MOD_PENVb);

auto main_mixer = AU.createInstance(AUDIO_UNIT_MIXER, MOD_MIXER_MAIN);
auto out_amp_left = AU.createInstance(AUDIO_UNIT_AMPLIFIER, "out_amp_left");
auto out_amp_right = AU.createInstance(AUDIO_UNIT_AMPLIFIER, "out_amp_right");

void testAudioUnitFactory()
{
    AU.set(amp_env_a, FK_ENV_ATTACK, 9292);
    AU.set(flt_env_a, FK_ENV_DECAY, 111);
    AU.set(out_amp_left, FK_AMP_GAIN, 0.2);
    AU.set(out_amp_right, FK_AMP_GAIN, 0.5);

    //AU.set(main_mixer, )
    

    AudioConnection(*amp_env_a.get(), 0, *flt_env_a.get(), 1);

    std::cout << "done..." << std::endl;
}
