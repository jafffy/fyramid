//
// Created by Jaewon Choi on 05/11/2016.
//

#include <fyramid.h>

#include <string>

int main()
{
    std::string data = "Hello, World!";

    fy::init();

    fy::File* fp = fy::open("hello.txt", fy::OpenMode::write);

    fy::write(fp, data, data.size(), 0);

    fy::close(fp);

    fy::release();

    return 0;
}