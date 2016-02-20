#pragma once
#include "ACAutomation.h"
#include "KmpSearch.h"


class Matrix2DMatch;
class HorizontalACAutomation:public ACAutomation
{
    Matrix2DMatch *parent;
public:
    HorizontalACAutomation(Matrix2DMatch *parent);
    void init(uint8_t *pattern,int32_t n);
    virtual bool matched(uint64_t position, uint32_t id) override;
};

class VerticalKmpSearch
{
    Matrix2DMatch *parent;
    KmpSearch *kmp;
    int32_t m;
public:
    VerticalKmpSearch(Matrix2DMatch *parent);
    ~VerticalKmpSearch();
    void init(uint8_t *matrix,int32_t m);
    bool push(uint8_t *data,int32_t n,int32_t row,int32_t col);
    void resetIndex();
};

class Matrix2DMatch:protected ACAutomation
{
    uint8_t *pattern;   //size=m*m
    uint8_t *data;      //size=n*n
    int32_t m,n;
    HorizontalACAutomation *automation;
    VerticalKmpSearch *kmp;
    int32_t row,col;
public:
    Matrix2DMatch();
    ~Matrix2DMatch();
    void init(uint8_t *data, int32_t n, uint8_t *pattern, int32_t m);
    void search();
    bool onHorizontalMatched(int32_t position, uint32_t id);
};




