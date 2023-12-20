#include <stc89.h>
#include "../hdr/modules.h"


/// @brief Show a sign in one nixie's unit.
/// @param location Set the value of P2_234 to select the LED1~8 (L to R).
/// @param display  Active particular LEDs accroding to the nixieTable.
void nixie(unsigned char location, unsigned char display){
    switch(location){
        case 1: P2 &= 0xe3; P2 |= 0x1c; break;
        case 2: P2 &= 0xe3; P2 |= 0x18; break;
        case 3: P2 &= 0xe3; P2 |= 0x14; break;
        case 4: P2 &= 0xe3; P2 |= 0x10; break;
        case 5: P2 &= 0xe3; P2 |= 0x0c; break;
        case 6: P2 &= 0xe3; P2 |= 0x08; break;
        case 7: P2 &= 0xe3; P2 |= 0x04; break;
        case 8: P2 &= 0xe3; P2 |= 0x00; break;
    }
    switch(display){
        case 0: P0 = 0x3f; break; // 0
        case 1: P0 = 0x06; break; // 1
        case 2: P0 = 0x5b; break; // 2
        case 3: P0 = 0x4f; break; // 3
        case 4: P0 = 0x66; break; // 4
        case 5: P0 = 0x6d; break; // 5
        case 6: P0 = 0x7d; break; // 6
        case 7: P0 = 0x07; break; // 7
        case 8: P0 = 0x7f; break; // 8
        case 9: P0 = 0x6f; break; // 9
        case 10: P0 = 0x00; break; // null
        case 11: P0 = 0x80; break; // .
        case 12: P0 = 0x40; break; // -
        default: P0 = display; break;
    }
    delay(1);
    P0 = 0x00;
}
