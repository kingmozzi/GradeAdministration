#pragma once
#include <stdio.h>
#include "strhandler.h"

typedef struct student
{
    unsigned long int sid;
    char name[20];
    int sub1;
    int sub2;
    int sub3;
    float mean;

}STUDENT;

void openGrade(FILE **fp, char* mode);
void closeGrade(FILE **fp);
void createGrade(STUDENT *student);
void writeGrade(STUDENT student, FILE *fp);
void printGrade(FILE *fp);
unsigned long int selectDeleteTarget();
int deleteGrade(FILE *fp, unsigned long int target);
