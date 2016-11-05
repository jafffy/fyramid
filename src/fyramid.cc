#include "fyramid.h"

#include <fcntl.h>
#include <unistd.h>
#include <cstring>

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
}
