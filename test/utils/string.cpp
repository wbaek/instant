
#include <gtest/gtest.h>

#include "utils/string.hpp"

TEST(instant_Utils_String, ToString) {
    EXPECT_EQ( "1", instant::Utils::String::ToString<int>(1) );
    EXPECT_EQ( "-1", instant::Utils::String::ToString<int>(-1) );
    EXPECT_EQ( "10", instant::Utils::String::ToString<float>(10.0f) );
    EXPECT_EQ( "10", instant::Utils::String::ToString<double>(10.0) );
}

TEST(instant_Utils_String, ToPrimitiveInt) {
    int value;
    EXPECT_EQ(true, instant::Utils::String::ToPrimitive("1", value));
    EXPECT_EQ(1, value);
    EXPECT_EQ(true, instant::Utils::String::ToPrimitive("-1", value));
    EXPECT_EQ(-1, value);
    EXPECT_EQ(true, instant::Utils::String::ToPrimitive("1.1", value));
    EXPECT_EQ(1, value);
    EXPECT_EQ(true, instant::Utils::String::ToPrimitive("1f", value));
    EXPECT_EQ(1, value);
    EXPECT_EQ(true, instant::Utils::String::ToPrimitive("3p", value));
    EXPECT_EQ(3, value);
    EXPECT_EQ(true, instant::Utils::String::ToPrimitive("5-2", value));
    EXPECT_EQ(5, value);
    EXPECT_EQ(true, instant::Utils::String::ToPrimitive(" 9", value));
    EXPECT_EQ(9, value);
    EXPECT_EQ(true, instant::Utils::String::ToPrimitive("8 ", value));
    EXPECT_EQ(8, value);
    EXPECT_EQ(true, instant::Utils::String::ToPrimitive(" 7 ", value));
    EXPECT_EQ(7, value);
    EXPECT_EQ(true, instant::Utils::String::ToPrimitive("\t6\n", value));
    EXPECT_EQ(6, value);
}

TEST(instant_Utils_String, ToPrimitiveUnsignedInt) {
    unsigned int value;
    EXPECT_EQ(true, instant::Utils::String::ToPrimitive("1", value));
    EXPECT_EQ((unsigned int)1, value);
    EXPECT_EQ(true, instant::Utils::String::ToPrimitive("1.1", value));
    EXPECT_EQ((unsigned int)1, value);
    EXPECT_EQ(true, instant::Utils::String::ToPrimitive("1f", value));
    EXPECT_EQ((unsigned int)1, value);
    EXPECT_EQ(true, instant::Utils::String::ToPrimitive("3p", value));
    EXPECT_EQ((unsigned int)3, value);
    EXPECT_EQ(true, instant::Utils::String::ToPrimitive("5-2", value));
    EXPECT_EQ((unsigned int)5, value);
}

TEST(instant_Utils_String, ToPrimitiveFloat) {
    float value;
    EXPECT_EQ(true, instant::Utils::String::ToPrimitive("1", value));
    EXPECT_EQ(1.0f, value);
    EXPECT_EQ(true, instant::Utils::String::ToPrimitive("-1", value));
    EXPECT_EQ(-1.0f, value);
    EXPECT_EQ(true, instant::Utils::String::ToPrimitive("1.1", value));
    EXPECT_EQ(1.1f, value);
    EXPECT_EQ(true, instant::Utils::String::ToPrimitive("5-2", value));
    EXPECT_EQ(5.0f, value);
    EXPECT_EQ(true, instant::Utils::String::ToPrimitive(".3425", value));
    EXPECT_EQ(0.3425f, value);
    EXPECT_EQ(true, instant::Utils::String::ToPrimitive("0.00000000000000000000", value));
    EXPECT_EQ(0.0f, value);

#ifdef __LINUX__
    EXPECT_EQ(true, instant::Utils::String::ToPrimitive("1f", value));
    EXPECT_EQ(1.0f, value);
    EXPECT_EQ(true, instant::Utils::String::ToPrimitive("3p", value));
    EXPECT_EQ(3.0f, value);
#endif //__LINUX__
}

