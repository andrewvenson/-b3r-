#ifndef GLOBAL_H
#define GLOBAL_H

const int SCREEN_SZ_X = 50;
const int SCREEN_SZ_Y = 25;
const int MAX_SPAWNS = 5;

struct Item {
    int posX;
    int posY;
    int active;
    int value;
    int touched;
};

#endif
