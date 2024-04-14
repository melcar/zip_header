#pragma once
#include <iostream>
#include <array>
#include <memory>
#include <bit>
#include "byteSize.h"

struct CentralDirectoryFileHeader
{
    CentralDirectoryFileHeader() = delete;
    CentralDirectoryFileHeader(std::unique_ptr<char *> data);

protected:
    fourBytes centralDirectorFileHeaderSignature;
    twoBytes compressVersion;
    twoBytes extractVersion;
    twoBytes generalPurposeBitFlag;
    twoBytes compressionMethod;
    twoBytes lastModifiedTime;
    twoBytes lastModifiedDate;
    fourBytes CRCC32OfUnCompressed;
    fourBytes compressedSize;
    fourBytes uncompressedSize;
    twoBytes fileNameLenght;
    twoBytes extraFieldLenght;
    twoBytes fileCommentLength;
    twoBytes diskNumberStartOfFIles;
    twoBytes internalFileAttributes;
    fourBytes externalFileAttributes;
    fourBytes relativeOffsetOfLocalFileHeader;
    std::string fileName = "";
    std::string extraField = "";
    std::string fileComments = "";

    // friend std::ostream &operator<<(std::ostream &os, const CentralDirectoryFileHeader &dt);
private:
    std::unique_ptr<char *> _data;
};