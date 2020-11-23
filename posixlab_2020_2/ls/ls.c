#include <dirent.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

bool lsdir(const char *dirname, bool printname) {
    DIR *dir = opendir(dirname);
    if (dir == NULL) {
        printf("ls: cannot access '%s'\n", dirname);
        return false;
    }
    if (printname) printf("%s:\n", dirname);
    struct dirent *file;
    while ((file = readdir(dir)) != NULL) {
        if (strcmp(file->d_name, ".") == 0 | strcmp(file->d_name, "..") == 0) {
            continue;
        }
        if (file->d_type == DT_DIR) {
            printf("%s/\n", file->d_name);
        } else {
            printf("%s\n", file->d_name);
        }
    }
    closedir(dir);

    if (printname) printf("\n");
    return true;
}

int main(int argc, char *argv[]) {
    if (argc == 1) {
        lsdir(".", false);
    } else if (argc == 2) {
        lsdir(argv[1], false);
    } else {
        for (int i = 1; i < argc; i++) {
            lsdir(argv[i], true);
        }
    }

    return 0;
}
