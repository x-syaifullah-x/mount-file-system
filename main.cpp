#include <iostream>
#include <filesystem>
#include <sys/mount.h>
#include <cstring>

namespace fs = std::filesystem;

/* if the folder does not exist, create a folder */
void created_directory(const std::string &path) {
    std::string delimiter = "/";
    std::string test;
    auto start = 0U;
    auto end = path.find(delimiter);
    while (end != std::string::npos) {
        start = end + delimiter.length();
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

int main(int argc, char *argv[]) {
    const char *paths[] = {
            "/tmp/aaaa/sasas",
            "/tmp/aaaa/asaaa",
            "/tmp/aaaa/aaaaa",
            "/tmp/aaaa/ssss",
            "/tmp/aaaa/sdsdsd",
    };

    for (auto &path : paths) {
        created_directory(path);
        if (argc == 2) {
            if (strcmp(argv[1], "umount") == 0) {
                if (umount2(path, 0) != 0) {
                    std::cout << "umont filed " << path << std::endl;
                }
            }
        } else {
            if (mount("tmpfs", path, "tmpfs", MS_REMOUNT, "size=5000m") == -1) {
                if (mount("tmpfs", path, "tmpfs", 0, "size=5000m") != 0) {
                    std::cout << "mount filed " << path << std::endl;
                }
            }
        }
    }
    return 0;
}
