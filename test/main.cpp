#include <gtest/gtest.h>

class InstantEnvironment : public ::testing::Environment{
    public:
        virtual ~InstantEnvironment() {
        }

        virtual void SetUp() {
        }

        virtual void TearDown() {
        }
};

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    ::testing::AddGlobalTestEnvironment(new InstantEnvironment);
    bool rv = RUN_ALL_TESTS();
    return rv;
}

