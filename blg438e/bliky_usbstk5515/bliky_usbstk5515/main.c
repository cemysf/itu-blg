#include <stdint.h>
#include "usbstk5515_led.h"

/* CPU clock speed (100MHz) */
#define CPU_CLOCK_HZ       100000000U

/* system clock ticking rate (number of TINT interrupts per second */
#define BSP_TICKS_PER_SEC  100U

#define TINT_EVENT         4U

#define C55X_IER0          ((unsigned int volatile *)0x0000)
#define C55X_IER1          ((unsigned int volatile *)0x0045)

#define IVPD               ((ioport unsigned int volatile *)0x0049)
#define IVPH               ((ioport unsigned int volatile *)0x004A)

#define EBSR               ((ioport unsigned int volatile *)0x1C00)
#define PSRCR              ((ioport unsigned int volatile *)0x1C04)
#define PRCR               ((ioport unsigned int volatile *)0x1C05)

#define CPU_TIM0_CTRL      ((ioport unsigned int volatile *)0x1890)
#define CPU_TIM0_PLWR      ((ioport unsigned int volatile *)0x1892)
#define CPU_TIM0_PHWR      ((ioport unsigned int volatile *)0x1893)
#define CPU_TIM0_CLWR      ((ioport unsigned int volatile *)0x1894)
#define CPU_TIM0_CHWR      ((ioport unsigned int volatile *)0x1895)
#define CPU_TIM0_IER       ((ioport unsigned int volatile *)0x1896)
#define CPU_TIMINT_AGGR    ((ioport unsigned int volatile *)0x1c14)
#define CPU_PRCR           ((ioport unsigned int volatile *)0x1c05)

void AIC_write2(Int16 data_right, Int16 data_left);
Int16 USBSTK5515_I2C_init( );
void AIC_init(void);

// CSL asm functions
extern void VECSTART(void);
extern int  IRQ_plug(uint16_t eventID, void (*isrPtr)(void));

Int16 right = 0;
Int16 left = 0;

/*..........................................................................*/
interrupt void TINT_isr(void) {
    static uint16_t ctr = 1U;

    *CPU_TIM0_IER     = 0x0001U;             /* clear Timer0 interrupt flag */
    *CPU_TIMINT_AGGR |= 0x0001U;                        /* clear Timer0 bit */




   /* blink User LED 0 at 1Hz... */
   if (--ctr == 0) {                             /* did 1/2 second elapse? */
        static uint16_t is_on = 1U;
        ctr = BSP_TICKS_PER_SEC / 2;
        if (is_on) {
            USBSTK5515_ULED_off(0U);
       }
        else {
            USBSTK5515_ULED_on(0U);
        }
        is_on = !is_on;
    }
}
/*..........................................................................*/
void main(void) {



    USBSTK5515_init();            /* initialize BSL */
    USBSTK5515_I2C_init();

    AIC_init();


    _disable_interrupts();

    *C55X_IER0 = 0U;
    *C55X_IER1 = 0U;

    *IVPD = (uint16_t)((uint32_t)&VECSTART >> 8);
    *IVPH = (uint16_t)((uint32_t)&VECSTART >> 8);


    IRQ_plug(TINT_EVENT, &TINT_isr);

    *CPU_TIM0_CTRL   = 0x802EU;		// control register
    *CPU_TIM0_PLWR   = (98304000 / 4096U)/10;
    *CPU_TIM0_PHWR   = 0;
    *CPU_TIM0_CLWR   = 0x0000U;
    *CPU_TIM0_CHWR   = 0x0000U;
    *CPU_TIMINT_AGGR = 0x0007U;
    *CPU_TIM0_IER    = 0x0001U;
    *CPU_TIM0_CTRL  |= 0x0001U;

    *C55X_IER0      |= 1U << TINT_EVENT;

    _enable_interrupts();


    while(1)
    {

    }
}
