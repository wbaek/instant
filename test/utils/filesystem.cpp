#include <gtest/gtest.h>
#include "../defines.hpp"

#include <vector>
#include "utils/filesystem.hpp"

class instant_Utils_Filesystem : public ::testing::Test {
    protected:
        virtual void SetUp() {
            instant::Utils::Filesystem::EnsureDirectory( OUTPUT_TEXT_FOLDER );
            instant::Utils::Filesystem::SetFileValue( OUTPUT_TEXT_FOLDER + std::string("/") + SAMPLE_TEXT_FILE, std::string("sample1 sample2 sample3") );
        }
        virtual void TearDown() {
            instant::Utils::Filesystem::RemoveDirectory( OUTPUT_TEXT_FOLDER );
        }
};

TEST_F(instant_Utils_Filesystem, MakeRemoveDirectory) {
    instant::Utils::Filesystem::EnsureDirectory( OUTPUT_TEXT_FOLDER + std::string("/sample_folder") );
    ASSERT_EQ( true, instant::Utils::Filesystem::IsDirectory( OUTPUT_TEXT_FOLDER ) );
    ASSERT_EQ( true, instant::Utils::Filesystem::IsDirectory( OUTPUT_TEXT_FOLDER + std::string("/sample_folder") ) );
    instant::Utils::Filesystem::RemoveDirectory( OUTPUT_TEXT_FOLDER );
    ASSERT_EQ( false, instant::Utils::Filesystem::IsDirectory( OUTPUT_TEXT_FOLDER + std::string("/sample_folder") ) );
    ASSERT_EQ( false, instant::Utils::Filesystem::IsDirectory( OUTPUT_TEXT_FOLDER ) );
}

TEST_F(instant_Utils_Filesystem, IsFileAndDirectory) {
    EXPECT_EQ( true, instant::Utils::Filesystem::IsFile( OUTPUT_TEXT_FOLDER + std::string("/") + SAMPLE_TEXT_FILE ) );
    EXPECT_EQ( true, instant::Utils::Filesystem::IsDirectory( OUTPUT_TEXT_FOLDER ) );
}

TEST_F(instant_Utils_Filesystem, GetFileNames) {
    std::vector<std::string> filenameList;
    instant::Utils::Filesystem::GetFileNames( OUTPUT_TEXT_FOLDER, filenameList, false);
    ASSERT_EQ( (unsigned int)1, filenameList.size() );
    EXPECT_EQ( SAMPLE_TEXT_FILE, filenameList[0] );
}

TEST_F(instant_Utils_Filesystem, Get_Set_FileValue) {
    std::string filename = "/test_set_get_file.txt";
    std::string value = "test_values_random-key\ndata2";
    instant::Utils::Filesystem::SetFileValue( OUTPUT_TEXT_FOLDER + filename, value );
    EXPECT_EQ( true, instant::Utils::Filesystem::IsFile( OUTPUT_TEXT_FOLDER + filename ) );
    EXPECT_EQ( value, instant::Utils::Filesystem::GetFileValue( OUTPUT_TEXT_FOLDER +  filename ) );
}

TEST_F(instant_Utils_Filesystem, JoinPath) {
    std::string joinedPath;
    
    joinedPath = instant::Utils::Filesystem::JoinPath( OUTPUT_TEXT_FOLDER, SAMPLE_TEXT_FILE);
    EXPECT_EQ( OUTPUT_TEXT_FOLDER + std::string("/") + SAMPLE_TEXT_FILE, joinedPath );

    joinedPath = instant::Utils::Filesystem::JoinPath( OUTPUT_TEXT_FOLDER, std::string("/") + SAMPLE_TEXT_FILE);
    EXPECT_EQ( OUTPUT_TEXT_FOLDER + std::string("/") + SAMPLE_TEXT_FILE, joinedPath );

    joinedPath = instant::Utils::Filesystem::JoinPath( OUTPUT_TEXT_FOLDER + std::string("/"), SAMPLE_TEXT_FILE);
    EXPECT_EQ( OUTPUT_TEXT_FOLDER + std::string("/") + SAMPLE_TEXT_FILE, joinedPath );

    joinedPath = instant::Utils::Filesystem::JoinPath( OUTPUT_TEXT_FOLDER + std::string("/"), std::string("/") + SAMPLE_TEXT_FILE);
    EXPECT_EQ( OUTPUT_TEXT_FOLDER + std::string("/") + SAMPLE_TEXT_FILE, joinedPath );
}

TEST_F(instant_Utils_Filesystem, BaseAndDirName) {
    std::string baesName;
    std::string dirName;
    
    baesName = instant::Utils::Filesystem::BaseName( OUTPUT_TEXT_FOLDER );
    dirName = instant::Utils::Filesystem::BaseName( OUTPUT_TEXT_FOLDER );
    EXPECT_EQ( "text", baesName );
    EXPECT_EQ( "text", dirName );

    baesName = instant::Utils::Filesystem::BaseName( OUTPUT_TEXT_FOLDER + std::string("/") );
    dirName = instant::Utils::Filesystem::BaseName( OUTPUT_TEXT_FOLDER + std::string("/") );
    EXPECT_EQ( "text", baesName );
    EXPECT_EQ( "text", dirName );

    baesName = instant::Utils::Filesystem::BaseName( OUTPUT_TEXT_FOLDER + std::string("/") + SAMPLE_TEXT_FILE );
    dirName = instant::Utils::Filesystem::BaseName( OUTPUT_TEXT_FOLDER + std::string("/") + SAMPLE_TEXT_FILE );
    EXPECT_EQ( "sample.txt", baesName );
    EXPECT_EQ( "sample.txt", dirName );
}

TEST_F(instant_Utils_Filesystem, Others) {
    std::cout << "GetCurrentPath() : " << instant::Utils::Filesystem::GetCurrentPath() << std::endl;
    std::cout << "AbsPath(\"../include/\") : " << instant::Utils::Filesystem::AbsPath("../include/") << std::endl;
    std::cout << "AbsPath(AbsPath(\"../include/\")) : " << instant::Utils::Filesystem::AbsPath(instant::Utils::Filesystem::AbsPath("../include/")) << std::endl;
}

