#include "localFileHeader.h"

#include <stdexcept>
#include <ranges>
#include <byteSize.h>
#include <iostream>
#include <bitset>

LocalFileHeader::LocalFileHeader(char *memory, std::streampos size)
{
    std::streampos offset = 0;
    if (size < minimumByteSize)
    {
        throw std::runtime_error("Zip file not properly formed.");
    }
    setValue(headerSignature, &memory[offset]);
    offset += getOffset(Field::HeaderSignature);

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

std::ostream &operator<<(std::ostream &os, const LocalFileHeader &lfh)

{
    os << "HeaderSignature: " << std::hex << lfh.headerSignature << "\n";
    os << "Version to extract: " << std::dec << lfh.versionToExtract << "\n";
    os << "Bit flags: " << std::bitset<8>{lfh.bitFlags} << "\n";
    os << "Compressed methods: " << lfh.compressedMethods << "\n";
    os << "Last modified time: " << lfh.lastModifiedTime << "\n";
    os << "Last modified date: " << lfh.lastModifiedDate << "\n";
    os << "CRC32: " << std::hex <<lfh.CRC32 << "\n";
    os << "Compressed size: " << std::dec <<lfh.compressedSize << "\n";
    os << "UncompressedSize: " << lfh.uncompressedSize << "\n";
    os << "Name length: " << lfh.nameLength << "\n";
    os << "Extra fields length: " << lfh.extraFieldsLength << "\n";
    return os;
}