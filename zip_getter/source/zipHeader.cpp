#include "zipHeader.h"


ZipHeader::ZipHeader(std::unique_ptr<char*> data): _data(move(data)){

}