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

    fy::init();

    fy::writeBulk("test.txt", data, 1024*1024*1024, 0);

    fy::release();

    delete data;

    return 0;
}
