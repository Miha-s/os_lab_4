#include <iostream> 
#include <unistd.h> 



int main()
{
    char str[100] = {0};
    std::cout << "pid: " << ::getpid() << std::endl;
    std::cout << "mem: " << &str << std::endl;

    while (std::cin >> str)
    {
        // std::cout << str << std::endl;
    }


    return 0;
}