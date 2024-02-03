#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include "JSONParser.h"
#include "PSControllerManager.h"
#include "PSParameterManager.h"

struct ParameterStruct
{
    const char *key;
    const char *displayName;
    float value;
    float min;
    float max;
    int taper;
};

struct ParmConnectionSruct
{
    const char *mode;
    const char *pKey;
};

struct ControllerStruct
{
    std::string key;
    std::string displayName;
    std::string typeName;
    int pin;
    int debounce;
    float min;
    float max;
};

class PSConfig
{
private:
    std::string _json_data;

    std::string loadJson(const char *filename)
    {
        std::ifstream jsonFile(filename);
        if (!jsonFile.is_open())
        {
            std::cerr << "Error opening the file." << std::endl;
            throw std::runtime_error("Error opening config file '" + std::string(filename) + "'");
        }
        std::stringstream buffer;
        buffer << jsonFile.rdbuf();
        std::string jsonString = buffer.str();
        jsonFile.close();
        return jsonString;
    }

public:

    void loadConfig(const char *filename) { _json_data = loadJson(filename); }

    void applyConfig()
    {
        try
        {
            JSONParser parser(_json_data);
            JSONValue result = parser.parse();
            loadParameters(result);
            loadControllers(result);
        }
        catch (const std::exception &e)
        {
            fprintf(stderr, "Error parsing JSON: %s\n", e.what());
        }
    }

    void loadControllers(JSONValue &result)
    {
        int count;
        printf("\n\nLOADING CONTROLLERS and PARAMETER MAPPINGS :\n\n");

        for (const auto &jsonController : result.objectValue.at("CONTROLLERS").arrayValue)
        {
            auto o = jsonController.objectValue;
            ControllerStruct cv;
            try
            {
                cv.key = o.at("key").stringValue;
                cv.typeName = o.at("type").stringValue;
                cv.displayName = o.at("name").stringValue;
                cv.pin = o.at("pin").numberValue;
                cv.debounce = o.at("debounce").numberValue;
                cv.min = o.at("min").numberValue;
                cv.max = o.at("max").numberValue;
            }
            catch (const std::exception &e)
            {
                std::cerr << e.what() << "|| Error parsing config at CONTROLLERS " << count << "\n";
            }

            if (cv.typeName == "PSCButton")
            {
                if (!Controllers.contains(cv.key))
                    Controllers.add(cv.key, PSCButton::create(cv.key.c_str(), cv.pin, cv.displayName.c_str()));
                // if (PSCButton *button = dynamic_cast<PSCButton *>(Controllers[cv.key]))
                // {
                        // button specific
                // }
            }
            else if (cv.typeName == "PSCPotentiometer")
            {
                if (!Controllers.contains(cv.key))
                    Controllers.add(cv.key, PSCPotentiometer::create(cv.key.c_str(), cv.pin, cv.displayName.c_str()));
                // if (PSCPotentiometer *pot = dynamic_cast<PSCPotentiometer *>(Controllers[cv.key]))
                // {
                        // Potentiometer specific
                // }
            }

            if (PSController *controller = Controllers[cv.key])
            {
                controller->debounceMS(cv.debounce);
                controller->setValueRange(cv.min, cv.max);
                loadControllerParameters(controller, jsonController);
            }
        }
    }

    void loadParameters(JSONValue &result)
    {
        printf("\n\nLOADING PARAMETERS :\n\n");

        try
        {
            auto obj = result.objectValue;
            auto parmsSection = obj.at("PARAMETERS");
            auto parmArray = parmsSection.arrayValue;

            int count;
            for (const auto &p : parmArray)
            {
                count++;
                try
                {
                    const char *key = p.objectValue.at("key").stringValue.c_str();
                    const char *displayName = p.objectValue.at("name").stringValue.c_str();
                    float value = p.objectValue.at("value").numberValue;
                    float min = p.objectValue.at("min").numberValue;
                    float max = p.objectValue.at("max").numberValue;
                    PSParameter::TAPER taper = (PSParameter::TAPER)p.objectValue.at("taper").numberValue;

                    if (!Parameters.contains(key))
                    {
                        printf("loading parameter: %s<>%s\n", key, displayName);
                        Parameters.add(key, PSParameter::create(key, displayName));
                    }

                    Parameters[key]
                        ->setRange((float)min, (float)max)
                        ->setTaper(taper)
                        ->setValue((float)value);
                }
                catch (const std::exception &e)
                {
                    std::cerr << e.what() << " | ERROR : JSON File error at PARAMETERS item " << count << '\n';
                }
            }
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << '\n';
        }
    }

    void loadControllerParameters(PSController *controller, const JSONValue &c)
    {
        if (controller)
        {
            for (const auto &parm : c.objectValue.at("PARMS").arrayValue)
            {
                auto pv = parm.objectValue;
                PSParameterMode mode = (pv.at("mode").stringValue == "normal") ? PSParameterMode::STANDARD_PARM : PSParameterMode::SHIFT_PARM;
                for (const auto &pk : pv.at("assigned").arrayValue)
                {
                    auto o = pk.objectValue;
                    const char *paramkey = o.at("pkey").stringValue.c_str();
                    if (PSParameter *pAssign = Parameters[paramkey])
                        controller->assignParameter(pAssign, mode);
                }
            }
        }
    }
};
