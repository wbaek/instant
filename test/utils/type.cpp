
#include <gtest/gtest.h>

#include "utils/type.hpp"

class TestClass {
    public:
        int a;
        TestClass(){}
        virtual ~TestClass(){}
        virtual const std::string TypeName() {
            return instant::Utils::Type::GetTypeName(this);
        }
};

class TestClassTwo : public TestClass {

};


TEST(instant_Utils_Type, GetTypeName) {
    EXPECT_EQ("TestClass", instant::Utils::Type::GetTypeName<TestClass>());
    EXPECT_EQ("TestClass", TestClass().TypeName());
    
    EXPECT_EQ("TestClassTwo", instant::Utils::Type::GetTypeName<TestClassTwo>());
    EXPECT_EQ("TestClassTwo", TestClassTwo().TypeName());

}

