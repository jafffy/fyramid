#ifndef FYRAMID_FYRAMID_H_
#define FYRAMID_FYRAMID_H_

#include <cstdio>
#include <cstddef>

#include <string>
#include <unordered_map>

#define BEGIN_NAMESPACE_FY namespace fy {
#define END_NAMESPACE_FY }

namespace fy {
    enum class OpenMode {
        write
    };

    class File {
    public:
    };

    File* open(const char* path, OpenMode openMode);

    void close(File* fp);

    void init();
    void release();

    void write(File* fp, const std::string& data, size_t size, off_t offset);
}

#endif // FYRAMID_FYRAMID_H_
