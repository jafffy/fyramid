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
    uint8_t* bulkOfData = new uint8_t[BUFSIZ];

    if (bulkOfData != nullptr) {
        fy::writeBulk(bulkOfData, BUFSIZ, 0);

        delete[] bulkOfData;
        bulkOfData = nullptr;
    }
}
