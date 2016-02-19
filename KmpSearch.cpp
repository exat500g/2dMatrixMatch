#include "KmpSearch.h"
#include <iostream>
#include <cstdlib>

KmpSearch::KmpSearch()
{
    pattern=0;
    nextTable=0;
    patternSize=0;
}
KmpSearch::~KmpSearch(){
    if(patternSize){
        delete pattern;
        delete nextTable;
    }
}

void KmpSearch::generateNextTable(){
    nextTable[0]=-1;
    int32_t j=0;
    for(int32_t i=1;i<patternSize;i++){
        nextTable[i]=j;
        if(pattern[i]==pattern[j]){
            j++;
        }else{
            j=0;
        }
    }
    /*std::cout<<"nextTable=";
    for(int i=0;i<patternSize;i++){
        std::cout<<nextTable[i]<<" ";
    }*/
}

void KmpSearch::setPattern(const uint8_t *_pattern, int32_t size){
    if(patternSize){
        delete pattern;
        delete nextTable;
    }
    pattern = new uint8_t[size];
    nextTable = new int32_t[size];
    memcpy(pattern,_pattern,size);
    patternSize=size;
    generateNextTable();
}

void KmpSearch::search(const uint8_t *data, uint64_t dataSize){
    if(patternSize==0){
        return;
    }
    uint64_t i = 0;
    int32_t j = 0;
    while (i < dataSize){
        //std::cout<<"search data["<<i<<"]="<<data[i]<<" patt["<<j<<"]="<<pattern[j]<<"\r\n";
        if (j==-1 || data[i] == pattern[j]){
            i++;
            j++;
            if (j == patternSize){
                bool continu=matched(data,i-j);
                if(continu==false){
                    return;
                }
                j = nextTable[patternSize-1];
            }
        }else{
            j = nextTable[j];
        }
    }
}

bool KmpSearch::matched(const uint8_t *data, uint64_t position){
    std::cout<<"KmpSearch::matched():data[p]="<<data[position]<<" position="<<position<<"\r\n";
    return true;
}






static const uint8_t context[]={"show me the money show me the money show me the money"};
static const uint8_t pattern[]={"show"};

int __attribute__((weak)) main()
{
    std::cout << "\r\n --------start of KmpSearch demo-----------\r\n";
    KmpSearch k1;
    k1.setPattern(pattern,sizeof(pattern)-1);
    k1.search(context,sizeof(context)-1);
    std::cout << "\r\n --------end of KmpSearch demo-----------\r\n";

    return 0;
}
