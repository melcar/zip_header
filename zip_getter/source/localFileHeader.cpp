#include "localFileHeader.h"

#include <stdexcept>
#include <ranges>
#include <byteSize.h>
#include <iostream>

LocalFileHeader::LocalFileHeader(char *memory, std::streampos size)
{
    std::streampos offset = 0;
    if (size < minimumByteSize)
    {
        throw std::runtime_error("Zip file not properly formed.");
    }
    setValue(headerSignature, &memory[offset]);
    offset += getOffset(Field::HeaderSignature);

    std::cout << std::hex<< headerSignature<<std::endl;
    setValue(versionToExtract, &memory[offset]);
    offset += getOffset(Field::VersionToExtract);

    setValue(bitFlags, &memory[offset]);
    offset += getOffset(Field::BitFlags);

    setValue(compressedMethods, &memory[offset]);
    offset += getOffset(Field::CompressedMethods);

    setValue(lastModifiedTime, &memory[offset]);
    offset += getOffset(Field::LastModifiedTime);

    setValue(lastModifiedDate, &memory[offset]);
    offset += getOffset(Field::LastModifiedDate);

    setValue(CRC32, &memory[offset]);
    offset += getOffset(Field::CRC32);

    setValue(compressedSize, &memory[offset]);
    offset += getOffset(Field::CompressedSize);

    setValue(uncompressedSize, &memory[offset]);
    offset += getOffset(Field::UncompressedSize);

    setValue(nameLength, &memory[offset]);
    offset += getOffset(Field::NameLength);

    setValue(extraFieldsLength, &memory[offset]);
    offset += getOffset(Field::ExtraFieldsLength);
}

void LocalFileHeader::print()
{
    std::cout << "HeaderSignature: " <<std::hex << headerSignature << "\n";
    std::cout << "Version to extract: " << versionToExtract << "\n";
    std::cout << "Bit flags: " << bitFlags << "\n";
    std::cout << "Compressed methods: " << compressedMethods << "\n";
    std::cout << "Last modified time: " << lastModifiedTime << "\n";
    std::cout << "Last modified date: " << lastModifiedDate << "\n";
    std::cout << "CRC32: " << CRC32 << "\n";
    std::cout << "Compressed size: " << compressedSize << "\n";
    std::cout << "UncompressedSize: " << uncompressedSize << "\n";
    std::cout << "Name length: " << nameLength << "\n";
    std::cout << "Extra fields length: " << extraFieldsLength << "\n";
}