#include <stc89.h>

extern void beep(unsigned int, unsigned int);
extern void delay(unsigned int);
extern unsigned char key(void);
extern void nixie(unsigned char, unsigned char);
extern void dateProcess(void);
void clockSetting(void);

extern unsigned char isHold;
extern unsigned char dateD2;
unsigned char clockFormat = 0;
unsigned char clockSelect = 0;
unsigned char clockH1 = 0;
unsigned char clockH2 = 5;
unsigned char clockM1 = 0;
unsigned char clockM2 = 0;
unsigned char clockS1 = 0;
unsigned char clockS2 = 0;
unsigned char clockH1Mem;
unsigned char clockH2Mem;
unsigned char clockM1Mem;
unsigned char clockM2Mem;
unsigned char clockS1Mem;
unsigned char clockS2Mem;


/// @brief <Clock Mode> display current time.
void clock(void){
    while(1){
        switch(clockFormat){
            // hh-mm-ss
            case 0:
                nixie(1, clockH1);
                nixie(2, clockH2);
                nixie(3, 12);
                nixie(4, clockM1);
                nixie(5, clockM2);
                nixie(6, 12);
                nixie(7, clockS1);
                nixie(8, clockS2);
                break;
            // hh-mm.
            case 1:
                nixie(1, clockH1);
                nixie(2, clockH2);
                nixie(3, 12);
                nixie(4, clockM1);
                nixie(5, clockM2);
                nixie(6, 11);
                break;
            // hh..
            case 2:
                nixie(1, clockH1);
                nixie(2, clockH2);
                nixie(3, 11);
                nixie(4, 11);
                break;
            // .mm.
            case 3:
                nixie(3, 11);
                nixie(4, clockM1);
                nixie(5, clockM2);
                nixie(6, 11);
                break;
            // .mm-ss
            case 4:
                nixie(3, 11);
                nixie(4, clockM1);
                nixie(5, clockM2);
                nixie(6, 12);
                nixie(7, clockS1);
                nixie(8, clockS2);
                break;
            // ..ss
            case 5:
                nixie(5, 11);
                nixie(6, 11);
                nixie(7, clockS1);
                nixie(8, clockS2);
        }

        switch(key()){
            // K1 -> toggle format
            case 1:
                ++clockFormat;
                if(clockFormat>5){clockFormat = 0;}
                beep(50,1000);
                break;
            // K2 -> change time
            case 2:
                clockH1Mem = clockH1;
                clockH2Mem = clockH2;
                clockM1Mem = clockM1;
                clockM2Mem = clockM2;
                clockS1Mem = clockS1;
                clockS2Mem = clockS2;
                beep(50, 1000);
                clockSetting();
                break;
            // K3 -> reset
            case 3:
                clockH1 = 0;
                clockH2 = 5;
                clockM1 = 0;
                clockM2 = 0;
                clockS1 = 0;
                clockS2 = 0;
                beep(100, 500);
                break;
            // K4 -> go back
            case 4:
                beep(50, 200);
                return;
        }

    }
}

void clockSetting(void){
    while(1){
        // nixie(3, 12);
        
        // nixie(6, 12);
        
        switch(clockSelect){
            // H1
            case 0:
                nixie(1, clockH1Mem);
                nixie(2, clockH2Mem);
                nixie(3, 0x60);
                break;
            // H2
            case 1:
                nixie(1, clockH1Mem);
                nixie(2, clockH2Mem);
                nixie(3, 0x50);
                break;
            // m1
            case 2:
                nixie(4, clockM1Mem);
                nixie(5, clockM2Mem);
                nixie(3, 0x42);
                nixie(6, 0x60);
                break;
            // m2
            case 3:
                nixie(4, clockM1Mem);
                nixie(5, clockM2Mem);
                nixie(3, 0x44);
                nixie(6, 0x50);
                break;
            // s1
            case 4:
                nixie(7, clockS1Mem);
                nixie(8, clockS2Mem);
                nixie(6, 0x42);
                break;
            // s2
            case 5:
                nixie(7, clockS1Mem);
                nixie(8, clockS2Mem);
                nixie(6, 0x44);
                break;
        }

        switch(key()){
            // K1 -> toggle unit | apply
            case 1:
                if(isHold){
                    clockH1 = clockH1Mem;
                    clockH2 = clockH2Mem;
                    clockM1 = clockM1Mem;
                    clockM2 = clockM2Mem;
                    clockS1 = clockS1Mem;
                    clockS2 = clockS2Mem;
                    beep(200, 2000);
                    return;
                }
                else{
                    ++clockSelect;
                    if(clockSelect>5){clockSelect = 0;}
                    beep(50,1000);
                }
                break;
            // K2 -> minus
            case 2:
                switch(clockSelect){
                    case 0: --clockH1Mem; break;
                    case 1: --clockH2Mem; break;
                    case 2: --clockM1Mem; break;
                    case 3: --clockM2Mem; break;
                    case 4: --clockS1Mem; break;
                    case 5: --clockS2Mem; break;
                }
                beep(100, 2000);
                break;
            // K3 -> plus
            case 3:
                switch(clockSelect){
                    case 0: ++clockH1Mem; break;
                    case 1: ++clockH2Mem; break;
                    case 2: ++clockM1Mem; break;
                    case 3: ++clockM2Mem; break;
                    case 4: ++clockS1Mem; break;
                    case 5: ++clockS2Mem; break;
                }
                beep(100, 2000);
                break;
            // K4 -> discard
            case 4:
                beep(50, 200);
                return;
        }

        // S2
        if(clockS2Mem==255){clockS2Mem = 9; --clockS1Mem;}
        if(clockS2Mem>9){clockS2Mem = 0; ++clockS1Mem;}
        // S1
        if(clockS1Mem==255){clockS1Mem = 5; clockS2Mem = 9;}
        if((clockS1Mem==5 && clockS2Mem>9) || clockS1Mem>5){clockS1Mem = 0; clockS1Mem = 0;}
        // M2
        if(clockM2Mem==255){clockM2Mem = 9; --clockM1Mem;}
        if(clockM2Mem>9){clockM2Mem = 0; ++clockM1Mem;}
        // M1
        if(clockM1Mem==255){clockM1Mem = 5; clockM2Mem = 9;}
        if((clockM1Mem==5 && clockM2Mem>9) || clockM1Mem>5){clockM1Mem = 0; clockM2Mem = 0;}
        // H2
        if(clockH2Mem==255){clockH2Mem = 9; --clockH1Mem;}
        else if(clockH2Mem==255 && clockH1Mem==2){clockH2Mem = 3; --clockH1Mem;}
        if(clockH2Mem>9){clockH2Mem = 0; ++clockH1Mem;}
        // H1
        if(clockH1Mem==255){clockH1Mem = 2; clockH2Mem = 3;}
        if((clockH1Mem==2 && clockH2Mem>3) || clockH1Mem>2){clockH1Mem = 0; clockH2Mem = 0;}
    }
}

void clockProcess(void){
    ++clockS2;
    // ss
    if(clockS1>=5 && clockS2>9){clockS1 = 0; clockS2 = 0; ++clockM2;}
    if(clockS2>9){clockS2 = 0; ++clockS1;}
    // mm
    if(clockM1>=5 && clockM2>9){clockM1 = 0; clockM2 = 0; ++clockH2;}
    if(clockM2>9){clockM2 = 0; ++clockM1;}
    // hh
    if(clockH1>=2 && clockH2>3){clockH1 = 0; clockH2 = 0; dateProcess();}
    if(clockH2>9){clockH2 = 0; ++clockH1;}
}
