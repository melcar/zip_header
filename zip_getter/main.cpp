// reading an entire binary file
#include "header/zipHeader.h"
#include <iostream>
#include <fstream>
#include <memory>

void printRawFile(const char *data, int size)
{
    if (size > 0)
    {
        std::cout << "\n----------START-----------\n";
        for (int i = 0; i < size; i++)
        {
            std::cout << data[i];
        }
        std::cout << "\n----------END-----------\n";
    }
}

int main()
{
    std::streampos size;
    std::unique_ptr<char *> memblock;

    std::ifstream file("ch5.zip", std::ios::in | std::ios::binary | std::ios::ate);
    if (file.is_open())
    {
        size = file.tellg();
        memblock = std::make_unique<char *>(new char[size]);
        file.seekg(0, std::ios::beg);
        file.read(*memblock, size);
        file.close();

        std::cout << "the entire file content is in memory:\n";
        printRawFile(*memblock, size);
        ZipHeader header{std::move(memblock), size};
    }
    else
    {
        std::cout << "Unable to open file";
    }
    return 0;
}