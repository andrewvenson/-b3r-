#include "global.h"
#include "world.h"
#include "move.h"
#include "item.h"
#include <thread>
#include <stdio.h>
#include <stdlib.h>
#include <curses.h>

class Person {
    public:
        int posX;
        int posY;
        int points;

        Person(int personPosX = 0, int personPosY = 0, int personPoints = 0){
            posX = personPosX;
            posY = personPosY;
            points = personPoints;
        }
};

int spawnThread(Item *ranItems, int *pShouldUpdatePos, int *pLevel, int *pLoop){
    std::thread t2(itemSpawn, ranItems, 5, pShouldUpdatePos, pLevel, pLoop);
    t2.detach();
    return 0;
}

void reset(int *pShouldUpdatePos, int *posX, int *posY, int *pLevel, int *pPoints, int *pLoop){
    *pShouldUpdatePos = 0;
    *posX = 0;
    *posY = 0;
    *pLevel = 1;
    *pPoints = 0;
    *pLoop = 1;
}


int main(){
    initscr();
    noecho();

    Person player;

    int loop = 1;
    int level = 1;
    int shouldUpdatePos = 0;
    char action;

    int *posX = &player.posX;
    int *posY = &player.posY;
    int *pPoints = &player.points;
    int *pLoop = &loop;
    int *pLevel = &level;
    int *pShouldUpdatePos = &shouldUpdatePos;
    char *pAction = &action;

    struct Item ranItems[5];

    while(*pLoop != 0){
        spawnThread(ranItems, pShouldUpdatePos, pLevel, pLoop);

        std::thread t1(getPlayerAction, posX, posY, pLoop, pLevel, pAction);

        while(*pLoop != 0 && *pLevel <= 5){
            renderWorld(ranItems, 5, player.posY, player.posX, pShouldUpdatePos, pPoints, pLevel);
        }

        *pLoop = 0;

        clear();

        char strPoints[3];
        sprintf(strPoints, "%d", *pPoints);

        mvaddstr(0,0,"Great job! You got: ");
        mvaddstr(0,22, strPoints);
        mvaddstr(0,26, "Points!");
        mvaddstr(1,0,"Would you like to play again?");

        refresh();

        t1.join();

        if(*pLevel < 5){
            char playAgain = getch();
            if(playAgain == 'q'){
                break;
            }
            reset(pShouldUpdatePos, posX, posY, pLevel, pPoints, pLoop);
            continue;
        }

        if(*pAction == 'q'){
            break;
        }

        reset(pShouldUpdatePos, posX, posY, pLevel, pPoints, pLoop);
    }

    endwin();
    return 0;
}
