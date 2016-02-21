#include "KmpSearch.h"
#include "ACAutomation.h"
#include "Matrix2DMatch.h"
#include <iostream>
#include <ctime>
#include <cmath>
#include <iomanip>
#include <ctime>

#include <sys/time.h>

#define MSIZE 50
#define NSIZE 1000

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
int64_t getTimestamp(){
    timeval linuxTime;
    gettimeofday(&linuxTime,0);
    int64_t ts=linuxTime.tv_sec*1000000 + linuxTime.tv_usec;
    return ts;
}
#if 1
static int64_t startTime=0;
static int64_t endTime=0;

int main(){
    std::cout<<"\r\n-------start of main-------\r\n";
    srand(time(0));
    while(1){
        dataInit();
        std::cout<<"data=\r\n";
        //printData((uint8_t*)data,NSIZE);
        std::cout<<"patternPos="<<patternRow<<","<<patternCol<<" pattern=\r\n";
        //printData((uint8_t*)pattern,MSIZE);
        std::cout<<"result:\r\n";
        {
            startTime=getTimestamp();
            Matrix2DMatch match;
            match.init((uint8_t*)data,NSIZE,(uint8_t*)pattern,MSIZE);
            match.search();
            endTime=getTimestamp();
            int64_t deltaTime=endTime-startTime;
            std::cout<<"cost time (us)="<<deltaTime<<"\r\n";
        }
        int cont;
        std::cout<<"continue?0=no,1=yes:";
        std::cin>>cont;
        if(cont==0)break;
    }
    std::cout<<"\r\n-------end of main-------\r\n";
}

#endif
