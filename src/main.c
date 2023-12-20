#include <stc89.h>
#include "../hdr/modules.h"
#include "../hdr/Timer.h"
#include "../hdr/features.h"

extern unsigned char isHold;


void main(void){
    // Initialization
    TMOD = 0x00;
    EA = 1;
    initT0();
    initT1();
    beep(100, 2500);
    delay(50);
    beep(100, 2500);

    // Main Loop    
    while(1){
        // root level
        nixie(1, 0x39);
        nixie(2, 12);
        nixie(3, 12);
        nixie(4, 12);
        nixie(5, 12);
        nixie(6, 12);
        nixie(7, 12);
        nixie(8, 0x0f);

        switch(key()){
            // K1 -> Clock Mode | Date Mode
            case 1:
                beep(100, 2000);
                isHold ? date() : clock();
                break;
            // K2 -> Alarm Mode
            case 2:
                beep(100, 2000);
                alarm();
                break;
            // K3 -> Timer Mode
            case 3:    
                beep(100, 2000);
                timer();
                break;
            // K4 -> Sandglass Mode
            case 4:
                beep(100, 2000);
                sandglass();
                break;
        }
    }
    // END Main Loop
}
