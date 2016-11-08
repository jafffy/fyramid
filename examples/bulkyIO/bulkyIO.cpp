//
// Created by Jaewon Choi on 06/11/2016.
//

#include <fyramid.h>
#include <stdlib.h>
#include <sys/time.h>

int main()
{
    unsigned testingSize = 1024 * 1024 * 1024;

    int* data = new int[testingSize / 4];
    for (int idx = 0; idx < testingSize / 4; ++idx) {
        data[idx] = rand();
    }

    int* validation = new int[testingSize / 4];

    fy::init();

    fy::writeBulk("test.txt", data, testingSize, 0);

    {
        struct timeval lastTime;
        gettimeofday(&lastTime, NULL);

        fy::readBulk("test.txt", validation, testingSize, 0);

        struct timeval now;
        gettimeofday(&now, NULL);

        fprintf(stderr, "%llu\n", now.tv_usec - lastTime.tv_usec);
    }

    {
        struct timeval lastTime;
        gettimeofday(&lastTime, NULL);

        fy::readBulkInParallel("test.txt", validation, testingSize, 0);

        struct timeval now;
        gettimeofday(&now, NULL);

        fprintf(stderr, "%llu\n", now.tv_usec - lastTime.tv_usec);
    }

    fy::release();

    for (int idx = 0; idx < testingSize / 4; ++idx) {
        assert(data[idx] == validation[idx]);
    }

    delete data;
    delete validation;

    return 0;
}