TEST(instant_Utils_String, Trim) {
    EXPECT_EQ("", instant::Utils::String::Trim(""));
    EXPECT_EQ("", instant::Utils::String::Trim("\n"));
    EXPECT_EQ("x", instant::Utils::String::Trim("x "));
    EXPECT_EQ("x", instant::Utils::String::Trim(" x"));
    EXPECT_EQ("x", instant::Utils::String::Trim(" x "));
    EXPECT_EQ("x", instant::Utils::String::Trim("x\r\n"));
    EXPECT_EQ("x", instant::Utils::String::Trim("abxab", "ab") );
    EXPECT_EQ(" x ", instant::Utils::String::Trim("a x b", "ab") );

    EXPECT_EQ("", instant::Utils::String::FTrim(""));
    EXPECT_EQ("\n", instant::Utils::String::FTrim("\n"));
    EXPECT_EQ("x ", instant::Utils::String::FTrim("x "));
    EXPECT_EQ("x", instant::Utils::String::FTrim(" x"));
    EXPECT_EQ("x ", instant::Utils::String::FTrim(" x "));
    EXPECT_EQ("x\r\n", instant::Utils::String::FTrim("x\r\n"));
    EXPECT_EQ("xab", instant::Utils::String::FTrim("abxab", "ab") );
    EXPECT_EQ(" x b", instant::Utils::String::FTrim("a x b", "ab") );

    EXPECT_EQ("", instant::Utils::String::RTrim(""));
    EXPECT_EQ("\n", instant::Utils::String::RTrim("\n"));
    EXPECT_EQ("x", instant::Utils::String::RTrim("x "));
    EXPECT_EQ(" x", instant::Utils::String::RTrim(" x"));
    EXPECT_EQ(" x", instant::Utils::String::RTrim(" x "));
    EXPECT_EQ("x", instant::Utils::String::RTrim("x\r\n"));
    EXPECT_EQ("abx", instant::Utils::String::RTrim("abxab", "ab") );
    EXPECT_EQ("a x ", instant::Utils::String::RTrim("a x b", "ab") );

    EXPECT_EQ("", instant::Utils::String::TrimWhitespace(""));
    EXPECT_EQ("", instant::Utils::String::TrimWhitespace("\n"));
    EXPECT_EQ("x", instant::Utils::String::TrimWhitespace("x "));
    EXPECT_EQ("x", instant::Utils::String::TrimWhitespace(" x"));
    EXPECT_EQ("x", instant::Utils::String::TrimWhitespace(" x "));
    EXPECT_EQ("x", instant::Utils::String::TrimWhitespace("x\r\n"));
    EXPECT_EQ("abxab", instant::Utils::String::TrimWhitespace("abxab") );
    EXPECT_EQ("axb", instant::Utils::String::TrimWhitespace("a x b") );
}

void TestSplitedString(const std::vector<std::string>& splited, const std::string& str, const unsigned int size) {
    for(unsigned int i=0; i<size; i++) {
        EXPECT_EQ(str, splited[i]);
    }
}

TEST(instant_Utils_String, Split) {
    std::vector<std::string> splited;

    // Split
    splited = instant::Utils::String::Split("", " ");
    ASSERT_EQ((unsigned int)1, splited.size());
    TestSplitedString(splited, "", 1);

    splited = instant::Utils::String::Split("abcdefg", "z");
    ASSERT_EQ((unsigned int)1, splited.size());
    TestSplitedString(splited, "abcdefg", 1);

    splited = instant::Utils::String::Split("x x", " ");
    ASSERT_EQ((unsigned int)2, splited.size());
    TestSplitedString(splited, "x", 2);

    splited = instant::Utils::String::Split("x x ", " ");
    ASSERT_EQ((unsigned int)3, splited.size());
    TestSplitedString(splited, "x", 2);
    EXPECT_EQ("", splited.back());

    splited = instant::Utils::String::Split("x<--SPLITTER-->x", "<--SPLITTER-->");
    ASSERT_EQ((unsigned int)2, splited.size());
    TestSplitedString(splited, "x", 2);

    splited = instant::Utils::String::Split("abcdefg", "bdf");
    ASSERT_EQ((unsigned int)1, splited.size());
    TestSplitedString(splited, "abcdefg", 1);

    splited = instant::Utils::String::Split("x__x", "_");
    ASSERT_EQ((unsigned int)3, splited.size());
    EXPECT_EQ("x", splited[0]);
    EXPECT_EQ("", splited[1]);
    EXPECT_EQ("x", splited[2]);

    // Splits
    splited = instant::Utils::String::Splits("", " ");
    ASSERT_EQ((unsigned int)0, splited.size());

    splited = instant::Utils::String::Splits("abcdefg", "z");
    ASSERT_EQ((unsigned int)1, splited.size());
    TestSplitedString(splited, "abcdefg", 1);

    splited = instant::Utils::String::Splits("x x", " ");
    ASSERT_EQ((unsigned int)2, splited.size());
    TestSplitedString(splited, "x", 2);

    splited = instant::Utils::String::Splits("x x ", " ");
    ASSERT_EQ((unsigned int)2, splited.size());
    TestSplitedString(splited, "x", 2);

    splited = instant::Utils::String::Splits("x<--SPLITTER-->x", "<--SPLITTER-->");
    ASSERT_EQ((unsigned int)2, splited.size());
    TestSplitedString(splited, "x", 2);

    splited = instant::Utils::String::Splits("abcdefg", "bdf");
    ASSERT_EQ((unsigned int)4, splited.size());
    EXPECT_EQ("a", splited[0]);
    EXPECT_EQ("c", splited[1]);
    EXPECT_EQ("e", splited[2]);
    EXPECT_EQ("g", splited[3]);

}

