#pragma once
#include <iostream>
#include <array>
#include <memory>
#include <bit>

namespace
{
    bool is_big_endian(void)
    {
        if constexpr (std::endian::native == std::endian::big)
        {
        return true;
        }
        else if constexpr (std::endian::native == std::endian::little)
        {
        return false;
        }
    }
}

union HeaderFields
{
    struct
    {
    } centralDirectoryFileHeaderSignature;
};

struct ZipHeader
{
    ZipHeader(std::unique_ptr<char *> data);

protected:
    uint32_t centralDirectorFileHeaderSignature : 32;
    uint16_t compressVersion : 16;
    uint16_t extractVersion : 16;
    uint16_t generalPurposeBitFlag : 16;
    uint16_t compressionMethod : 16;
    uint16_t lastModifiedTime : 16;
    uint16_t lastModifiedDate : 16;
    uint32_t CRCC32OfUnCompressed : 32;
    uint32_t compressedSize : 32;
    uint32_t uncompressedSize : 32;
    uint16_t fileNameLenght : 16;
    uint16_t extraFieldLenght : 16;
    uint16_t fileCommentLength : 16;
    uint16_t diskNumberStartOfFIles : 16;
    uint16_t internalFileAttributes : 16;
    uint32_t externalFileAttributes : 32;
    uint32_t relativeOffsetOfLocalFileHeader : 32;
    std::string fileName = "";
    std::string extraField = "";
    std::string fileComments = "";

    // friend std::ostream &operator<<(std::ostream &os, const ZipHeader &dt);
private:
    std::unique_ptr<char *> _data;
};