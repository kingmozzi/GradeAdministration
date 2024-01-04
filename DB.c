#include "DB.h"
#define DB_INFO "DB.csv"

//db.csv에서 정보(마지막 인덱스, 레이블 수)들을 읽어서 db 구조체에 전달하는 함수
//해당 파일이 없으면 초기화
//input data = 마지막index번호(unsinged log int),rable수(unsinged log int)
void getDB(DB *db)
{
    FILE *fp;
    fp = fopen(DB_INFO, "r");
    
    if(fp == NULL){
        //없으면 초기화
        db->IDidx = 0;
        db->rableCount = 0;
    }
    else{
        //있으면 get value
        char c;
        unsigned long int temp = 0;

        while(1){
            c=fgetc(fp);

            if(c==EOF){
                break;
            }
            else if(c==','){
                //comma로 value 구분
                db->IDidx = temp;
                temp = 0;
            }
            else{
                //string to unsinged long int
                temp = temp*10+(c-'0');
            }
        }
        //마지막 value는 comma가 없으므로 대입
        db->rableCount = temp;

        fclose(fp);
    }

    printf("lastIdx: %lu, rable: %lu\n", db->IDidx, db->rableCount);
    return;
}

//현재 DB정보를 DB.csv에 저장
void saveDB(DB db)
{
    FILE *fp;
    fp = fopen(DB_INFO, "w");

    //value,value 형태로 formatting
    char buffer[50];
    snprintf(buffer, sizeof(buffer), "%lu,%lu", db.IDidx, db.rableCount);

    fputs(buffer, fp);

    fclose(fp);
    return;
}