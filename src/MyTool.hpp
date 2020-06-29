#ifndef _MY_TOOL_HPP
#define _MY_TOOL_HPP

#include <iostream>

class MyTool {
private:

public:
    void umount_path(const char *path);

    void mount_path(const char *path, const char *options);

    void usage();

    void check_directory(const char *path);

    void user_check(const char *path);

};


#endif //_MY_TOOL_HPP
