#include <iostream>
#include <filesystem>
#include <sys/mount.h>
#include <cstring>

namespace fs = std::filesystem;

int main(int argc, char *argv[]) {
    const char *paths[] = {
            "/tmp/test/test1",
            "/tmp/test/test2",
            "/tmp/test/test3",
            "/tmp/test/test4",
            "/tmp/test/test5",
            "/tmp/test/test6",
            "/tmp/test/test7",
            "/tmp/test/test8",
            "/tmp/test/test9",
            "/tmp/test/test10",
            "/tmp/test/test11",
            "/tmp/test/test12",
            "/tmp/test/test13",
            "/tmp/test/test14",
            "/tmp/test/test15",
            "/tmp/test/test16",
            "/tmp/test/test17",
            "/tmp/test/test18",
            "/tmp/test/test19",
            "/tmp/test/test20",
            "/tmp/test/test21",
            "/tmp/test/test22",
            "/tmp/test/test23",
            "/tmp/test/test24",
            "/tmp/test/test25",
            "/tmp/test/test26",
    };

    /* created directory */
    for (const auto &path : paths) {
        if (!fs::exists(path)) {
            fs::create_directory(path);
            fs::permissions(path, fs::perms::owner_all | fs::perms::group_read | fs::perms::group_exec |
                                  fs::perms::others_read | fs::perms::others_exec);
        } else {
            /* directory not empty remove isi directory */
            if (!fs::is_empty(path)) {
                for (auto &entry : fs::directory_iterator(path)) {
                    std::cout << fs::remove(entry) << std::endl;
                }
            }
        }


        if (argc == 2) {
            if (strcmp(argv[1], "umount") == 0) {
                std::cout << umount2(path, 0) << std::endl;

            }
        } else {
            if (mount("tmpfs", path, "tmpfs", MS_REMOUNT, "size=5000m") == -1) {
                std::cout << mount("tmpfs", path, "tmpfs", 0, "size=5000m") << std::endl;
            }
        }
    }
    return 0;
}
