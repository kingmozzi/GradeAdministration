#include "strhandler.h"

//입력버퍼 비우기
void deleteBuffer()
{
    while(getchar()!='\n');

    return;
}

void printLine()
{
    printf("-------------------------------------------------------------------------\n");

    return;
}

//문자열에서 id 추출
//sid,name ..... 에서 첫번째 쉼표가 나올때까지가 sid임.
unsigned long int getIdFromString(const char* str)
{
    char c;
    int idx=0;
    unsigned long int id=0;

    while(1){
        c = str[idx++];
        if(c == ','){
            break;
        }
        id=id*10+(c-'0');
    }

    return id;
}