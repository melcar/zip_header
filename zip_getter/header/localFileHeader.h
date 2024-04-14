#pragma once
#include <cstdint>
#include "byteSize.h"
#include <string>
#include <memory>
#include <numeric>
namespace
{
    constexpr size_t numberOfFields = 11;
    // contains offset for each field we have to read up to fileName
    constexpr std::array<size_t, numberOfFields + 1> offsets{0, 4, 2, 2, 2, 2, 2, 4, 4, 4, 2, 2};
    constexpr int minimumByteSize = std::accumulate(offsets.begin(), offsets.end(), 0);

    typedef enum
    {
        HeaderSignature = 0,
        VersionToExtract = 1,
        BitFlags = 2,
        CompressedMethods = 3,
        LastModifiedTime = 4,
        LastModifiedDate = 5,
        CRC32 = 6,
        CompressedSize = 7,
        UncompressedSize = 8,
        NameLength = 9,
        ExtraFieldsLength = 10
    } Field;

    constexpr std::array<Field, numberOfFields> fields = {HeaderSignature, VersionToExtract, BitFlags, CompressedMethods, LastModifiedTime, LastModifiedDate, CRC32, CompressedSize, UncompressedSize, NameLength, ExtraFieldsLength};

    [[maybe_unused]] size_t getOffset(Field field){
        return offsets[field];
    }
}

struct LocalFileHeader
{
    fourBytes headerSignature;
    twoBytes versionToExtract;
    twoBytes bitFlags;
    twoBytes compressedMethods;
    twoBytes lastModifiedTime;
    twoBytes lastModifiedDate;
    fourBytes CRC32;
    fourBytes compressedSize;
    fourBytes uncompressedSize;
    twoBytes nameLength;
    twoBytes extraFieldsLength;
    std::string fileName;
    std::string extraFields;
    // byte offset
    size_t offset;
    LocalFileHeader() = delete;

    /*
     @memory has to be at the right place
     */
    LocalFileHeader(char *memory, std::streampos size);
    void print();
};