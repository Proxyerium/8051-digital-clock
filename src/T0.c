#include <stc89.h>

extern void timerProcess(void);
extern void sandglassProcess(void);
extern unsigned char timerActive;
extern unsigned char sandglassActive;
unsigned int timerT0C = 0;
unsigned int sandglassT0C = 0;
/* 
OSC@11.088MHz -> 1.082251μs
1.082251*924000 = 999999.924μs
65535-924 = 64611 + offset
there's still +-5ms error.
*/


void initT0(void){
    // set T0 as 16bit Timer
    TMOD |= 0x01;
    // Timer overflow 
    TF0 = 0;
    // Timer Run
    TR0 = 0;
    // Approximately 1000μs per Timer overflow
    TH0 = 64694/256;
    TL0 = 64694%256;
    // Interrupt system
    ET0 = 1;
    PT0 = 0;
}

/// @brief For modes that need to be triggered.
void routineT0(void) __interrupt(1){
    TH0 = 64694/256;
    TL0 = 64694%256;

    if(timerActive){
        timerT0C++; 
        if(timerT0C>=1000){timerT0C = 0; timerProcess();}
    }
    if(sandglassActive){
        sandglassT0C++; 
        if(sandglassT0C>=1000){sandglassT0C = 0; sandglassProcess();}
    }
}
