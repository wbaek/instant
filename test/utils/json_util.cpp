
#include <gtest/gtest.h>

#include "json/json.h"
#include "utils/json_util.hpp"

TEST(instant_Utils_JsonUtil, ToString) {
    Json::Value node;
    node["string"] = "value";
    node["int"] = 1;

    EXPECT_EQ( "value", instant::Utils::JsonUtil::ToString(node, "string") );
    EXPECT_THROW( instant::Utils::JsonUtil::ToString(node, "int"), instant::Utils::JsonException);
    EXPECT_THROW( instant::Utils::JsonUtil::ToString(node, "INVALID"), instant::Utils::JsonException);
}

TEST(instant_Utils_JsonUtil, ToInt) {
    Json::Value node;
    node["string"] = "value";
    node["int"] = 1;

    EXPECT_EQ( 1, instant::Utils::JsonUtil::ToInt(node, "int") );
    EXPECT_THROW( instant::Utils::JsonUtil::ToInt(node, "string"), instant::Utils::JsonException);
    EXPECT_THROW( instant::Utils::JsonUtil::ToInt(node, "INVALID"), instant::Utils::JsonException);
}

TEST(instant_Utils_JsonUtil, ToFloat) {
    Json::Value node;
    node["string"] = "value";
    node["int"] = 1;
    node["float"] = 2.0;

    EXPECT_EQ( 2, instant::Utils::JsonUtil::ToFloat(node, "float") );
    EXPECT_EQ( 1, instant::Utils::JsonUtil::ToFloat(node, "int") );
    EXPECT_THROW( instant::Utils::JsonUtil::ToFloat(node, "string"), instant::Utils::JsonException);
    EXPECT_THROW( instant::Utils::JsonUtil::ToFloat(node, "INVALID"), instant::Utils::JsonException);
}

TEST(instant_Utils_JsonUtil, ToDouble) {
    Json::Value node;
    node["string"] = "value";
    node["int"] = 1;
    node["float"] = 2.0;

    EXPECT_EQ( 2, instant::Utils::JsonUtil::ToDouble(node, "float") );
    EXPECT_EQ( 1, instant::Utils::JsonUtil::ToDouble(node, "int") );
    EXPECT_THROW( instant::Utils::JsonUtil::ToDouble(node, "string"), instant::Utils::JsonException);
    EXPECT_THROW( instant::Utils::JsonUtil::ToDouble(node, "INVALID"), instant::Utils::JsonException);
}

TEST(instant_Utils_JsonUtil, ToObject) {
    Json::Value node;
    node["string"] = "value";
    node["int"] = 1;
    node["float"] = 2.0;
    node["object"]["test"] = 7;

    Json::Value object;
    object["test"] = 7;
    EXPECT_EQ( object, instant::Utils::JsonUtil::ToObject(node, "object") );
    EXPECT_THROW( instant::Utils::JsonUtil::ToObject(node, "string"), instant::Utils::JsonException);
    EXPECT_EQ( Json::Value(), instant::Utils::JsonUtil::ToObject(node, "INVALID"));
}

TEST(instant_Utils_JsonUtil, ToArray) {
    Json::Value node;
    node["string"] = "value";
    node["int"] = 1;
    node["float"] = 2.0;
    node["array"][7] = 7;

    Json::Value array;
    array[7] = 7;
    EXPECT_EQ( array, instant::Utils::JsonUtil::ToArray(node, "array") );
    EXPECT_THROW( instant::Utils::JsonUtil::ToArray(node, "string"), instant::Utils::JsonException);
    EXPECT_EQ( Json::Value(), instant::Utils::JsonUtil::ToArray(node, "INVALID"));
}

