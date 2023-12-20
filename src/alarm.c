#include <stc89.h>
#include "../hdr/modules.h"

extern unsigned char clockH1;
extern unsigned char clockH2;
extern unsigned char clockM1;
extern unsigned char clockM2;
extern unsigned char clockS1;
extern unsigned char clockS2;
unsigned char alarmSelect = 0;
unsigned char alarmSetup = 0;
unsigned char alarmH1 = 0;
unsigned char alarmH2 = 5;
unsigned char alarmM1 = 0;
unsigned char alarmM2 = 0;
unsigned char alarmS1 = 0;
unsigned char alarmS2 = 0;


/// @brief <Alarm Mode> set up an alarm.
void alarm(void){
    while(1){
        nixie(1, alarmH1);
        nixie(2, alarmH2);
        nixie(3, 12);
        nixie(4, alarmM1);
        nixie(5, alarmM2);
        nixie(6, 12);
        nixie(7, alarmS1);
        nixie(8, alarmS2);

        if(alarmSetup){
            nixie(3, 0x40);
            nixie(6, 0x40);
        }
        else{
            switch(alarmSelect){
                // H1
                case 0:
                    nixie(3, 0x60);
                    break;
                // H2
                case 1:
                    nixie(3, 0x50);
                    break;
                // m1
                case 2:
                    nixie(3, 0x42);
                    nixie(6, 0x60);
                    break;
                // m2
                case 3:
                    nixie(3, 0x44);
                    nixie(6, 0x50);
                    break;
                // s1
                case 4:
                    nixie(6, 0x42);
                    break;
                // s2
                case 5:
                    nixie(6, 0x44);
                    break;
            }
        }

        switch(key()){
            // K1 -> toggle unit | apply
            case 1:
                if(isHold==0){
                    ++alarmSelect;
                    if(alarmSelect>5){alarmSelect = 0;}
                    beep(50,1000);
                }
                else{
                    alarmSetup = !alarmSetup;
                    beep(300, 2000);
                }
                break;
            // K2 -> minus
            case 2:
                switch(alarmSelect){
                    case 0: --alarmH1; break;
                    case 1: --alarmH2; break;
                    case 2: --alarmM1; break;
                    case 3: --alarmM2; break;
                    case 4: --alarmS1; break;
                    case 5: --alarmS2; break;
                }
                beep(100, 2000);
                break;
            // K3 -> plus
            case 3:
                switch(alarmSelect){
                    case 0: ++alarmH1; break;
                    case 1: ++alarmH2; break;
                    case 2: ++alarmM1; break;
                    case 3: ++alarmM2; break;
                    case 4: ++alarmS1; break;
                    case 5: ++alarmS2; break;
                }
                beep(100, 2000);
                break;
            // K4 -> discard
            case 4:
                if(alarmSetup==0){
                    alarmH1 = 0;
                    alarmH2 = 5;
                    alarmM1 = 0;
                    alarmM2 = 0;
                    alarmS1 = 0;
                    alarmS2 = 0;
                }
                beep(50, 200);
                return;
        }
        
        // S2
        if(alarmS2==255){alarmS2 = 9, --alarmS1;}
        if(alarmS2>9){alarmS2 = 0, ++alarmS1;}
        // S1
        if(alarmS1==255){alarmS1 = 5, alarmS2 = 9;}
        if((alarmS1>=5 && alarmS2>9) || alarmS1>5){alarmS1 = 0, alarmS1 = 0;}
        // M2
        if(alarmM2==255){alarmM2 = 9, --alarmM1;}
        if(alarmM2>9){alarmM2 = 0, ++alarmM1;}
        // M1
        if(alarmM1==255){alarmM1 = 5, alarmM2 = 9;}
        if((alarmM1>=5 && alarmM2>9) || alarmM1>5){alarmM1 = 0, alarmM2 = 0;}
        // H2
        if(alarmH2==255){alarmH2 = 9, --alarmH1;}
        else if(alarmH2==255 && alarmH1==2){alarmH2 = 3, --alarmH1;}
        if(alarmH2>9){alarmH2 = 0, ++alarmH1;}
        // H1
        if(alarmH1==255){alarmH1 = 2, alarmH2 = 3;}
        if((alarmH1>=2 && alarmH2>3) || alarmH1>2){alarmH1 = 0, alarmH2 = 0;}
    }
}

void alarmProcess(void){
    if(alarmSetup){
        if(alarmH1==clockH1 && alarmH1==clockH1){
            if(alarmM1==clockM1 && alarmM2==clockM2){
                if(alarmS1==clockS1 && alarmS2==clockS2){
                    alarmSetup = 0;
                    beep(80 ,2000);
                    delay(100);
                    beep(80 ,2000);
                    delay(100);
                    beep(80 ,2000);
                    delay(100);
                    beep(80 ,2000);
                    delay(100);
                    beep(240 ,2000);
                }
            }
        }
    }
}
