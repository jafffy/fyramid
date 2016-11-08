#include "fyramid.h"

#include <fcntl.h>
#include <unistd.h>
#include <cstring>

#include <thread>

using namespace std;

static std::unordered_map<std::string, fy::File*> gFileMap;

namespace fy {
    File::File(const char *path, OpenMode openMode)
    : _path(path), _openMode(openMode), _fileDescriptor(-1)
    {
        if (openMode == OpenMode::write) {
            _fileDescriptor = ::open(path,
                                     O_WRONLY | O_CREAT | O_TRUNC,
                                     S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
            if (_fileDescriptor == -1) {
                fprintf(stderr, "%s\n", strerror(errno));
                _exit(-1);
            }
        } else if (openMode == OpenMode::read) {
            _fileDescriptor = ::open(path, O_RDONLY);
            if (_fileDescriptor == -1) {
                fprintf(stderr, "%s\n", strerror(errno));
                _exit(-1);
            }
        }
    }

    File::~File() {
        if (_fileDescriptor != -1) {
            ::close(_fileDescriptor);
        }
    }

    void File::read(std::string& data, size_t size, off_t offset) {
        assert(_fileDescriptor != -1);

        ssize_t res = pread(_fileDescriptor, &data.front(), size, offset);
        if (res == -1) {
            fprintf(stderr, "%s\n", strerror(errno));
            _exit(-1);
        }
    }

    void File::write(const std::string &data, size_t size, off_t offset) {
        assert(_fileDescriptor != -1);

        ssize_t res = pwrite(_fileDescriptor, &data.front(), size, offset);
        if (res == -1) {
            fprintf(stderr, "%s\n", strerror(errno));
            _exit(-1);
        }
    }

    File* File::open(const char* path, OpenMode openMode) {
        return gFileMap[path] = new File(path, openMode);
    }

    void File::close(File* fp) {
        ::close(fp->_fileDescriptor);

        gFileMap.erase(fp->_path);

        if (fp != nullptr) {
            delete fp;
            fp = nullptr;
        }
    }

    void init() {

    }

    void release() {
        for (auto& it : gFileMap) {
            if (it.second != nullptr) {
                delete it.second;
            }
        }

        gFileMap.clear();
    }

    void writeBulk(const char* path, const void* data, size_t size, off_t offset) {
        assert(size != 0);

        int fd = ::open(path, O_WRONLY | O_CREAT | O_TRUNC,
                        S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
        if (fd == -1) {
            fprintf(stderr, "open: %s\n", strerror(errno));
            _exit(-1);
        }

        assert(fd != -1);

        ssize_t res = pwrite(fd, data, size, offset);
        if (res == -1) {
            fprintf(stderr, "pwrite: %s\n", strerror(errno));
            _exit(-1);
        }

        ::close(fd);
    }

    void readBulk(const char *path, void *data, size_t size, off_t offset) {
        assert(size != 0);

        int fd = ::open(path, O_RDONLY);
        if (fd == -1) {
            fprintf(stderr, "open: %s\n", strerror(errno));
            _exit(-1);
        }

        assert(fd != -1);

        ssize_t res = pread(fd, data, size, offset);
        if (res == -1) {
            fprintf(stderr, "pread: %s\n", strerror(errno));
            _exit(-1);
        }

        ::close(fd);
    }

    void readBulkInParallel(const char *path, void *data, size_t size, off_t offset) {
        assert(size != 0);

        int fd = ::open(path, O_RDONLY);
        if (fd == -1) {
            fprintf(stderr, "open: %s\n", strerror(errno));
            _exit(-1);
        }

        assert(fd != -1);

        std::thread t1 { [&]() {
            ssize_t res = pread(fd, data, size / 2, offset);
            if (res == -1) {
                fprintf(stderr, "pread: %s\n", strerror(errno));
                _exit(-1);
            }
        } };

        std::thread t2 { [&]() {
            ssize_t res = pread(fd, data + size / 2, size - size / 2, offset + size / 2);
            if (res == -1) {
                fprintf(stderr, "pread: %s\n", strerror(errno));
                _exit(-1);
            }
        } };

        t1.join();
        t2.join();

        ::close(fd);
    }
}
