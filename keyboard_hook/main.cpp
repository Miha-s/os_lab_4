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
#include <errno.h>
#include <linux/input.h>


int main() {
    const auto path = "/dev/input/mice";

    int fd = open(path, O_RDONLY);
    std::cout << "fd: "<< fd << std::endl;
    int left, right, middle;
    while (true)
    {
        unsigned char data[3];
        data[0] = 0;
        data[1] = 0;
        data[2] = 0;

        int size = read(fd, &data, sizeof(data));
        if(size == -1) {
            std::cout << "Errno: " << errno << std::endl;
        } else {
            signed char x = data[1];
            signed char y = data[2];
            left = data[0] & 0x1;
            right = data[0] & 0x2;
            middle = data[0] & 0x4;
            printf("x=%d, y=%d, left=%d, middle=%d, right=%d\n", x, y, left, middle, right);
        }
        
    }
    

    return 0;
}