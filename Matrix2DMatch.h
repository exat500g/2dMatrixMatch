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
    virtual bool matched(uint8_t *data, uint64_t position, uint32_t id) override;
};

class Matrix2DMatch:protected ACAutomation
{
    uint8_t *pattern;   //size=n*n
    uint8_t *data;      //size=m*m
    int32_t m,n;
    HorizontalACAutomation *automation;
    int32_t row,col;
public:
    Matrix2DMatch();
    void init(uint8_t *data,int32_t m,uint8_t *pattern,int32_t n);
    void search();
    bool onHorizontalMatched(uint8_t *data, uint64_t position, uint32_t id);
};




