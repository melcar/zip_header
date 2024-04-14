#include "zipHeader.h"

ZipHeader::ZipHeader(std::unique_ptr<char *> data, std::streampos size) : _data(move(data)), _size(size)
{
    std::streampos offset = 0;
    while (offset < size)
    {
        char *current = &(*_data)[offset];
        switch (getHeaderType(current))
        {
        case HeaderType::LocalHeader:
            _localFileHeaders.push_back({current, size - offset});
            break;
        case HeaderType::DataDescriptor:
            break;
        case HeaderType::CentralDirectory:
            break;
        case HeaderType::EndOfCentralDirectory:
            break;
        case HeaderType::Uknown:
            break;
        }
        offset += 1; // just for now
    }
}

HeaderType ZipHeader::getHeaderType(char *data)
{
    switch (*reinterpret_cast<fourBytes *>(data))
    {
    case LocalHeaderFileSignature:
        std::cout << "localHeader";
        return HeaderType::LocalHeader;
    case DataDescriptorSignature:
        std::cout << "DATADESCRIPTOR";
        return HeaderType::DataDescriptor;
    case CentralDirectorySignature:
        std::cout << "CD";
        return HeaderType::CentralDirectory;
    case EndOfCentralDirectorySignature:
        std::cout << "EOFCD";
        return HeaderType::EndOfCentralDirectory;
    default:
        return HeaderType::Uknown;
    }
}

std::ostream &operator<<(std::ostream &os, const ZipHeader &zh)
{
    for (const auto &lfh : zh._localFileHeaders)
    {
        os << lfh << "\n--------------------------------\n";
    }
    return os;
}