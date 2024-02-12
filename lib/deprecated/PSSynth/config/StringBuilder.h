#pragma once
#include <string>

namespace PS
{

    class StringBuilder
    {
    public:
        StringBuilder *add(const std::string &s)
        {
            _s += s;
            return this;
        }

        StringBuilder *begin() { return this; }

        StringBuilder *addLabel(const std::string &s)
        {
            _s += "\"" + s + "\": ";
            return this;
        }

        StringBuilder *startValue()
        {
            _s += "\"";
            return this;
        }

        StringBuilder *endValue() { return this->startValue(); }

        StringBuilder *addValue(const std::string &s)
        {
            _s += "\"" + s + "\"";
            return this;
        }

        StringBuilder *startArray(const std::string &arrayName)
        {
            _s += "\"" + arrayName + "\": [";
            return this;
        }

        StringBuilder *startElement()
        {
            _s += "{";
            return this;
        }
        StringBuilder *endElement()
        {
            _s += "}";
            return this;
        }

        StringBuilder *endArray()
        {
            _s += "]";
            return this;
        }

        StringBuilder *addPair(const std::string &key, const std::string &value)
        {
            _s += "\"" + key + "\":\"" + value + "\"";
            return this;
        }

        StringBuilder *addPair(const std::string &key, const char *value)
        {
            _s += "\"" + key + "\":\"" + value + "\"";
            return this;
        }

        StringBuilder *addPair(const std::string &key, const float &value)
        {
            _s += "\"" + key + "\":" + std::to_string(value);
            return this;
        }

        StringBuilder *addPair(const std::string &key, const bool &value)
        {
            _s += "\"" + key + "\":" + ((value) ? "true" : "false");
            return this;
        }

        StringBuilder *addPair(const std::string &key, const int &value)
        {
            _s += "\"" + key + "\":" + std::to_string(value);
            return this;
        }

        StringBuilder *delimiter()
        {
            _s += ", ";
            return this;
        }

        const std::string &toString()
        {
            _s.shrink_to_fit();
            return _s;
        }

        const char *c_str() { return toString().c_str(); }

        void clear() { _s.clear(); }

    private:
        std::string _s;
    };

}