//
// Created by Jaewon Choi on 05/11/2016.
//

#include <fyramid.h>

int main()
{
    fy::init();

    {
        std::string data = "Hello, World!";

        fy::File* fp = fy::File::open("./hello.txt", fy::OpenMode::write);
        fp->write(data, data.size(), 0);

        fy::File::close(fp);
    }

    {
        std::string data;
        data.resize(5);

        fy::File* fp = fy::File::open("./hello.txt", fy::OpenMode::read);
        fp->read(data, 5, 0);

        fy::File::close(fp);

        printf("%s\n", data.c_str());
    }

    fy::release();

    return 0;
}
