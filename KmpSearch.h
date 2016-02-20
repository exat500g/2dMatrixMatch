#pragma once

#include <cstdint>

class KmpSearch
{
    uint8_t *pattern;
    int32_t *nextTable;
    int32_t  patternSize;
    void generateNextTable();
    int32_t  patternIndex;
public:
    KmpSearch();
    ~KmpSearch();
    void setPattern(const uint8_t *_pattern, int32_t size);
    int32_t searchOnce(const uint8_t *data, int32_t size);
    bool push(uint8_t data);
    void resetIndex();
};




