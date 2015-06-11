#include <iostream>

#include "create_path.h"



int main(int argc, const char *argv[])
{
    const char* path = "C:\\Documents and Settings\\Administrator\\Application Data\\ComplexSystems\\Delta8\\Settings";

    if(!create_path(path)) {
        std::cout << "Done\n";
    }
    else {
        std::cout << "Fail\n";
    }

    return 0;
}

