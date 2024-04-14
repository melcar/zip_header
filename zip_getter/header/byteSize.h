#pragma once
#include <cstdint>
#include <variant>
#include <iostream>

typedef uint8_t oneByte;
typedef uint16_t twoBytes;
typedef uint32_t fourBytes;
typedef uint64_t heightBytes;

// helper function to set field values of header class:
template <class T>
void setValue(T &field, char *value)
{
    field = *((T *)value);
}