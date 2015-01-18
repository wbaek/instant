#ifndef __UTILS_JSON_HPP__
#define __UTILS_JSON_HPP__

#include "json/json.h"

namespace instant {
    namespace Utils{
        class JsonException {
            public:
                std::string key;
                std::string typeName;
                JsonException(const std::string& key, const std::string& typeName) {
                    this->key = key;
                    this->typeName = typeName;
                }
        };

        class JsonParsingError {
            public:
                std::string message;
                JsonParsingError(const std::string& message) {
                    this->message = message;
                }
        };

        class JsonUtil {
            public:
                static Json::Value Parse(const std::string& jsonString) {
                    Json::Value rootNode;
                    Json::Reader reader;
                    if ( reader.parse(jsonString, rootNode) == false ) {
                        throw JsonParsingError(reader.getFormattedErrorMessages());
                    }
                    return rootNode;
                }

                static std::string ToString(const Json::Value& node, const std::string& key) {
                    Json::Value value = node.get(key, Json::Value());
                    if ( value.empty() || !value.isString() ) throw JsonException(key, "string");
                    return value.asString();
                }

                static int ToInt(const Json::Value& node, const std::string& key) {
                    Json::Value value = node.get(key, Json::Value());
                    if ( value.empty() || !value.isInt() ) throw JsonException(key, "int");
                    return value.asInt();
                }

                static float ToFloat(const Json::Value& node, const std::string& key) {
                    Json::Value value = node.get(key, Json::Value());
                    if ( value.empty() || (!value.isDouble() && !value.isInt()) ) throw JsonException(key, "float");
                    return value.asFloat();
                }
                
                static double ToDouble(const Json::Value& node, const std::string& key) {
                    Json::Value value = node.get(key, Json::Value());
                    if ( value.empty() || (!value.isDouble() && !value.isInt()) ) throw JsonException(key, "double");
                    return value.asDouble();
                }

                static Json::Value ToObject(const Json::Value& node, const std::string& key) {
                    Json::Value value = node.get(key, Json::Value());
                    // object는 empty여도 상관없음 (isObject(Json::Value())==true)
                    if ( !value.isObject() ) throw JsonException(key, "object");
                    return value;
                }

                static Json::Value ToArray(const Json::Value& node, const std::string& key) {
                    Json::Value value = node.get(key, Json::Value());
                    // array는 empty여도 상관없음 (isArray(Json::Value())==true)
                    if ( !value.isArray() ) throw JsonException(key, "array");
                    return value;
                }
        };
    }
}
#endif //__UTILS_JSON_HPP__
