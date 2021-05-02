#include <stdio.h>
#include <malloc.h>
#include <string.h>

typedef struct _LFSR_INFO
{
    int* polynomial;
    int polyLen;
    int* status;
    int startInd;
    int m;
    int outLen;
} LFSR_INFO_T;

typedef struct _OUT_INFO
{
    int bitOfInd;
    int noDupLen;
    int min;
    int max;
} OUT_INFO_T;

typedef struct _LFSR_OUT
{
    int* bits;
    int* status;
    int* startInd;
} LFSR_OUT_T;


void randBitsGen(LFSR_INFO_T lfsrInfo, LFSR_OUT_T out)
{
    int startInd;
    int endInd;
    int inBit;

    startInd = lfsrInfo.startInd;
    
    for(int q = 0; q < lfsrInfo.outLen; q++)
    {
        inBit = 0;
        for(int p = 0; p < lfsrInfo.polyLen; p++)
        {
            inBit += *(lfsrInfo.status + (*(lfsrInfo.polynomial + p) + startInd)%lfsrInfo.m);
        }
        endInd = (startInd + (lfsrInfo.m-1)) % lfsrInfo.m;
        *(out.bits + q) = *(lfsrInfo.status + endInd);

        startInd = endInd;
        *(lfsrInfo.status + startInd) = inBit%2;
    }
    memcpy(out.status, lfsrInfo.status, lfsrInfo.m * sizeof(int));
    *(out.startInd) = startInd;
}

int main()
{
    LFSR_INFO_T lfsrInfo;
    int inits[3] = {1, 0, 0};
    int polyn[2] = {0, 2};
    lfsrInfo.status = inits;
    lfsrInfo.polynomial = polyn;
    lfsrInfo.polyLen = 2;
    lfsrInfo.startInd = 0;
    lfsrInfo.m = 3;
    lfsrInfo.outLen = 15;

    LFSR_OUT_T out;
    out.bits = (int *)malloc(sizeof(int)*lfsrInfo.outLen);
    int statusBuf[3] = {0};
    out.status = statusBuf;
    int stIndBuf = 0;
    out.startInd = &stIndBuf;

    randBitsGen(lfsrInfo, out);
    
    for(int i=0;i<lfsrInfo.outLen; i++)
        printf("%d: %d\n", i, *(out.bits+i));
    printf("------\n");
    for(int i=0;i<lfsrInfo.m; i++)
        printf("%d: %d\n", i, *(out.status+i));
    printf("------\n");
    printf("startInd: %d\n", *(out.startInd));
    printf("------\n");


    lfsrInfo.startInd = *(out.startInd);
    lfsrInfo.status = out.status;
    randBitsGen(lfsrInfo, out);
    for(int i=0;i<lfsrInfo.outLen; i++)
        printf("%d: %d\n", i, *(out.bits+i));
    return 0;    
}