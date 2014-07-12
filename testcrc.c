#include <stdio.h>
#include <string.h>  //memset
#include <stdlib.h>  //malloc
#include <time.h>
#include <sys/time.h>

typedef unsigned int uint32_t, size_t;
typedef unsigned char uint8_t;


#define SIZE_OF_TEST_BUFFER 102*1024
unsigned char myRand()
{
    struct timeval seed;
    gettimeofday(&seed, NULL);
    srand(seed.tv_usec); 
    return rand();
}


/*
* TODO
* ====
* get more precious seed for rand (usecs)
*
*/

int main(int argc, char *argv[])
{
    unsigned int i, j, t1=0, t2=0, uiRes=0;
    unsigned char *pucBuf = NULL;
    struct timeval time1, time2;
    int c1, c2;
    pucBuf = malloc(SIZE_OF_TEST_BUFFER);
    memset(pucBuf, 0, sizeof(pucBuf));   
    
    for( i=0 ;i<SIZE_OF_TEST_BUFFER; i++)
	pucBuf[i] = myRand(); 

//view buffer
//    for( i=0; i<SIZE_OF_TEST_BUFFER; i++)
//	printf("%x", pucBuf++);
//    printf("\n");

for(j=0; j<5; j++)
{
    for( i=0 ;i<SIZE_OF_TEST_BUFFER; i++)
	pucBuf[i] = myRand(); 
    
    printf("**clock():%d\n", clock());

    gettimeofday(&time1, NULL);
    printf("time1.tv_usec %d\n", time1.tv_usec);
    c1 = clock();
    uiRes = crc32(0, pucBuf, sizeof(pucBuf));
    c2 = clock();
    gettimeofday(&time2, NULL);
    printf("time2.tv_usec %d %d\n", time2.tv_usec, c2-c1);
    printf("CRC(BUFFER)\t=%08x\t Total Time[us]:%u\n", uiRes, (time2.tv_usec - time1.tv_usec));
    memset(&time1, 0, sizeof(time1));   
    memset(&time2, 0, sizeof(time2));   

    printf("**clock():%d\n", clock());

    gettimeofday(&time1, NULL);
    printf("time1.tv_usec %d %d\n", time1.tv_usec, c2-c1);
    c1 = clock();
    uiRes = adler(pucBuf, sizeof(pucBuf));
    c2 = clock();
    gettimeofday(&time2, NULL);
    printf("time2.tv_usec %d\n", time2.tv_usec);
    printf("Adler(BUFFER)\t=%08x\t Total Time[us]:%u\n", adler(pucBuf, sizeof(pucBuf)), (time2.tv_usec - time1.tv_usec));
    memset(&time1, 0, sizeof(time1));   
    memset(&time2, 0, sizeof(time2));   
}
    free(pucBuf);
    return 0;
}

