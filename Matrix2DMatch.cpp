#include "Matrix2DMatch.h"
#include <iostream>

//--------------HorizonalACAutomation-------------
HorizontalACAutomation::HorizontalACAutomation(Matrix2DMatch *parent):
    ACAutomation()
{
    this->parent=parent;
}

void HorizontalACAutomation::init(uint8_t *pattern,int32_t m){
    for(int32_t i=0;i<m;i++){
        insert(pattern+i*m,m,i);
    }
    build();
}

bool HorizontalACAutomation::matched(uint64_t position, uint32_t id){
    return parent->onHorizontalMatched(position,id);
}
//-------------VerticalKmpSearch-------------------
VerticalKmpSearch::VerticalKmpSearch(Matrix2DMatch *parent){
    this->parent=parent;
    kmp=0;
}
VerticalKmpSearch::~VerticalKmpSearch(){
    if(kmp){
        delete[] kmp;
    }
}
void VerticalKmpSearch::init(uint8_t *matrix,int32_t m){
    if(kmp){
        delete[] kmp;
    }
    this->m=m;
    kmp = new KmpSearch[m];
    uint8_t *pattern = new uint8_t[m];
    for(int32_t i=0;i<m;i++){
        //std::cout<<"kmp::vertical pattern["<<i<<"]=";
        for(int32_t j=0;j<m;j++){
            pattern[j]=matrix[j*m+i];
            //std::cout<<(int)pattern[j];
        }
        //std::cout<<"\r\n";
        kmp[i].setPattern(pattern,m);
    }
    delete[] pattern;
}
bool VerticalKmpSearch::push(uint8_t *data,int32_t n,int32_t row,int32_t col){
    int32_t counter=0;
    for(int32_t i=0;i<m;i++){
        int32_t index=n*row+col+i;
        bool match=kmp[i].push(data[index]);
        //std::cout<<"kmp::push data["<<index<<"]="<<(int)data[index]<<" row="<<row<<" col="<<col<<" i="<<i<<" match="<<match<<"\r\n";
        if(match){
            counter++;
        }
    }
    if(counter==m){
        return true;
    }
    return false;
}
void VerticalKmpSearch::resetIndex(){
    for(int32_t i=0;i<m;i++){
        kmp[i].resetIndex();
    }
}

//--------------Matrix2DMatch-----------------------
Matrix2DMatch::Matrix2DMatch()
{
    data=0;
    n=0;
    pattern=0;
    m=0;
    row=0;
    col=0;
    automation = new HorizontalACAutomation(this);
    kmp = new VerticalKmpSearch(this);
}
Matrix2DMatch::~Matrix2DMatch(){
    delete automation;
    delete kmp;
}
void Matrix2DMatch::init(uint8_t *data,int32_t n,uint8_t *pattern,int32_t m){
    this->data=data;
    this->n=n;
    this->pattern=pattern;
    this->m=m;
    automation->init(pattern,m);
    kmp->init(pattern,m);
}

void Matrix2DMatch::search(){
    for(row=m-1;row<n;row+=m){
        automation->search(data + row*n,n);
    }
}

bool Matrix2DMatch::onHorizontalMatched(int32_t position, uint32_t id){
    col=position;
    std::cout<<"horizonal search find id="<<id<<" @row="<<row<<" col="<<col<<"\r\n";
    kmp->resetIndex();
    for(int32_t i=row-(m-1);i<=row+(m-1) && i<n ; i++){
        bool match=kmp->push(data,n,i,col);
        if(match){
            std::cout<<"vertical search find @row="<<i-(m-1)<<" col="<<col<<"\r\n";
        }
    }
    return true;
}
