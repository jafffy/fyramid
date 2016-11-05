#include <fyramid.h>

#include "fyramid.h"

using namespace std;

static std::unordered_map<std::string, fy::File*> gFileMap;

namespace fy {

    File* open(const char* path, OpenMode openMode) {
        return nullptr;
    }

    void close(File* fp) {
    }

    void init() {

    }

    void release() {
    }

    void write(File* fp, const std::string& data, size_t size, off_t offset) {

    }
}
