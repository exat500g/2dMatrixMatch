#include <iostream>
#include <stdint.h>

using namespace std;

#define PATTERN_NUM 24

const uint8_t context[]={"show me the money operation call power overwhelming there is no cow level whosyourdaddy"};
const uint8_t pattern[]={"PARTICIPATE IN PARACHUTE"};

int nextTable[PATTERN_NUM];

void generateKmpNextTable(const uint8_t *data,int32_t *table,int32_t size){
    table[0]=-1;
    int32_t j=0;
    for(int32_t i=1;i<size;i++){
        table[i]=j;
        if(data[i]==data[j]){
            j++;
        }else{
            j=0;
        }
    }
}

int32_t kmpSearch(const uint8_t *context,int32_t contextSize,const uint8_t *pattern,int32_t patternSize,const int32_t *nextTable){
    int32_t i = 0;
    int32_t j = 0;
    while (i < contextSize && j < patternSize){
        if (j==-1 || context[i] == pattern[j]){
            i++;
            j++;
        }else{
            j = nextTable[j];
        }
    }
    if (j == patternSize)
        return i - j;
    else
        return -1;
}

void printArray(int *array,int size){
    for(int i=0;i<size;i++){
        cout<<array[i]<<" ";
    }
}

int main()
{
    generateKmpNextTable(pattern,nextTable,PATTERN_NUM);
    int32_t ret=kmpSearch(context,sizeof(context),pattern,PATTERN_NUM,nextTable);
    printArray(nextTable,PATTERN_NUM);
    cout << "Hello World! ret="<<ret << endl;
    return 0;
}



