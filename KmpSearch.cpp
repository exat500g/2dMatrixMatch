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

int32_t KmpSearch::searchOnce(const uint8_t *data, int32_t size){
    int32_t i = 0;
    int32_t j = 0;
    while (i < size){
        if (j==-1 || data[i] == pattern[j]){
            i++;
            j++;
            if (j == patternSize){
                return i-j;
            }
        }else{
            j = nextTable[j];
        }
    }
    return -1;
}

bool KmpSearch::push(uint8_t data){
    bool found=false;
    while (1){
        if (patternIndex==-1 || data == pattern[patternIndex]){
            patternIndex++;
            if (patternIndex == patternSize){
                found=true;
                patternIndex = nextTable[patternSize-1];
            }
            break;
        }else{
            patternIndex = nextTable[patternIndex];
        }
    }
    return found;
}

void KmpSearch::resetIndex(){
    patternIndex=0;
}

#if 1

static const uint8_t context[]={"thereisnocowlevelgreedisgoodwhosyourdaddyshowmethemoneyshowmethemoney"};
static const uint8_t pattern[]={"show"};

int __attribute__((weak)) main()
{
    std::cout << "\r\n--------KmpSearch demo 1-----------\r\n";
    KmpSearch k1;
    k1.setPattern(pattern,sizeof(pattern)-1);
    int32_t pos=k1.searchOnce(context,sizeof(context)-1);
    if(pos>=0){
        std::cout<<"pos="<<pos<<" context[pos]="<<context[pos]<<"\r\n";
    }else{
        std::cout<<"not found\r\n";
    }
    std::cout << "--------KmpSearch demo 2-----------\r\n";
    k1.resetIndex();
    for(uint32_t i=0;i<sizeof(context)-1;i++){
        bool found=k1.push(context[i]);
        if(found){
            uint32_t index=i-(sizeof(pattern)-2);
            std::cout<<"pos="<<index<<" context[pos]="<<context[index]<<"\r\n";
        }
    }
    std::cout << "--------KmpSearch demo 3-----------\r\n";
    k1.resetIndex();
    for(uint32_t i=0;i<sizeof(context)-1;i++){
        bool found=k1.push(context[i]);
        if(found){
            uint32_t index=i-(sizeof(pattern)-2);
            std::cout<<"pos="<<index<<" context[pos]="<<context[index]<<"\r\n";
        }
    }
    std::cout << "--------end of KmpSearch demo-----------\r\n";

    return 0;
}

#endif

