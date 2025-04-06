#include <iostream>
#include <cstdlib>


int main()
{
    const char* value = std::getenv("amapKey");
    std::cout <<value << std::endl;


    return 0;
}