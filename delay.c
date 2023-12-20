/// @brief Do meaningless compute to make a sort of delay.
void delay(unsigned int ms){
    unsigned char i, j;
    while(ms){
        i = 2;
        j = 239;
        do{
            while(--j);
        } while(--i);
        ms--;
    }
}
