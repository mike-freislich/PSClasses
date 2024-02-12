#pragma once
#include <cstdio>
#include <string>
#include <vector>
#include <map>

namespace PS
{

    enum class JSONType
    {
        OBJECT,
        ARRAY,
        STRING,
        NUMBER,
        BOOL,
        NULL_TYPE,
        ERROR
    };

    struct JSONValue
    {
        JSONType type;
        std::string stringValue;
        double numberValue;
        bool boolValue;
        std::vector<JSONValue> arrayValue;
        std::map<std::string, JSONValue> objectValue;
    };

    bool isFirstCharDigit(const std::string &str)
    {
        if (!str.empty())
        {
            char firstChar = str[0];
            return std::isdigit(firstChar) != 0;
        }
        return false; // Return false if the string is empty
    }

    class JSONParser
    {
    public:
        JSONParser(const std::string &jsonData) : jsonData(jsonData), currentIndex(0) {}

        JSONValue parse()
        {
            skipWhitespace();
            return parseValue();
        }

    private:
        char getCurrentChar() const
        {
            return currentIndex < jsonData.size() ? jsonData[currentIndex] : '\0';
        }

        char getNextChar()
        {
            return currentIndex + 1 < jsonData.size() ? jsonData[++currentIndex] : '\0';
        }

        void skipWhitespace()
        {
            while (std::isspace(getCurrentChar()))
            {
                currentIndex++;
            }
        }

        JSONValue parseValue()
        {
            skipWhitespace();
            switch (getCurrentChar())
            {
            case '{':
                return parseObject();
            case '[':
                return parseArray();
            case '"':
                return parseString();
            case 't':
            case 'f':
                return parseBool();
            case 'n':
                return parseNull();
            default:
                return parseNumber();
            }
        }

        JSONValue parseObject()
        {
            JSONValue result;
            result.type = JSONType::OBJECT;
            getNextChar(); // Skip '{'

            while (getCurrentChar() != '}')
            {
                skipWhitespace();
                std::string key = parseString().stringValue;

                skipWhitespace();
                if (getCurrentChar() != ':')
                {
                    result.stringValue = "Expected ':' in object.\n";
                    result.type = JSONType::ERROR;
                    return result;
                }
                getNextChar(); // Skip ':'

                JSONValue value = parseValue();
                result.objectValue[key] = value;

                skipWhitespace();
                if (getCurrentChar() == ',')
                {
                    getNextChar(); // Skip ','
                }
                else if (getCurrentChar() != '}')
                {
                    result.stringValue = "Expected ',' or '}' in object.\n";
                    result.type = JSONType::ERROR;
                    return result;
                }
            }

            getNextChar(); // Skip '}'
            return result;
        }

        JSONValue parseArray()
        {
            JSONValue result;
            result.type = JSONType::ARRAY;
            getNextChar(); // Skip '['

            while (getCurrentChar() != ']')
            {
                skipWhitespace();
                result.arrayValue.push_back(parseValue());

                skipWhitespace();
                if (getCurrentChar() == ',')
                {
                    getNextChar(); // Skip ','
                }
                else if (getCurrentChar() != ']')
                {
                    result.stringValue = "Expected ',' or ']' in array.\n";
                    result.type = JSONType::ERROR;
                    return result;
                }
            }

            getNextChar(); // Skip ']'
            return result;
        }

        JSONValue parseString()
        {
            JSONValue result;
            result.type = JSONType::STRING;
            getNextChar(); // Skip '"'

            while (getCurrentChar() != '"')
            {
                result.stringValue += getCurrentChar();
                getNextChar();
            }

            getNextChar(); // Skip '"'
            return result;
        }

        JSONValue parseBool()
        {
            JSONValue result;
            result.type = JSONType::BOOL;

            if (getCurrentChar() == 't')
            {
                result.boolValue = true;
                currentIndex += 4; // Skip "true"
            }
            else if (getCurrentChar() == 'f')
            {
                result.boolValue = false;
                currentIndex += 5; // Skip "false"
            }
            else
            {
                result.stringValue = "Invalid boolean value.\n";
                result.type = JSONType::ERROR;
                return result;
            }

            return result;
        }

        JSONValue parseNull()
        {
            JSONValue result;
            result.type = JSONType::NULL_TYPE;

            currentIndex += 4; // Skip "null"
            return result;
        }

        JSONValue parseNumber()
        {
            JSONValue result;
            result.type = JSONType::NUMBER;

            size_t endPos;
            // std::string x = jsonData.substr(currentIndex);
            // if (isFirstCharDigit(jsonData.substr(currentIndex)))
            result.numberValue = std::stod(jsonData.substr(currentIndex), &endPos);
            // else
            // {
            //     result.type = JSONType::ERROR;
            //     result.stringValue = "Error Parsing JSON";
            // }
            currentIndex += endPos;

            return result;
        }

        const std::string &jsonData;
        size_t currentIndex;
    };

    void printj(const std::string &key, const JSONValue &json) { printf("(%s: %s) ", key.c_str(), json.objectValue.at(key).stringValue.c_str()); }

}
