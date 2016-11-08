#ifndef FYRAMID_FYRAMID_H_
#define FYRAMID_FYRAMID_H_

#include <cstdio>
#include <cstddef>
#include <cassert>

#include <string>
#include <unordered_map>

namespace fy {
    enum class OpenMode {
        write, read
    };

    class File {
    public:
        File(const char* path, OpenMode openMode);
        ~File();

        void read(std::string& data, size_t size, off_t offset);
        void write(const std::string& data, size_t size, off_t offset);

        static File* open(const char* path, OpenMode openMode);
        static void close(File* fp);

        std::string _path;
        OpenMode _openMode;

        int _fileDescriptor;
    };

    void init();
    void release();

    void writeBulk(const char* path, const void* data, size_t size, off_t offset);
    void readBulk(const char *path, void *data, size_t size, off_t offset);
    void readBulkInParallel(const char *path, void *data, size_t size, off_t offset);
}

#endif // FYRAMID_FYRAMID_H_
