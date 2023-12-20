#include <stc89.h>

/// @brief Set the frequency of beep! Working incorrectly at some frequencies somehow.
void beepFreq(unsigned int freq){
    // delay 1μs @11MHz
    unsigned char i;
    i = 2*freq;
    while(--i);
}

/// @brief Buzzer beep!
void beep(unsigned int ms, unsigned int freq){
    for(unsigned int b=0; b<ms; b++){
        P2_5 = !P2_5;
        beepFreq(freq);
    }
}
