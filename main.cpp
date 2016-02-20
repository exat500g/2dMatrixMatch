#include "KmpSearch.h"
#include "ACAutomation.h"
#include "Matrix2DMatch.h"
#include <iostream>
#include <ctime>
#include <cmath>
#include <iomanip>

#define MSIZE 3
#define NSIZE 10

uint8_t data[NSIZE][NSIZE];
uint8_t pattern[MSIZE][MSIZE];
int32_t patternRow,patternCol;

void dataInit(){
    for(int i=0;i<NSIZE;i++){
        for(int j=0;j<NSIZE;j++){
            data[i][j]=rand()%0x100;
        }
    }
    patternRow=rand()%(NSIZE-MSIZE-1);
    patternCol=rand()%(NSIZE-MSIZE-1);
    for(int i=0;i<MSIZE;i++){
        for(int j=0;j<MSIZE;j++){
            pattern[i][j]=data[i+patternRow][j+patternCol];
        }
    }
}

void printData(uint8_t *data,int32_t size){
    for(int i=0;i<size;i++){
        for(int j=0;j<size;j++){
            std::cout<<std::setfill('0')<<std::setw(2)<<std::hex<<(int)*(data+i*size+j)<<" ";
        }
        std::cout<<"\r\n";
    }
}

#if 1

int main(){
    std::cout<<"\r\n-------start of main-------\r\n";
    srand(time(0));
    while(1){
        dataInit();
        std::cout<<"data=\r\n";
        printData((uint8_t*)data,NSIZE);
        std::cout<<"patternPos="<<patternRow<<","<<patternCol<<" pattern=\r\n";
        printData((uint8_t*)pattern,MSIZE);
        std::cout<<"result:\r\n";
        {
            Matrix2DMatch match;
            match.init((uint8_t*)data,NSIZE,(uint8_t*)pattern,MSIZE);
            match.search();
        }
        int cont;
        std::cout<<"continue?0=no,1=yes:";
        std::cin>>cont;
        if(cont==0)break;
    }
    std::cout<<"\r\n-------end of main-------\r\n";
}

#endif
