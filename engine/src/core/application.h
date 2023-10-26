#pragma once

#include "defines.h"

struct game;

typedef struct applicationConfic {

    int16 statPosX;
    int16 statPosY;
    int16 statWidth;
    int16 statHeight;
    char* name;

} applicationConfic;

GLUTTONY_API bool8 applicationCreate(struct game* gameInst);
GLUTTONY_API bool8 applicationRun();