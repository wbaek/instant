
#include <gtest/gtest.h>

#include "json/json.h"

TEST(json_type, FloatAndDouble) {
    std::string jsonString = "\n\
// Configuration options\n\
{\n\
    \"int\" : 1,\n\
    \"float\" : 1.0,\n\
    \"double\" : 1.0e-42\n\
}\n\
";

    Json::Value root;
    Json::Reader reader;
    ASSERT_EQ(true, reader.parse(jsonString, root));
    EXPECT_EQ((unsigned int)3, root.size());

    EXPECT_TRUE( root["int"].isInt() );
    EXPECT_FALSE( root["int"].isDouble() );
    EXPECT_EQ( 1, root["int"].asInt() );
    EXPECT_NEAR( 1, root["int"].asFloat(), 1.0e-42 );
    EXPECT_NEAR( 1, root["int"].asDouble(), 1.0e-42 );

    EXPECT_FALSE( root["float"].isInt() );
    EXPECT_TRUE( root["float"].isDouble() );
    EXPECT_EQ( 1, root["float"].asInt() );
    EXPECT_NEAR( 1, root["float"].asFloat(), 1.0e-42 );
    EXPECT_NEAR( 1, root["float"].asDouble(), 1.0e-42 );


    EXPECT_FALSE( root["double"].isInt() );
    EXPECT_TRUE( root["double"].isDouble() );
    EXPECT_EQ( 0, root["double"].asInt() );
    EXPECT_NEAR( 1.0e-42, root["double"].asFloat(), 1.0e-42 );
    EXPECT_NEAR( 1.0e-42, root["double"].asDouble(), 1.0e-42 );
}

TEST(json_type, EmptyObject) {
    std::string jsonString = "\n\
// Configuration options\n\
{\n\
    \"object\" : {}\n\
}\n\
";

    Json::Value root;
    Json::Reader reader;
    ASSERT_EQ(true, reader.parse(jsonString, root));

    EXPECT_TRUE( root["object"].empty() );
    EXPECT_TRUE( root["object"].isObject() );

    Json::Value empty;
    EXPECT_TRUE( empty.empty() );
    EXPECT_TRUE( empty.isObject() );
    EXPECT_FALSE( empty.isInt() );

    EXPECT_TRUE( empty.get("not_exist", Json::Value()).empty() );
}

TEST(json_type, EmptyList) {
    std::string jsonString = "\n\
// Configuration options\n\
{\n\
    \"list\" : []\n\
}\n\
";

    Json::Value root;
    Json::Reader reader;
    ASSERT_EQ(true, reader.parse(jsonString, root));

    EXPECT_TRUE( root["list"].empty() );
    EXPECT_TRUE( root["list"].isArray() );
    EXPECT_EQ( (unsigned int)0, root["list"].size() );

    Json::Value empty;
    EXPECT_TRUE( empty.empty() );
    EXPECT_TRUE( empty.isArray() );

    EXPECT_EQ( (unsigned int)0, empty.size() );
}

