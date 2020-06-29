#include <iostream>
#include "MyTool.hpp"
#include "paths.h"


int main(int argc, char *argv[]) {
    MyTool tool;
    if (argc > 1 && argc % 2 == 1) {
        for (int i = 0; i < argc; ++i) {
            switch (argv[i][1]) {
                case 'U': /* user */
                    std::cout << "option -U user" << std::endl;
                    break;
                case 'u':
                    std::cout << "option -u umount" << std::endl;
                    break;
            }
        }
    } else {
        tool.usage();
    }


    /* looping path */
    for (auto path : paths) {
        tool.check_directory(path);
    }
    return 0;
}
