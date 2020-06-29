#ifndef _MY_TOOL_HPP
#define _MY_TOOL_HPP

class MyTool {
public:
    void umount_path(const char *path);

    void mount_path_to_ram(const char *path, const char *options);

    void usage();

    void created_directory(const char *path);
};


#endif //_MY_TOOL_HPP
