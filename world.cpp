#include "global.h"
#include <stdio.h>
#include <curses.h>
#include <stdlib.h>
#include <cstdlib>
#include <thread>

using namespace std::chrono;
using namespace std::this_thread;
using namespace std::chrono_literals; // ns, us, ms, s, h, etc.
using std::chrono::system_clock;

int displayItem(int *shouldUpdatePosition, int *active, int *value, int *touched){
    int itemsForLooping[10] = {0, 3, 1, 4, 2, 5, 8, 9, 6, 7};
    int x = 0;

    *active = 1;

    while(true){
        if(*touched == 1){
            break;
        }
        if(*shouldUpdatePosition == 1){
            break;
        }
        *value = itemsForLooping[x];
        if(x == 10){
            x = 0;
            continue;
        }
        sleep_for(50ms);
        x++;
    }

    return 0;
}

void renderWorld(Item *ranItems, int spawnNum, int personPosY, int personPosX, int *shouldUpdatePosition, int *points, int *level){
    clear();

    for(int y = 0; y < SCREEN_SZ_Y; y++){
        for(int x = 0; x < SCREEN_SZ_X; x++){
            int itemLanded = 0;

            for(int ranItemI = 0; ranItemI < spawnNum; ranItemI++){
                if(y == ranItems[ranItemI].posY && x == ranItems[ranItemI].posX){
                    itemLanded = 1;
                    if((x != personPosX || y != personPosY)){
                        if(ranItems[ranItemI].active == 0){
                            std::thread t1(displayItem, shouldUpdatePosition, &ranItems[ranItemI].active, &ranItems[ranItemI].value, &ranItems[ranItemI].touched);
                            t1.detach();
                        }
                        char val[3];
                        sprintf(val, "%d", ranItems[ranItemI].value);
                        mvaddstr(y, x, val);
                    }

                    break;
                }
            }

            if(itemLanded){
                continue;
            }

            if(x == personPosX && y == personPosY){
                mvaddch(y, x, '+');
                continue;
            }

            mvaddch(y, x, '#');
        }
    }

    // Draw shield on player
    if((personPosY+1) < SCREEN_SZ_Y){
        mvaddch(personPosY+1, personPosX, ' ');
        for(int ranItemI = 0; ranItemI < spawnNum; ranItemI++){
            if(ranItems[ranItemI].posY == personPosY+1 && ranItems[ranItemI].posX == personPosX){
                if(ranItems[ranItemI].touched != 1){
                    ranItems[ranItemI].touched = 1;
                    *points = *points + ranItems[ranItemI].value;
                }
            }
        }
    }
    if((personPosY-1) > 0){
        mvaddch(personPosY-1, personPosX, ' ');
        for(int ranItemI = 0; ranItemI < spawnNum; ranItemI++){
            if(ranItems[ranItemI].posY == personPosY-1 && ranItems[ranItemI].posX == personPosX){
                if(ranItems[ranItemI].touched != 1){
                    ranItems[ranItemI].touched = 1;
                    *points = *points + ranItems[ranItemI].value;
                }
            }
        }
    }
    if((personPosX+1) < SCREEN_SZ_X){
        mvaddch(personPosY, personPosX+1, ' ');
        for(int ranItemI = 0; ranItemI < spawnNum; ranItemI++){
            if(ranItems[ranItemI].posX == personPosX+1 && ranItems[ranItemI].posY == personPosY){
                if(ranItems[ranItemI].touched != 1){
                    ranItems[ranItemI].touched = 1;
                    *points = *points + ranItems[ranItemI].value;
                }
            }
        }
    }
    if((personPosX-1) > 0){
        mvaddch(personPosY, personPosX-1, ' ');
        for(int ranItemI = 0; ranItemI < spawnNum; ranItemI++){
            if(ranItems[ranItemI].posX == personPosX-1 && ranItems[ranItemI].posY == personPosY){
                if(ranItems[ranItemI].touched != 1){
                    ranItems[ranItemI].touched = 1;
                    *points = *points + ranItems[ranItemI].value;
                }
            }
        }
    }

    // Draw screen dash
    char sPoints[4];

    sprintf(sPoints, "%d", *points);
    sprintf(sPoints, "%d", *points);

    mvaddstr(25, 0, "Points:");
    mvaddstr(25, 8, sPoints);

    mvaddstr(26, 0, "Level:");
    mvaddch(26, 8, *level+'0');

    mvaddstr(30, 0, "Press 'q' to quit");
    sleep_for(90ms);
    refresh();
}
