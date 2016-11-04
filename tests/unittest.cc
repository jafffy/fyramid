#include "gtest/gtest.h"

#include <fyramid.h>

#include <unistd.h>

TEST(BasicIOFunctions, open) {
    fy::File* fp = fy::open("test.txt", fy::OpenMode::write);

    EXPECT_TRUE(access("test.txt", F_OK) != -1);

    fy::close(fp);
}
