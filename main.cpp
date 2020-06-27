#include <iostream>
#include <filesystem>
#include <sys/mount.h>
#include <cstring>
#include <sys/stat.h>
#include <cerrno>
#include <charconv>
#include "paths.h"

namespace fs = std::filesystem;

/* if the folder does not exist, create a folder */
void created_directory(const std::string &path) {
    std::string delimiter = "/";
    std::string test;
    auto end = path.find(delimiter);
    while (end != std::string::npos) {
        auto start = end + delimiter.length();
        end = path.find(delimiter, start);
        if (start != 0) {
            test += delimiter + path.substr(start, end - start);
            if (!fs::exists(test)) {
                fs::create_directory(test);
                fs::permissions(test, fs::perms::owner_all | fs::perms::group_read | fs::perms::group_exec |
                                      fs::perms::others_read | fs::perms::others_exec);
            } else {
                /* directory not empty remove isi directory */
//                if (!fs::is_empty(path)) {
//                    for (auto &entry : fs::directory_iterator(path)) {
//                        std::cout << fs::remove(entry) << std::endl;
//                    }
//                }
            }
        }
    }
}

void mount_path_to_ram(const char *path, const char *options) {
    mount("tmpfs", path, "tmpfs", MS_REMOUNT, options);
    switch (errno) {
        case EPERM:
            std::cout << "mount_path_to_ram: need access root " << path << std::endl;
            break;
        case EINVAL:
            mount("tmpfs", path, "tmpfs", 0, options);
            break;
    };
}

void umount_path(const char *path) {
    umount2(path, 0);
    switch (errno) {
        case 0:
            std::cout << "success umount " << path << std::endl;
            break;
        case EINVAL:
            std::cout << path << " not mounted" << std::endl;
            break;
    }
}

void usage() {
    std::cout << "command -id user" << std::endl;
    std::cout << "command -u" << std::endl;
}

struct data {
    std::string devices;
    std::string user;
};

int main(int argc, char *argv[]) {
    data a;
    for (int i = 0; i < argc; ++i) {
        if (argv[i][0] == '-' && i != 0 && i + 1 != argc) {
            const char *value = argv[i + 1];
            switch (argv[i][1]) {
                case 'd':
                    a.devices = value;
                    break;
                case 'u':
                    a.user = value;
                    break;
                default:
                    exit(0);
            }
        }
    }
    std::cout << a.devices << std::endl;
    std::cout << a.user << std::endl;
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
