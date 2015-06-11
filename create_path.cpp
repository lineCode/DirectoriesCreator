#include "create_path.h"

#include <shlwapi.h>

#include <cstring>

#include <iostream>



uint64_t create_path(const char* path)
{
    if (path == nullptr) {
        return 1;
    }

    char directory[strlen(path)+1] = { "" };

    while (path) {
        const char* next = PathFindNextComponent(path);
        if (next) {
            std::size_t count;
            if (strcmp(next, "\0")) {
                const char* position = strstr(path, next);
                count = position-path;
            }
            else {
                count = strlen(path);
            }

            char current[count+1];
            strncpy_s(current, sizeof(current), path, count);
            strcat_s(directory, sizeof(directory), current);

            if (!PathFileExists(directory)) {
                if (!CreateDirectory(directory, nullptr)) {
                    return GetLastError();
                }
            }
        }
        path = next;
    }

    return 0;
}
