#include <iostream>
#include <filesystem>
#include <sys/mount.h>
#include <cstring>
#include <sys/stat.h>
#include <unistd.h>
#include <pwd.h>
#include <cerrno>

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
    if (umount2(path, 0) != 0) {
        switch (errno) {
            case EINVAL:
                std::cout << path << " not mounted" << std::endl;
                break;
        }
    }
}

void usage(){
    std::cout << "test" << std::endl;
}

int main(int argc, char *argv[]) {
    std::string path_home = "/root";
    if (argc == 2) {
        path_home.replace(0, 5, "/home/");
        path_home.append(argv[1]);
    }

    const char *paths[] = {
            "/home/xxx/.cache/test",
            "/home/xxx/.cache/ttest1",
            "/home/xxx/.cache/tedada",
    };

    for (auto &path : paths) {
        created_directory(path);
        if (argc == 2 && strcmp(argv[1], "umount") == 0) {
            umount_path(path);
        } else if (argc == 1) {
            std::string options = "size=5000m,mode=0755";
            struct stat st{};
            stat(path_home.c_str(), &st);
            options.append(",uid=" + std::to_string(st.st_gid) + ",gid=" + std::to_string(st.st_gid));
            mount_path_to_ram(path, options.c_str());
        } else{
            usage();
            break;
        }
    }
    return 0;
}
