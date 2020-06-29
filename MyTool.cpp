#include "MyTool.hpp"
#include <sys/mount.h>
#include <cerrno>
#include <iostream>
#include <filesystem>
#include <sys/mount.h>
#include <cstring>
#include <sys/stat.h>

#define DELIMITER "/"

namespace fs = std::filesystem;

void MyTool::umount_path(const char *path) {
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

void MyTool::mount_path_to_ram(const char *path, const char *options) {
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

/* if the folder does not exist, create a folder */
void MyTool::created_directory(const char *path) {
    std::string buffer;
    std::string pathToString = path;

    auto end = pathToString.find(DELIMITER);
    while (end != std::string::npos) {
        auto start = end + 1;
        end = pathToString.find(DELIMITER, start);
        if (start != 0) {
            buffer += DELIMITER + pathToString.substr(start, end - start);

            if (!fs::exists(path)) {
                fs::create_directory(path);
                fs::permissions(path, fs::perms::owner_all | fs::perms::group_read | fs::perms::group_exec |
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

void MyTool::usage() {
    std::cout << "command -U user" << std::endl;
    std::cout << "command -u umount" << std::endl;
    exit(0);
}