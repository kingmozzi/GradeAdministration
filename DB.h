#pragma once
#include <stdio.h>
#include "strhandler.h"

typedef struct db
{
    unsigned long int IDidx;
    unsigned long int rableCount;
}DB;

void getDB(DB *db);
void saveDB(DB db);