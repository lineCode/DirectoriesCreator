#include <iostream>

#include "create_path.h"



int main()
{
    const char* path = "C:\\My Cool Folder\\Administrator\\Application Data\\ComplexSystems\\Delta8\\Settings";

    std::cout << create_path_v1(path) << "\n";
    std::cout << create_path_v2(path) << "\n";
    std::cout << create_path_v3(path) << "\n";

    return 0;
}

