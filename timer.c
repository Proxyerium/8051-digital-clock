#include <stc89.h>

extern void beep(unsigned int, unsigned int);
extern void delay(unsigned int);
extern unsigned char key(void);
extern void nixie(unsigned char, unsigned char);
void timerLoad(void);

extern unsigned char isHold;
unsigned char timerActive = 0;
unsigned char timerA = 10;
unsigned char timerB = 10;
unsigned char timerC = 0;
unsigned char timerD = 0;
unsigned char timerMem[10];
unsigned char memIndex = 0;

/// @brief <Timer Mode> +1 per second.
void timer(void){ 
    while(1){
        nixie(5, timerA);
        nixie(6, timerB);
        nixie(7, timerC);
        nixie(8, timerD);

        switch(key()){
            // K1 -> start/pause | load
            case 1:
                if(isHold){timerLoad();}
                else{timerActive = !timerActive; TR0 = !TR0;}
                beep(25, 1000);
                break;
            // K2 -> save
            case 2:
                timerMem[memIndex] = timerA*(char)1000 + timerB*(char)100 + timerC*(char)10 + timerD;
                memIndex++;
                if(memIndex==255){memIndex = 9;}
                if(memIndex>9){memIndex = 0;}
                nixie(1, memIndex);
                beep(50, 500);
                break;
            // K3 -> reset
            case 3:
                TR0 = 0;
                timerA = 10;
                timerB = 10;
                timerC = 0;
                timerD = 0;
                beep(100, 500);
                break;
            // K4 -> go back
            case 4:
                timerActive = 0;
                TR0 = 0;
                beep(50, 200);
                // break;
                return;
        }
    }
}

void timerLoad(void){
    while(1){
        nixie(1, memIndex);
        nixie(5, timerMem[memIndex]/(char)1000);
        nixie(6, (timerMem[memIndex]/(char)100)%(char)10);
        nixie(7, ((timerMem[memIndex]/(char)10)%(char)100)%(char)10);
        nixie(8, ((timerMem[memIndex]%(char)1000)%(char)(100)%(char)10));
        
        switch(key()){
            // K1 -> clear
            case 1:
                for(unsigned char i = 0; i<10; i++){timerMem[i]=0;}
                memIndex = 0;
                beep(100, 3000);
                break;
            // K2 -> previous
            case 2:
                --memIndex;
                beep(50, 1000);
                break;
            // K3 -> next
            case 3:
                ++memIndex;
                beep(50, 1000);
                break;
            // K4 -> go back
            case 4:
                return;
        }
        if(memIndex==255){memIndex = 9;}
        if(memIndex>9){memIndex = 0;}
    }
}

void timerProcess(void){
    if(TR0 && timerActive){
        ++timerD;
        if(timerD>9){timerD = 0; ++timerC;}
        if(timerC>9){timerC = 0; ++timerB;}
        if(timerB>9){timerB = 0; ++timerA;}
        if(timerA>9){timerA = 0;}
        beep(25,1000);
    }
}
