
#include <gtest/gtest.h>

#include "json/json.h"

TEST(json_json, EmptyString) {
    std::string jsonString = "";

    Json::Value root;
    Json::Reader reader;
    EXPECT_EQ(false, reader.parse(jsonString, root));
    EXPECT_EQ((unsigned int)0, root.size());

    std::cout << reader.getFormattedErrorMessages() << std::endl;
}

TEST(json_json, EmptyJson) {
    std::string jsonString = "{}";

    Json::Value root;
    Json::Reader reader;
    EXPECT_EQ(true, reader.parse(jsonString, root));
    EXPECT_EQ((unsigned int)0, root.size());
}

TEST(json_json, ParseSucess) {
    std::string jsonString = "\n\
// Configuration options\n\
{\n\
    // Default encoding for text\n\
    \"encoding\" : \"UTF-8\",\n\
    \n\
    // Plug-ins loaded at start-up\n\
    \"plug-ins\" : [\n\
        \"python\",\n\
        \"c++\",\n\
        \"ruby\"\n\
        ],\n\
    \n\
    // Tab indent size\n\
    \"indent\" : { \"length\" : 3, \"use_space\": true }\n\
}\n\
";

    Json::Value root;
    Json::Reader reader;
    ASSERT_EQ(true, reader.parse(jsonString, root));
    EXPECT_EQ((unsigned int)3, root.size());

    EXPECT_EQ(true, root.isMember("encoding"));
    EXPECT_EQ(true, root["encoding"].isString());
    EXPECT_EQ("UTF-8", root["encoding"].asString());

    EXPECT_EQ(false, root.isMember("not_exist_attribute"));
    EXPECT_EQ("default", root.get("not_exist_attribute", "default").asString());

    EXPECT_EQ(true, root["plug-ins"].isArray());
    ASSERT_EQ((unsigned int)3, root["plug-ins"].size());
    EXPECT_EQ("python", root["plug-ins"][0].asString());
    EXPECT_EQ("c++", root["plug-ins"][1].asString());
    EXPECT_EQ("ruby", root["plug-ins"][2].asString());

    EXPECT_EQ(3, root["indent"]["length"].asInt());
    EXPECT_EQ(true, root["indent"]["use_space"].asBool());

    std::vector<std::string> members = root["indent"].getMemberNames();
    EXPECT_EQ((unsigned int)2, members.size());
    EXPECT_EQ("length", members[0]);
    EXPECT_EQ("use_space", members[1]);
}

TEST(json_json, ParseFail) {
    std::string jsonString = "\n\
// Configuration options\n\
{\n\
    // Default encoding for text\n\
    \"encoding\" : \"UTF-8\",\n\
    \n\
    // Plug-ins loaded at start-up\n\
    \"plug-ins\" : [\n\
        \"python\",\n\
        \"c++\",\n\
";

    Json::Value root;
    Json::Reader reader;
    ASSERT_EQ(false, reader.parse(jsonString, root));

    //WARNING parsing을 실패하더라도 root 에 invalidate 한 데이터가 들어 있을 수 있음 
    EXPECT_NE((unsigned int)0, root.size());
    root.clear();

    std::string errorMessage = "* Line 11, Column 1\n  Syntax error: value, object or array expected.\n";
    EXPECT_EQ(errorMessage, reader.getFormattedErrorMessages());    
}

TEST(json_json, ParseFail2) {
    std::string jsonString = "\
{\n\
    \"ProcessorPipeliner\": [\n\
        \"SplitBypass\": {\n\
        },\n\
        \"SelectFirstFrame\": {\n\
        }\n\
    ]\n\
}\n\
";
    Json::Value root;
    Json::Reader reader;
    ASSERT_FALSE( reader.parse(jsonString, root) );
}

TEST(json_json, Dump) {
    std::string expectedJsonString = "{\"encoding\":\"UTF-8\",\"indent\":{\"length\":3,\"use_space\":true},\"plug-ins\":[\"python\",\"c++\",\"ruby\"]}\n";

    Json::Value root;
    root["encoding"] = "UTF-8";
    root["plug-ins"].resize(3);
    root["plug-ins"][0] = "python";
    root["plug-ins"][1] = "c++";
    root["plug-ins"][2] = "ruby";
    root["indent"]["length"] = 3;
    root["indent"]["use_space"] = true;

    Json::FastWriter writer;
    EXPECT_EQ(expectedJsonString, writer.write(root));
}

TEST(json_json, DumpPretty) {
    std::string expectedJsonString = "\
{\n\
   \"encoding\" : \"UTF-8\",\n\
   \"indent\" : {\n\
      \"length\" : 3,\n\
      \"use_space\" : true\n\
   },\n\
   \"plug-ins\" : [ \"python\", \"c++\", \"ruby\" ]\n\
}\n\
";

    Json::Value root;
    root["encoding"] = "UTF-8";
    root["plug-ins"].resize(2);
    root["plug-ins"][0] = "python";
    root["plug-ins"][1] = "c++";
    root["plug-ins"].append("ruby");
    root["indent"]["length"] = 3;
    root["indent"]["use_space"] = true;

    Json::StyledWriter writer;
    EXPECT_EQ(expectedJsonString, writer.write(root));
}


