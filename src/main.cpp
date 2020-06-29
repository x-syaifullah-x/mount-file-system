#include <iostream>
#include "MyTool.hpp"
#include "paths.h"

struct Data {
    std::string user = "root";
    std::string umount;
};

int main(int argc, char *argv[]) {
    MyTool tool;
    Data data;
    if (argc > 1 && argc % 2 == 1) {
        for (int i = 0; i < argc; ++i) {
            switch (argv[i][1]) {
                case 'U': /* user */
                    data.user = argv[i + 1];
                    break;
                case 'u':
                    data.umount = argv[i + 1];
                    break;
            }
        }
    } else {
        tool.usage();
    }


    /* user check */
    if (data.user != "root")
        if (!tool.user_check(data.user)) exit(0);

    if (tool.user_check(data.user)) {
        for (auto path : paths) {
            if (!data.umount.empty()){

            }
        }
    }
    return 0;
}
