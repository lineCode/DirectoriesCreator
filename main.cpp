#include <iostream>

#include "create_path.h"



int main(int argc, const char *argv[])
{
    const char* path_root_required = "C:\\Documents and Settings\\Administrator\\Application Data\\ComplexSystems\\Delta8\\Settings";
    const char* path = "C:\\My Cool Folder\\Administrator\\Application Data\\ComplexSystems\\Delta8\\Settings";

    std::cout << create_path(path_root_required) << "\n";
    std::cout << create_path(path) << "\n";

    return 0;
}

