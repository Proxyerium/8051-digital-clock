#ifndef __TIMERS_H__
#define __TIMERS_H__

void initT0(void);
void routineT0(void) __interrupt(1);
void initT1(void);
void routineT1(void) __interrupt(3);

#endif
