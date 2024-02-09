#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include "JSONParser.h"
#include "ControllerManager.h"
#include "ParameterManager.h"

namespace PS
{

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

                if (cv.typeName == "CButton")
                {
                    if (!Controllers.contains(cv.key))
                        Controllers.add(cv.key, CButton::create(cv.key.c_str(), cv.pin, cv.displayName.c_str()));
                    // if (CButton *button = dynamic_cast<CButton *>(Controllers[cv.key]))
                    // {
                    // button specific
                    // }
                }
                else if (cv.typeName == "CPotentiometer")
                {
                    if (!Controllers.contains(cv.key))
                        Controllers.add(cv.key, CPotentiometer::create(cv.key.c_str(), cv.pin, cv.displayName.c_str()));
                    // if (CPotentiometer *pot = dynamic_cast<CPotentiometer *>(Controllers[cv.key]))
                    // {
                    // Potentiometer specific
                    // }
                }

                if (Controller *controller = Controllers[cv.key])
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
                        std::map<std::string, JSONValue> obj = p.objectValue;
                        const char *key = obj.at("key").stringValue.c_str();
                        const char *displayName = obj.at("name").stringValue.c_str();
                        float value = obj.at("value").numberValue;
                        float min = obj.at("min").numberValue;
                        float max = obj.at("max").numberValue;
                        Parameter::TAPER taper = (Parameter::TAPER)p.objectValue.at("taper").numberValue;
                        // optional integerValue
                        float integerValue = false;
                        if (obj.find("integervalue") != obj.cend())
                            integerValue = obj.at("integervalue").boolValue;

                        if (!Parameters.contains(key))
                        {
                            printf("loading parameter: %s<>%s\n", key, displayName);
                            if (Parameter *np = Parameters.add(key, Parameter::create(key, displayName)))
                                np->integerValue(integerValue);
                        }

                        Parameters[key]
                            ->setRange((float)min, (float)max)
                            ->setTaper(taper)
                            ->integerValue(integerValue)
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

        void loadControllerParameters(Controller *controller, const JSONValue &c)
        {
            if (controller)
            {
                for (const auto &parm : c.objectValue.at("PARMS").arrayValue)
                {
                    auto pv = parm.objectValue;
                    ParameterMode mode = (pv.at("mode").stringValue == "normal") ? ParameterMode::STANDARD_PARM : ParameterMode::SHIFT_PARM;
                    for (const auto &pk : pv.at("assigned").arrayValue)
                    {
                        auto o = pk.objectValue;
                        const char *paramkey = o.at("pkey").stringValue.c_str();
                        if (Parameter *pAssign = Parameters[paramkey])
                            controller->assignParameter(pAssign, mode);
                    }
                }
            }
        }
    };

}