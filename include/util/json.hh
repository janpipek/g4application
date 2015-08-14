#ifndef UTILJSON_HH
#define UTILJSON_HH

/**
  * @short A few utilities for better work with input JSON files.
  */

#include <string>
#include <memory>
#include <stdexcept>
#include <vector>

#include <globals.hh>

#include <json/json.h>

namespace g4
{
    namespace util
    {
        /**
          * @short Create a JSON value from a file.
          */
        std::shared_ptr<Json::Value> parseJsonFile(const std::string& path);

        /**
          * @short Template-based JSON value parsing (for use in other templates).
          */
        template<typename T> T readJsonValue(const Json::Value& value);

        template<> inline double readJsonValue<double>(const Json::Value& value)
        {
            try
            {
                return value.asDouble();
            }
            catch (std::runtime_error& err)
            {
                G4Exception("JSON::readJsonValue<double>", "CannotConvert", FatalException, "Cannot convert JSON value to double");
            }
        }

        template<> inline std::string readJsonValue<std::string>(const Json::Value& value)
        {
            try
            {
                return value.asString();
            }
            catch (std::runtime_error& err)
            {
                G4Exception("JSON::readJsonValue<string>", "CannotConvert", FatalException, "Cannot convert JSON value to string");
            }
        }

        template<> inline int readJsonValue<int>(const Json::Value& value)
        {
            try
            {
                return value.asInt();
            }
            catch (std::runtime_error& err)
            {
                G4Exception("JSON::readJsonValue<int>", "CannotConvert", FatalException, "Cannot convert JSON value to int");
            }
        }

        template<typename T> std::vector<T> readJsonArray(const Json::Value& value)
        {
            try
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
            catch (std::runtime_error& err)
            {
                G4Exception("JSON::readJsonArray<vector>", "CannotConvert", FatalException, "Cannot convert JSON value to vector");
            }
        }
    }
}

#endif
