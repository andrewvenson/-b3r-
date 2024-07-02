#include "global.h"
#include <cstdlib>
#include <thread>
#include <chrono>

int itemSpawn(Item *ranItems, int spawnNum, int *shouldUpdatePosition, int *level, int *pLoop){
    using namespace std::chrono;

    time_point<system_clock> start, end;

    while(*pLoop-'0' != 0 && *level <= 5){
        *shouldUpdatePosition = 0;
        for(int x = 0; x < spawnNum; x++){
            int ranX = rand() % SCREEN_SZ_X-1;
            int ranY = rand() % SCREEN_SZ_Y-1;
            ranItems[x].posX = ranX;
            ranItems[x].posY = ranY;
            ranItems[x].active = 0;
            ranItems[x].value = 0;
            ranItems[x].touched = 0;
        }
        start = system_clock::now();
        while(true){
            end = system_clock::now();
            duration<double> elapsed_seconds = end - start;
            if(elapsed_seconds.count() >=10.0){
                break;
            }
        }
        *level = *level + 1;
        *shouldUpdatePosition = 1;
    }
    return 0;
}
