#include "create_path.h"

#include <cstring>
#include <shlwapi.h>



/**
 * @brief create_path_v1
 * Uses PathFindNextComponent to determine next folder
 * @param path
 * @return Returns 0 if success and nonzero if failure
 */
uint64_t create_path_v1(const char* path)
{
    if (path == nullptr) {
        return 1;
    }

    char directory[strlen(path) + 1] = { "" };

    while (path) {
        const char* next = PathFindNextComponent(path);
        if (next) {
            std::size_t count;
            if (strcmp(next, "\0")) {
                const char* position = strstr(path, next);
                count = position - path;
            }
            else {
                count = strlen(path);
            }

            char current[count + 1];
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



/**
 * @brief create_path_v2
 * Uses strtok to determine next folder. Required additional memory for saving a copy of path
 * @param path
 * @return Returns 0 if success and nonzero if failure
 */
uint64_t create_path_v2(const char *path)
{
    if (path == nullptr) {
        return 1;
    }

    const char delimiter[] = "\\";

    char copy[ strlen(path) + 1 ];
    strcpy_s(copy, sizeof(copy), path);

    char directory[strlen(path) + 1] = { "" };

    char* current = strtok(copy, delimiter);
    while (current != nullptr) {
        strcat_s(directory, sizeof(directory), current);
        PathAddBackslash(directory);

        if (!PathFileExists(directory)) {
            if (!CreateDirectory(directory, nullptr)) {
                return GetLastError();
            }
        }

        current = strtok(nullptr, delimiter);
    }

    return 0;
}



/**
 * @brief create_path_v3
 * Uses strchr to determine next folder. Minimal memory using (perfect for embedded systems).
 * @param path
 * @return Returns 0 if success and nonzero if failure
 */
uint64_t create_path_v3(const char *path)
{
    if (path == nullptr) {
        return 1;
    }

    const char back_slash = '\\';
    char* position = strchr(path, back_slash);
    while (position != nullptr) {
        char directory[ position - path + 1 ];
        strncpy_s(directory, sizeof(directory), path, position - path);
        PathAddBackslash(directory);

        if (!PathFileExists(directory)) {
            if (!CreateDirectory(directory, nullptr)) {
                return GetLastError();
            }
        }

        position = strchr(position + 1, back_slash);
    }

    return 0;
}
