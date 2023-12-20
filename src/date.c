#include <stc89.h>
#include "../hdr/modules.h"

void dateSetting(void);
unsigned char dateFormat = 0;
unsigned char dateSelect = 0;
unsigned char dateY1 = 2;
unsigned char dateY2 = 0;
unsigned char dateY3 = 2;
unsigned char dateY4 = 3;
unsigned char dateM1 = 1;
unsigned char dateM2 = 2;
unsigned char dateD1 = 1;
unsigned char dateD2 = 5;
unsigned char dateY1Mem;
unsigned char dateY2Mem;
unsigned char dateY3Mem;
unsigned char dateY4Mem;
unsigned char dateM1Mem;
unsigned char dateM2Mem;
unsigned char dateD1Mem;
unsigned char dateD2Mem;
unsigned char year;


/// @brief <Date Mode> display current date.
void date(void){
    while(1){
        switch(dateFormat){
            // YYYYMMDD
            case 0:
                nixie(1, dateY1);
                nixie(2, dateY2);
                nixie(3, dateY3);
                nixie(4, dateY4);
                nixie(5, dateM1);
                nixie(6, dateM2);
                nixie(7, dateD1);
                nixie(8, dateD2);
                break;
            // YYMMDD
            case 1:
                nixie(3, dateY3);
                nixie(4, dateY4);
                nixie(5, dateM1);
                nixie(6, dateM2);
                nixie(7, dateD1);
                nixie(8, dateD2);
                break;
            // YYYY . .
            case 2:
                nixie(1, dateY1);
                nixie(2, dateY2);
                nixie(3, dateY3);
                nixie(4, dateY4);
                nixie(5, 11);
                nixie(6, 11);
                break;
            // .MMDD
            case 3:
                nixie(4, 11);
                nixie(5, dateM1);
                nixie(6, dateM2);
                nixie(7, dateD1);
                nixie(8, dateD2);
                break;
            // .MM.
            case 4:
                nixie(4, 11);
                nixie(5, dateM1);
                nixie(6, dateM2);
                nixie(7, 11);
                break;
            // ..DD
            case 5:
                nixie(5, 11);
                nixie(6, 11);
                nixie(7, dateD1);
                nixie(8, dateD2);
                break;
        }

        switch(key()){
            // K1 -> toggle fomat
            case 1:
                ++dateFormat;
                if(dateFormat>5){dateFormat = 0;}
                beep(50,1000);
                break;
            // K2 -> change time
            case 2:
                dateY1Mem = dateY1;
                dateY2Mem = dateY2;
                dateY3Mem = dateY3;
                dateY4Mem = dateY4;
                dateM1Mem = dateM1;
                dateM2Mem = dateM2;
                dateD1Mem = dateD1;
                dateD2Mem = dateD2;
                beep(50, 1000);
                dateSetting();
                break;
            // K4 -> go back;
            case 4:
                beep(50, 200);
                return;
        }
    }
}

