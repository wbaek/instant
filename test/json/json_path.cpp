
#include <gtest/gtest.h>

#include "json/json.h"

/** \brief Experimental and untested: represents a "path" to access a node.
 *
 * Syntax:
 * - "." => root node
 * - ".[n]" => elements at index 'n' of root node (an array value)
 * - ".name" => member named 'name' of root node (an object value)
 * - ".name1.name2.name3"
 * - ".[0][1][2].name1[3]"
 * - ".%" => member name is provided as parameter
 * - ".[%]" => index is provied as parameter
 */
TEST(json_path, TraversalUsingPath) {
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

    Json::Path path(".encoding");
    EXPECT_EQ(true, path.resolve( root ).asBool() );

    path = Json::Path(".plug-ins[1]");
    EXPECT_EQ("c++", path.resolve( root ).asString() );

    path = Json::Path(".invalid");
    EXPECT_TRUE( path.resolve( root ).empty() );

}

