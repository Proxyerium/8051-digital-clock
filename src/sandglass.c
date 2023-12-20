#include <stc89.h>
#include "../hdr/modules.h"

void sandglassSetting(void);

unsigned char sandglassActive = 0;
unsigned char sandglassSelect = 0;
unsigned char sandglassA = 0;
unsigned char sandglassB = 6;
unsigned char sandglassC = 0;
unsigned char sandglassD = 0;


/// @brief <Sandglass Mode> count down.
void sandglass(void){
    while(1){
        nixie(5, sandglassA);
        nixie(6, sandglassB);
        nixie(7, sandglassC);
        nixie(8, sandglassD);
    
        switch(key()){
            // K1 -> start/pause
            case 1:
                sandglassActive = !sandglassActive;                
                TR0 = !TR0;
                beep(25, 1000);
                break;
            // K2 -> setting
            case 2:
                beep(50, 500);
                sandglassSetting();
                break;
            // K3 -> reset
            case 3:
                TR0 = 0;
                sandglassA = 0;
                sandglassB = 6;
                sandglassC = 0;
                sandglassD = 0;
                beep(100, 500);
                break;
            // K4 -> go back
            case 4:
                sandglassActive = 0;
                TR0 = 0;
                beep(50, 200);
                return;
        }
    }
}

void sandglassSetting(void){
    while(1){
        nixie(5, sandglassA);
        nixie(6, sandglassB);
        nixie(7, sandglassC);
        nixie(8, sandglassD);

        switch(sandglassSelect){
            case 0:
                nixie(5, 11);
                break;
            case 1:
                nixie(6, 11);
                break;
            case 2:
                nixie(7, 11);
                break;
            case 3:
                nixie(8, 11);
                break;
        }

        switch(key()){
            // K1 -> toggle unit | apply
            case 1:
                if(isHold){
                    beep(200, 2000);
                    return;
                }
                else{
                    ++sandglassSelect;
                    if(sandglassSelect>3){sandglassSelect = 0;}
                    beep(50,1000);
                }
                break;
            // K2 -> minus
            case 2:
                switch(sandglassSelect){
                    case 0: --sandglassA; break;
                    case 1: --sandglassB; break;
                    case 2: --sandglassC; break;
                    case 3: --sandglassD; break;
                }
                beep(100, 2000);
                break;
            // K3 -> plus
            case 3:
                switch(sandglassSelect){
                    case 0: ++sandglassA; break;
                    case 1: ++sandglassB; break;
                    case 2: ++sandglassC; break;
                    case 3: ++sandglassD; break;
                }
                beep(100, 2000);
                break;
            // K4 -> discard
            case 4:
                sandglassA = 0;
                sandglassB = 6;
                sandglassC = 0;
                sandglassD = 0;
                beep(50, 1000);
                return;
        }

        // D
        if(sandglassD==255){sandglassD = 9;}
        if(sandglassD>9){sandglassD = 0;}
        // C
        if(sandglassC==255){sandglassC = 9;}
        if(sandglassC>9){sandglassC = 0;}
        // B
        if(sandglassB==255){sandglassB = 9;}
        if(sandglassB>9){sandglassB = 0;}
        // A
        if(sandglassA==255){sandglassA = 9;}
        if(sandglassA>9){sandglassA = 0;}
    }
}

void sandglassProcess(void){
    if(TR0 && sandglassActive){
        --sandglassD;
        if(sandglassD==255){sandglassD = 9; --sandglassC;}
        if(sandglassC==255){sandglassC = 9; --sandglassB;}
        if(sandglassB==255){sandglassB = 9; --sandglassA;}
        if(sandglassA==255){sandglassA = 0;}
        
        if(sandglassA==0){
            if(sandglassB==0){
                if(sandglassC==0){
                    if(sandglassD==0){
                        sandglassActive = 0;
                        TR0 = 0;

                        beep(100, 2000);
                        delay(100);
                        beep(100, 2000);
                        delay(100);
                        beep(100, 2000);
                    }
                }
            }
        }
    }
}
