#ifndef FYRAMID_FYRAMID_H_
#define FYRAMID_FYRAMID_H_

#include <cstdio>
#include <cstddef>

namespace fy {
    enum class OpenMode {
        write
    };

    class File {
    };

    File* open(const char* path, OpenMode openMode);

    void close(File* fp);

    void writeBulk(const void* data, size_t nbyte, off_t offset);
}

#endif // FYRAMID_FYRAMID_H_
