#pragma once
#include <vector>
#include <iostream>
#include <array>
#include <memory>
#include <bit>

#include "byteSize.h"
#include "localFileHeader.h"
#include "endOfCentralDirectory.h"
#include "centralDirectoryFileHeader.h"
#include "dataDescriptor.h"

namespace
{
    [[maybe_unused]] bool is_big_endian(void)
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

    constexpr fourBytes LocalHeaderFileSignature = 0x04034b50;
    constexpr fourBytes DataDescriptorSignature = 0x08074b50;
    constexpr fourBytes CentralDirectorySignature = 0x02014b50;
    constexpr fourBytes EndOfCentralDirectorySignature = 0x06054b50;
    typedef enum
    {
        LocalHeader = 0,
        DataDescriptor = 1,
        CentralDirectory = 2,
        EndOfCentralDirectory = 3,
        Uknown = 4
    } HeaderType;

}

struct ZipHeader
{
    ZipHeader() = delete;
    ZipHeader(std::unique_ptr<char *> data, std::streampos size);

    friend std::ostream &operator<<(std::ostream &os, const ZipHeader &zh);

private:
protected:
    // friend std::ostream &operator<<(std::ostream &os, const ZipHeader &dt);
private:
    static HeaderType getHeaderType(char *data);
    std::unique_ptr<char *> _data;
    std::streampos _size;
    std::vector<LocalFileHeader> _localFileHeaders;
    // EndOfCentralDirectoryRecord endOfCentralDirectoryRecord;
    // CentralDirectoryFileHeader centralDirectoryFileHeader;
};