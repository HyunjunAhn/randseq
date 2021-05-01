#include <stdio.h>

typedef struct _LFSR_INFO
{
    int* polynomial;
    int polyLen;
    int* initState;
    int m;
} LFSR_INFO_T;

typedef struct _OUT_INFO
{
    int bitOfInd;
    int noDupLen;
    int min;
    int max;
} OUT_INFO_T;


void randSeqGen(LFSR_INFO_T lfsrInfo, OUT_INFO_T outInfo, int* out)
{
    int startInd;
    int endInd;
    int inBit;
    int outBit;

    startInd = 0;
    endInd = (lfsrInfo.m-1);
    
    for(int q = 0; q < outInfo.bitOfInd; q++)
    {
        inBit = 0;
        for(int p = 0; p < lfsrInfo.polyLen; p++)
        {
            inBit += *(lfsrInfo.initState + (*(lfsrInfo.polynomial + p) + startInd)%lfsrInfo.m);
        }
        outBit = *(lfsrInfo.initState + endInd);

        startInd = endInd;
        *(lfsrInfo.initState + startInd) = inBit%2;
            
        if(endInd > 0)
        {
            endInd--;
        }
        else{
            endInd = (lfsrInfo.m-1);
        }
        printf("%d: %d\n", q, outBit);
    }
}

int main()
{
    LFSR_INFO_T lfsrInfo;
    int inits[3] = {1, 0, 0};
    int polyn[2] = {0, 2};
    lfsrInfo.initState = inits;
    lfsrInfo.polynomial = polyn;
    lfsrInfo.polyLen = 2;
    lfsrInfo.m = 3;
    OUT_INFO_T outInfo;
    outInfo.bitOfInd = 20;
    int out;
    randSeqGen(lfsrInfo, outInfo, &out);
    return 0;    
}