TEST(instant_Utils_String, Join) {
    std::vector<std::string> splited;

    EXPECT_EQ("", instant::Utils::String::Join(splited, ""));
    EXPECT_EQ("", instant::Utils::String::Join(splited, " "));

    splited.push_back("a"); splited.push_back("b"); splited.push_back("c");
    EXPECT_EQ("abc", instant::Utils::String::Join(splited, ""));
    EXPECT_EQ("a\nb\nc", instant::Utils::String::Join(splited, "\n"));
    EXPECT_EQ("a----b----c", instant::Utils::String::Join(splited, "----"));
}

TEST(instant_Utils_String, Replace) {
    EXPECT_EQ("", instant::Utils::String::Replace("", "", ""));
    EXPECT_EQ("", instant::Utils::String::Replace("", "x", "z"));
    EXPECT_EQ("f(z)=y", instant::Utils::String::Replace("f(x)=y", "x", "z"));
    EXPECT_EQ("f(x)=y", instant::Utils::String::Replace("f(arguments)=y", "arguments", "x"));
}

TEST(instant_Utils_String, Format) {
    EXPECT_EQ("", instant::Utils::String::Format(""));
    EXPECT_EQ("13", instant::Utils::String::Format("%d", 13));
    EXPECT_EQ("013", instant::Utils::String::Format("%03d", 13));
    EXPECT_EQ("0.03", instant::Utils::String::Format("%.2f", 0.0344));
    EXPECT_EQ("0.04", instant::Utils::String::Format("%.2f", 0.0374));
    EXPECT_EQ("013, 0.04", instant::Utils::String::Format("%03d, %.2f", 13, 0.0374)); 
}

TEST(instant_Utils_String, UpperLowerString) {

    EXPECT_EQ("", instant::Utils::String::UpperString(""));
    EXPECT_EQ("", instant::Utils::String::LowerString(""));

    EXPECT_EQ("X", instant::Utils::String::UpperString("x"));
    EXPECT_EQ("x", instant::Utils::String::LowerString("X"));

    EXPECT_EQ("X", instant::Utils::String::UpperString("X"));
    EXPECT_EQ("x", instant::Utils::String::LowerString("x"));

    EXPECT_EQ("3X5", instant::Utils::String::UpperString("3x5"));
    EXPECT_EQ("3x5", instant::Utils::String::LowerString("3X5"));

}

TEST(instant_Utils_String, ParseOptions) {
    std::map<std::string, std::string> options;

    options = instant::Utils::String::ParseOptions( "" );
    EXPECT_EQ((unsigned int)0, options.size());
    EXPECT_EQ("", options["key"]);

    options = instant::Utils::String::ParseOptions( "key=value" );
    EXPECT_EQ((unsigned int)1, options.size());
    EXPECT_EQ("value", options["key"]);
    EXPECT_EQ("", options["another_key"]);

    options = instant::Utils::String::ParseOptions( "key1=value1&key2=value2" );
    EXPECT_EQ((unsigned int)2, options.size());
    EXPECT_EQ("value1", options["key1"]);
    EXPECT_EQ("value2", options["key2"]);
    EXPECT_EQ("", options["another_key"]);
}

TEST(instant_Utils_String, EncodeDecodeURL) {
    EXPECT_EQ("", instant::Utils::String::EncodeURL(""));
    EXPECT_EQ("", instant::Utils::String::DecodeURL(""));

    EXPECT_EQ("test%20string%20%26%20query%20value", instant::Utils::String::EncodeURL("test string & query value"));
    EXPECT_EQ("test string & query value", instant::Utils::String::DecodeURL("test%20string%20%26%20query%20value"));
}
