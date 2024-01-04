//satreci assignment - Grade Administration program
//Name: Kim Jaehee Email: kingmozzi_@naver.com
#include <stdio.h>
#include "Student.h"
#include "DB.h"
#include "strhandler.h"
#include "sort.h"

int main(int argc, char **argv)
{
    int op=0;
    char c;
    STUDENT temp = {0,};

    FILE *fp;

    DB db = {0, 0};
    //마지막인덱스, 레이블 수 불러오기 
    getDB(&db);

    //grade table 체크
    openGrade(&fp, "r");
    closeGrade(&fp);
    
    while(op!=4){
        printf("What do you want? 1.input 2.delete 3.output 4.exit\n");
        printLine();
        scanf("%d", &op);

        deleteBuffer();

        switch(op){
            case 1:
                printf("input\n");
                //인덱스(id)와 레이블 수를 증가시킴
                temp.sid = db.IDidx++;
                db.rableCount++;
                //데이터 생성
                createGrade(&temp);
                //데이터 파일에 쓰기
                openGrade(&fp, "a");
                writeGrade(temp, fp);
                closeGrade(&fp);
                break;
            case 2:
                printf("delete\n");
                //데이터 삭제 하기
                openGrade(&fp, "r");
                //찾았으면 1을 return해서 레이블 수를 하나 빼줌.
                db.rableCount-=deleteGrade(fp, selectDeleteTarget());
                closeGrade(&fp);
                break;
            case 3:
                printf("output\n");
                //데이터 출력 하기
                openGrade(&fp, "r");
                printGrade(fp);
                closeGrade(&fp);
                break;
            case 4:
                printf("exit\n");
                break;
            default:
                printf("wrong input\n");
                break;
        }
    }
    splitFile();

    closeGrade(&fp);
    saveDB(db);
    return 0;
}