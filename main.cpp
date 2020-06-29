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
//        tool.usage();
    }

    for (auto path : paths) {
        tool.created_directory(path);
    }


//    std::string path_home = "/root";
//    if (argc == 3 && (strcmp(argv[1], "-id") == 0)) {
//        path_home.replace(0, 5, "/home/");
//        path_home.append(argv[2]);
//        if (!fs::exists(path_home)) {
//            std::cout << "user dengan name " << argv[2] << " tidak ada" << std::endl;
//        }
//    }
//
//
//    for (auto &path : paths) {
//        created_directory(path);
//        if (argc == 2 && strcmp(argv[1], "-u") == 0) {
//            umount_path(path);
//        } else if (argc == 1 || argc == 3 && (strcmp(argv[1], "-id") == 0)) {
//            std::string options = "size=5000m,mode=0755";
//            struct stat st{};
//            stat(path_home.c_str(), &st);
//            options.append(",uid=" + std::to_string(st.st_gid) + ",gid=" + std::to_string(st.st_gid));
//            mount_path_to_ram(path, options.c_str());
//        } else {
//            usage();
//            break;
//        }
//    }
    return 0;
}
