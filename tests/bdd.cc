#include "gtest/gtest.h"

#include <fyramid.h>
#include <cstdio>
#include <cstdint>

TEST(BDD, OpenAndCloseFileInWriteMode) {
    fy::File* fp = fy::open("test.txt", fy::OpenMode::write);

    fy::close(fp);
}

TEST(RDD, OpenAndWriteFile) {
}

TEST(RDD, OpenAndReadFile) {
}

TEST(RDD, WriteAndReadBulkOfData) {
    // Open test.txt file using fyramid

    // Write bulk of data

    // Close fyramid handle

    // Open test.txt file using fyramid

    // Read bulk of data

    // Read from selected offset

    // Close fyramid handle
}
