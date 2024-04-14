#pragma once
#include <cstdint>
#include "byteSize.h"
#include <string>
#include <memory>
#include <variant>
constexpr fourBytes signatyre = 0x06054b50;
struct EndOfCentralDirectoryRecord
{
    fourBytes signature;
    twoBytes numberOfThisDisck;
    twoBytes DiskWhereCentralDirectoryStarts;
    twoBytes numberOfCentralDirectoryRecordsOnThisDesk;
    twoBytes TotalNumberOfCentralDirectoryRecords;
    fourBytes sizeOfCentralDirectoryRecord;
    fourBytes OffsetOfStartOfCentralDirectory;
    twoBytes commentLength;
    std::string comment;

    EndOfCentralDirectoryRecord() = delete;

    /*
     @memory has to be at the right place
     */
    EndOfCentralDirectoryRecord(std::weak_ptr<char *> memory);
};