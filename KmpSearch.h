#pragma once

#include <cstdint>

class KmpSearch
{
    uint8_t *pattern;
    int32_t *nextTable;
    int32_t  patternSize;
    void generateNextTable();
public:
    KmpSearch();
    ~KmpSearch();
    void setPattern(const uint8_t *_pattern, int32_t size);
    void search(const uint8_t *data, uint64_t dataSize);
    virtual bool matched(const uint8_t *data,uint64_t position);
};




