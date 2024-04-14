#pragma once
#include <cstdint>
#include "byteSize.h"
#include <string>
#include <memory>
#include <variant>

struct DataDescriptor
{
    fourBytes signature;
    twoBytes CRC32;
    std::variant<fourBytes, heightBytes> compressedSize;
    std::variant<fourBytes, heightBytes> uncompressedSize;

    DataDescriptor() = delete;

    /*
     @memory has to be at the right place
     */
    DataDescriptor(std::weak_ptr<char *> memory);
};