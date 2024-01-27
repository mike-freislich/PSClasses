#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include "JSONParser.h"

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
            throw std::runtime_error("Error opening config file '" + string(filename) + "'");
        }
        std::stringstream buffer;
        buffer << jsonFile.rdbuf();
        std::string jsonString = buffer.str();
        jsonFile.close();
        return jsonString;
    }

public:
    PSConfig(const char *filename) { _json_data = loadJson(filename); }

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
        printf("\n\nADDING CONTROLLERS and MAPPINGS :\n\n");
        for (const auto &c : result.objectValue.at("CONTROLLERS").arrayValue)
        {
            std::map<std::string, JSONValue> v = c.objectValue;
            PSK key = str_topsk(v.at("key").stringValue);
            std::string name = v.at("name").stringValue;
            int pin = std::stoi(v.at("pin").stringValue);
            int debounce = std::stoi(v.at("debounce").stringValue);

            PSController *controller;
            if (name == "PSCButton")
            {
                PSCButton *button = Controllers.add<PSCButton>(key, name);
                button->setPin(pin);
                button->debounceMS(debounce);
                controller = button;
            }
            else if (name == "PSCPotentiometer")
            {
                PSCPotentiometer *pot = Controllers.add<PSCPotentiometer>(key, name);
                pot->setPin(pin);
                pot->debounceMS(debounce);
                controller = pot;
            }

            if (controller)
            {
                printf("\n");      
                loadControllerParameters(controller, c);        
            }
        }
    }

    void loadParameters(JSONValue &result)
    {
        printf("\n\nADDING PARAMETERS :\n\n");

        for (const auto &p : result.objectValue.at("PARAMETERS").arrayValue)
        {
            std::map<std::string, JSONValue> v = p.objectValue;
            std::string name = v.at("name").stringValue;
            PSK key = str_topsk(v.at("key").stringValue);
            float value = std::stof(v.at("value").stringValue);
            float min = std::stof(v.at("min").stringValue);
            float max = std::stof(v.at("max").stringValue);
            PSParameter::TAPER taper = (PSParameter::TAPER)std::stoi(v.at("taper").stringValue);
            if (PSParameter *parameter = Parameters.add(key, name)->setRange(min, max)->setTaper(taper))
                parameter->setValue(value);
        }
    }

    void loadControllerParameters(PSController *controller, const JSONValue &c)
    {
        if (controller)
        {
            for (const auto &parm : c.objectValue.at("PARMS").arrayValue)
            {
                std::map<std::string, JSONValue> pv = parm.objectValue;
                PSParameterMode mode = (pv.at("mode").stringValue == "normal") ? PSParameterMode::STANDARD_PARM : PSParameterMode::SHIFT_PARM;
                for (const auto &pk : parm.objectValue.at("assigned").arrayValue)
                {
                    PSK paramkey = str_topsk(pk.objectValue.at("pkey").stringValue);
                    if (PSParameter *pAssign = Parameters.byKey(paramkey))                       
                        controller->assignParameter(pAssign, mode);                                            
                }                
            }  
        }
    }
};
