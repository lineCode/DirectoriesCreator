#include "create_path.h"

#include <shlwapi.h>

#include <cstring>

#include <iostream>



uint64_t create_path(const char* path)
{
    if (path == nullptr) {
        return -1;
    }

    while (path) {
        const char* next = PathFindNextComponent(path);
        if (next) {
            std::size_t count = 0;
            if (strcmp(next, "\0")) {
                const char* position = strstr(path, next);
                count = position-path;
            }
            else {
                count = strlen(path);
            }
            char directory[count+1];
            strncpy_s(directory, sizeof(directory), path, count);

            std::cout << directory << "\n";
        }
        path = next;
    }

    return GetLastError();
}
