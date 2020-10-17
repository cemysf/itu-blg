#ifndef _TIMER_H_
#define _TIMER_H_

/*  Timer register declaration*/

#define CPU_TIM0_CTRL ((ioport volatile unsigned*)0x1810)
#define CPU_TIM0_PLWR ((ioport volatile unsigned*)0x1812)
#define CPU_TIM0_PHWR ((ioport volatile unsigned*)0x1813)
#define CPU_TIM0_CLWR ((ioport volatile unsigned*)0x1814)
#define CPU_TIM0_CHWR ((ioport volatile unsigned*)0x1815)
#define CPU_TIM0_IER ((ioport volatile unsigned*)0x1816)
#define CPU_TIMINT_AGGR ((ioport volatile unsigned*)0x1c14)
#define CPU_PRCR ((ioport volatile unsigned*)0x1c05)

void Timer0Init(void);
void StartTimer0(void);
interrupt void Timer_isr(void);

#endif

