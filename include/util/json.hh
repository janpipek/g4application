#ifndef UTILJSON_HH
#define UTILJSON_HH

#include <string>
#include <memory>
#include <stdexcept>
#include <vector>

#include <json/reader.h>

namespace g4
{
    namespace util
    {
        /**
          * @short Create a JSON value from a file-
          */
        std::shared_ptr<Json::Value> parseJsonFile(const std::string& path);

        template<typename T> T readJsonValue(const Json::Value& value);

        template<> double readJsonValue<double>(const Json::Value& value)
        {
            return value.asDouble();
        }

        template<> std::string readJsonValue<std::string>(const Json::Value& value)
        {
            return value.asString();
        }

        template<> int readJsonValue<int>(const Json::Value& value)
        {
            return value.asInt();
        }

        template<typename T> std::vector<T> readJsonArray(const Json::Value& value)
        {
            if (!value.isArray())
            {
                throw std::runtime_error("Cannot make vector from JSON non-array.");
            }
            std::vector<T> result;
            for (int i = 0; i < value.size(); i++)
            {
                T val = readJsonValue<T>(value[i]);
                result.push_back(val);
            }
            return result;
        }
    }
}

#endif