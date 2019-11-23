#include "lib.hpp"
#include <iostream>

int main(int argc, const char* argv[])
{
    Program program;
    std::cout << "Hello world " << program.add(1,2) << ".\n";
    return program.add(-10, 10);
}