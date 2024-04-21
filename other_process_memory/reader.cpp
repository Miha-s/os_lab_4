#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <thread>
#include <chrono>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>

std::string read_str(int fd, long long int memory_address)
{
    std::string result;

    lseek(fd, memory_address, SEEK_SET);
    // std::cout << "errno 1: " <<errno <<std::endl;
    char data;
    int size = read(fd, &data, 1);
    // std::cout << "errno 2: " << errno << std::endl;

    while(data != 0) {
        // std::cout << data << std::endl;
        result.push_back(data);
        read(fd, &data, 1);
    }

    return result;
}

int main()
{
    int pid;
    long long int memory_address;
    std::string memory;
    std::cout << "Enter process id: ";
    std::cin >> pid;
    std::cout << "Enter memory address: ";
    std::cin >> memory;
    std::stringstream ss;
    ss << std::hex << memory;
    ss >> memory_address;

    std::stringstream file_name;
    file_name << "/proc/" << pid << "/mem";

    std::cout << "memory: " << memory_address << std::endl;
    std::cout << file_name.str() << std::endl;

    int fd = open(file_name.str().c_str(), O_RDONLY);
    std::cout << "fd: "<< fd << std::endl;

    // lseek(fd, memory_address, SEEK_SET);
    // std::cout << "errno 1: " <<errno <<std::endl;
    // char data;
    // int size = read(fd, &data, 1);
    // std::cout << "errno 2: " << errno << std::endl;
    // std::cout << data << std::endl;

    std::string prev;
    std::string next;
    while (true)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
        next = read_str(fd, memory_address);
        if(next != prev) {
            std::cout << next << std::endl;
        }

        prev = next;
    }
     
    return 0;    
}