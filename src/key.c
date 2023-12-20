#include <stc89.h>
#include "../hdr/modules.h"

unsigned char isHold = 0;


/// @brief Detect which button was pressed.
unsigned char key(void){
    unsigned char keyNum = 0;
    // K1
    if(P3_1==0){
        delay(20);
        while(P3_1==0){
            // 500ms to hold
            isHold = 0;
            unsigned char holding = 0;
            while(P3_1==0){
                delay(5);
                holding++;
            }
            if(holding>=100){
                isHold = 1;
            }
        }
        delay(20);
        keyNum = 1;
    }
    // K2
    if(P3_0==0){
        delay(20);
        while(P3_0==0){

    };
        delay(20);
        keyNum = 2;
    }
    // K3
    if(P3_2==0){
        delay(20);
        while(P3_2==0){

    };
        delay(20);
        keyNum = 3;
    }
    // K4
    if(P3_3==0){
        delay(20);
        while(P3_3==0){

    };
        delay(20);
        keyNum = 4;
    }

    return keyNum;
}