void dateSetting(void){
    while(1){
        switch(dateSelect){
            // YYYY
            case 0:
                nixie(1, dateY1Mem);
                nixie(2, dateY2Mem);
                nixie(3, dateY3Mem);
                nixie(4, dateY4Mem);
                break;
            // MM
            case 1:
                nixie(5, dateM1Mem);
                nixie(6, dateM2Mem);
                break;
            // DD
            case 2:
                nixie(7, dateD1Mem);
                nixie(8, dateD2Mem);
                break;
        }

        switch(key()){
            // K1 -> toggle unit | apply
            case 1:
                if(isHold){
                    dateY1 = dateY1Mem;
                    dateY2 = dateY2Mem;
                    dateY3 = dateY3Mem;
                    dateY4 = dateY4Mem;
                    dateM1 = dateM1Mem;
                    dateM2 = dateM2Mem;
                    dateD1 = dateD1Mem;
                    dateD2 = dateD2Mem;
                    beep(200, 2000);
                    return;
                }
                else{
                    ++dateSelect;
                    if(dateSelect>2){dateSelect = 0;}
                    beep(50,1000);
                }
                break;
            // K2 -> minus
            case 2:
                switch(dateSelect){
                    case 0: --dateY4Mem; break;
                    case 1: --dateM2Mem; break;
                    case 2: --dateD2Mem; break;
                }
                beep(100, 2000);
                break;
            // K3 -> plus
            case 3:
                switch(dateSelect){
                    case 0: ++dateY4Mem; break;
                    case 1: ++dateM2Mem; break;
                    case 2: ++dateD2Mem; break;
                }
                beep(100, 2000);
                break;
            // K4 -> go back
            case 4:
                beep(50, 200);
                return;
        }

        year = dateY1Mem*(char)1000 + dateY2Mem*(char)100 + dateY3Mem*(char)10 + dateY4Mem;
        // DD
        switch(dateM1Mem*(char)10 + dateM2Mem){
            // 31 days
            case 1:
            case 3:
            case 5:
            case 7:
            case 8:
            case 10:
            case 12:
                if(dateD1Mem>=3 && dateD2Mem>1){dateD2Mem = 1; dateD1Mem = 0;}
                break;
            // 30 days
            case 4:
            case 6:
            case 9:
            case 11:
                if(dateD1Mem>=3 && dateD2Mem>0){dateD2Mem = 1; dateD1Mem = 0;}
                break;
            // Feburary
            case 2:
                if(year%400==0 && year%4==0){
                    if(dateD1Mem>=2 && dateD2Mem>9){dateD2Mem = 1; dateD1Mem = 0;}
                }
                else{
                    if(dateD1Mem>=2 && dateD2Mem>8){dateD2Mem = 1; dateD1Mem = 0;}
                }
                break;
        }
        if(dateD1Mem==255){dateD1Mem = 0;}
        if(dateD2Mem==255){dateD2Mem = 0; --dateD1Mem;}
        if(dateD2Mem>9){dateD2Mem = 0; ++dateD1Mem;}
        // M2
        if(dateM2Mem==255){dateM2Mem = 0; --dateM1Mem;}
        if(dateM2Mem>9){dateM2Mem = 0; ++dateM1Mem;}
        // M1
        if(dateM1Mem==255 && dateM2Mem<1){dateM1Mem = 1; dateM2Mem = 2;}
        if(dateM1Mem>=1 && dateM2Mem>2){dateM1Mem = 0; dateM2Mem = 1;}
        // Y4
        if(dateY4Mem==255){dateY4Mem = 9; --dateY3Mem;}
        if(dateY4Mem>9){dateY4Mem = 0; ++dateY3Mem;}
        // Y3
        if(dateY3Mem==255){dateY3Mem = 9; --dateY2Mem;}
        if(dateY3Mem>9){dateY3Mem = 0; ++dateY2Mem;}
        // Y2
        if(dateY2Mem==255){dateY2Mem = 0; --dateY1Mem;}
        if(dateY2Mem>9){dateY2Mem = 0; ++dateY2Mem;}
        // Y1
        if(dateY1Mem<=1 && dateY2Mem<9){dateY2Mem = 9; dateY3Mem = 0; dateY4Mem = 0;}
        if(dateY1Mem>=2 && dateY2Mem>1){dateY2Mem = 1; dateY3Mem = 0; dateY4Mem = 0;}
    }
}

void dateProcess(void){
    year = dateY1Mem*(char)1000 + dateY2Mem*(char)100 + dateY3Mem*(char)10 + dateY4Mem;

    ++dateD2;
    switch(dateM1Mem*(char)10 + dateM2Mem){
            case 1:
            case 3:
            case 5:
            case 7:
            case 8:
            case 10:
            case 12:
                if(dateD1Mem>=3 && dateD2Mem>1){dateD2Mem = 1; --dateD1Mem;}
                break;
            case 4:
            case 6:
            case 9:
            case 11:
                if(dateD1Mem>=3 && dateD2Mem>0){dateD2Mem = 1; --dateD1Mem;}
                break;
            case 2:
                if(year%400==0 && year%4==0){
                    if(dateD1Mem>=2 && dateD2Mem>9){dateD2Mem = 1; --dateD1Mem;}
                }
                else{
                    if(dateD1Mem>=2 && dateD2Mem>8){dateD2Mem = 1; --dateD1Mem;}
                }
                break;
        }
    if(dateD2Mem>9){dateD2Mem = 0; ++dateD1Mem;}
    if(dateM2Mem>9){dateM2Mem = 0; ++dateM1Mem;}
    if(dateM1Mem>=1 && dateM2Mem>2){dateM1Mem = 0; dateM2Mem = 1;}
    if(dateY4Mem>9){dateY4Mem = 0; ++dateY3Mem;}
    if(dateY3Mem>9){dateY3Mem = 0; ++dateY2Mem;}
    if(dateY2Mem>9){dateY2Mem = 0; ++dateY2Mem;}
    if(dateY1Mem>=2 && dateY2Mem>1){dateY2Mem = 1; dateY3Mem = 0; dateY4Mem = 0;}
    beep(200, 2000);
}
