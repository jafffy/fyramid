//
// Created by Jaewon Choi on 06/11/2016.
//

#include <fyramid.h>
#include <stdlib.h>

int main()
{
    int* data = new int[1024*1024*1024 / 4];
    for (int idx = 0; idx < 1024*1024*1024 / 4; ++idx) {
        data[idx] = rand();
    }

    int* validation = new int[1024*1024*1024 / 4];

    fy::init();

    fy::writeBulk("test.txt", data, 1024*1024*1024, 0);
    fy::readBulk("test.txt", validation, 1024*1024*1024, 0);

    fy::release();

    for (int idx = 0; idx < 1024*1024*1024 / 4; ++idx) {
        assert(data[idx] == validation[idx]);
    }

    delete data;
    delete validation;

    return 0;
}
