#include "sort.h"
#define BLOCK_SIZE 2147483648
#define GRADE_TABLE "GradeTable.csv"

//파일 분할
void splitFile()
{
    FILE *fp = fopen(GRADE_TABLE, "r");

    if(fp == NULL){
        printf("file null\n");
        return;
    }

    //분할 크기만큼 동적할당
    char* recordBuffer = (char*)malloc(BLOCK_SIZE);
    int blockCount = 0;

    while(1){
        //지정한 사이즈만큼 버퍼에 씀
        size_t bytesRead = fread(recordBuffer, 1, BLOCK_SIZE, fp);

        if(bytesRead == 0){
            break;
        }

        char tempFileName[1000];
        snprintf(tempFileName, sizeof(tempFileName), "%s_%d", "temp", blockCount);

        FILE *tempFile = fopen(tempFileName, "w");
        if(tempFile == NULL){
            printf("temp file open error");
            return;
        }

        fwrite(recordBuffer, 1, bytesRead, tempFile);
        fclose(tempFile);

        blockCount++;
        
    }
    
    free(recordBuffer);
    fclose(fp);
}

int compareValue(const void* a, const void* b, int category){




}