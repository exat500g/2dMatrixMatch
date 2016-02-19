#include "Matrix2DMatch.h"
#include <iostream>

//--------------HorizonalACAutomation-------------
HorizontalACAutomation::HorizontalACAutomation(Matrix2DMatch *parent){
    this->parent=parent;
}

void HorizontalACAutomation::init(uint8_t *pattern,int32_t n){
    for(int32_t i=0;i<n;i++){
        insert(pattern+i*n,n,i);
    }
    build();
}

bool HorizontalACAutomation::matched(uint8_t *data, uint64_t position, uint32_t id){
    return parent->onHorizontalMatched(data,position,id);
}

//--------------Matrix2DMatch-----------------------
Matrix2DMatch::Matrix2DMatch()
{
    data=0;
    m=0;
    pattern=0;
    n=0;
    automation = new HorizontalACAutomation(this);
    row=0;
    col=0;
}

void Matrix2DMatch::init(uint8_t *data,int32_t m,uint8_t *pattern,int32_t n){
    this->data=data;
    this->m=m;
    this->pattern=pattern;
    this->n=n;
    automation->init(this->pattern,n);
}

void Matrix2DMatch::search(){
    for(row=0;row<m;row+=n){
        automation->search(data + row*m,m);
    }
}

bool Matrix2DMatch::onHorizontalMatched(uint8_t *data, uint64_t position, uint32_t id){
    col=position;
    data=0;
    std::cout<<"horizonal search find id="<<id<<" @row="<<row<<" col="<<col<<"\r\n";
    return true;
}
