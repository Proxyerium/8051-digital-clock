#include <stc89.h>

extern void beep(unsigned int, unsigned int);
extern void clockProcess(void);
extern void alarmProcess(void);

unsigned int T1C = 0;


void initT1(void){
    // set T1 as 16bit Timer
    TMOD |= 0x10;
    // Timer overflow
    TF1 = 0;
    // Timer Run (always ON)
    TR1 = 1;
    // Approximately 1000μs per Timer overflow
    TH1 = 64670/256;
    TL1 = 64670%256;
    // Interrupt system
    ET1 = 1;
    PT1 = 0;
}

//// @brief For modes that run continuously.
void routineT1(void) __interrupt(3){
    TH1 = 64670/256;
    TL1 = 64670%256;
    T1C++;

    if(T1C>=1000){
        T1C = 0;

        clockProcess();
        
        alarmProcess();
    }

}


