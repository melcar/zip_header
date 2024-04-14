#include "localFileHeader.h"

#include <stdexcept>
#include <ranges>
#include <byteSize.h>
#include <iostream>
#include <bitset>

LocalFileHeader::LocalFileHeader(char *data, std::streampos size)
{
    std::streampos offset = 0;
    if (size < minimumByteSize)
    {
        throw std::runtime_error("Zip file not properly formed.");
    }
    setValue(headerSignature, &data[offset]);
    offset += getOffset(Field::HeaderSignature);

    setValue(versionToExtract, &data[offset]);
    offset += getOffset(Field::VersionToExtract);

    setValue(bitFlags, &data[offset]);
    offset += getOffset(Field::BitFlags);

    setValue(compressedMethods, &data[offset]);
    offset += getOffset(Field::CompressedMethods);

    setValue(lastModifiedTime, &data[offset]);
    offset += getOffset(Field::LastModifiedTime);

    setValue(lastModifiedDate, &data[offset]);
    offset += getOffset(Field::LastModifiedDate);

    setValue(CRC32, &data[offset]);
    offset += getOffset(Field::CRC32);

    setValue(compressedSize, &data[offset]);
    offset += getOffset(Field::CompressedSize);

    setValue(uncompressedSize, &data[offset]);
    offset += getOffset(Field::UncompressedSize);

    setValue(nameLength, &data[offset]);
    offset += getOffset(Field::NameLength);

    setValue(extraFieldsLength, &data[offset]);
    offset += getOffset(Field::ExtraFieldsLength);

    setFileName(data);
    offset += nameLength;

    setExtraFields(data);
    offset += extraFieldsLength;
    setCompressedContent(data);
}

void LocalFileHeader::setFileName(char *data)
{
    const uint16_t offset = minimumByteSize;
    for (uint16_t i = 0; i < nameLength; i++)
    {
        fileName.push_back(data[offset + i]);
    }
}

void LocalFileHeader::setExtraFields(char *data)
{
    const uint16_t offset = minimumByteSize + nameLength;
    for (uint16_t i = 0; i < extraFieldsLength; i++)
    {
        extraFields.push_back(data[offset + i]);
    }
}

void LocalFileHeader::setCompressedContent(char *data)
{
    const uint16_t offset = minimumByteSize + nameLength + extraFieldsLength;
    for (uint16_t i = 0; i < CompressedSize; i++)
    {
        compressedContent.push_back(data[offset + i]);
    }
}

size_t LocalFileHeader::getHeaderSize()
{
    return minimumByteSize + nameLength + extraFieldsLength + compressedSize;
}
std::ostream &operator<<(std::ostream &os, const LocalFileHeader &lfh)

{
    os << "HeaderSignature: " << std::hex << lfh.headerSignature << "\n";
    os << "Version to extract: " << std::dec << lfh.versionToExtract << "\n";
    os << "Bit flags: " << std::bitset<8>{lfh.bitFlags} << "\n";
    os << "Compressed methods: " << lfh.compressedMethods << "\n";
    os << "Last modified time: " << lfh.lastModifiedTime << "\n";
    os << "Last modified date: " << lfh.lastModifiedDate << "\n";
    os << "CRC32: " << std::hex << lfh.CRC32 << "\n";
    os << "Compressed size: " << std::dec << lfh.compressedSize << "\n";
    os << "UncompressedSize: " << lfh.uncompressedSize << "\n";
    os << "Name length: " << lfh.nameLength << "\n";
    os << "Extra fields length: " << lfh.extraFieldsLength << "\n";
    auto addBytesToStream = [&](std::vector<char> chars)
    {
        for (const auto &lchar : chars)
        {
            os << lchar;
        }
        os << "\n";
    };

    os << "File name: ";
    addBytesToStream(lfh.fileName);

    os << "Extra fields: ";
    addBytesToStream(lfh.extraFields);

    os << "compressed Content: ";
    addBytesToStream(lfh.compressedContent);
    return os;
}