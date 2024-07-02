#include<cstdio>
#include <curses.h>

int getPlayerAction(int *posX, int *posY, int *loop, int *level, char *action){

    while(*loop != 0 && *level <= 5){
        *action = getch();

        switch(*action){
            case 'l': // move right
                *posX = *posX+1;
                break;
            case 'j': // move left
                *posX = *posX-1;
                break;
            case 'i': // move up
                *posY = *posY-1;
                break;
            case 'k': // move down
                *posY = *posY+1;
                break;
            case 'q': // quit
                *loop = 0;
                break;
            default:
                printf("");
        }
        if(*loop == 0){
            break;
        }
    }

    return 0;
}
