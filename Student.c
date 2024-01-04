#include "Student.h"
#define GRADE_TABLE "GradeTable.csv"

//파일 오픈
void openGrade(FILE **fp, char* mode)
{
    *fp = fopen(GRADE_TABLE, mode);

    //파일이 없으면 만들고 파일의 가장 상단에 feature 부여
    if(*fp == NULL){
        *fp = fopen(GRADE_TABLE, "w");
        fputs("sid,name,sub1,sub2,sub3,mean\n", *fp);
        fclose(*fp);
        *fp = fopen(GRADE_TABLE, mode);
    }

    return;
}

//파일 닫기
void closeGrade(FILE **fp)
{   
    if(*fp != NULL){
        fclose(*fp);
        *fp = NULL;
    }
    return;
}

//구조체의 구조(자료)대로 입력받아 구조체에 저장함.
void createGrade(STUDENT *student)
{
    if(student == NULL){
        printf("para error");
        return;
    }

    int state = 0;

    while(state < 4){
        switch(state){
            case 0:
                //name
                printf("what's name?(20 characters or less)\n");
                scanf("%s", student->name);
                printf(student->name);
                break;
            case 1:
                //subject 1
                printf("sub1 point?\n");
                scanf("%d", &student->sub1);
                printf("%d", student->sub1);
                break;
            case 2:
                //subject 2
                printf("sub2 point?\n");
                scanf("%d", &student->sub2);
                printf("%d", student->sub2);
                break;
            case 3:
                //subject 3
                printf("sub3 point?\n");
                scanf("%d", &student->sub3);
                printf("%d", student->sub3);
                break;
            case 4:
                break;
            default:
                printf("createGrade error\n");
                break;
        }
        deleteBuffer();
        //입력한 값이 맞으면 다음 state로
        state+=checkValue();
        printLine();
    }
    //mean
    student->mean = (student->sub1+student->sub2+student->sub3)/3.0;

    printf("name: %s, sub1: %d, sub2: %d, sub3: %d, mean: %f\n", 
            student->name, student->sub1, student->sub2, student->sub3, student->mean);
    return;
}

//입력한 값이 맞는지 확인
int checkValue()
{
    int answer = 0;
    while(1){
        printf(", right? 1.yes 2.no\n");
        scanf("%d", &answer);
        deleteBuffer();
        if(answer==1 || answer ==2){
            break;
        }
    }
    
    if(answer==1){
        return 1;
    }
    
    return 0;
}

//Stduent 구조체를 파일에 씀.
void writeGrade(STUDENT student, FILE *fp)
{
    if(fp == NULL){
        printf("file open error");
        return;
    }

    //sid,name,sub1,sub2,sub3,mean 형태로 formatting
    char buffer[100];
    snprintf(buffer, sizeof(buffer), "%lu,%s,%d,%d,%d,%.2f\n",
                student.sid, student.name, student.sub1, student.sub2, student.sub3, student.mean);

    fputs(buffer, fp);

    return;
}

//테이블 출력
void printGrade(FILE *fp)
{
    if(fp == NULL){
        printf("file open error");
        return;
    }

    char line[100];

    printLine();

    while(1){
        if(fgets(line, sizeof(line), fp) == NULL){
            break;
        }
        printf(line);
    }

    printLine();

    return;
}

//지우고 싶은 sid 입력
unsigned long int selectDeleteTarget()
{
    unsigned long int target;
    while(1){
        printf("input a sid of target to delete\n");
        scanf("%lu", &target);
        deleteBuffer();
        
        printf("%lu", target);
        if(checkValue()){
            break;
        }
    }

    return target;
}

//target id 삭제
//새로운 temp.csv에 target을 제외하고 작성 -> 원본 삭제 -> temp를 원본이름으로 바꿈.
//찾았으면 1을 return해서 레이블 수를 빼줌.
int deleteGrade(FILE *fp, unsigned long int target)
{
    FILE *output = fopen("temp.csv", "w");

    if(fp == NULL || output == NULL){
        printf("file open error");
        return 0;
    }

    char line[100];
    unsigned long int temp = 0;
    //해당 target을 찾았는가에 대한 flag
    int skip = 0;
    
    //feature 줄 제외
    fgets(line, sizeof(line), fp);
    fputs(line, output);

    //한 줄씩 읽어 id추출 후 비교
    while(1){
        if(fgets(line, sizeof(line), fp) == NULL){
            break;
        }
        
        if(skip != 1){
            if(target != getIdFromString(line)){
                fputs(line, output);
            }
            else{
                skip = 1;
            }
        }
        else{
            fputs(line, output);
        }
    }

    fclose(fp);
    fclose(output);

    //원본삭제 -> output을 원본이름으로 바꿔줌.
    if(remove(GRADE_TABLE) == 0){
        if(rename("temp.csv", GRADE_TABLE) == 0){
            printf("deleted sid %lu\n", target);
        }
        else{
            printf("file rename error");
        }
    }
    else{
        printf("file delete erorr");
    }

    return skip;
}