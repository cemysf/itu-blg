;****************************************************************************************
;
;    File Name   : lpva200.h
;    Author      : Pedro Gelabert
;
;    Version     : 0.1
;    Date        : 23 June 2004
;    Update      : 
;
;    Description : This file defines LPVA200 memory mapped registers
;
;****************************************************************************************
;****************************************************************************************
;    Test Mode Control Register
;****************************************************************************************
    ;.include "map_da214.inc"            ; (was uma_map.inc) Memory + I/O space + MMRs mapping file...

;****************************************************************************************
;    Testbench Registers
;****************************************************************************************
TB_INTGEN       .set    0x7FF1
    ; TB_INTGEN   Address:  0x7FF1 (IO Space)           Testbench Driver Data for GPIO PINS[15:0]
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ; |15:14:13:12|11:10: 9: 8| 7: 6: 5: 4| 3: 2: 1: 0|  <<== Bit Position
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; | w: w: w: w| w: w: w: w| w: w: w: w| w: w: w: w|  <<== Read / Write Access
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; | 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0|  <<== Reset Values
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-- TB_INTGEN[0]      Writing a 1 forces the NMI    pin low after 4us
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  +----- TB_INTGEN[1]      Writing a 1 forces the INT0   pin low after 4us
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  +-------- TB_INTGEN[2]      Writing a 1 forces the INT1   pin low after 4us
    ;   |  |  |  |  |  |  |  |  |  |  |  |  +----------- TB_INTGEN[3]      Writing a 1 forces the RESETN pin low after 4us & high again after another 500ns
    ;   |  |  |  |  |  |  |  |  |  |  |  |                           
    ;   |  |  |  |  |  |  |  |  |  |  |  +-------------- TB_INTGEN[4]      Writing a 1 forces the WAKEUP pin high after 4us
    ;   |  |  |  |  |  |  |  |  |  |  +----------------- TB_INTGEN[5]      >
    ;   |  |  |  |  |  |  |  |  |  +-------------------- TB_INTGEN[6]      >
    ;   |  |  |  |  |  |  |  |  +----------------------- TB_INTGEN[7]      >
    ;   |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  +-------------------------- TB_INTGEN[8]      >
    ;   |  |  |  |  |  |  +----------------------------- TB_INTGEN[9]      >>>>> Writing anything else sets all interrupts high & WAKEUP low  (all pins to inactive state)
    ;   |  |  |  |  |  +-------------------------------- TB_INTGEN[10]     >
    ;   |  |  |  |  +----------------------------------- TB_INTGEN[11]     >
    ;   |  |  |  |
    ;   |  |  |  +-------------------------------------- TB_INTGEN[12]     >
    ;   |  |  +----------------------------------------- TB_INTGEN[13]     >
    ;   |  +-------------------------------------------- TB_INTGEN[14]     >
    ;   +----------------------------------------------- TB_INTGEN[15]     >
    ;-----------------------------------------------------------------------------
TB_GPIO_DOUT0   .set    0x7FF2
    ; TB_GPIO_DOUT0   Address:  0x7FF2 (IO Space)           Testbench Driver Data for GPIO PINS[15:0]
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ; |15:14:13:12|11:10: 9: 8| 7: 6: 5: 4| 3: 2: 1: 0|  <<== Bit Position
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; | w: w: w: w| w: w: w: w| w: w: w: w| w: w: w: w|  <<== Read / Write Access
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; | 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0|  <<== Reset Values
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-- TB_GPIO_DOUT[0]
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  +----- TB_GPIO_DOUT[1]
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  +-------- TB_GPIO_DOUT[2]
    ;   |  |  |  |  |  |  |  |  |  |  |  |  +----------- TB_GPIO_DOUT[3]
    ;   |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  +-------------- TB_GPIO_DOUT[4]
    ;   |  |  |  |  |  |  |  |  |  |  +----------------- TB_GPIO_DOUT[5]
    ;   |  |  |  |  |  |  |  |  |  +-------------------- TB_GPIO_DOUT[6]
    ;   |  |  |  |  |  |  |  |  +----------------------- TB_GPIO_DOUT[7]
    ;   |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  +-------------------------- TB_GPIO_DOUT[8]
    ;   |  |  |  |  |  |  +----------------------------- TB_GPIO_DOUT[9]
    ;   |  |  |  |  |  +-------------------------------- TB_GPIO_DOUT[10]
    ;   |  |  |  |  +----------------------------------- TB_GPIO_DOUT[11]
    ;   |  |  |  |
    ;   |  |  |  +-------------------------------------- TB_GPIO_DOUT[12]
    ;   |  |  +----------------------------------------- TB_GPIO_DOUT[13]
    ;   |  +-------------------------------------------- TB_GPIO_DOUT[14]
    ;   +----------------------------------------------- TB_GPIO_DOUT[15]
TB_GPIO_DOUT1   .set    0x7FF3
    ; TB_GPIO_DOUT1   Address:  0x7FF3 (IO Space)           Testbench Driver Data for GPIO PINS[31:16]
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ; |15:14:13:12|11:10: 9: 8| 7: 6: 5: 4| 3: 2: 1: 0|  <<== Bit Position
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; | w: w: w: w| w: w: w: w| w: w: w: w| w: w: w: w|  <<== Read / Write Access
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; | 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0|  <<== Reset Values
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-- TB_GPIO_DOUT[16]
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  +----- TB_GPIO_DOUT[17]
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  +-------- TB_GPIO_DOUT[18]
    ;   |  |  |  |  |  |  |  |  |  |  |  |  +----------- TB_GPIO_DOUT[19]
    ;   |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  +-------------- TB_GPIO_DOUT[20]
    ;   |  |  |  |  |  |  |  |  |  |  +----------------- TB_GPIO_DOUT[21]
    ;   |  |  |  |  |  |  |  |  |  +-------------------- TB_GPIO_DOUT[22]
    ;   |  |  |  |  |  |  |  |  +----------------------- TB_GPIO_DOUT[23]
    ;   |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  +-------------------------- TB_GPIO_DOUT[24]
    ;   |  |  |  |  |  |  +----------------------------- TB_GPIO_DOUT[25]
    ;   |  |  |  |  |  +-------------------------------- TB_GPIO_DOUT[26]
    ;   |  |  |  |  +----------------------------------- TB_GPIO_DOUT[27]
    ;   |  |  |  |
    ;   |  |  |  +-------------------------------------- TB_GPIO_DOUT[28]
    ;   |  |  +----------------------------------------- TB_GPIO_DOUT[29]
    ;   |  +-------------------------------------------- TB_GPIO_DOUT[30]
    ;   +----------------------------------------------- TB_GPIO_DOUT[31]
TB_GPIO_DOUT_SEL0   .set    0x7FF4
    ; TB_GPIO_DOUT_SEL0   Address:  0x7FF4 (IO Space)           Testbench Driver Data Selector of GPIO Pins[15:0]
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ; |15:14:13:12|11:10: 9: 8| 7: 6: 5: 4| 3: 2: 1: 0|  <<== Bit Position
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; | w: w: w: w| w: w: w: w| w: w: w: w| w: w: w: w|  <<== Read / Write Access
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; | 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0|  <<== Reset Values
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-- TB_GPIO_DOUT_SEL[0]       (0:drive the value of TB_GPIO_DOUT, 1:drive the last latched value of the gpio PIN)
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  +----- TB_GPIO_DOUT_SEL[1]       (0:drive the value of TB_GPIO_DOUT, 1:drive the last latched value of the gpio PIN)
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  +-------- TB_GPIO_DOUT_SEL[2]       (0:drive the value of TB_GPIO_DOUT, 1:drive the last latched value of the gpio PIN)
    ;   |  |  |  |  |  |  |  |  |  |  |  |  +----------- TB_GPIO_DOUT_SEL[3]       (0:drive the value of TB_GPIO_DOUT, 1:drive the last latched value of the gpio PIN)
    ;   |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  +-------------- TB_GPIO_DOUT_SEL[4]       (0:drive the value of TB_GPIO_DOUT, 1:drive the last latched value of the gpio PIN)
    ;   |  |  |  |  |  |  |  |  |  |  +----------------- TB_GPIO_DOUT_SEL[5]       (0:drive the value of TB_GPIO_DOUT, 1:drive the last latched value of the gpio PIN)
    ;   |  |  |  |  |  |  |  |  |  +-------------------- TB_GPIO_DOUT_SEL[6]       (0:drive the value of TB_GPIO_DOUT, 1:drive the last latched value of the gpio PIN)
    ;   |  |  |  |  |  |  |  |  +----------------------- TB_GPIO_DOUT_SEL[7]       (0:drive the value of TB_GPIO_DOUT, 1:drive the last latched value of the gpio PIN)
    ;   |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  +-------------------------- TB_GPIO_DOUT_SEL[8]       (0:drive the value of TB_GPIO_DOUT, 1:drive the last latched value of the gpio PIN)
    ;   |  |  |  |  |  |  +----------------------------- TB_GPIO_DOUT_SEL[9]       (0:drive the value of TB_GPIO_DOUT, 1:drive the last latched value of the gpio PIN)
    ;   |  |  |  |  |  +-------------------------------- TB_GPIO_DOUT_SEL[10]      (0:drive the value of TB_GPIO_DOUT, 1:drive the last latched value of the gpio PIN)
    ;   |  |  |  |  +----------------------------------- TB_GPIO_DOUT_SEL[11]      (0:drive the value of TB_GPIO_DOUT, 1:drive the last latched value of the gpio PIN)
    ;   |  |  |  |
    ;   |  |  |  +-------------------------------------- TB_GPIO_DOUT_SEL[12]      (0:drive the value of TB_GPIO_DOUT, 1:drive the last latched value of the gpio PIN)
    ;   |  |  +----------------------------------------- TB_GPIO_DOUT_SEL[13]      (0:drive the value of TB_GPIO_DOUT, 1:drive the last latched value of the gpio PIN)
    ;   |  +-------------------------------------------- TB_GPIO_DOUT_SEL[14]      (0:drive the value of TB_GPIO_DOUT, 1:drive the last latched value of the gpio PIN)
    ;   +----------------------------------------------- TB_GPIO_DOUT_SEL[15]      (0:drive the value of TB_GPIO_DOUT, 1:drive the last latched value of the gpio PIN)
TB_GPIO_DOUT_SEL1   .set    0x7FF5
    ; TB_GPIO_DOUT_SEL1   Address:  0x7FF5 (IO Space)           Testbench Driver Data Selector of GPIO Pins[31:16]
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ; |15:14:13:12|11:10: 9: 8| 7: 6: 5: 4| 3: 2: 1: 0|  <<== Bit Position
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; | w: w: w: w| w: w: w: w| w: w: w: w| w: w: w: w|  <<== Read / Write Access
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; | 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0|  <<== Reset Values
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-- TB_GPIO_DOUT_SEL[16]      (0:drive the value of TB_GPIO_DOUT, 1:drive the last latched value of the gpio PIN)
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  +----- TB_GPIO_DOUT_SEL[17]      (0:drive the value of TB_GPIO_DOUT, 1:drive the last latched value of the gpio PIN)
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  +-------- TB_GPIO_DOUT_SEL[18]      (0:drive the value of TB_GPIO_DOUT, 1:drive the last latched value of the gpio PIN)
    ;   |  |  |  |  |  |  |  |  |  |  |  |  +----------- TB_GPIO_DOUT_SEL[19]      (0:drive the value of TB_GPIO_DOUT, 1:drive the last latched value of the gpio PIN)
    ;   |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  +-------------- TB_GPIO_DOUT_SEL[20]      (0:drive the value of TB_GPIO_DOUT, 1:drive the last latched value of the gpio PIN)
    ;   |  |  |  |  |  |  |  |  |  |  +----------------- TB_GPIO_DOUT_SEL[21]      (0:drive the value of TB_GPIO_DOUT, 1:drive the last latched value of the gpio PIN)
    ;   |  |  |  |  |  |  |  |  |  +-------------------- TB_GPIO_DOUT_SEL[22]      (0:drive the value of TB_GPIO_DOUT, 1:drive the last latched value of the gpio PIN)
    ;   |  |  |  |  |  |  |  |  +----------------------- TB_GPIO_DOUT_SEL[23]      (0:drive the value of TB_GPIO_DOUT, 1:drive the last latched value of the gpio PIN)
    ;   |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  +-------------------------- TB_GPIO_DOUT_SEL[24]      (0:drive the value of TB_GPIO_DOUT, 1:drive the last latched value of the gpio PIN)
    ;   |  |  |  |  |  |  +----------------------------- TB_GPIO_DOUT_SEL[25]      (0:drive the value of TB_GPIO_DOUT, 1:drive the last latched value of the gpio PIN)
    ;   |  |  |  |  |  +-------------------------------- TB_GPIO_DOUT_SEL[26]      (0:drive the value of TB_GPIO_DOUT, 1:drive the last latched value of the gpio PIN)
    ;   |  |  |  |  +----------------------------------- TB_GPIO_DOUT_SEL[27]      (0:drive the value of TB_GPIO_DOUT, 1:drive the last latched value of the gpio PIN)
    ;   |  |  |  |
    ;   |  |  |  +-------------------------------------- TB_GPIO_DOUT_SEL[28]      (0:drive the value of TB_GPIO_DOUT, 1:drive the last latched value of the gpio PIN)
    ;   |  |  +----------------------------------------- TB_GPIO_DOUT_SEL[29]      (0:drive the value of TB_GPIO_DOUT, 1:drive the last latched value of the gpio PIN)
    ;   |  +-------------------------------------------- TB_GPIO_DOUT_SEL[30]      (0:drive the value of TB_GPIO_DOUT, 1:drive the last latched value of the gpio PIN)
    ;   +----------------------------------------------- TB_GPIO_DOUT_SEL[31]      (0:drive the value of TB_GPIO_DOUT, 1:drive the last latched value of the gpio PIN)
TB_GPIO_CONTROL   .set    0x7FF6
    ; TB_GPIO_CONTROL   Address:  0x7FF6 (IO Space)           Testbench GPIO Control Register
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ; |15:14:13:12|11:10: 9: 8| 7: 6: 5: 4| 3: 2: 1: 0|  <<== Bit Position
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; | w: w: w: w| w: w: w: w| w: w: w: w| w: w: w: w|  <<== Read / Write Access
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; | 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0|  <<== Reset Values
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-- GPIO_LATCH_EN             (0: GPIO_LATCHED[31:0] is held, 1: GPIO_LATCHED[31:0] gets current gpio pin states)
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  +----- reserved
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  +-------- reserved
    ;   |  |  |  |  |  |  |  |  |  |  |  |  +----------- reserved
    ;   |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  +-------------- reserved
    ;   |  |  |  |  |  |  |  |  |  |  +----------------- reserved
    ;   |  |  |  |  |  |  |  |  |  +-------------------- reserved
    ;   |  |  |  |  |  |  |  |  +----------------------- reserved
    ;   |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  +-------------------------- reserved
    ;   |  |  |  |  |  |  +----------------------------- reserved
    ;   |  |  |  |  |  +-------------------------------- reserved
    ;   |  |  |  |  +----------------------------------- reserved
    ;   |  |  |  |
    ;   |  |  |  +-------------------------------------- reserved
    ;   |  |  +----------------------------------------- reserved
    ;   |  +-------------------------------------------- reserved
    ;   +----------------------------------------------- reserved
TB_POWERVCD_CONTROL   .set    0x7FFC
    ; TB_POWERVCD_CONTROL   Address:  0x7FFC (IO Space)    Testbench Power VCD Control Register
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ; |15:14:13:12|11:10: 9: 8| 7: 6: 5: 4| 3: 2: 1: 0|  <<== Bit Position
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; | w: w: w: w| w: w: w: w| w: w: w: w| w: w: w: w|  <<== Read / Write Access
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; | 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0|  <<== Reset Values
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-- POWER_VCD  (0:VCD capture is off, 1:enable VCD capture)
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  +----- reserved
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  +-------- reserved
    ;   |  |  |  |  |  |  |  |  |  |  |  |  +----------- reserved
    ;   |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  +-------------- reserved
    ;   |  |  |  |  |  |  |  |  |  |  +----------------- reserved
    ;   |  |  |  |  |  |  |  |  |  +-------------------- reserved
    ;   |  |  |  |  |  |  |  |  +----------------------- reserved
    ;   |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  +-------------------------- reserved
    ;   |  |  |  |  |  |  +----------------------------- reserved
    ;   |  |  |  |  |  +-------------------------------- reserved
    ;   |  |  |  |  +----------------------------------- reserved
    ;   |  |  |  |
    ;   |  |  |  +-------------------------------------- reserved
    ;   |  |  +----------------------------------------- reserved
    ;   |  +-------------------------------------------- reserved
    ;   +----------------------------------------------- reserved

;----------------------------------------------------------------------------------------
;        Test Bench Driver Data for INTGEN Selection Bit Fields
;----------------------------------------------------------------------------------------
NMI_HIGH           .set    0b<<0        ; NMI high 
NMI_LOW            .set    1b<<0        ; NMI low
INT0_HIGH          .set    0b<<1        ; INT0 high 
INT0_LOW           .set    1b<<1        ; INT0 low
INT1_HIGH          .set    0b<<2        ; INT1 high 
INT1_LOW           .set    1b<<2        ; INT1 low
RESET_HIGH         .set    0b<<3        ; RESET high 
RESET_LOW          .set    1b<<3        ; RESET low
WAKEUP_LOW         .set    0b<<4        ; WAKEUP low
WAKEUP_HIGH        .set    1b<<4        ; WAKEUP high

; *******************************************************************************************
; *******************************************************************************************
; *****  SYSREG Registers:               (IO Space:  0x1C00 - 0x1CFF)
; *******************************************************************************************
; *******************************************************************************************
PERIPHSEL0              .set    0x1C00
    ; PERIPHSEL0   Address:  0x1C00 (IO Space)           PERIPHSEL0 (Peripheral Pin Mapping Register 0)
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ; |15:14:13:12|11:10: 9: 8| 7: 6: 5: 4| 3: 2: 1: 0|  <<== Bit Position
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; |rw:rw:rw:rw|rw:rw:rw:rw|rw:rw:rw:rw|rw:rw:rw:rw|  <<== Read / Write Access
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; | 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0|  <<== Reset Values
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-- [0]  SEL_GPIO21_nA15
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  +----- [1]  SEL_GPIO22_nA16
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  +-------- [2]  SEL_GPIO23_nA17
    ;   |  |  |  |  |  |  |  |  |  |  |  |  +----------- [3]  SEL_GPIO24_nA18
    ;   |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  +-------------- [4]  SEL_GPIO25_nA19
    ;   |  |  |  |  |  |  |  |  |  |  +----------------- [5]  SEL_GPIO26_nA20
    ;   |  |  |  |  |  |  |  |  |  +-------------------- [6]  reserved
    ;   |  |  |  |  |  |  |  |  +----------------------- [7]  reserved
    ;   |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  +-------------------------- [8]  SEL_S0[0]
    ;   |  |  |  |  |  |  +----------------------------- [9]  SEL_S0[1]
    ;   |  |  |  |  |  +-------------------------------- [10] SEL_S1[0]
    ;   |  |  |  |  +----------------------------------- [11] SEL_S1[1]
    ;   |  |  |  |
    ;   |  |  |  +-------------------------------------- [12] SEL_P[0]
    ;   |  |  +----------------------------------------- [13] SEL_P[1]
    ;   |  +-------------------------------------------- [14] SEL_P[2]
    ;   +----------------------------------------------- [15] reserved

    ; PERIPHSEL1   Address:  0x1C01 (IO Space)           PERIPHSEL1 (Peripheral Pin Mapping Register 1)
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ; |15:14:13:12|11:10: 9: 8| 7: 6: 5: 4| 3: 2: 1: 0|  <<== Bit Position
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; |r :r :r :r |r :r :r :r |r :r :r :r |r :r :r :r |  <<== Read / Write Access
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; | 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0|  <<== Reset Values
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-- [0]  reserved
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  +----- [1]  reserved
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  +-------- [2]  reserved
    ;   |  |  |  |  |  |  |  |  |  |  |  |  +----------- [3]  reserved
    ;   |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  +-------------- [4]  reserved
    ;   |  |  |  |  |  |  |  |  |  |  +----------------- [5]  reserved
    ;   |  |  |  |  |  |  |  |  |  +-------------------- [6]  reserved
    ;   |  |  |  |  |  |  |  |  +----------------------- [7]  reserved
    ;   |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  +-------------------------- [8]  reserved
    ;   |  |  |  |  |  |  +----------------------------- [9]  reserved
    ;   |  |  |  |  |  +-------------------------------- [10] reserved
    ;   |  |  |  |  +----------------------------------- [11] reserved
    ;   |  |  |  |
    ;   |  |  |  +-------------------------------------- [12] reserved
    ;   |  |  +----------------------------------------- [13] reserved
    ;   |  +-------------------------------------------- [14] reserved
    ;   +----------------------------------------------- [15] reserved
;----------------------------------------------------------------------------------------
;        Peripheral (External) Bus Selection Bit Fields
;----------------------------------------------------------------------------------------
A15_GPIO           .set    1b<<0        ; Enable Address pin 15 as GPIO 
A16_GPIO           .set    1b<<1        ; Enable Address pin 16 as GPIO 
A17_GPIO           .set    1b<<2        ; Enable Address pin 17 as GPIO 
A18_GPIO           .set    1b<<3        ; Enable Address pin 18 as GPIO 
A19_GPIO           .set    1b<<4        ; Enable Address pin 19 as GPIO 
A20_GPIO           .set    1b<<5        ; Enable Address pin 20 as GPIO 
S0_MMCSD0          .set    00b<<8       ; MMC/SD0 module routed to Serial Port 0 pins
S0_I2S0            .set    01b<<8       ; I2S0 routed to Serial Port 0 pins
S0_GPIO            .set    10b<<8       ; Serial Port 0 pins configured as GPIO
S1_MMCSD1          .set    00b<<10      ; MMC/SD1 module routed to Serial Port 1 pins
S1_I2S1            .set    01b<<10      ; I2S1 routed to Serial Port 1 pins
S1_GPIO            .set    10b<<10      ; Serial Port 1 pins configured as GPIO

PP_LCD             .set    000b<<12     ; 21 Parallel port pins configured as 16-bit LCD
PP_GPIO_SPI_UART_I2S2 .set 001b<<12     ; 6:GPIO + 7:SPI(CS-0,1,2,3) + 4:UART + 4:I2S2
PP_LCD_GPI0        .set    010b<<12     ; 10:8-bit LCD + 8:GPIO
PP_LCD_SPI_I2S3    .set    011b<<12     ; 10:8-bit LCD + 4:SPI(CS-0) + 4:I2S2
PP_LCD_UART_I2S2   .set    100b<<12     ; 10:8-bit LCD + 4:UART + 4:I2S2
PP_LCD_UART_SPI    .set    101b<<12     ; 10:8-bit LCD + 4:UART + 4:SPI(CS-0)
PP_GPIO_SPI_I2S2_3 .set    110b<<12     ; 6:GPIO + 7:SPI(CS-0,1,2,3) + 4:I2S2 + 4:I2S3
;----------------------------------------------------------------------------------------

IDLE_PCGCR              .set    0x1C02
    ; IDLE_PCGCR   Address:  0x1C02 (IO Space)           Peripheral Clock Gating Control Register LSW
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ; |15:14:13:12|11:10: 9: 8| 7: 6: 5: 4| 3: 2: 1: 0|  <<== Bit Position
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; |rw:rw:rw:rw|rw:rw:rw:rw|rw:rw:rw:rw|rw:rw:rw:rw|  <<== Read / Write Access
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; | 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0|  <<== Reset Values
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-- [0]  IIS3_IDLE         (0:clk active, 1:clk disabled)
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  +----- [1]  SPI_IDLE          (0:clk active, 1:clk disabled)
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  +-------- [2]  UART_IDLE         (0:clk active, 1:clk disabled)
    ;   |  |  |  |  |  |  |  |  |  |  |  |  +----------- [3]  DMA0_IDLE         (0:clk active, 1:clk disabled)
    ;   |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  +-------------- [4]  MMCSD0_IDLE       (0:clk active, 1:clk disabled)
    ;   |  |  |  |  |  |  |  |  |  |  +----------------- [5]  COPROC_IDLE       (0:clk active, 1:clk disabled)
    ;   |  |  |  |  |  |  |  |  |  +-------------------- [6]  I2C_IDLE          (0:clk active, 1:clk disabled)
    ;   |  |  |  |  |  |  |  |  +----------------------- [7]  MMCSD1_IDLE       (0:clk active, 1:clk disabled)
    ;   |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  +-------------------------- [8]  IIS0_IDLE         (0:clk active, 1:clk disabled)
    ;   |  |  |  |  |  |  +----------------------------- [9]  IIS1_IDLE         (0:clk active, 1:clk disabled)
    ;   |  |  |  |  |  +-------------------------------- [10] TIMER0_IDLE       (0:clk active, 1:clk disabled)
    ;   |  |  |  |  +----------------------------------- [11] EMIF_IDLE         (0:clk active, 1:clk disabled)
    ;   |  |  |  |
    ;   |  |  |  +-------------------------------------- [12] TIMER1_IDLE       (0:clk active, 1:clk disabled)
    ;   |  |  +----------------------------------------- [13] TIMER2_IDLE       (0:clk active, 1:clk disabled)
    ;   |  +-------------------------------------------- [14] IIS2_IDLE         (0:clk active, 1:clk disabled)
    ;   +----------------------------------------------- [15] MASTER_CLK_DIS    (0:Master clock active, 1:all clks disabled)

;----------------------------------------------------------------------------------------
;        IDLE_PCGCR         Bit Fields
;----------------------------------------------------------------------------------------
IIS3_IDLE           .set    1b<<0       ; IIS3 Idle Control Bit
SPI_IDLE            .set    1b<<1       ; SPI Idle Control Bit
UART_IDLE           .set    1b<<2       ; UART Control Bit
DMA0_IDLE           .set    1b<<3       ; DMA0 Idle Control Bit
MMCSD0_IDLE         .set    1b<<4       ; MMCSD0 Idle Control Bit
COPROC_IDLE         .set    1b<<5       ; CoProcessor Idle Control Bit
I2C_IDLE            .set    1b<<6       ; I2C Idle Control Bit
MMCSD1_IDLE         .set    1b<<7       ; MMCSD0 Idle Control Bit
IIS0_IDLE           .set    1b<<8       ; I2S0 Idle Control Bit
IIS1_IDLE           .set    1b<<9       ; I2S1 Idle Control Bit
TIMER0_IDLE         .set    1b<<10      ; Timer 0 Idle Control Bit
EMIF_IDLE           .set    1b<<11      ; EMIF Idle Control Bit
TIMER1_IDLE         .set    1b<<12      ; Timer 1 Module Clock off
TIMER2_IDLE         .set    1b<<13      ; Timer 2 Module Clock off
IIS2_IDLE           .set    1b<<14      ; IIS2 Idle Control Bit
OSC_DISABLE         .set    1b<<15      ; Oscillator disable      (cory: use of this name should be discontinued... use 'MASTER_CLK_DIS')
MASTER_CLK_DIS      .set    1b<<15      ; Disables clock to ALL domains (can only wake via: RTC alarms, WAKEUP, INT0, INT1, & RESET)
RESERVED_PCGCR      .set    0000000000000000b       ; Reserved bits (MSB --> LSB)

IDLE_PCGCR_MSW          .set    0x1C03
    ; IDLE_PCGCR_MSW   Address:  0x1C03 (IO Space)           Peripheral Clock Gating Control Register MSW
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ; |15:14:13:12|11:10: 9: 8| 7: 6: 5: 4| 3: 2: 1: 0|  <<== Bit Position
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; |r :r :r :r |r :r :r :r |r :r :rw:rw|rw:rw:rw:rw|  <<== Read / Write Access
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; | 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0|  <<== Reset Values
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-- [0]  LCD_CG        (0:active, 1:disabled)
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  +----- [1]  SAR_CG        (0:active, 1:disabled)
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  +-------- [2]  USB_CG        (0:active, 1:disabled)
    ;   |  |  |  |  |  |  |  |  |  |  |  |  +----------- [3]  DMA1_CG       (0:active, 1:disabled)
    ;   |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  +-------------- [4]  DMA2_CG       (0:active, 1:disabled)
    ;   |  |  |  |  |  |  |  |  |  |  +----------------- [5]  DMA3_CG       (0:active, 1:disabled)
    ;   |  |  |  |  |  |  |  |  |  +-------------------- [6]  ANAREG_CG     (0:active, 1:disabled) (note: SAR_CG==0 then this reg is ignored and the ANAREG clocks are forced ON).
    ;   |  |  |  |  |  |  |  |  +----------------------- [7]  reserved
    ;   |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  +-------------------------- [8]  reserved
    ;   |  |  |  |  |  |  +----------------------------- [9]  reserved
    ;   |  |  |  |  |  +-------------------------------- [10] reserved
    ;   |  |  |  |  +----------------------------------- [11] reserved
    ;   |  |  |  |
    ;   |  |  |  +-------------------------------------- [12] reserved
    ;   |  |  +----------------------------------------- [13] reserved
    ;   |  +-------------------------------------------- [14] reserved
    ;   +----------------------------------------------- [15] reserved

;----------------------------------------------------------------------------------------
;        IDLE_PCGCR_MSW         Bit Fields
;----------------------------------------------------------------------------------------
LCD_IDLE            .set    1b<<0       ; LCD Idle Control Bit
SARADC_IDLE         .set    1b<<1       ; SAR A/D Idle Control Bit
USB_IDLE            .set    1b<<2       ; USB Idle Control Bit
DMA1_IDLE           .set    1b<<3       ; DMA1 Idle Control Bit
DMA2_IDLE           .set    1b<<4       ; DMA2 Idle Control Bit
DMA3_IDLE           .set    1b<<5       ; DMA3 Idle Control Bit
ANAREG_IDLE         .set    1b<<6       ; ANAREG Idle Control Bit
RESERVED_PCGCR_MSW  .set    1111111110000000b       ; Reserved bits


PER_RSTCOUNT            .set    0x1C04
    ; PER_RSTCOUNT   Address:  0x1C04 (IO space)          Peripheral Software Reset Counter Register
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ; |15:14:13:12|11:10: 9: 8| 7: 6: 5: 4| 3: 2: 1: 0|  <<== Bit Position
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; |rw:rw:rw:rw|rw:rw:rw:rw|rw:rw:rw:rw|rw:rw:rw:rw|  <<== Read / Write Access
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; | 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0|  <<== Reset Values
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-- [0]  PeripheralsResetCount[0]
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  +----- [1]  PeripheralsResetCount[1]
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  +-------- [2]  PeripheralsResetCount[2]
    ;   |  |  |  |  |  |  |  |  |  |  |  |  +----------- [3]  PeripheralsResetCount[3]
    ;   |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  +-------------- [4]  PeripheralsResetCount[4]
    ;   |  |  |  |  |  |  |  |  |  |  +----------------- [5]  PeripheralsResetCount[5]
    ;   |  |  |  |  |  |  |  |  |  +-------------------- [6]  PeripheralsResetCount[6]
    ;   |  |  |  |  |  |  |  |  +----------------------- [7]  PeripheralsResetCount[7]
    ;   |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  +-------------------------- [8]  PeripheralsResetCount[8]
    ;   |  |  |  |  |  |  +----------------------------- [9]  PeripheralsResetCount[9]
    ;   |  |  |  |  |  +-------------------------------- [10] PeripheralsResetCount[10]
    ;   |  |  |  |  +----------------------------------- [11] PeripheralsResetCount[11]
    ;   |  |  |  |
    ;   |  |  |  +-------------------------------------- [12] PeripheralsResetCount[12]
    ;   |  |  +----------------------------------------- [13] PeripheralsResetCount[13]
    ;   |  +-------------------------------------------- [14] PeripheralsResetCount[14]
    ;   +----------------------------------------------- [15] PeripheralsResetCount[15]

PER_RESET               .set    0x1C05
    ; PER_RESET   Address:  0x1C05 (IO space)             Peripheral Reset Register
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ; |15:14:13:12|11:10: 9: 8| 7: 6: 5: 4| 3: 2: 1: 0|  <<== Bit Position
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; |rw:rw:rw:rw|rw:rw:rw:rw|rw:rw:rw:rw|rw:rw:rw:rw|  <<== Read / Write Access
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; | 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0|  <<== Reset Values
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+       Note:  Order matters.  Write to PeripheralsResetCount[15:0] first, then this register.
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |               ******* WRITES TO THIS REGISTER ********
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-- [0]  ResetEn_I2C                         (0:reset left not asserted, 1:reset asserted for count cycles (HoldInReset==0) or indefinitely (HoldInReset==1))
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  +----- [1]  ResetEn_EMIF_Timers_RTC             (0:reset left not asserted, 1:reset asserted for count cycles (HoldInReset==0) or indefinitely (HoldInReset==1))
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  +-------- [2]  ResetEn_Analog_SAR  (& TRIM!!!)     (0:reset left not asserted, 1:reset asserted for count cycles (HoldInReset==0) or indefinitely (HoldInReset==1)) (Customers should never reset this domain because of its effect on trim!!)
    ;   |  |  |  |  |  |  |  |  |  |  |  |  +----------- [3]  ResetEn_USB                         (0:reset left not asserted, 1:reset asserted for count cycles (HoldInReset==0) or indefinitely (HoldInReset==1))
    ;   |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  +-------------- [4]  ResetEn_DMA                         (0:reset left not asserted, 1:reset asserted for count cycles (HoldInReset==0) or indefinitely (HoldInReset==1))
    ;   |  |  |  |  |  |  |  |  |  |  +----------------- [5]  ResetEn_MMCSD0_MMCSD1_IIS0_IIS1     (0:reset left not asserted, 1:reset asserted for count cycles (HoldInReset==0) or indefinitely (HoldInReset==1))
    ;   |  |  |  |  |  |  |  |  |  +-------------------- [6]  ResetEn_FFTCOP                      (0:reset left not asserted, 1:reset asserted for count cycles (HoldInReset==0) or indefinitely (HoldInReset==1))
    ;   |  |  |  |  |  |  |  |  +----------------------- [7]  ResetEn_LCD_IIS2_IIS3_UART_SPI      (0:reset left not asserted, 1:reset asserted for count cycles (HoldInReset==0) or indefinitely (HoldInReset==1))
    ;   |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  +-------------------------- [8]  HoldInReset_I2C                     (0:hold in reset for PeripheralsResetCount[15:0] cycles, 1:hold in reset indefinitely)  (note ResetEn must also be written with a 1 to hold indefinitely)
    ;   |  |  |  |  |  |  +----------------------------- [9]  HoldInReset_EMIF_TIMERS_RTC         (0:hold in reset for PeripheralsResetCount[15:0] cycles, 1:hold in reset indefinitely)  (note ResetEn must also be written with a 1 to hold indefinitely)
    ;   |  |  |  |  |  +-------------------------------- [10] HoldInReset_Analog_SAR  (& TRIM!!!) (0:hold in reset for PeripheralsResetCount[15:0] cycles, 1:hold in reset indefinitely)  (note ResetEn must also be written with a 1 to hold indefinitely)
    ;   |  |  |  |  +----------------------------------- [11] HoldInReset_USB                     (0:hold in reset for PeripheralsResetCount[15:0] cycles, 1:hold in reset indefinitely)  (note ResetEn must also be written with a 1 to hold indefinitely)
    ;   |  |  |  |
    ;   |  |  |  +-------------------------------------- [12] HoldInReset_DMA                     (0:hold in reset for PeripheralsResetCount[15:0] cycles, 1:hold in reset indefinitely)  (note ResetEn must also be written with a 1 to hold indefinitely)
    ;   |  |  +----------------------------------------- [13] HoldInReset_MMCSD0_MMCSD1_IIS0_IIS1 (0:hold in reset for PeripheralsResetCount[15:0] cycles, 1:hold in reset indefinitely)  (note ResetEn must also be written with a 1 to hold indefinitely)
    ;   |  +-------------------------------------------- [14] HoldInReset_FFTCOP                  (0:hold in reset for PeripheralsResetCount[15:0] cycles, 1:hold in reset indefinitely)  (note ResetEn must also be written with a 1 to hold indefinitely)
    ;   +----------------------------------------------- [15] HoldInReset_LCD_IIS2_IIS3_UART_SPI  (0:hold in reset for PeripheralsResetCount[15:0] cycles, 1:hold in reset indefinitely)  (note ResetEn must also be written with a 1 to hold indefinitely)
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |               ******* READS FROM THIS REGISTER ********
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-- [0]  ResetState_I2C                      (read returns current state of peripheral's RESET REQUEST (0: not in reset, 1:peripheral is in reset))
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  +----- [1]  ResetState_EMIF_Timers_RTC          (read returns current state of peripheral's RESET REQUEST (0: not in reset, 1:peripheral is in reset))
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  +-------- [2]  ResetState_Analog_SAR               (read returns current state of peripheral's RESET REQUEST (0: not in reset, 1:peripheral is in reset))
    ;   |  |  |  |  |  |  |  |  |  |  |  |  +----------- [3]  ResetState_USB                      (read returns current state of peripheral's RESET REQUEST (0: not in reset, 1:peripheral is in reset))
    ;   |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  +-------------- [4]  ResetState_DMA                      (read returns current state of peripheral's RESET REQUEST (0: not in reset, 1:peripheral is in reset))
    ;   |  |  |  |  |  |  |  |  |  |  +----------------- [5]  ResetState_MMCSD0_MMCSD1_IIS0_IIS1  (read returns current state of peripheral's RESET REQUEST (0: not in reset, 1:peripheral is in reset))
    ;   |  |  |  |  |  |  |  |  |  +-------------------- [6]  ResetState_FFTCOP                   (read returns current state of peripheral's RESET REQUEST (0: not in reset, 1:peripheral is in reset))
    ;   |  |  |  |  |  |  |  |  +----------------------- [7]  ResetState_LCD_IIS2_IIS3_UART_SPI   (read returns current state of peripheral's RESET REQUEST (0: not in reset, 1:peripheral is in reset))
    ;   |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  +-------------------------- [8]  HoldInReset_I2C                     (read returns the value last written)
    ;   |  |  |  |  |  |  +----------------------------- [9]  HoldInReset_EMIF_Timers_RTC         (read returns the value last written)
    ;   |  |  |  |  |  +-------------------------------- [10] HoldInReset_Analog_SAR              (read returns the value last written)
    ;   |  |  |  |  +----------------------------------- [11] HoldInReset_USB                     
    ;   |  |  |  |
    ;   |  |  |  +-------------------------------------- [12] HoldInReset_DMA                     (read returns the value last written)
    ;   |  |  +----------------------------------------- [13] HoldInReset_MMCSD0_MMCSD1_IIS0_IIS1 (read returns the value last written)
    ;   |  +-------------------------------------------- [14] HoldInReset_FFTCOP                  (read returns the value last written)
    ;   +----------------------------------------------- [15] HoldInReset_LCD_IIS2_IIS3_UART_SPI  (read returns the value last written)

;----------------------------------------------------------------------------------------
;        PER_RESET      Bit Fields
;----------------------------------------------------------------------------------------
I2C_RST                         .set    1b<<0       ; I2C Reset Bit
;EMIF_UART_TIMER_I2S_RST        .set    1b<<1       ; EMIF, UART, Timers, and I2S Reset Bit
EMIF_TIMERS_RTC_RST             .set    1b<<1       ; EMIF_TIMERS_RTC Reset Bit
;ANALOG_RST                     .set    1b<<2       ; Analog Reset Bit
SAR_RST                         .set    1b<<2       ; SAR Reset Bit
USB_RST                         .set    1b<<3       ; USB Reset Bit
DMA_RST                         .set    1b<<4       ; DMA Reset Bit
;DMA0_RST                       .set    1b<<4       ; DMA0 Reset Bit
;DMA1_RST                       .set    1b<<5       ; DMA1 Reset Bit
MMCSD0_MMCSD1_IIS0_IIS1_RST     .set    1b<<5       ; MMCSD0_MMCSD1_IIS0_IIS1 Reset Bit
FFTCOP_RST                      .set    1b<<6       ; FFT CoProcessor Reset Bit
;SPI_RST                        .set    1b<<7       ; SPI Reset Bit
LCD_IIS2_IIS3_UART_SPI_RST      .set    1b<<7       ; LCD_IIS2_IIS3_UART_SPI Reset Bit



GPIO_DIR0               .set    0x1C06
GPIO_DIR                .set    0x1C06
    ; GPIO_DIR0/GPIO_DIR   Address:  0x1C06 (IO space)             GPIO Direction Register
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ; |15:14:13:12|11:10: 9: 8| 7: 6: 5: 4| 3: 2: 1: 0|  <<== Bit Position
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; |rw:rw:rw:rw|rw:rw:rw:rw|rw:rw:rw:rw|rw:rw:rw:rw|  <<== Read / Write Access
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; | 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0|  <<== Reset Values
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-- [0]  GPIO_DIR[0]   (0:gpio pin is an input, 1:gpio pin is an output)
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  +----- [1]  GPIO_DIR[1]   (0:gpio pin is an input, 1:gpio pin is an output)
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  +-------- [2]  GPIO_DIR[2]   (0:gpio pin is an input, 1:gpio pin is an output)
    ;   |  |  |  |  |  |  |  |  |  |  |  |  +----------- [3]  GPIO_DIR[3]   (0:gpio pin is an input, 1:gpio pin is an output)
    ;   |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  +-------------- [4]  GPIO_DIR[4]   (0:gpio pin is an input, 1:gpio pin is an output)
    ;   |  |  |  |  |  |  |  |  |  |  +----------------- [5]  GPIO_DIR[5]   (0:gpio pin is an input, 1:gpio pin is an output)
    ;   |  |  |  |  |  |  |  |  |  +-------------------- [6]  GPIO_DIR[6]   (0:gpio pin is an input, 1:gpio pin is an output)
    ;   |  |  |  |  |  |  |  |  +----------------------- [7]  GPIO_DIR[7]   (0:gpio pin is an input, 1:gpio pin is an output)
    ;   |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  +-------------------------- [8]  GPIO_DIR[8]   (0:gpio pin is an input, 1:gpio pin is an output)
    ;   |  |  |  |  |  |  +----------------------------- [9]  GPIO_DIR[9]   (0:gpio pin is an input, 1:gpio pin is an output)
    ;   |  |  |  |  |  +-------------------------------- [10] GPIO_DIR[10]  (0:gpio pin is an input, 1:gpio pin is an output)
    ;   |  |  |  |  +----------------------------------- [11] GPIO_DIR[11]  (0:gpio pin is an input, 1:gpio pin is an output)
    ;   |  |  |  |
    ;   |  |  |  +-------------------------------------- [12] GPIO_DIR[12]  (0:gpio pin is an input, 1:gpio pin is an output)
    ;   |  |  +----------------------------------------- [13] GPIO_DIR[13]  (0:gpio pin is an input, 1:gpio pin is an output)
    ;   |  +-------------------------------------------- [14] GPIO_DIR[14]  (0:gpio pin is an input, 1:gpio pin is an output)
    ;   +----------------------------------------------- [15] GPIO_DIR[15]  (0:gpio pin is an input, 1:gpio pin is an output)

GPIO_DIR1               .set    0x1C07
    ; GPIO_DIR1   Address:  0x1C07 (IO space)
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ; |15:14:13:12|11:10: 9: 8| 7: 6: 5: 4| 3: 2: 1: 0|  <<== Bit Position
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; |rw:rw:rw:rw|rw:rw:rw:rw|rw:rw:rw:rw|rw:rw:rw:rw|  <<== Read / Write Access
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; | 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0|  <<== Reset Values
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-- [0]  GPIO_DIR[16]  (0:gpio pin is an input, 1:gpio pin is an output)
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  +----- [1]  GPIO_DIR[17]  (0:gpio pin is an input, 1:gpio pin is an output)
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  +-------- [2]  GPIO_DIR[18]  (0:gpio pin is an input, 1:gpio pin is an output)
    ;   |  |  |  |  |  |  |  |  |  |  |  |  +----------- [3]  GPIO_DIR[19]  (0:gpio pin is an input, 1:gpio pin is an output)
    ;   |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  +-------------- [4]  GPIO_DIR[20]  (0:gpio pin is an input, 1:gpio pin is an output)
    ;   |  |  |  |  |  |  |  |  |  |  +----------------- [5]  GPIO_DIR[21]  (0:gpio pin is an input, 1:gpio pin is an output)
    ;   |  |  |  |  |  |  |  |  |  +-------------------- [6]  GPIO_DIR[22]  (0:gpio pin is an input, 1:gpio pin is an output)
    ;   |  |  |  |  |  |  |  |  +----------------------- [7]  GPIO_DIR[23]  (0:gpio pin is an input, 1:gpio pin is an output)
    ;   |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  +-------------------------- [8]  GPIO_DIR[24]  (0:gpio pin is an input, 1:gpio pin is an output)
    ;   |  |  |  |  |  |  +----------------------------- [9]  GPIO_DIR[25]  (0:gpio pin is an input, 1:gpio pin is an output)
    ;   |  |  |  |  |  +-------------------------------- [10] GPIO_DIR[26]  (0:gpio pin is an input, 1:gpio pin is an output)
    ;   |  |  |  |  +----------------------------------- [11] GPIO_DIR[27]  (0:gpio pin is an input, 1:gpio pin is an output)
    ;   |  |  |  |
    ;   |  |  |  +-------------------------------------- [12] GPIO_DIR[28]  (0:gpio pin is an input, 1:gpio pin is an output)
    ;   |  |  +----------------------------------------- [13] GPIO_DIR[29]  (0:gpio pin is an input, 1:gpio pin is an output)
    ;   |  +-------------------------------------------- [14] GPIO_DIR[30]  (0:gpio pin is an input, 1:gpio pin is an output)
    ;   +----------------------------------------------- [15] GPIO_DIR[31]  (0:gpio pin is an input, 1:gpio pin is an output)




GPIO_DIN0               .set    0x1C08
GPIO_DIN                .set    0x1C08
    ; GPIO_DIN0/GPIO_DIN   Address:  0x1C08 (IO space)             GPIO Data In Register
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ; |15:14:13:12|11:10: 9: 8| 7: 6: 5: 4| 3: 2: 1: 0|  <<== Bit Position
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; |r :r :r :r |r :r :r :r |r :r :r :r |r :r :r :r |  <<== Read / Write Access
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; | ?: ?: ?: ?| ?: ?: ?: ?| ?: ?: ?: ?| ?: ?: ?: ?|  <<== Reset Values
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-- [0]  GPIO_DIN[0]   data in value
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  +----- [1]  GPIO_DIN[1]   data in value
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  +-------- [2]  GPIO_DIN[2]   data in value
    ;   |  |  |  |  |  |  |  |  |  |  |  |  +----------- [3]  GPIO_DIN[3]   data in value
    ;   |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  +-------------- [4]  GPIO_DIN[4]   data in value
    ;   |  |  |  |  |  |  |  |  |  |  +----------------- [5]  GPIO_DIN[5]   data in value
    ;   |  |  |  |  |  |  |  |  |  +-------------------- [6]  GPIO_DIN[6]   data in value
    ;   |  |  |  |  |  |  |  |  +----------------------- [7]  GPIO_DIN[7]   data in value
    ;   |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  +-------------------------- [8]  GPIO_DIN[8]   data in value
    ;   |  |  |  |  |  |  +----------------------------- [9]  GPIO_DIN[9]   data in value
    ;   |  |  |  |  |  +-------------------------------- [10] GPIO_DIN[10]  data in value
    ;   |  |  |  |  +----------------------------------- [11] GPIO_DIN[11]  data in value
    ;   |  |  |  |
    ;   |  |  |  +-------------------------------------- [12] GPIO_DIN[12]  data in value
    ;   |  |  +----------------------------------------- [13] GPIO_DIN[13]  data in value
    ;   |  +-------------------------------------------- [14] GPIO_DIN[14]  data in value
    ;   +----------------------------------------------- [15] GPIO_DIN[15]  data in value

GPIO_DIN1               .set    0x1C09
    ; GPIO_DIN1   Address:  0x1C09 (IO space)
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ; |15:14:13:12|11:10: 9: 8| 7: 6: 5: 4| 3: 2: 1: 0|  <<== Bit Position
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; |r :r :r :r |r :r :r :r |r :r :r :r |r :r :r :r |  <<== Read / Write Access
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; | ?: ?: ?: ?| ?: ?: ?: ?| ?: ?: ?: ?| ?: ?: ?: ?|  <<== Reset Values
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-- [0]  GPIO_DIN[16]  data in value
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  +----- [1]  GPIO_DIN[17]  data in value
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  +-------- [2]  GPIO_DIN[18]  data in value
    ;   |  |  |  |  |  |  |  |  |  |  |  |  +----------- [3]  GPIO_DIN[19]  data in value
    ;   |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  +-------------- [4]  GPIO_DIN[20]  data in value
    ;   |  |  |  |  |  |  |  |  |  |  +----------------- [5]  GPIO_DIN[21]  data in value
    ;   |  |  |  |  |  |  |  |  |  +-------------------- [6]  GPIO_DIN[22]  data in value
    ;   |  |  |  |  |  |  |  |  +----------------------- [7]  GPIO_DIN[23]  data in value
    ;   |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  +-------------------------- [8]  GPIO_DIN[24]  data in value
    ;   |  |  |  |  |  |  +----------------------------- [9]  GPIO_DIN[25]  data in value
    ;   |  |  |  |  |  +-------------------------------- [10] GPIO_DIN[26]  data in value
    ;   |  |  |  |  +----------------------------------- [11] GPIO_DIN[27]  data in value
    ;   |  |  |  |
    ;   |  |  |  +-------------------------------------- [12] GPIO_DIN[28]  data in value
    ;   |  |  +----------------------------------------- [13] GPIO_DIN[29]  data in value
    ;   |  +-------------------------------------------- [14] GPIO_DIN[30]  data in value
    ;   +----------------------------------------------- [15] GPIO_DIN[31]  data in value


GPIO_DOUT0              .set    0x1C0A
GPIO_DOUT               .set    0x1C0A
    ; GPIO_DOUT0/GPIO_DOUT   Address:  0x1C0A (IO space)  GPIO Data Out Register 0
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ; |15:14:13:12|11:10: 9: 8| 7: 6: 5: 4| 3: 2: 1: 0|  <<== Bit Position
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; |rw:rw:rw:rw|rw:rw:rw:rw|rw:rw:rw:rw|rw:rw:rw:rw|  <<== Read / Write Access
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; | 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0|  <<== Reset Values
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-- [0]  GPIO_DOUT[0]   data out value
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  +----- [1]  GPIO_DOUT[1]   data out value
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  +-------- [2]  GPIO_DOUT[2]   data out value
    ;   |  |  |  |  |  |  |  |  |  |  |  |  +----------- [3]  GPIO_DOUT[3]   data out value
    ;   |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  +-------------- [4]  GPIO_DOUT[4]   data out value
    ;   |  |  |  |  |  |  |  |  |  |  +----------------- [5]  GPIO_DOUT[5]   data out value
    ;   |  |  |  |  |  |  |  |  |  +-------------------- [6]  GPIO_DOUT[6]   data out value
    ;   |  |  |  |  |  |  |  |  +----------------------- [7]  GPIO_DOUT[7]   data out value
    ;   |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  +-------------------------- [8]  GPIO_DOUT[8]   data out value
    ;   |  |  |  |  |  |  +----------------------------- [9]  GPIO_DOUT[9]   data out value
    ;   |  |  |  |  |  +-------------------------------- [10] GPIO_DOUT[10]  data out value
    ;   |  |  |  |  +----------------------------------- [11] GPIO_DOUT[11]  data out value
    ;   |  |  |  |
    ;   |  |  |  +-------------------------------------- [12] GPIO_DOUT[12]  data out value
    ;   |  |  +----------------------------------------- [13] GPIO_DOUT[13]  data out value
    ;   |  +-------------------------------------------- [14] GPIO_DOUT[14]  data out value
    ;   +----------------------------------------------- [15] GPIO_DOUT[15]  data out value

GPIO_DOUT1              .set    0x1C0B
    ; GPIO_DOUT1   Address:  0x1C0B (IO space)           GPIO Data Out Register 1
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ; |15:14:13:12|11:10: 9: 8| 7: 6: 5: 4| 3: 2: 1: 0|  <<== Bit Position
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; |rw:rw:rw:rw|rw:rw:rw:rw|rw:rw:rw:rw|rw:rw:rw:rw|  <<== Read / Write Access
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; | 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0|  <<== Reset Values
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-- [0]  GPIO_DOUT[16]  data out value
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  +----- [1]  GPIO_DOUT[17]  data out value
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  +-------- [2]  GPIO_DOUT[18]  data out value
    ;   |  |  |  |  |  |  |  |  |  |  |  |  +----------- [3]  GPIO_DOUT[19]  data out value
    ;   |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  +-------------- [4]  GPIO_DOUT[20]  data out value
    ;   |  |  |  |  |  |  |  |  |  |  +----------------- [5]  GPIO_DOUT[21]  data out value
    ;   |  |  |  |  |  |  |  |  |  +-------------------- [6]  GPIO_DOUT[22]  data out value
    ;   |  |  |  |  |  |  |  |  +----------------------- [7]  GPIO_DOUT[23]  data out value
    ;   |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  +-------------------------- [8]  GPIO_DOUT[24]  data out value
    ;   |  |  |  |  |  |  +----------------------------- [9]  GPIO_DOUT[25]  data out value
    ;   |  |  |  |  |  +-------------------------------- [10] GPIO_DOUT[26]  data out value
    ;   |  |  |  |  +----------------------------------- [11] GPIO_DOUT[11]  data out value
    ;   |  |  |  |
    ;   |  |  |  +-------------------------------------- [12] GPIO_DOUT[12]  data out value
    ;   |  |  +----------------------------------------- [13] GPIO_DOUT[13]  data out value
    ;   |  +-------------------------------------------- [14] GPIO_DOUT[14]  data out value
    ;   +----------------------------------------------- [15] GPIO_DOUT[15]  data out value


GPIO_INTEDGE0           .set    0x1C0C
GPIO_INTTRIG            .set    0x1C0C
    ; GPIO_INTEDGE0/GPIO_INTTRIG   Address:  0x1C0C (IO space)    GPIO Interrupt Edge Trigger Register 0
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ; |15:14:13:12|11:10: 9: 8| 7: 6: 5: 4| 3: 2: 1: 0|  <<== Bit Position
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; |rw:rw:rw:rw|rw:rw:rw:rw|rw:rw:rw:rw|rw:rw:rw:rw|  <<== Read / Write Access
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; | 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0|  <<== Reset Values
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-- [0]  GPIO_INTEDGE[0]   (0:gpio pin rising edge triggered, 1:gpio pin falling edge triggered)
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  +----- [1]  GPIO_INTEDGE[1]   (0:gpio pin rising edge triggered, 1:gpio pin falling edge triggered)
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  +-------- [2]  GPIO_INTEDGE[2]   (0:gpio pin rising edge triggered, 1:gpio pin falling edge triggered)
    ;   |  |  |  |  |  |  |  |  |  |  |  |  +----------- [3]  GPIO_INTEDGE[3]   (0:gpio pin rising edge triggered, 1:gpio pin falling edge triggered)
    ;   |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  +-------------- [4]  GPIO_INTEDGE[4]   (0:gpio pin rising edge triggered, 1:gpio pin falling edge triggered)
    ;   |  |  |  |  |  |  |  |  |  |  +----------------- [5]  GPIO_INTEDGE[5]   (0:gpio pin rising edge triggered, 1:gpio pin falling edge triggered)
    ;   |  |  |  |  |  |  |  |  |  +-------------------- [6]  GPIO_INTEDGE[6]   (0:gpio pin rising edge triggered, 1:gpio pin falling edge triggered)
    ;   |  |  |  |  |  |  |  |  +----------------------- [7]  GPIO_INTEDGE[7]   (0:gpio pin rising edge triggered, 1:gpio pin falling edge triggered)
    ;   |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  +-------------------------- [8]  GPIO_INTEDGE[8]   (0:gpio pin rising edge triggered, 1:gpio pin falling edge triggered)
    ;   |  |  |  |  |  |  +----------------------------- [9]  GPIO_INTEDGE[9]   (0:gpio pin rising edge triggered, 1:gpio pin falling edge triggered)
    ;   |  |  |  |  |  +-------------------------------- [10] GPIO_INTEDGE[10]  (0:gpio pin rising edge triggered, 1:gpio pin falling edge triggered)
    ;   |  |  |  |  +----------------------------------- [11] GPIO_INTEDGE[11]  (0:gpio pin rising edge triggered, 1:gpio pin falling edge triggered)
    ;   |  |  |  |
    ;   |  |  |  +-------------------------------------- [12] GPIO_INTEDGE[12]  (0:gpio pin rising edge triggered, 1:gpio pin falling edge triggered)
    ;   |  |  +----------------------------------------- [13] GPIO_INTEDGE[13]  (0:gpio pin rising edge triggered, 1:gpio pin falling edge triggered)
    ;   |  +-------------------------------------------- [14] GPIO_INTEDGE[14]  (0:gpio pin rising edge triggered, 1:gpio pin falling edge triggered)
    ;   +----------------------------------------------- [15] GPIO_INTEDGE[15]  (0:gpio pin rising edge triggered, 1:gpio pin falling edge triggered)

GPIO_INTEDGE1           .set    0x1C0D
    ; GPIO_INTEDGE1   Address:  0x1C0D (IO space)         GPIO Interrupt Edge Trigger Register 1
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ; |15:14:13:12|11:10: 9: 8| 7: 6: 5: 4| 3: 2: 1: 0|   <<== Bit Position
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; |rw:rw:rw:rw|rw:rw:rw:rw|rw:rw:rw:rw|rw:rw:rw:rw|   <<== Read / Write Access
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; | 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0|  <<== Reset Values
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-- [0]  GPIO_INTEDGE[16]  (0:gpio pin rising edge triggered, 1:gpio pin falling edge triggered)
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  +----- [1]  GPIO_INTEDGE[17]  (0:gpio pin rising edge triggered, 1:gpio pin falling edge triggered)
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  +-------- [2]  GPIO_INTEDGE[18]  (0:gpio pin rising edge triggered, 1:gpio pin falling edge triggered)
    ;   |  |  |  |  |  |  |  |  |  |  |  |  +----------- [3]  GPIO_INTEDGE[19]  (0:gpio pin rising edge triggered, 1:gpio pin falling edge triggered)
    ;   |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  +-------------- [4]  GPIO_INTEDGE[20]  (0:gpio pin rising edge triggered, 1:gpio pin falling edge triggered)
    ;   |  |  |  |  |  |  |  |  |  |  +----------------- [5]  GPIO_INTEDGE[21]  (0:gpio pin rising edge triggered, 1:gpio pin falling edge triggered)
    ;   |  |  |  |  |  |  |  |  |  +-------------------- [6]  GPIO_INTEDGE[22]  (0:gpio pin rising edge triggered, 1:gpio pin falling edge triggered)
    ;   |  |  |  |  |  |  |  |  +----------------------- [7]  GPIO_INTEDGE[23]  (0:gpio pin rising edge triggered, 1:gpio pin falling edge triggered)
    ;   |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  +-------------------------- [8]  GPIO_INTEDGE[24]  (0:gpio pin rising edge triggered, 1:gpio pin falling edge triggered)
    ;   |  |  |  |  |  |  +----------------------------- [9]  GPIO_INTEDGE[25]  (0:gpio pin rising edge triggered, 1:gpio pin falling edge triggered)
    ;   |  |  |  |  |  +-------------------------------- [10] GPIO_INTEDGE[26]  (0:gpio pin rising edge triggered, 1:gpio pin falling edge triggered)
    ;   |  |  |  |  +----------------------------------- [11] GPIO_INTEDGE[27]  (0:gpio pin rising edge triggered, 1:gpio pin falling edge triggered)
    ;   |  |  |  |
    ;   |  |  |  +-------------------------------------- [12] GPIO_INTEDGE[28]  (0:gpio pin rising edge triggered, 1:gpio pin falling edge triggered)
    ;   |  |  +----------------------------------------- [13] GPIO_INTEDGE[29]  (0:gpio pin rising edge triggered, 1:gpio pin falling edge triggered)
    ;   |  +-------------------------------------------- [14] GPIO_INTEDGE[30]  (0:gpio pin rising edge triggered, 1:gpio pin falling edge triggered)
    ;   +----------------------------------------------- [15] GPIO_INTEDGE[31]  (0:gpio pin rising edge triggered, 1:gpio pin falling edge triggered)



GPIO_IER0               .set    0x1C0E
GPIO_INTEN              .set    0x1C0E
    ; GPIO_IER0/GPIO_INTEN   Address:  0x1C0E (IO space)  GPIO Interrupt Enable Register 0
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ; |15:14:13:12|11:10: 9: 8| 7: 6: 5: 4| 3: 2: 1: 0|  <<== Bit Position
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; |rw:rw:rw:rw|rw:rw:rw:rw|rw:rw:rw:rw|rw:rw:rw:rw|  <<== Read / Write Access
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; | 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0|  <<== Reset Values
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-- [0]  GPIO_IER[0]   (0:no interrupt, 1:interrupt generated)
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  +----- [1]  GPIO_IER[1]   (0:no interrupt, 1:interrupt generated)
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  +-------- [2]  GPIO_IER[2]   (0:no interrupt, 1:interrupt generated)
    ;   |  |  |  |  |  |  |  |  |  |  |  |  +----------- [3]  GPIO_IER[3]   (0:no interrupt, 1:interrupt generated)
    ;   |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  +-------------- [4]  GPIO_IER[4]   (0:no interrupt, 1:interrupt generated)
    ;   |  |  |  |  |  |  |  |  |  |  +----------------- [5]  GPIO_IER[5]   (0:no interrupt, 1:interrupt generated)
    ;   |  |  |  |  |  |  |  |  |  +-------------------- [6]  GPIO_IER[6]   (0:no interrupt, 1:interrupt generated)
    ;   |  |  |  |  |  |  |  |  +----------------------- [7]  GPIO_IER[7]   (0:no interrupt, 1:interrupt generated)
    ;   |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  +-------------------------- [8]  GPIO_IER[8]   (0:no interrupt, 1:interrupt generated)
    ;   |  |  |  |  |  |  +----------------------------- [9]  GPIO_IER[9]   (0:no interrupt, 1:interrupt generated)
    ;   |  |  |  |  |  +-------------------------------- [10] GPIO_IER[10]  (0:no interrupt, 1:interrupt generated)
    ;   |  |  |  |  +----------------------------------- [11] GPIO_IER[11]  (0:no interrupt, 1:interrupt generated)
    ;   |  |  |  |
    ;   |  |  |  +-------------------------------------- [12] GPIO_IER[12]  (0:no interrupt, 1:interrupt generated)
    ;   |  |  +----------------------------------------- [13] GPIO_IER[13]  (0:no interrupt, 1:interrupt generated)
    ;   |  +-------------------------------------------- [14] GPIO_IER[14]  (0:no interrupt, 1:interrupt generated)
    ;   +----------------------------------------------- [15] GPIO_IER[15]  (0:no interrupt, 1:interrupt generated)

GPIO_IER1               .set    0x1C0F
    ; GPIO_IER1   Address:  0x1C0F (IO space)             GPIO Interrupt Enable Register 1
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ; |15:14:13:12|11:10: 9: 8| 7: 6: 5: 4| 3: 2: 1: 0|  <<== Bit Position
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; |rw:rw:rw:rw|rw:rw:rw:rw|rw:rw:rw:rw|rw:rw:rw:rw|  <<== Read / Write Access
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; | 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0|  <<== Reset Values
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-- [0]  GPIO_IER[16]  (0:no interrupt, 1:interrupt generated)
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  +----- [1]  GPIO_IER[17]  (0:no interrupt, 1:interrupt generated)
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  +-------- [2]  GPIO_IER[18]  (0:no interrupt, 1:interrupt generated)
    ;   |  |  |  |  |  |  |  |  |  |  |  |  +----------- [3]  GPIO_IER[19]  (0:no interrupt, 1:interrupt generated)
    ;   |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  +-------------- [4]  GPIO_IER[20]  (0:no interrupt, 1:interrupt generated)
    ;   |  |  |  |  |  |  |  |  |  |  +----------------- [5]  GPIO_IER[21]  (0:no interrupt, 1:interrupt generated)
    ;   |  |  |  |  |  |  |  |  |  +-------------------- [6]  GPIO_IER[22]  (0:no interrupt, 1:interrupt generated)
    ;   |  |  |  |  |  |  |  |  +----------------------- [7]  GPIO_IER[23]  (0:no interrupt, 1:interrupt generated)
    ;   |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  +-------------------------- [8]  GPIO_IER[24]  (0:no interrupt, 1:interrupt generated)
    ;   |  |  |  |  |  |  +----------------------------- [9]  GPIO_IER[25]  (0:no interrupt, 1:interrupt generated)
    ;   |  |  |  |  |  +-------------------------------- [10] GPIO_IER[26]  (0:no interrupt, 1:interrupt generated)
    ;   |  |  |  |  +----------------------------------- [11] GPIO_IER[27]  (0:no interrupt, 1:interrupt generated)
    ;   |  |  |  |
    ;   |  |  |  +-------------------------------------- [12] GPIO_IER[28]  (0:no interrupt, 1:interrupt generated)
    ;   |  |  +----------------------------------------- [13] GPIO_IER[29]  (0:no interrupt, 1:interrupt generated)
    ;   |  +-------------------------------------------- [14] GPIO_IER[30]  (0:no interrupt, 1:interrupt generated)
    ;   +----------------------------------------------- [15] GPIO_IER[31]  (0:no interrupt, 1:interrupt generated)



GPIO_IFR0               .set    0x1C10
GPIO_INTF               .set    0x1C10
    ; GPIO_IFR0/GPIO_INTF   Address:  0x1C10 (IO space)   GPIO Interrupt Flag Register 0
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ; |15:14:13:12|11:10: 9: 8| 7: 6: 5: 4| 3: 2: 1: 0|  <<== Bit Position
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; |rw:rw:rw:rw|rw:rw:rw:rw|rw:rw:rw:rw|rw:rw:rw:rw|  <<== Read / Write Access
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; | 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0|  <<== Reset Values
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |   (Writing a '1' clears the bit; writing a '0' has no effect)
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-- [0]  GPIO_IFR[0]   (0:no interrupt occurred, 1:interrupt occured)
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  +----- [1]  GPIO_IFR[1]   (0:no interrupt occurred, 1:interrupt occured)
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  +-------- [2]  GPIO_IFR[2]   (0:no interrupt occurred, 1:interrupt occured)
    ;   |  |  |  |  |  |  |  |  |  |  |  |  +----------- [3]  GPIO_IFR[3]   (0:no interrupt occurred, 1:interrupt occured)
    ;   |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  +-------------- [4]  GPIO_IFR[4]   (0:no interrupt occurred, 1:interrupt occured)
    ;   |  |  |  |  |  |  |  |  |  |  +----------------- [5]  GPIO_IFR[5]   (0:no interrupt occurred, 1:interrupt occured)
    ;   |  |  |  |  |  |  |  |  |  +-------------------- [6]  GPIO_IFR[6]   (0:no interrupt occurred, 1:interrupt occured)
    ;   |  |  |  |  |  |  |  |  +----------------------- [7]  GPIO_IFR[7]   (0:no interrupt occurred, 1:interrupt occured)
    ;   |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  +-------------------------- [8]  GPIO_IFR[8]   (0:no interrupt occurred, 1:interrupt occured)
    ;   |  |  |  |  |  |  +----------------------------- [9]  GPIO_IFR[9]   (0:no interrupt occurred, 1:interrupt occured)
    ;   |  |  |  |  |  +-------------------------------- [10] GPIO_IFR[10]  (0:no interrupt occurred, 1:interrupt occured)
    ;   |  |  |  |  +----------------------------------- [11] GPIO_IFR[11]  (0:no interrupt occurred, 1:interrupt occured)
    ;   |  |  |  |
    ;   |  |  |  +-------------------------------------- [12] GPIO_IFR[12]  (0:no interrupt occurred, 1:interrupt occured)
    ;   |  |  +----------------------------------------- [13] GPIO_IFR[13]  (0:no interrupt occurred, 1:interrupt occured)
    ;   |  +-------------------------------------------- [14] GPIO_IFR[14]  (0:no interrupt occurred, 1:interrupt occured)
    ;   +----------------------------------------------- [15] GPIO_IFR[15]  (0:no interrupt occurred, 1:interrupt occured)

GPIO_IFR1               .set    0x1C11
    ; GPIO_IFR1   Address:  0x1C11 (IO space)            GPIO Interrupt Flag Register 1
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ; |15:14:13:12|11:10: 9: 8| 7: 6: 5: 4| 3: 2: 1: 0|  <<== Bit Position
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; |rw:rw:rw:rw|rw:rw:rw:rw|rw:rw:rw:rw|rw:rw:rw:rw|  <<== Read / Write Access
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; | ?: ?: ?: ?| ?: ?: ?: ?| ?: ?: ?: ?| ?: ?: ?: ?|  <<== Reset Values
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |   (Writing a '1' clears the bit; writing a '0' has no effect)
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-- [0]  GPIO_IFR[16]  (0:no interrupt occurred, 1:interrupt occured)
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  +----- [1]  GPIO_IFR[17]  (0:no interrupt occurred, 1:interrupt occured)
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  +-------- [2]  GPIO_IFR[18]  (0:no interrupt occurred, 1:interrupt occured)
    ;   |  |  |  |  |  |  |  |  |  |  |  |  +----------- [3]  GPIO_IFR[19]  (0:no interrupt occurred, 1:interrupt occured)
    ;   |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  +-------------- [4]  GPIO_IFR[20]  (0:no interrupt occurred, 1:interrupt occured)
    ;   |  |  |  |  |  |  |  |  |  |  +----------------- [5]  GPIO_IFR[21]  (0:no interrupt occurred, 1:interrupt occured)
    ;   |  |  |  |  |  |  |  |  |  +-------------------- [6]  GPIO_IFR[22]  (0:no interrupt occurred, 1:interrupt occured)
    ;   |  |  |  |  |  |  |  |  +----------------------- [7]  GPIO_IFR[23]  (0:no interrupt occurred, 1:interrupt occured)
    ;   |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  +-------------------------- [8]  GPIO_IFR[24]  (0:no interrupt occurred, 1:interrupt occured)
    ;   |  |  |  |  |  |  +----------------------------- [9]  GPIO_IFR[25]  (0:no interrupt occurred, 1:interrupt occured)
    ;   |  |  |  |  |  +-------------------------------- [10] GPIO_IFR[26]  (0:no interrupt occurred, 1:interrupt occured)
    ;   |  |  |  |  +----------------------------------- [11] GPIO_IFR[27]  (0:no interrupt occurred, 1:interrupt occured)
    ;   |  |  |  |
    ;   |  |  |  +-------------------------------------- [12] GPIO_IFR[28]  (0:no interrupt occurred, 1:interrupt occured)
    ;   |  |  +----------------------------------------- [13] GPIO_IFR[29]  (0:no interrupt occurred, 1:interrupt occured)
    ;   |  +-------------------------------------------- [14] GPIO_IFR[30]  (0:no interrupt occurred, 1:interrupt occured)
    ;   +----------------------------------------------- [15] GPIO_IFR[31]  (0:no interrupt occurred, 1:interrupt occured)


   
EMIF25_BASE		.set 	0x1000	; EMIF 25 base address

EMIF25_RCSR_OFFSET	.set	0x00	; EMIF25 Revision Code and Status Register 	  
EMIF25_RCSR_0		.set 	EMIF25_BASE + EMIF25_RCSR_OFFSET
EMIF25_RCSR_1		.set	EMIF25_RCSR_0 + 1

EMIF25_ASYNC_WAIT_OFFSET .set	0x04	; EMIF25 Async Wait Cycle Config Register
EMIF25_ASYNC_WAIT_0	.set	EMIF25_BASE + EMIF25_ASYNC_WAIT_OFFSET
EMIF25_ASYNC_WAIT_1	.set	EMIF25_ASYNC_WAIT_0 + 1

EMIF25_SDRAM_CR_OFFSET	.set	0x08	; SDRAM Config Register
EMIF25_SDRAM_CR_0	.set	EMIF25_BASE + EMIF25_SDRAM_CR_OFFSET
EMIF25_SDRAM_CR_1	.set	EMIF25_SDRAM_CR_0 + 1

EMIF25_SDRAM_RCR_OFFSET	.set	0x0C	; SDRAM Refresh Control Register
EMIF25_SDRAM_RCR_0	.set	EMIF25_BASE + EMIF25_SDRAM_RCR_OFFSET
EMIF25_SDRAM_RCR_1	.set	EMIF25_SDRAM_RCR_0 + 1

EMIF25_ASYNC1_CR_OFFSET	.set	0x010	; Async1 Config Register
EMIF25_ASYNC1_CR_0	.set	EMIF25_BASE + EMIF25_ASYNC1_CR_OFFSET
EMIF25_ASYNC1_CR_1	.set	EMIF25_ASYNC1_CR_0 + 1

EMIF25_ASYNC2_CR_OFFSET	.set	0x14	; Async2 Config Register
EMIF25_ASYNC2_CR_0	.set	EMIF25_BASE + EMIF25_ASYNC2_CR_OFFSET
EMIF25_ASYNC2_CR_1	.set	EMIF25_ASYNC2_CR_0 + 1

EMIF25_ASYNC3_CR_OFFSET	.set	0x18	; Async3 Config Register
EMIF25_ASYNC3_CR_0	.set	EMIF25_BASE + EMIF25_ASYNC3_CR_OFFSET
EMIF25_ASYNC3_CR_1	.set	EMIF25_ASYNC3_CR_0 + 1

    ; EMIF25_ASYNC4_CR_0   Address:  0x101C (IO space)            ASYNC4 Config Register LSW
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ; |15:14:13:12|11:10: 9: 8| 7: 6: 5: 4| 3: 2: 1: 0|  <<== Bit Position
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; |rw:rw:rw:rw|rw:rw:rw:rw|rw:rw:rw:rw|rw:rw:rw:rw|  <<== Read / Write Access
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; | 1: 1: 1: 1| 1: 1: 1: 1| 1: 1: 1: 1| 1: 1: 0: 1|  <<== Reset Values
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-- [0]  asize[0]      Defines the width of the data bus.  0: 8bit, 1: 16bit, 2:reserved, 3:reserved.
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  +----- [1]  asize[1]
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  +-------- [2]  ta[0]         Turn around cycles.  Number of emif_clock cycles between the end of one async access and another, minus one cycle.
    ;   |  |  |  |  |  |  |  |  |  |  |  |  +----------- [3]  ta[1]         This delay is not incurred between back-to-back reads or back-to-back writes within the same chip select.
    ;   |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  +-------------- [4]  r_hold[0]     Read Strobe Hold cycles.  Number of emif_clock cycles for which A, BA, DQM,
    ;   |  |  |  |  |  |  |  |  |  |  +----------------- [5]  r_hold[1]     and chip select pins are held after OE has been deasserted, minus one cycle.
    ;   |  |  |  |  |  |  |  |  |  +-------------------- [6]  r_hold[2]
    ;   |  |  |  |  |  |  |  |  +----------------------- [7]  r_strobe[0]   Read strobe Duration cycles.  Number of emif_clock cycles for which OE
    ;   |  |  |  |  |  |  |  |                                              pin is held active, minus one cycle.  This field cannot be zero when ew=1.
    ;   |  |  |  |  |  |  |  +-------------------------- [8]  r_strobe[1]
    ;   |  |  |  |  |  |  +----------------------------- [9]  r_strobe[2]
    ;   |  |  |  |  |  +-------------------------------- [10] r_strobe[3]
    ;   |  |  |  |  +----------------------------------- [11] r_strobe[4]
    ;   |  |  |  |
    ;   |  |  |  +-------------------------------------- [12] r_strobe[5]
    ;   |  |  +----------------------------------------- [13] r_setup[0]    Read Strobe Setup cycles.  Number of emif_clock cycles from A, BA, DQM, and
    ;   |  +-------------------------------------------- [14] r_setup[1]    chip select pins being set to OE pin asserted, minus one cycle.
    ;   +----------------------------------------------- [15] r_setup[2]

    ; EMIF25_ASYNC4_CR_1   Address:  0x101D (IO space)            ASYNC4 Config Register MSW
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ; |15:14:13:12|11:10: 9: 8| 7: 6: 5: 4| 3: 2: 1: 0|  <<== Bit Position
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; |rw:rw:rw:rw|rw:rw:rw:rw|rw:rw:rw:rw|rw:rw:rw:rw|  <<== Read / Write Access
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; | 0: 0: 1: 1| 1: 1: 1: 1| 1: 1: 1: 1| 1: 1: 1: 1|  <<== Reset Values
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-- [0]  r_setup[3]
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  +----- [1]  w_hold[0]     Write Strobe Hold cycles.  Number of emif_clock cycles for which A, BA, D, DQM, 
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  +-------- [2]  w_hold[1]     and chip select pins are held after WE has been deasserted, minus one cycle.
    ;   |  |  |  |  |  |  |  |  |  |  |  |  +----------- [3]  w_hold[2]
    ;   |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  +-------------- [4]  w_strobe[0]   Write Strobe Duration cycles.  Number of emif_clock cycles for which WE is held 
    ;   |  |  |  |  |  |  |  |  |  |  +----------------- [5]  w_strobe[1]   active, minus one cycle.  This field cannot be zero when ew=1.
    ;   |  |  |  |  |  |  |  |  |  +-------------------- [6]  w_strobe[2]
    ;   |  |  |  |  |  |  |  |  +----------------------- [7]  w_strobe[3]
    ;   |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  +-------------------------- [8]  w_strobe[4]
    ;   |  |  |  |  |  |  +----------------------------- [9]  w_strobe[5]
    ;   |  |  |  |  |  +-------------------------------- [10] w_setup[0]    Write Strobe Setup cycles.  Number of emif_clock cycles from A, BA, D, DQM, and the chip 
    ;   |  |  |  |  +----------------------------------- [11] w_setup[1]    select pins being asserted to WE pin being asserted, minus one cycle.
    ;   |  |  |  |
    ;   |  |  |  +-------------------------------------- [12] w_setup[2]
    ;   |  |  +----------------------------------------- [13] w_setup[3]
    ;   |  +-------------------------------------------- [14] ew            Extend wait mode.  Set to 1 if extended asynchronous cycles are required based on RDY.
    ;   +----------------------------------------------- [15] ss            Select strobe mode. Set to 1 if chip selects need to have write or read strobe timing.
EMIF25_ASYNC4_CR_OFFSET	.set	0x1C	; Async4 Config Register
EMIF25_ASYNC4_CR_0	.set	EMIF25_BASE + EMIF25_ASYNC4_CR_OFFSET
EMIF25_ASYNC4_CR_1	.set 	EMIF25_ASYNC4_CR_0 + 1

EMIF25_SDRAM_TR_OFFSET	.set	0x20	; SDRAM Timing Register
EMIF25_SDRAM_TR_0	.set	EMIF25_BASE + EMIF25_SDRAM_TR_OFFSET
EMIF25_SDRAM_TR_1	.set	EMIF25_SDRAM_TR_0 + 1

EMIF25_SDRAM_SR_OFFSET	.set	0x24	; SDRAM Status Register
EMIF25_SDRAM_SR_0	.set	EMIF25_BASE + EMIF25_SDRAM_SR_OFFSET
EMIF25_SDRAM_SR_1	.set	EMIF25_SDRAM_SR_0 + 1

EMIF25_DDR_CR_OFFSET	.set	0x28	; DDR Control Register
EMIF25_DDR_CR_0		.set	EMIF25_BASE + EMIF25_DDR_CR_OFFSET
EMIF25_DDR_CR_1		.set	EMIF25_DDR_CR_0 + 1

EMIF25_DDR_SR_OFFSET	.set	0x2C	; DDR Status Register
EMIF25_DDR_SR_0		.set	EMIF25_BASE + EMIF25_DDR_SR_OFFSET
EMIF25_DDR_SR_1		.set	EMIF25_DDR_SR_0 + 1

EMIF25_SDRAM_ACR_OFFSET	.set	0x30	; Total SDRAM Accesses Register
EMIF25_SDRAM_ACR_0	.set	EMIF25_BASE + EMIF25_SDRAM_ACR_OFFSET
EMIF25_SDRAM_ACR_1	.set	EMIF25_SDRAM_ACR_0 + 1

EMIF25_SDRAM_ATR_OFFSET	.set	0x34	; Total SDRAM Activate Register
EMIF25_SDRAM_ATR_0	.set	EMIF25_BASE + EMIF25_SDRAM_ATR_OFFSET
EMIF25_SDRAM_ATR_1	.set	EMIF25_SDRAM_ATR_0 + 1

EMIF25_DDR_RR_OFFSET	.set	0x38	; DDR ID and Revision Register
EMIF25_DDR_RR_0		.set	EMIF25_BASE + EMIF25_DDR_RR_OFFSET
EMIF25_DDR_RR_1		.set	EMIF25_DDR_RR_0 + 1

EMIF25_SDRAM_ETR_OFFSET	.set	0x3C	; SDRAM SR/PD Exit Timing Register
EMIF25_SDRAM_ETR_0	.set	EMIF25_BASE + EMIF25_SDRAM_ETR_OFFSET
EMIF25_SDRAM_ETR_1	.set	EMIF25_SDRAM_ETR_0 + 1

EMIF25_IRR_OFFSET	.set	0x40	; Interrupt Raw Register
EMIF25_IRR_0		.set	EMIF25_BASE + EMIF25_IRR_OFFSET
EMIF25_IRR_1		.set	EMIF25_IRR_0 + 1

EMIF25_IMR_OFFSET	.set	0x44	; Interrupt Masked Register
EMIF25_IMR_0		.set	EMIF25_BASE + EMIF25_IMR_OFFSET
EMIF25_IMR_1		.set	EMIF25_IMR_0 + 1

EMIF25_IMSR_OFFSET	.set	0x48	; Interrupt Mask Set Register
EMIF25_IMSR_0		.set	EMIF25_BASE + EMIF25_IMSR_OFFSET
EMIF25_IMSR_1		.set	EMIF25_IMSR_0 + 1

EMIF25_IMCR_OFFSET	.set	0x4C	; Interrupt Mask Clear Register
EMIF25_IMCR_0		.set	EMIF25_BASE + EMIF25_IMCR_OFFSET
EMIF25_IMCR_1 		.set	EMIF25_IMCR_0 + 1

EMIF25_IO_CR_OFFSET	.set	0x50	; IO Control Register
EMIF25_IO_CR_0		.set	EMIF25_BASE + EMIF25_IO_CR_OFFSET
EMIF25_IO_CR_1 		.set	EMIF25_IO_CR_0 + 1

EMIF25_IO_SR_OFFSET	.set	0x54	; IO Status Register
EMIF25_IO_SR_0		.set	EMIF25_BASE + EMIF25_IO_SR_OFFSET
EMIF25_IO_SR_1		.set	EMIF25_IO_SR_0 + 1

EMIF25_SDRAM_CR2_OFFSET	.set	0x58	; SDRAM Config 2 Register
EMIF25_SDRAM_CR2_0	.set	EMIF25_BASE + EMIF25_SDRAM_CR2_OFFSET
EMIF25_SDRAM_CR2_1	.set	EMIF25_SDRAM_CR2_0 + 1

EMIF25_1NAND_CR_OFFSET	.set	0x5C	; OneNAND Flash Control Register
EMIF25_1NAND_CR_0	.set	EMIF25_BASE + EMIF25_1NAND_CR_OFFSET
EMIF25_1NAND_CR_1	.set	EMIF25_1NAND_CR_0 + 1

EMIF25_NAND_CR_OFFSET	.set	0x60	; NAND Flash Control Register
EMIF25_NAND_CR_0	.set	EMIF25_BASE + EMIF25_NAND_CR_OFFSET
EMIF25_NAND_CR_1	.set	EMIF25_NAND_CR_0 + 1

EMIF25_NAND_SR_OFFSET	.set	0x64	; NAND Flash Status Register
EMIF25_NAND_SR_0	.set	EMIF25_BASE + EMIF25_NAND_SR_OFFSET
EMIF25_NAND_SR_1	.set	EMIF25_NAND_SR_0 + 1

EMIF25_PM_CR_OFFSET	.set	0x68	; NAND Page Mode Control Register
EMIF25_PM_CR_0		.set	EMIF25_BASE + EMIF25_PM_CR_OFFSET
EMIF25_PM_CR_1		.set	EMIF25_PM_CR_0 + 1

EMIF25_NANDCS2_ECC_OFF	.set	0x70	; NAND CS2 1-bit ECC Register
EMIF25_NANDCS2_ECC_0	.set	EMIF25_BASE + EMIF25_NANDCS2_ECC_OFF
EMIF25_NANDCS2_ECC_1	.set	EMIF25_NANDCS2_ECC_0 + 1

EMIF25_NANDCS3_ECC_OFF	.set	0x74	; NAND CS3 1-bit ECC Register
EMIF25_NANDCS3_ECC_0	.set	EMIF25_BASE + EMIF25_NANDCS3_ECC_OFF
EMIF25_NANDCS3_ECC_1	.set	EMIF25_NANDCS3_ECC_0 + 1

EMIF25_NANDCS4_ECC_OFF	.set	0x78	; NAND CS4 1-bit ECC Register
EMIF25_NANDCS4_ECC_0	.set	EMIF25_BASE + EMIF25_NANDCS4_ECC_OFF
EMIF25_NANDCS4_ECC_1	.set	EMIF25_NANDCS4_ECC_0 + 1

EMIF25_NANDCS5_ECC_OFF	.set	0x7C	; NAND CS5 1-bit ECC Register
EMIF25_NANDCS5_ECC_0	.set	EMIF25_BASE + EMIF25_NANDCS5_ECC_OFF
EMIF25_NANDCS5_ECC_1	.set	EMIF25_NANDCS5_ECC_0 + 1

EMIF25_IODFT_LEC_OFFSET	.set	0x84	; IODFT Test Logic Execution Counter Register
EMIF25_IODFT_LEC_0	.set	EMIF25_BASE + EMIF25_IODFT_LEC_OFFSET
EMIF25_IODFT_LEC_1	.set	EMIF25_IODFT_LEC_0 + 1

EMIF25_IODFT_LGC_OFFSET	.set	0x88	; IODFT Test Logic Global Control Register
EMIF25_IODFT_LGC_0	.set	EMIF25_BASE + EMIF25_IODFT_LGC_OFFSET
EMIF25_IODFT_LGC_1	.set	EMIF25_IODFT_LGC_0 + 1

EMIF25_IODFT_LGC_OFFSET	.set	0x88	; IODFT Test Logic Global Control Register
EMIF25_IODFT_LGC_0	.set	EMIF25_BASE + EMIF25_IODFT_LGC_OFFSET
EMIF25_IODFT_LGC_1	.set	EMIF25_IODFT_LGC_0 + 1

EMIF25_IODFT_LMR_L_OFF	.set	0x90	; IODFT Test Logic Logic MISR Result LSB Register
EMIF25_IODFT_LMR_L_0	.set	EMIF25_BASE + EMIF25_IODFT_LMR_L_OFF
EMIF25_IODFT_LMR_L_1	.set	EMIF25_IODFT_LMR_L_0 + 1

EMIF25_IODFT_LMR_MI_OFF	.set	0x94	; IODFT Test Logic Logic MISR Result MID Register
EMIF25_IODFT_LMR_MI_0	.set	EMIF25_BASE + EMIF25_IODFT_LMR_MI_OFF
EMIF25_IODFT_LMR_MI_1	.set	EMIF25_IODFT_LMR_MI_0 + 1

EMIF25_IODFT_LMR_M_OFF	.set	0x98	; IODFT Test Logic Logic MISR Result MSB Register
EMIF25_IODFT_LMR_M_0	.set	EMIF25_BASE + EMIF25_IODFT_LMR_M_OFF
EMIF25_IODFT_LMR_M_1	.set	EMIF25_IODFT_LMR_M_0 + 1

EMIF25_MRNR_OFFSET	.set	0xB0	; Module Release Number Register
EMIF25_MRNR_0		.set	EMIF25_BASE + EMIF25_MRNR_OFFSET
EMIF25_MRNR_1		.set	EMIF25_MRNR_0 + 1

EMIF25_NAND_ECC_OFFSET	.set	0xBC	; NAND Flash 4-Bit ECC Load Register
EMIF25_NAND_ECC_0	.set	EMIF25_BASE + EMIF25_NAND_ECC_OFFSET
EMIF25_NAND_ECC_1	.set	EMIF25_NAND_ECC_0 + 1

EMIF25_NAND_ECC1_OFFSET	.set	0xC0	; NAND Flash 4-Bit ECC 1 Register
EMIF25_NAND_ECC1_0	.set	EMIF25_BASE + EMIF25_NAND_ECC1_OFFSET
EMIF25_NAND_ECC1_1	.set	EMIF25_NAND_ECC1_0 + 1

EMIF25_NAND_ECC2_OFFSET	.set	0xC4	; NAND Flash 4-Bit ECC 2 Register
EMIF25_NAND_ECC2_0	.set	EMIF25_BASE + EMIF25_NAND_ECC2_OFFSET
EMIF25_NAND_ECC2_1	.set	EMIF25_NAND_ECC2_0 + 1

EMIF25_NAND_ECC3_OFFSET	.set	0xC8	; NAND Flash 4-Bit ECC 3 Register
EMIF25_NAND_ECC3_0	.set	EMIF25_BASE + EMIF25_NAND_ECC3_OFFSET
EMIF25_NAND_ECC3_1	.set	EMIF25_NAND_ECC3_0 + 1

EMIF25_NAND_ECC4_OFFSET	.set	0xCC	; NAND Flash 4-Bit ECC 4 Register
EMIF25_NAND_ECC4_0	.set	EMIF25_BASE + EMIF25_NAND_ECC4_OFFSET
EMIF25_NAND_ECC4_1	.set	EMIF25_NAND_ECC4_0 + 1

EMIF25_NAND_EAR1_OFFSET	.set	0xD0	; NAND Flash Error Address 1 Register
EMIF25_NAND_EAR1_0	.set	EMIF25_BASE + EMIF25_NAND_EAR1_OFFSET
EMIF25_NAND_EAR1_1	.set	EMIF25_NAND_EAR1_0 + 1

EMIF25_NAND_EAR2_OFFSET	.set	0xD4	; NAND Flash Error Address 2 Register
EMIF25_NAND_EAR2_0	.set	EMIF25_BASE + EMIF25_NAND_EAR2_OFFSET
EMIF25_NAND_EAR2_1	.set	EMIF25_NAND_EAR2_0 + 1

EMIF25_NAND_EVA1_OFFSET	.set	0xD8	; NAND Flash Error Value 1 Register
EMIF25_NAND_EVA1_0	.set	EMIF25_BASE + EMIF25_NAND_EVA1_OFFSET
EMIF25_NAND_EVA1_1	.set	EMIF25_NAND_EVA1_0 + 1

EMIF25_NAND_EVA2_OFFSET	.set	0xDC	; NAND Flash Error Value 2 Register
EMIF25_NAND_EVA2_0	.set	EMIF25_BASE + EMIF25_NAND_EVA2_OFFSET
EMIF25_NAND_EVA2_1	.set	EMIF25_NAND_EVA2_0 + 1
;****************************************************************************************

; (cory removed in release #76)    INT_CONFIG              .set    0x1C12
; (cory removed in release #76)        ; INT_CONFIG   Address:  0x1C12 (IO space)           DSP Interrupt Source Configuration Register
; (cory removed in release #76)        
; (cory removed in release #76)        ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
; (cory removed in release #76)        ; |15:14:13:12|11:10: 9: 8| 7: 6: 5: 4| 3: 2: 1: 0|  <<== Bit Position
; (cory removed in release #76)        ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
; (cory removed in release #76)        ; | r: r: r: r| r: r: r: r| r: r: r:rw|rw:rw:rw:rw|  <<== Read / Write Access
; (cory removed in release #76)        ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
; (cory removed in release #76)        ; | 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0|  <<== Reset Values
; (cory removed in release #76)        ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
; (cory removed in release #76)        ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
; (cory removed in release #76)        ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-- [0]  1->IIS0_XMIT / 0->MMCSD0
; (cory removed in release #76)        ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  +----- [1]  1->IIS0_RCV  / 0->MMCSD0_SDIO
; (cory removed in release #76)        ;   |  |  |  |  |  |  |  |  |  |  |  |  |  +-------- [2]  1->IIS1_XMIT / 0->MMCSD1
; (cory removed in release #76)        ;   |  |  |  |  |  |  |  |  |  |  |  |  +----------- [3]  1->IIS1_RCV  / 0->MMCSD1_SDIO
; (cory removed in release #76)        ;   |  |  |  |  |  |  |  |  |  |  |  |
; (cory removed in release #76)        ;   |  |  |  |  |  |  |  |  |  |  |  +-------------- [4]  reserved
; (cory removed in release #76)        ;   |  |  |  |  |  |  |  |  |  |  +----------------- [5]  reserved
; (cory removed in release #76)        ;   |  |  |  |  |  |  |  |  |  +-------------------- [6]  reserved
; (cory removed in release #76)        ;   |  |  |  |  |  |  |  |  +----------------------- [7]  reserved
; (cory removed in release #76)        ;   |  |  |  |  |  |  |  |
; (cory removed in release #76)        ;   |  |  |  |  |  |  |  +-------------------------- [8]  reserved
; (cory removed in release #76)        ;   |  |  |  |  |  |  +----------------------------- [9]  reserved
; (cory removed in release #76)        ;   |  |  |  |  |  +-------------------------------- [10] reserved
; (cory removed in release #76)        ;   |  |  |  |  +----------------------------------- [11] reserved
; (cory removed in release #76)        ;   |  |  |  |
; (cory removed in release #76)        ;   |  |  |  +-------------------------------------- [12] reserved
; (cory removed in release #76)        ;   |  |  +----------------------------------------- [13] reserved
; (cory removed in release #76)        ;   |  +-------------------------------------------- [14] reserved
; (cory removed in release #76)        ;   +----------------------------------------------- [15] reserved
; (cory removed in release #76)        ;
; (cory removed in release #76)        ; ????   Address:  0x1C13 (IO space)
; (cory removed in release #76)        ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
; (cory removed in release #76)        ; |15:14:13:12|11:10: 9: 8| 7: 6: 5: 4| 3: 2: 1: 0|  <<== Bit Position
; (cory removed in release #76)        ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
; (cory removed in release #76)        ; |r :r :r :r |r :r :r :r |r :r :r :r |r :r :r :r |  <<== Read / Write Access
; (cory removed in release #76)        ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
; (cory removed in release #76)        ; | ?: ?: ?: ?| ?: ?: ?: ?| ?: ?: ?: ?| ?: ?: ?: ?|  <<== Reset Values
; (cory removed in release #76)        ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
; (cory removed in release #76)        ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
; (cory removed in release #76)        ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-- [0]  reserved
; (cory removed in release #76)        ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  +----- [1]  reserved
; (cory removed in release #76)        ;   |  |  |  |  |  |  |  |  |  |  |  |  |  +-------- [2]  reserved
; (cory removed in release #76)        ;   |  |  |  |  |  |  |  |  |  |  |  |  +----------- [3]  reserved
; (cory removed in release #76)        ;   |  |  |  |  |  |  |  |  |  |  |  |
; (cory removed in release #76)        ;   |  |  |  |  |  |  |  |  |  |  |  +-------------- [4]  reserved
; (cory removed in release #76)        ;   |  |  |  |  |  |  |  |  |  |  +----------------- [5]  reserved
; (cory removed in release #76)        ;   |  |  |  |  |  |  |  |  |  +-------------------- [6]  reserved
; (cory removed in release #76)        ;   |  |  |  |  |  |  |  |  +----------------------- [7]  reserved
; (cory removed in release #76)        ;   |  |  |  |  |  |  |  |
; (cory removed in release #76)        ;   |  |  |  |  |  |  |  +-------------------------- [8]  reserved
; (cory removed in release #76)        ;   |  |  |  |  |  |  +----------------------------- [9]  reserved
; (cory removed in release #76)        ;   |  |  |  |  |  +-------------------------------- [10] reserved
; (cory removed in release #76)        ;   |  |  |  |  +----------------------------------- [11] reserved
; (cory removed in release #76)        ;   |  |  |  |
; (cory removed in release #76)        ;   |  |  |  +-------------------------------------- [12] reserved
; (cory removed in release #76)        ;   |  |  +----------------------------------------- [13] reserved
; (cory removed in release #76)        ;   |  +-------------------------------------------- [14] reserved
; (cory removed in release #76)        ;   +----------------------------------------------- [15] reserved
; (cory removed in release #76)        ;****************************************************************************************
; (cory removed in release #76)        ;    DSP Interrupt Source Bit Fields
; (cory removed in release #76)        I2S0_TX_INT      .set    1b<<0    ; enable I2S0 transmit interrupt
; (cory removed in release #76)        I2S0_RX_INT      .set    1b<<1    ; enable I2S0 receive interrupt
; (cory removed in release #76)        I2S1_TX_INT      .set    1b<<2    ; enable I2S1 transmit interrupt 
; (cory removed in release #76)        I2S1_RX_INT      .set    1b<<3    ; enable I2S1 receive interrupt  
; (cory removed in release #76)        MMCSD0_INT       .set    0b<<0    ; enable MMC/SD0 interrupt 
; (cory removed in release #76)        MMCSD0_SDIO_INT  .set    0b<<1    ; enable MMC/SD0 SDIO interrupt  
; (cory removed in release #76)        MMCSD1_INT       .set    0b<<2    ; enable MMC/SD1 interrupt  
; (cory removed in release #76)        MMCSD1_SDIO_INT  .set    0b<<3    ; enable MMC/SD1 SDIO interrupt  

;****************************************************************************************

TIMER_IF                .set    0x1C14
TIMER_IFR               .set    0x1C14
    ; TIMER_IFR/TIMER_IF   Address:  0x1C14 (IO space)       Timer Interrupt Flag Register
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ; |15:14:13:12|11:10: 9: 8| 7: 6: 5: 4| 3: 2: 1: 0|  <<== Bit Position
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; |r :r :r :r |r :r :r :r |r :r :r :r |rw:rw:rw:rw|  <<== Read / Write Access
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; | 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0|  <<== Reset Values
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-- [0]  TIMER0_INTF   (0=no interrupt occured, 1=interrupt occured)
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  +----- [1]  TIMER1_INTF   (0=no interrupt occured, 1=interrupt occured)
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  +-------- [2]  TIMER2_INTF   (0=no interrupt occured, 1=interrupt occured)
    ;   |  |  |  |  |  |  |  |  |  |  |  |  +----------- [3]  reserved
    ;   |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  +-------------- [4]  reserved
    ;   |  |  |  |  |  |  |  |  |  |  +----------------- [5]  reserved
    ;   |  |  |  |  |  |  |  |  |  +-------------------- [6]  reserved
    ;   |  |  |  |  |  |  |  |  +----------------------- [7]  reserved
    ;   |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  +-------------------------- [8]  reserved
    ;   |  |  |  |  |  |  +----------------------------- [9]  reserved
    ;   |  |  |  |  |  +-------------------------------- [10] reserved
    ;   |  |  |  |  +----------------------------------- [11] reserved
    ;   |  |  |  |
    ;   |  |  |  +-------------------------------------- [12] reserved
    ;   |  |  +----------------------------------------- [13] reserved
    ;   |  +-------------------------------------------- [14] reserved
    ;   +----------------------------------------------- [15] reserved
    ;
    ; ????   Address:  0x1C15 (IO space)
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ; |15:14:13:12|11:10: 9: 8| 7: 6: 5: 4| 3: 2: 1: 0|  <<== Bit Position
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; |r :r :r :r |r :r :r :r |r :r :r :r |r :r :r :r |  <<== Read / Write Access
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; | ?: ?: ?: ?| ?: ?: ?: ?| ?: ?: ?: ?| ?: ?: ?: ?|  <<== Reset Values
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-- [0]  reserved
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  +----- [1]  reserved
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  +-------- [2]  reserved
    ;   |  |  |  |  |  |  |  |  |  |  |  |  +----------- [3]  reserved
    ;   |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  +-------------- [4]  reserved
    ;   |  |  |  |  |  |  |  |  |  |  +----------------- [5]  reserved
    ;   |  |  |  |  |  |  |  |  |  +-------------------- [6]  reserved
    ;   |  |  |  |  |  |  |  |  +----------------------- [7]  reserved
    ;   |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  +-------------------------- [8]  reserved
    ;   |  |  |  |  |  |  +----------------------------- [9]  reserved
    ;   |  |  |  |  |  +-------------------------------- [10] reserved
    ;   |  |  |  |  +----------------------------------- [11] reserved
    ;   |  |  |  |
    ;   |  |  |  +-------------------------------------- [12] reserved
    ;   |  |  +----------------------------------------- [13] reserved
    ;   |  +-------------------------------------------- [14] reserved
    ;   +----------------------------------------------- [15] reserved

; (cory removed) IN_PULL_OUT_DR          .set    0x1C16
SLEW_RATE          .set    0x1C16
    ; SLEW_RATE   Address:  0x1C16 (IO space)       Output Pin Slew Rate Control Register
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ; |15:14:13:12|11:10: 9: 8| 7: 6: 5: 4| 3: 2: 1: 0|  <<== Bit Position
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; |r :r :r :r |r :r :r :r |r :r :r :r |r :rw:r :rw|  <<== Read / Write Access
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; | 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0| 0: 1: 0: 1|  <<== Reset Values
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-- [0]  EMIF_SR[0]          (0:low freq, 1:high freq operation)
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  +----- [1]  reserved
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  +-------- [2]  CLKOUT_SR[0]        (0:low freq, 1:high freq operation)
    ;   |  |  |  |  |  |  |  |  |  |  |  |  +----------- [3]  reserved
    ;   |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  +-------------- [4]  reserved
    ;   |  |  |  |  |  |  |  |  |  |  +----------------- [5]  reserved
    ;   |  |  |  |  |  |  |  |  |  +-------------------- [6]  reserved
    ;   |  |  |  |  |  |  |  |  +----------------------- [7]  reserved
    ;   |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  +-------------------------- [8]  reserved
    ;   |  |  |  |  |  |  +----------------------------- [9]  reserved
    ;   |  |  |  |  |  +-------------------------------- [10] reserved
    ;   |  |  |  |  +----------------------------------- [11] reserved
    ;   |  |  |  |
    ;   |  |  |  +-------------------------------------- [12] reserved
    ;   |  |  +----------------------------------------- [13] reserved
    ;   |  +-------------------------------------------- [14] reserved
    ;   +----------------------------------------------- [15] reserved

PULL_INHIBIT0       .set    0x1C17
    ; PULL_INHIBIT0   Address:  0x1C17 (IO space)         Pullup/Pulldown Disable (Inhibit) Register #0
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ; |15:14:13:12|11:10: 9: 8| 7: 6: 5: 4| 3: 2: 1: 0|  <<== Bit Position
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; |r :r :rw:rw|rw:rw:rw:rw|r :r :rw:rw|rw:rw:rw:rw|  <<== Read / Write Access
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; | 0: 0: 1: 1| 1: 1: 1: 1| 0: 0: 1: 1| 1: 1: 1: 1|  <<== Reset Values
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-- [0]  s0pi[0]     S0_PI[0]    S00 Pin Pulldown Inhibit (0=enabled, 1=disabled)
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  +----- [1]  s0pi[1]     S0_PI[1]    S01 Pin Pulldown Inhibit (0=enabled, 1=disabled)
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  +-------- [2]  s0pi[2]     S0_PI[2]    S02 Pin Pulldown Inhibit (0=enabled, 1=disabled)
    ;   |  |  |  |  |  |  |  |  |  |  |  |  +----------- [3]  s0pi[3]     S0_PI[3]    S03 Pin Pulldown Inhibit (0=enabled, 1=disabled)
    ;   |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  +-------------- [4]  s0pi[4]     S0_PI[4]    S04 Pin Pulldown Inhibit (0=enabled, 1=disabled)
    ;   |  |  |  |  |  |  |  |  |  |  +----------------- [5]  s0pi[5]     S0_PI[5]    S05 Pin Pulldown Inhibit (0=enabled, 1=disabled)
    ;   |  |  |  |  |  |  |  |  |  +-------------------- [6]  reserved
    ;   |  |  |  |  |  |  |  |  +----------------------- [7]  reserved
    ;   |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  +-------------------------- [8]  s1pi[0]     S1_PI[0]    S10 Pin Pulldown Inhibit (0=enabled, 1=disabled)
    ;   |  |  |  |  |  |  +----------------------------- [9]  s1pi[1]     S1_PI[1]    S11 Pin Pulldown Inhibit (0=enabled, 1=disabled)
    ;   |  |  |  |  |  +-------------------------------- [10] s1pi[2]     S1_PI[2]    S12 Pin Pulldown Inhibit (0=enabled, 1=disabled)
    ;   |  |  |  |  +----------------------------------- [11] s1pi[3]     S1_PI[3]    S13 Pin Pulldown Inhibit (0=enabled, 1=disabled)
    ;   |  |  |  |
    ;   |  |  |  +-------------------------------------- [12] s1pi[4]     S1_PI[4]    S14 Pin Pulldown Inhibit (0=enabled, 1=disabled)
    ;   |  |  +----------------------------------------- [13] s1pi[5]     S1_PI[5]    S15 Pin Pulldown Inhibit (0=enabled, 1=disabled)
    ;   |  +-------------------------------------------- [14] reserved
    ;   +----------------------------------------------- [15] reserved

;(cory removed) PULL_INHIBIT            .set    0x1C18
PULL_INHIBIT1       .set    0x1C18
    ; PULL_INHIBIT1   Address:  0x1C18 (IO space)         Pullup/Pulldown Disable (Inhibit) Register #1
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ; |15:14:13:12|11:10: 9: 8| 7: 6: 5: 4| 3: 2: 1: 0|  <<== Bit Position
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; |r :rw:rw:rw|rw:rw:rw:rw|r :r :rw:rw|rw:rw:rw:rw|  <<== Read / Write Access
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; | 0: 1: 1: 0| 0: 0: 0: 0| 0: 0: 1: 1| 1: 1: 1: 1|  <<== Reset Values
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-- [0]  A_PI[15]      Address Pin 15  Pulldown Inhibit (0=enabled, 1=disabled)
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  +----- [1]  A_PI[16]      Address Pin 16  Pulldown Inhibit (0=enabled, 1=disabled)
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  +-------- [2]  A_PI[17]      Address Pin 17  Pulldown Inhibit (0=enabled, 1=disabled)
    ;   |  |  |  |  |  |  |  |  |  |  |  |  +----------- [3]  A_PI[18]      Address Pin 18  Pulldown Inhibit (0=enabled, 1=disabled)
    ;   |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  +-------------- [4]  A_PI[19]      Address Pin 19  Pulldown Inhibit (0=enabled, 1=disabled)
    ;   |  |  |  |  |  |  |  |  |  |  +----------------- [5]  A_PI[20]      Address Pin 20  Pulldown Inhibit (0=enabled, 1=disabled)
    ;   |  |  |  |  |  |  |  |  |  +-------------------- [6]  reserved
    ;   |  |  |  |  |  |  |  |  +----------------------- [7]  reserved
    ;   |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  +-------------------------- [8]  TCK_PI        TCK Pin Pullup Inhibit (0=enabled, 1=disabled)
    ;   |  |  |  |  |  |  +----------------------------- [9]  TMS_PI        TMS Pin Pullup Inhibit (0=enabled, 1=disabled)
    ;   |  |  |  |  |  +-------------------------------- [10] TDI_PI        TDI Pin Pullup Inhibit (0=enabled, 1=disabled)
    ;   |  |  |  |  +----------------------------------- [11] EMU01_PI      EMU0 & EMU1 Pins Pullup Inhibit (0=enabled, 1=disabled)
    ;   |  |  |  |
    ;   |  |  |  +-------------------------------------- [12] RESETN_PI     RESETN Pin Pullup Inhibit (0=enabled, 1=disabled)
    ;   |  |  +----------------------------------------- [13] INT0_PI       INT0 Pin Pullup Inhibit   (0=enabled, 1=disabled)
    ;   |  +-------------------------------------------- [14] INT1_PI       INT1 Pin Pullup Inhibit   (0=enabled, 1=disabled)
    ;   +----------------------------------------------- [15] reserved

PULL_INHIBIT2       .set    0x1C19
    ; PULL_INHIBIT2   Address:  0x1C19 (IO space)         Pullup/Pulldown Disable (Inhibit) Register #2
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ; |15:14:13:12|11:10: 9: 8| 7: 6: 5: 4| 3: 2: 1: 0|  <<== Bit Position
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; |rw:rw:rw:rw|rw:rw:rw:rw|rw:rw:rw:rw|rw:rw:r :r |  <<== Read / Write Access
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; | 1: 1: 1: 1| 1: 1: 1: 1| 1: 1: 1: 1| 1: 1: 0: 0|  <<== Reset Values
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-- [0]  reserved
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  +----- [1]  reserved
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  +-------- [2]  PD_PI[2]         PD2  pin Pulldown Inhibit (0=enabled, 1=disabled)
    ;   |  |  |  |  |  |  |  |  |  |  |  |  +----------- [3]  PD_PI[3]         PD3  pin Pulldown Inhibit (0=enabled, 1=disabled)
    ;   |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  +-------------- [4]  PD_PI[4]         PD4  pin Pulldown Inhibit (0=enabled, 1=disabled)
    ;   |  |  |  |  |  |  |  |  |  |  +----------------- [5]  PD_PI[5]         PD5  pin Pulldown Inhibit (0=enabled, 1=disabled)
    ;   |  |  |  |  |  |  |  |  |  +-------------------- [6]  PD_PI[6]         PD6  pin Pulldown Inhibit (0=enabled, 1=disabled)
    ;   |  |  |  |  |  |  |  |  +----------------------- [7]  PD_PI[7]         PD7  pin Pulldown Inhibit (0=enabled, 1=disabled)
    ;   |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  +-------------------------- [8]  PD_PI[8]         PD8  pin Pulldown Inhibit (0=enabled, 1=disabled)
    ;   |  |  |  |  |  |  +----------------------------- [9]  PD_PI[9]         PD9  pin Pulldown Inhibit (0=enabled, 1=disabled)
    ;   |  |  |  |  |  +-------------------------------- [10] PD_PI[10]        PD10 pin Pulldown Inhibit (0=enabled, 1=disabled)
    ;   |  |  |  |  +----------------------------------- [11] PD_PI[11]        PD11 pin Pulldown Inhibit (0=enabled, 1=disabled)
    ;   |  |  |  |
    ;   |  |  |  +-------------------------------------- [12] PD_PI[12]        PD12 pin Pulldown Inhibit (0=enabled, 1=disabled)
    ;   |  |  +----------------------------------------- [13] PD_PI[13]        PD13 pin Pulldown Inhibit (0=enabled, 1=disabled)
    ;   |  +-------------------------------------------- [14] PD_PI[14]        PD14 pin Pulldown Inhibit (0=enabled, 1=disabled)
    ;   +----------------------------------------------- [15] PD_PI[15]        PD15 pin Pulldown Inhibit (0=enabled, 1=disabled)


;****************************************************************************************
;   DMA Event Source Registers
;****************************************************************************************
DMA0_CH10_EVENT_SRC     .set     0x1C1A
    ; DMA0_CH10_EVENT_SRC   Address:  0x1C1A (IO space)  DMA0 channel 0 and channel 1 Event Source Register
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ; |15:14:13:12|11:10: 9: 8| 7: 6: 5: 4| 3: 2: 1: 0|  <<== Bit Position
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; |r :r :r :r |rw:rw:rw:rw|r :r :r :r |rw:rw:rw:rw|  <<== Read / Write Access
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; | 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0|  <<== Reset Values
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-- [0]  Ch0Src[0]
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  +----- [1]  Ch0Src[1]
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  +-------- [2]  Ch0Src[2]
    ;   |  |  |  |  |  |  |  |  |  |  |  |  +----------- [3]  Ch0Src[3]
    ;   |  |  |  |  |  |  |  |  |  |  |  |                             
    ;   |  |  |  |  |  |  |  |  |  |  |  +-------------- [4]  reserved 
    ;   |  |  |  |  |  |  |  |  |  |  +----------------- [5]  reserved 
    ;   |  |  |  |  |  |  |  |  |  +-------------------- [6]  reserved 
    ;   |  |  |  |  |  |  |  |  +----------------------- [7]  reserved 
    ;   |  |  |  |  |  |  |  |                                         
    ;   |  |  |  |  |  |  |  +-------------------------- [8]  Ch1Src[0]
    ;   |  |  |  |  |  |  +----------------------------- [9]  Ch1Src[1]
    ;   |  |  |  |  |  +-------------------------------- [10] Ch1Src[2]
    ;   |  |  |  |  +----------------------------------- [11] Ch1Src[3]
    ;   |  |  |  |                                                     
    ;   |  |  |  +-------------------------------------- [12] reserved 
    ;   |  |  +----------------------------------------- [13] reserved
    ;   |  +-------------------------------------------- [14] reserved
    ;   +----------------------------------------------- [15] reserved
DMA0_CH32_EVENT_SRC     .set     0x1C1B
    ; DMA0_CH32_EVENT_SRC   Address:  0x1C1B (IO space)  DMA0 channel 3 and channel 2 Event Source Register
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ; |15:14:13:12|11:10: 9: 8| 7: 6: 5: 4| 3: 2: 1: 0|  <<== Bit Position
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; |r :r :r :r |rw:rw:rw:rw|r :r :r :r |rw:rw:rw:rw|  <<== Read / Write Access
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; | 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0|  <<== Reset Values
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-- [0]  Ch2Src[0]
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  +----- [1]  Ch2Src[1]
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  +-------- [2]  Ch2Src[2]
    ;   |  |  |  |  |  |  |  |  |  |  |  |  +----------- [3]  Ch2Src[3]
    ;   |  |  |  |  |  |  |  |  |  |  |  |                             
    ;   |  |  |  |  |  |  |  |  |  |  |  +-------------- [4]  reserved
    ;   |  |  |  |  |  |  |  |  |  |  +----------------- [5]  reserved
    ;   |  |  |  |  |  |  |  |  |  +-------------------- [6]  reserved
    ;   |  |  |  |  |  |  |  |  +----------------------- [7]  reserved
    ;   |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  +-------------------------- [8]  Ch3Src[0]
    ;   |  |  |  |  |  |  +----------------------------- [9]  Ch3Src[1]
    ;   |  |  |  |  |  +-------------------------------- [10] Ch3Src[2]
    ;   |  |  |  |  +----------------------------------- [11] Ch3Src[3]
    ;   |  |  |  |
    ;   |  |  |  +-------------------------------------- [12] reserved
    ;   |  |  +----------------------------------------- [13] reserved
    ;   |  +-------------------------------------------- [14] reserved
    ;   +----------------------------------------------- [15] reserved

DMA1_CH10_EVENT_SRC     .set    0x1C1C     ; DMA1 channel 0 and channel 1 Event Source Register
    ; DMA1_CH10_EVENT_SRC   Address:  0x1C1C (IO space)  DMA1 channel 0 and channel 1 Event Source Register
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ; |15:14:13:12|11:10: 9: 8| 7: 6: 5: 4| 3: 2: 1: 0|  <<== Bit Position
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; |r :r :r :r |rw:rw:rw:rw|r :r :r :r |rw:rw:rw:rw|  <<== Read / Write Access
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; | 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0|  <<== Reset Values
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-- [0]  Ch0Src[0]
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  +----- [1]  Ch0Src[1]
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  +-------- [2]  Ch0Src[2]
    ;   |  |  |  |  |  |  |  |  |  |  |  |  +----------- [3]  Ch0Src[3]
    ;   |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  +-------------- [4]  reserved
    ;   |  |  |  |  |  |  |  |  |  |  +----------------- [5]  reserved
    ;   |  |  |  |  |  |  |  |  |  +-------------------- [6]  reserved
    ;   |  |  |  |  |  |  |  |  +----------------------- [7]  reserved
    ;   |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  +-------------------------- [8]  Ch1Src[0]
    ;   |  |  |  |  |  |  +----------------------------- [9]  Ch1Src[1]
    ;   |  |  |  |  |  +-------------------------------- [10] Ch1Src[2]
    ;   |  |  |  |  +----------------------------------- [11] Ch1Src[3]
    ;   |  |  |  |
    ;   |  |  |  +-------------------------------------- [12] reserved
    ;   |  |  +----------------------------------------- [13] reserved
    ;   |  +-------------------------------------------- [14] reserved
    ;   +----------------------------------------------- [15] reserved

DMA1_CH32_EVENT_SRC     .set    0x1C1D     ; DMA1 channel 3 and channel 2 Event Source Register
    ; DMA1_CH32_EVENT_SRC   Address:  0x1C1D (IO space)  DMA1 channel 3 and channel 2 Event Source Register
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ; |15:14:13:12|11:10: 9: 8| 7: 6: 5: 4| 3: 2: 1: 0|  <<== Bit Position
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; |r :r :r :r |rw:rw:rw:rw|r :r :r :r |rw:rw:rw:rw|  <<== Read / Write Access
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; | 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0|  <<== Reset Values
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-- [0]  Ch2Src[0]
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  +----- [1]  Ch2Src[1]
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  +-------- [2]  Ch2Src[2]
    ;   |  |  |  |  |  |  |  |  |  |  |  |  +----------- [3]  Ch2Src[3]
    ;   |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  +-------------- [4]  reserved
    ;   |  |  |  |  |  |  |  |  |  |  +----------------- [5]  reserved
    ;   |  |  |  |  |  |  |  |  |  +-------------------- [6]  reserved
    ;   |  |  |  |  |  |  |  |  +----------------------- [7]  reserved
    ;   |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  +-------------------------- [8]  Ch3Src[0]
    ;   |  |  |  |  |  |  +----------------------------- [9]  Ch3Src[1]
    ;   |  |  |  |  |  +-------------------------------- [10] Ch3Src[2]
    ;   |  |  |  |  +----------------------------------- [11] Ch3Src[3]
    ;   |  |  |  |
    ;   |  |  |  +-------------------------------------- [12] reserved
    ;   |  |  +----------------------------------------- [13] reserved
    ;   |  +-------------------------------------------- [14] reserved
    ;   +----------------------------------------------- [15] reserved

DMA2_CH10_EVENT_SRC     .set    0x1C36     ; DMA2 channel 0 and channel 1 Event Source Register
    ; DMA2_CH10_EVENT_SRC   Address:  0x1C36 (IO space)  DMA2 channel 0 and channel 1 Event Source Register
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ; |15:14:13:12|11:10: 9: 8| 7: 6: 5: 4| 3: 2: 1: 0|  <<== Bit Position
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; |r :r :r :r |rw:rw:rw:rw|r :r :r :r |rw:rw:rw:rw|  <<== Read / Write Access
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; | 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0|  <<== Reset Values
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-- [0]  Ch0Src[0]
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  +----- [1]  Ch0Src[1]
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  +-------- [2]  Ch0Src[2]
    ;   |  |  |  |  |  |  |  |  |  |  |  |  +----------- [3]  Ch0Src[3]
    ;   |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  +-------------- [4]  reserved
    ;   |  |  |  |  |  |  |  |  |  |  +----------------- [5]  reserved
    ;   |  |  |  |  |  |  |  |  |  +-------------------- [6]  reserved
    ;   |  |  |  |  |  |  |  |  +----------------------- [7]  reserved
    ;   |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  +-------------------------- [8]  Ch1Src[0]
    ;   |  |  |  |  |  |  +----------------------------- [9]  Ch1Src[1]
    ;   |  |  |  |  |  +-------------------------------- [10] Ch1Src[2]
    ;   |  |  |  |  +----------------------------------- [11] Ch1Src[3]
    ;   |  |  |  |
    ;   |  |  |  +-------------------------------------- [12] reserved
    ;   |  |  +----------------------------------------- [13] reserved
    ;   |  +-------------------------------------------- [14] reserved
    ;   +----------------------------------------------- [15] reserved

DMA2_CH32_EVENT_SRC     .set    0x1C37     ; DMA2 channel 3 and channel 2 Event Source Register
    ; DMA2_CH32_EVENT_SRC   Address:  0x1C37 (IO space)  DMA2 channel 3 and channel 2 Event Source Register
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ; |15:14:13:12|11:10: 9: 8| 7: 6: 5: 4| 3: 2: 1: 0|  <<== Bit Position
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; |r :r :r :r |rw:rw:rw:rw|r :r :r :r |rw:rw:rw:rw|  <<== Read / Write Access
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; | 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0|  <<== Reset Values
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-- [0]  Ch2Src[0]
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  +----- [1]  Ch2Src[1]
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  +-------- [2]  Ch2Src[2]
    ;   |  |  |  |  |  |  |  |  |  |  |  |  +----------- [3]  Ch2Src[3]
    ;   |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  +-------------- [4]  reserved
    ;   |  |  |  |  |  |  |  |  |  |  +----------------- [5]  reserved
    ;   |  |  |  |  |  |  |  |  |  +-------------------- [6]  reserved
    ;   |  |  |  |  |  |  |  |  +----------------------- [7]  reserved
    ;   |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  +-------------------------- [8]  Ch3Src[0]
    ;   |  |  |  |  |  |  +----------------------------- [9]  Ch3Src[1]
    ;   |  |  |  |  |  +-------------------------------- [10] Ch3Src[2]
    ;   |  |  |  |  +----------------------------------- [11] Ch3Src[3]
    ;   |  |  |  |
    ;   |  |  |  +-------------------------------------- [12] reserved
    ;   |  |  +----------------------------------------- [13] reserved
    ;   |  +-------------------------------------------- [14] reserved
    ;   +----------------------------------------------- [15] reserved

DMA3_CH10_EVENT_SRC     .set    0x1C38     ; DMA3 channel 0 and channel 1 Event Source Register
    ; DMA3_CH10_EVENT_SRC   Address:  0x1C38 (IO space)  DMA3 channel 0 and channel 1 Event Source Register
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ; |15:14:13:12|11:10: 9: 8| 7: 6: 5: 4| 3: 2: 1: 0|  <<== Bit Position
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; |r :r :r :r |rw:rw:rw:rw|r :r :r :r |rw:rw:rw:rw|  <<== Read / Write Access
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; | 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0|  <<== Reset Values
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-- [0]  Ch0Src[0]
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  +----- [1]  Ch0Src[1]
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  +-------- [2]  Ch0Src[2]
    ;   |  |  |  |  |  |  |  |  |  |  |  |  +----------- [3]  Ch0Src[3]
    ;   |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  +-------------- [4]  reserved
    ;   |  |  |  |  |  |  |  |  |  |  +----------------- [5]  reserved
    ;   |  |  |  |  |  |  |  |  |  +-------------------- [6]  reserved
    ;   |  |  |  |  |  |  |  |  +----------------------- [7]  reserved
    ;   |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  +-------------------------- [8]  Ch1Src[0]
    ;   |  |  |  |  |  |  +----------------------------- [9]  Ch1Src[1]
    ;   |  |  |  |  |  +-------------------------------- [10] Ch1Src[2]
    ;   |  |  |  |  +----------------------------------- [11] Ch1Src[3]
    ;   |  |  |  |
    ;   |  |  |  +-------------------------------------- [12] reserved
    ;   |  |  +----------------------------------------- [13] reserved
    ;   |  +-------------------------------------------- [14] reserved
    ;   +----------------------------------------------- [15] reserved

DMA3_CH32_EVENT_SRC     .set    0x1C39    ; DMA3 channel 3 and channel 2 Event Source Register
    ; DMA3_CH32_EVENT_SRC   Address:  0x1C39 (IO space)  DMA3 channel 3 and channel 2 Event Source Register
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ; |15:14:13:12|11:10: 9: 8| 7: 6: 5: 4| 3: 2: 1: 0|  <<== Bit Position
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; |r :r :r :r |rw:rw:rw:rw|r :r :r :r |rw:rw:rw:rw|  <<== Read / Write Access
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; | 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0|  <<== Reset Values
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-- [0]  Ch2Src[0]
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  +----- [1]  Ch2Src[1]
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  +-------- [2]  Ch2Src[2]
    ;   |  |  |  |  |  |  |  |  |  |  |  |  +----------- [3]  Ch2Src[3]
    ;   |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  +-------------- [4]  reserved
    ;   |  |  |  |  |  |  |  |  |  |  +----------------- [5]  reserved
    ;   |  |  |  |  |  |  |  |  |  +-------------------- [6]  reserved
    ;   |  |  |  |  |  |  |  |  +----------------------- [7]  reserved
    ;   |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  +-------------------------- [8]  Ch3Src[0]
    ;   |  |  |  |  |  |  +----------------------------- [9]  Ch3Src[1]
    ;   |  |  |  |  |  +-------------------------------- [10] Ch3Src[2]
    ;   |  |  |  |  +----------------------------------- [11] Ch3Src[3]
    ;   |  |  |  |
    ;   |  |  |  +-------------------------------------- [12] reserved
    ;   |  |  +----------------------------------------- [13] reserved
    ;   |  +-------------------------------------------- [14] reserved
    ;   +----------------------------------------------- [15] reserved

CLKSTOP         .set    0x1C3A
    ; CLKSTOP   Address:  0x1C3A (IO Space)           Clock Stop Request/Acknowledge Register
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ; |15:14:13:12|11:10: 9: 8| 7: 6: 5: 4| 3: 2: 1: 0|  <<== Bit Position
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; |r :r :r :r |r :r :r :r |r :r :r :rw|r :rw:r :rw|  <<== Read / Write Access
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; | 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: x: 0| x: 0: x: 0|  <<== Reset Values
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-- [0]  EMIF_CLKSTOP_REQ    (0:normal, 1:request permission to stop the clock)
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  +----- [1]  EMIF_CLKSTOP_ACK    (status register: 0:not ok to stop the clock, 1:ok to stop the clock)
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  +-------- [2]  USB_CLKSTOP_REQ     (0:normal, 1:request permission to stop the clock)
    ;   |  |  |  |  |  |  |  |  |  |  |  |  +----------- [3]  USB_CLKSTOP_ACK     (status register: 0:not ok to stop the clock, 1:ok to stop the clock)
    ;   |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  +-------------- [4]  UART_CLKSTOP_REQ    (0:normal, 1:request permission to stop the clock)
    ;   |  |  |  |  |  |  |  |  |  |  +----------------- [5]  UART_CLKSTOP_ACK    (status register: 0:not ok to stop the clock, 1:ok to stop the clock)
    ;   |  |  |  |  |  |  |  |  |  +-------------------- [6]  reserved
    ;   |  |  |  |  |  |  |  |  +----------------------- [7]  reserved
    ;   |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  +-------------------------- [8]  reserved
    ;   |  |  |  |  |  |  +----------------------------- [9]  reserved
    ;   |  |  |  |  |  +-------------------------------- [10] reserved
    ;   |  |  |  |  +----------------------------------- [11] reserved
    ;   |  |  |  |
    ;   |  |  |  +-------------------------------------- [12] reserved
    ;   |  |  +----------------------------------------- [13] reserved
    ;   |  +-------------------------------------------- [14] reserved
    ;   +----------------------------------------------- [15] reserved

;----------------------------------------------------------------------------------------
;        CLK STOP Register Bit Fields 
;----------------------------------------------------------------------------------------
EMIF_CLKSTOP_REQ                .set    1b<<0     ; Request permission to stop EMIF internal clock
EMIF_CLKSTOP_ACK                .set    1b<<1     ; EMIF clock stop request status
USB_CLKSTOP_REQ                 .set    1b<<2     ; Request permission to stop USB internal clock
USB_CLKSTOP_ACK                 .set    1b<<3     ; USB clock stop request status
UART_CLKSTOP_REQ                .set    1b<<4     ; Request permission to stop UART internal clock
UART_CLKSTOP_ACK                .set    1b<<5     ; UART clock stop request status
;****************************************************************************************

;****************************************************************************************
;    DMA Event Source Macros
;****************************************************************************************
I2S0_TX_DMA_0      .set    0001b    ; I2S0 transmit event to DMA0
I2S0_RX_DMA_0      .set    0010b    ; I2S0 receive  event to DMA0
MMCSD0_DMA_0       .set    0101b    ; MMC/SD0 event to DMA0 
MMCSD0_SDIO_DMA_0  .set    0110b    ; MMC/SD0 SDIO event to DMA0 
MMCSD1_DMA_0       .set    0111b    ; MMC/SD1 event to DMA0 
MMCSD1_SDIO_DMA_0  .set    1000b    ; MMC/SD1 SDIO event to DMA0 

I2S2_TX_DMA_1      .set    0001b    ; I2S2 transmit event to DMA1
I2S2_RX_DMA_1      .set    0010b    ; I2S2 receive  event to DMA1
UART_TX_DMA_1      .set    0101b    ; UART transmit event to DMA1
UART_RX_DMA_1      .set    0110b    ; UART receive  event to DMA1

I2C_TX_DMA_2       .set    0001b    ; I2C transmit event to DMA2
I2C_RX_DMA_2       .set    0010b    ; I2C receive  event to DMA2
SAR_AD_DMA_2       .set    0011b    ; SAR A/D event to DMA2
I2S3_TX_DMA_2      .set    0100b    ; I2S3 transmit event to DMA2
I2S3_RX_DMA_2      .set    0101b    ; I2S3 receive  event to DMA2

I2S1_TX_DMA_3      .set    0001b    ; I2S1 transmit event to DMA3
I2S1_RX_DMA_3      .set    0010b    ; I2S1 receive  event to DMA3

TIMER0_DMA_0123    .set    1100b    ; TIMER0 event to DMA0, DMA1, DMA2 or DMA3
TIMER1_DMA_0123    .set    1101b    ; TIMER1 event to DMA0, DMA1, DMA2 or DMA3
TIMER2_DMA_0123    .set    1110b    ; TIMER2 event to DMA0, DMA1, DMA2 or DMA3
;****************************************************************************************

;****************************************************************************************
;    DMA Transfer Control Register Bit Fields
;****************************************************************************************
START               .set    1b << 15 ; Start
STOP                .set    0b << 15 ; Stop
INT_EN              .set    1b << 13 ; Interrupt Enable
AUTO_RELOAD         .set    1b << 12 ; Auto Reload
DST_DATA_8          .set    10b << 10 ; Destination Data Size is 8-bits
DST_DATA_16         .set    01b << 10 ; Destination Data Size is 16-bits
DST_DATA_32         .set    00b << 10 ; Destination Data Size is 32-bits
DST_ADDR_INCR       .set    00b << 8  ; Destination Address Mode is incrementing
DST_ADDR_FIX        .set    10b << 8  ; Destination Address Mode is fixed
SRC_ADDR_INCR       .set    00b << 6  ; Source Address Mode is incrementing
SRC_ADDR_FIX        .set    10b << 6  ; Source Address Mode is fixed
BURST_16            .set    100b << 3 ; Burst Mode 16 transfers
BURST_8             .set    011b << 3 ; Burst Mode 8 transfers
BURST_4             .set    010b << 3 ; Burst Mode 4 transfers
BURST_2             .set    001b << 3 ; Burst Mode 2 transfers
BURST_1             .set    000b << 3 ; Burst Mode 1 transfers
INT_SYNC            .set    1b << 2  ; Interrupt Synchronization mode
SRC_DATA_8          .set    10b << 0 ; Source Data Size is 8-bits
SRC_DATA_16         .set    01b << 0 ; Source Data Size is 16-bits
SRC_DATA_32         .set    00b << 0 ; Source Data Size is 32-bits
;****************************************************************************************

;****************************************************************************************
PIN_CONFIG              .set    0x1C1E
CONFIG_LSW              .set    0x1C1E
    ; PIN_CONFIG/CONFIG_LSW   Address:  0x1C1E (IO space)      Configuration LSW Register
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ; |15:14:13:12|11:10: 9: 8| 7: 6: 5: 4| 3: 2: 1: 0|  <<== Bit Position
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; |r :r :r :r |r :r :r :r |r :r :r :r |r :r :r :rw|  <<== Read / Write Access
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; | 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0|  <<== Reset Values
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-- [0]  ExtOscResEn       (0:XI & XO pins have internal 1Mohm resistor between them, 1:XI & XO have no internal resistor between them (external resistor required))
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  +----- [1]  reserved
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  +-------- [2]  reserved
    ;   |  |  |  |  |  |  |  |  |  |  |  |  +----------- [3]  reserved
    ;   |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  +-------------- [4]  reserved
    ;   |  |  |  |  |  |  |  |  |  |  +----------------- [5]  reserved
    ;   |  |  |  |  |  |  |  |  |  +-------------------- [6]  reserved
    ;   |  |  |  |  |  |  |  |  +----------------------- [7]  reserved
    ;   |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  +-------------------------- [8]  reserved
    ;   |  |  |  |  |  |  +----------------------------- [9]  reserved
    ;   |  |  |  |  |  +-------------------------------- [10] reserved
    ;   |  |  |  |  +----------------------------------- [11] reserved
    ;   |  |  |  |
    ;   |  |  |  +-------------------------------------- [12] reserved
    ;   |  |  +----------------------------------------- [13] reserved
    ;   |  +-------------------------------------------- [14] reserved
    ;   +----------------------------------------------- [15] reserved

CONFIG_MSW              .set    0x1C1F
    ; CONFIG_MSW   Address:  0x1C1F (IO space)           Clock Configuration MSW Register
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ; |15:14:13:12|11:10: 9: 8| 7: 6: 5: 4| 3: 2: 1: 0|  <<== Bit Position
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; |r :r :r :r |r :r :r :r |r :r :r :r |rw:r :r :rw|  <<== Read / Write Access
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; | 0: 0: 0: 0| 0: 0: 0: 0| 0: 0:??: 0| 0:??: 0: 0|  <<== Reset Values
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-- [0]  SysClkSel        (0:PLL Bypassed (sysclk=osc), 1:PLL used (sysclk=pllout))
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  +----- [1]  reserved
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  +-------- [2]  CLK_SEL_PIN      (read only - reads the state of the CLK_SEL pin; writes have no affect)
    ;   |  |  |  |  |  |  |  |  |  |  |  |  +----------- [3]  Timer0ClkSel     (0:normal mode/same as all other peripherals (sysclk), 1:PLL used (Timer0clk <= pllout) (testmode for pll))
    ;   |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  +-------------- [4]  SysClkSelStatus[0]  (Read Only Status of Glitch-Free-Clock Mux's selected clk source:
    ;   |  |  |  |  |  |  |  |  |  |  +----------------- [5]  SysClkSelStatus[1]   00:RTCXI, 01:PLL out, 10:CLKIN pin, 11:PLL out)   (note: bit1 is identical to CLK_SEL_PIN, bit0 is the pll used vs bypassed status)
    ;   |  |  |  |  |  |  |  |  |  +-------------------- [6]  reserved
    ;   |  |  |  |  |  |  |  |  +----------------------- [7]  reserved
    ;   |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  +-------------------------- [8]  reserved
    ;   |  |  |  |  |  |  +----------------------------- [9]  reserved
    ;   |  |  |  |  |  +-------------------------------- [10] reserved
    ;   |  |  |  |  +----------------------------------- [11] reserved
    ;   |  |  |  |
    ;   |  |  |  +-------------------------------------- [12] reserved
    ;   |  |  +----------------------------------------- [13] reserved
    ;   |  +-------------------------------------------- [14] reserved
    ;   +----------------------------------------------- [15] reserved

;****************************************************************************************
;    Clock Config Control Register Bit Fields
;****************************************************************************************
SYS_PLL_BYPASS      .set    0b << 0     ; System clock has PLL Bypassed
SYS_PLL_SEL         .set    1b << 0     ; System clock has PLL Selected
SAR_PLL_BYPASS      .set    0b << 1     ; SAR clock has PLL Bypassed
;(cory) removed in REL_CORAZON_80    SAR_PLL_SEL         .set    1b << 1     ; SAR clock PLL Selected
CLK_SEL_STAT        .set    2           ; To test the status fo the CLK_SEL_PIN
OSC_INT_RES_EN      .set    0b << 0     ; Osciallator internal 1MOhm reistance enabled
OSC_INT_RES_DIS     .set    1b << 0     ; Osciallator internal 1MOhm reistance disabled
TIMER0_SYSCLK       .set    0b << 3     ; Timer0 clock is the same as the system clock
TIMER0_OSCCLK       .set    1b << 3     ; Timer0 clock derived before PLL (Oscillator or CLKIN) (Incorrect description, see below)
TIMER0_PLLCLK       .set    1b << 3     ; Timer0 clock derived from PLL
;****************************************************************************************

PLL_CNTL1               .set    0x1C20
    ; PLL_CNTL1   Address:  0x1C20 (IO space)       PLL Control Register #1
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ; |15:14:13:12|11:10: 9: 8| 7: 6: 5: 4| 3: 2: 1: 0|  <<== Bit Position
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; |rw:r :rw:rw|r :r :rw:rw|rw:rw:rw:rw|rw:rw:rw:rw|  <<== Read / Write Access
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; | 0: 0: 0: 1| 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0|  <<== Reset Values
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-- [0]  VP[0]           [VCO Feedback Divider, coarse adjust.
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  +----- [1]  VP[1]              Total feedback divide by value is = {VP[9:0], VS[1:0]} + 4 ]
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  +-------- [2]  VP[2]
    ;   |  |  |  |  |  |  |  |  |  |  |  |  +----------- [3]  VP[3]
    ;   |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  +-------------- [4]  VP[4]
    ;   |  |  |  |  |  |  |  |  |  |  +----------------- [5]  VP[5]
    ;   |  |  |  |  |  |  |  |  |  +-------------------- [6]  VP[6]
    ;   |  |  |  |  |  |  |  |  +----------------------- [7]  VP[7]
    ;   |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  +-------------------------- [8]  VP[8]
    ;   |  |  |  |  |  |  +----------------------------- [9]  VP[9]
    ;   |  |  |  |  |  +-------------------------------- [10] reserved
    ;   |  |  |  |  +----------------------------------- [11] reserved
    ;   |  |  |  |
    ;   |  |  |  +-------------------------------------- [12] PWDN            [0:PLL is powered, 1:PLL powered down (everything in the pll powered down)]
    ;   |  |  +----------------------------------------- [13] STANDBY         [0:PLL is active, 1:PLL is in standby (ibias remains powered for faster powerup).]
    ;   |  +-------------------------------------------- [14] reserved
    ;   +----------------------------------------------- [15] CLRZ            [0:clears LONG_LK_CNT counter & holds the charge on the LPF capacitor.  Normally, take CLRZ low while changing PLL programming to make smoother frequency transitions, thus its not required to bypass the pll while changing ratios.]
;****************************************************************************************
;    PLL Control 1 Control Register Bit Fields
;****************************************************************************************
PLL_PWRDN       .set    1b << 12     ; PLL powered down
PLL_POWERED     .set    0b << 12     ; PLL is powered
PLL_STANDBY     .set    1b << 13     ; PLL is in standby
PLL_ACTIVE      .set    0b << 13     ; PLL is active
CLRZ_LOW        .set    0b << 15     ; Clear CLRZ
CLRZ_HIGH       .set    1b << 15     ; Clear CLRZ
;****************************************************************************************


PLL_CNTL2               .set    0x1C21
    ; PLL_CNTL2   Address:  0x1C21 (IO space)       PLL Control Register #2
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ; |15:14:13:12|11:10: 9: 8| 7: 6: 5: 4| 3: 2: 1: 0|  <<== Bit Position
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; |rw:r :rw:rw|rw:rw:rw:rw|rw:rw:rw:rw|rw:rw:rw:rw|  <<== Read / Write Access
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; | 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0|  <<== Reset Values
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-- [0]  RP[0]           [Reference divider.  If RP_BYPASS==0, the divide by value is = RP[11:0] + 4 else it is = 1.]
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  +----- [1]  RP[1]
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  +-------- [2]  RP[2]
    ;   |  |  |  |  |  |  |  |  |  |  |  |  +----------- [3]  RP[3]
    ;   |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  +-------------- [4]  RP[4]
    ;   |  |  |  |  |  |  |  |  |  |  +----------------- [5]  RP[5]
    ;   |  |  |  |  |  |  |  |  |  +-------------------- [6]  RP[6]
    ;   |  |  |  |  |  |  |  |  +----------------------- [7]  RP[7]
    ;   |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  +-------------------------- [8]  RP[8]
    ;   |  |  |  |  |  |  +----------------------------- [9]  RP[9]
    ;   |  |  |  |  |  +-------------------------------- [10] RP[10]
    ;   |  |  |  |  +----------------------------------- [11] RP[11]
    ;   |  |  |  |
    ;   |  |  |  +-------------------------------------- [12] VS[0]           [VCO Feedback Swallow divider, fine frequency adjust.  See 'VP' for equation.]
    ;   |  |  +----------------------------------------- [13] VS[1]
    ;   |  +-------------------------------------------- [14] reserved
    ;   +----------------------------------------------- [15] RP_BYPASS       [0:use the reference divider, 1:bypass the reference divider (divide by 1)]
;****************************************************************************************
;    PLL Control 2 Control Register Bit Fields
;****************************************************************************************
VS_0            .set    00b << 12       ; VS[1:0]
VS_1            .set    01b << 12
VS_2            .set    10b << 12
VS_3            .set    11b << 12
RP_BYPASS       .set    1b  << 15       ; bypass the reference divider
RP_ACTIVE       .set    0b  << 15       ; use the reference divider
;****************************************************************************************

PLL_CNTL3               .set    0x1C22
    ; PLL_CNTL3   Address:  0x1C22 (IO space)      PLL Control Register #3
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ; |15:14:13:12|11:10: 9: 8| 7: 6: 5: 4| 3: 2: 1: 0|  <<== Bit Position
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; |rw:rw:rw:rw|rw:r :rw:rw|r :r :rw:rw|r :rw:rw:rw|  <<== Read / Write Access
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; | 0: 0: 0: 0| 1: 0: 0: 0| 0: 0: 1: 1| 0: 0: 1: 0|  <<== Reset Values
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-- [0]  NARWZ           [Narrowband Mode Select - Selects the cutoff freq of the LPF Op-Amp Low-Pass-Filter.  In wideband, the 
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |                            cutoff is higher and the LPF settling time is faster which allows for faster lock but more frequency
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |                            error.  Narrowband mode has a lower freq cutoff for better freq error at the expense of slower lock 
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |                            time.  NARWZ works in conjunction with EN_FASTSTART, CLRZ, & LONG_LK_CNT as shown below:
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |                                   EN_FASTSTART    NARWZ   RESULT
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |                                   ============    =====   ==============================================
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |                                   0               0       Narrowband Mode (slower lock but better freq error)
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |                                   0               1       Wideband Mode (faster lock at the expense of freq error)
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |                   recommended --> 1               0       Auto Mode (From CLRZ going high (or POR), will be in Wideband Mode for LONG_LK_CNT (feedback) clock cycles and then automatically switch to Narrowband Mode)
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |                                   1               1       Wideband Mode (faster lock at the expense of freq error)                       ]
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  +----- [1]  EN_FASTSTART    [Enables dynamically switching bandwidth for faster startup - 0:disabled, 1:enabled (recommended).]
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  +-------- [2]  LONG_LK_CNT     [0:16 clock counts (recommended), 1:64 clock counts till lock monitor value goes high after a powerdown or CLRZ reset.  Clocked by the output of the feedback divider.]
    ;   |  |  |  |  |  |  |  |  |  |  |  |  +----------- [3]  TESTLOCKMON     ['Stable' status monitor.  Output of LONG_LK_CNT counter.  0:not locked, 1:locked.  Note:  this really isn't a true LOCK or stability indicator.  It just helps as a rough indicator of when the PLL should be stable.]
    ;   |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  +-------------- [4]  LOW_CURR        [0:normal ibias currents used, 1:Reduces ibias current in half (recommended, but needs to be proven in si).  Note, in schematic its called 'SEL_VCOOUT_TEST'.  ]
    ;   |  |  |  |  |  |  |  |  |  |  +----------------- [5]  EN_LP           [Lower Power Mode (lowers the drive strength of the LPF op-amp) but -may- cause instability. - 0:mode disabled, 1:mode enabled (recommended).  Testchips have shown this to always be useful, however we need to re-evaluate for Corazon's VCO freq range adjustments that have been made to this ckt.)]
    ;   |  |  |  |  |  |  |  |  |  +-------------------- [6]  reserved
    ;   |  |  |  |  |  |  |  |  +----------------------- [7]  reserved
    ;   |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |                                                Charge Sharing Blocking Switches are used to prevent charge leakage out of the LPF capacitor thru the op-amp's bias input resistor.
    ;   |  |  |  |  |  |  |  |                                                At 32 Khz, the clock period is much longer than is necessary to allow for settling, so charge blocking switches OPEN automatically,
    ;   |  |  |  |  |  |  |  |                                                modulated by the phase detector error, to prevent the charge loss.  This results in much lower sideband frequency error and much
    ;   |  |  |  |  |  |  |  |                                                lower power.  Stan has a patent pending for this invention.  PD_SW_TOG_DEL & PD_SW_CLOSE are test mode signals to allow for debug
    ;   |  |  |  |  |  |  |  |                                                if necessary.
    ;   |  |  |  |  |  |  |  +-------------------------- [8]  PD_SW_TOG_DEL   [Charge Sharing Blocking Switches Test Control. 1:At power up switches are closed and at lock they toggle with phase detector error. 0:(recommended) allows PD switches to always toggle.]
    ;   |  |  |  |  |  |  +----------------------------- [9]  PD_SW_CLOSE     [Charge Sharing Blocking Switches Test Control. 1:Always closes phase detector switches, no toggling. 0:(recommended) allows switches to be toggled by phase detector error.]
    ;   |  |  |  |  |  +-------------------------------- [10] reserved
    ;   |  |  |  |  +----------------------------------- [11] EN_LOW_JIT      [Disables test paths that may cause jitter injection. - 0:mode disabled, 1:mode enabled (recommended) ]
    ;   |  |  |  |
    ;   |  |  |  +-------------------------------------- [12] EN_TP_SIGNALS   [To Be Removed.  0:(recommended) internal test points disabled, 1:internal test points enabled]
    ;   |  |  +----------------------------------------- [13] ENABLE_VCODIV   [0: normal mode (recommended), 1:Enables the VCO input voltage to be directly controlled for test.  Must also select this path via the 'anareg_anatestmodesel_tr' register that enables the GPAIN3 pin to connect to the VCO input.  Note, signal name is misleading but this description is correct.]
    ;   |  +-------------------------------------------- [14] CK_DISABLE      [0:clock on (recommended), 1:Turns off VCO output clocks to core applications.  Note: PCGCR bit 15 should normally be used for master clock gating rather than this bit.]
    ;   +----------------------------------------------- [15] BYPASSPLL       [0:PLL is enabled (recommended), 1:PLL bypassed & VCO powered down.  Note: Not glitchfree switched.  Normally, the PLL should be bypassed with CONFIG_MSW bit 0 rather than this bit.]
;****************************************************************************************
;    PLL Control 3 Control Register Bit Fields
;****************************************************************************************
NARROWBAND      .set    0b  << 0        ; Narrowband mode
WIDEBAND        .set    1b  << 0        ; Wideband mode
FASTSTART_EN    .set    1b  << 1        ; Fast Start enabled
FASTSTART_DIS   .set    0b  << 1        ; Fast Start disabled
CLK_CNT_16      .set    0b  << 2        ; 16 clock count
CLK_CNT_64      .set    1b  << 2        ; 64 clock counts till lock monitor value goes high after a powerdown or CLRZ reset
LOW_CURRENT     .set    1b  << 4        ; Reduces ibias current in half
HIGH_CURRENT    .set    0b  << 4        ; normal ibias currents
LOW_POWER_EN    .set    1b  << 5        ; low power mode enabled
LOW_POWER_DIS   .set    0b  << 5        ; low power mode disabled
PD_SW_TOGGLE    .set    0b  << 8        ; allows PD switches to always toggle
PD_SW_PWUP_CL   .set    1b  << 8        ; Closes PD switches until lock, when they are opened and toggle
PD_SW_OPEN      .set    0b  << 9        ; allows switches to be toggled by phase detector error
LOW_JITTER_EN   .set    1b  << 11       ; low jitter enabled
VCO_CK_ENABLED  .set    0b  << 14       ; VCO output clock on
VCO_CK_DISABLED .set    0b  << 14       ; Turns off VCO output clocks to core applications
PLL_ENABLED     .set    0b  << 15       ; PLL is enabled
PLL_BYPASS      .set    1b  << 15       ; PLL bypassed & VCO powered down
;****************************************************************************************


PLL_CNTL4               .set    0x1C23
    ; PLL_CNTL4   Address:  0x1C23 (IO space)      PLL Control Register #4
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ; |15:14:13:12|11:10: 9: 8| 7: 6: 5: 4| 3: 2: 1: 0|  <<== Bit Position
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; |r :r :r :r |r :r :r :r |r :r :r :r |r :r :r :r |  <<== Read / Write Access
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; | 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0|  <<== Reset Values
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-- [0]  OP[0]         PLL Output Divider
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  +----- [1]  OP[1]
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  +-------- [2]  OP[2]
    ;   |  |  |  |  |  |  |  |  |  |  |  |  +----------- [3]  OP[3]
    ;   |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  +-------------- [4]  OP[4]
    ;   |  |  |  |  |  |  |  |  |  |  +----------------- [5]  OP[5]
    ;   |  |  |  |  |  |  |  |  |  +-------------------- [6]  reserved
    ;   |  |  |  |  |  |  |  |  +----------------------- [7]  reserved
    ;   |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  +-------------------------- [8]  OUTDIV2       THIS_IS_A_GUESS: (0:programmable divider enabled, 1:programmable divider bypassed & div-by-2 enabled)
    ;   |  |  |  |  |  |  +----------------------------- [9]  OUTDIVIDE     THIS_IS_A_GUESS: (0:programmable divider bypassed & div-by-2 bypassed, 1:programmable divider enabled & div-by-2 enabled)
    ;   |  |  |  |  |  +-------------------------------- [10] reserved
    ;   |  |  |  |  +----------------------------------- [11] reserved
    ;   |  |  |  |
    ;   |  |  |  +-------------------------------------- [12] reserved
    ;   |  |  +----------------------------------------- [13] reserved
    ;   |  +-------------------------------------------- [14] reserved
    ;   +----------------------------------------------- [15] reserved
;****************************************************************************************
;    PLL Control 4 Control Register Bit Fields
;****************************************************************************************
OUTDIV2_EN      .set    0b  << 8        ; programmable output divider enabled
OUTDIV2_DIS     .set    1b  << 8        ; programmable output divider bypassed
OUTDIV_EN       .set    1b  << 9        ; programmable output divider & div-2 enabled
OUTDIV_DIS      .set    0b  << 9        ; programmable output divider & div-2 bypassed
;****************************************************************************************




CLKOUT_CFG              .set    0x1C24
    ; CLKOUT_CFG   Address:  0x1C24 (IO space)           CLKOUT Clock Source Select Register
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ; |15:14:13:12|11:10: 9: 8| 7: 6: 5: 4| 3: 2: 1: 0|  <<== Bit Position
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; |r :r :r :r |r :r :r :r |r :r :r :r |rw:rw:rw:rw|  <<== Read / Write Access
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; | 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0| 1: 0: 1: 1|  <<== Reset Values
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |        *** This clock selector is not a glitch-free clock switcher! ***
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-- [0]  clkout_src(0)    # CLKOUT_SRC[3:0]      CLKOUT Selected                 Comment
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  +----- [1]  clkout_src(1)    # ===============      ============================    =====================================
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  +-------- [2]  clkout_src(2)    # 0000                 SYSPLL_VCO_Output               (** Quietest for testing SYS PLL ***)
    ;   |  |  |  |  |  |  |  |  |  |  |  |  +----------- [3]  clkout_src(3)    # 0001                 1'b1
    ;   |  |  |  |  |  |  |  |  |  |  |  |                                     # 0010                 SYSPLL_VCO_Output
    ;   |  |  |  |  |  |  |  |  |  |  |  +-------------- [4]  reserved         # 0011                 1'b0
    ;   |  |  |  |  |  |  |  |  |  |  +----------------- [5]  reserved         # 0100                 SYSPLL_VCO_Output
    ;   |  |  |  |  |  |  |  |  |  +-------------------- [6]  reserved         # 0101                 1'b0
    ;   |  |  |  |  |  |  |  |  +----------------------- [7]  reserved         # 0110                 SYSPLL_VCO_Output
    ;   |  |  |  |  |  |  |  |                                                 # 0111                 USB_PHYCLKOUT                   (** Quietest for testing USB PLL ***)
    ;   |  |  |  |  |  |  |  +-------------------------- [8]  reserved         # 1000                 SYSPLL_VCO_Output
    ;   |  |  |  |  |  |  +----------------------------- [9]  reserved         # 1001                 SARClock
    ;   |  |  |  |  |  +-------------------------------- [10] reserved         # 1010                 SYSPLL_VCO_Output
    ;   |  |  |  |  +----------------------------------- [11] reserved         # 1011                 DSP Clock                       (** CLKOUT_SRC[3:0] reset state **)
    ;   |  |  |  |                                                             # 1100                 SYSPLL_VCO_Output
    ;   |  |  |  +-------------------------------------- [12] reserved         # 1101                 GlitchFreeClkMuxOut
    ;   |  |  +----------------------------------------- [13] reserved         # 1110                 SYSPLL_VCO_Output
    ;   |  +-------------------------------------------- [14] reserved         # 1111                 USB_PHYCLKOUT
    ;   +----------------------------------------------- [15] reserved

SECUREROM_ADDR  .set    0x2400          ; SECURE_ROM io-space starting addr (512 words: 0x2400 - 0x25FF)

SECUREROM_CNTL  .set    0x1C25          ; SECURE ROM CONTROL REGISTER
    ; SECUREROM_CNTL   Address:  0x1C25 (IO space)      SECURE ROM CONTROL REGISTER
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ; |15:14:13:12|11:10: 9: 8| 7: 6: 5: 4| 3: 2: 1: 0|  <<== Bit Position
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; |r :r :r :r |r :r :r :r |r :r :r :r |r :r :r :r |  <<== Read / Write Access
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; | ?: ?: ?: ?| ?: ?: ?: ?| ?: ?: ?: ?| ?: ?: ?: ?|  <<== Reset Values
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-- [0]  reserved
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  +----- [1]  reserved
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  +-------- [2]  reserved
    ;   |  |  |  |  |  |  |  |  |  |  |  |  +----------- [3]  reserved
    ;   |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  +-------------- [4]  reserved
    ;   |  |  |  |  |  |  |  |  |  |  +----------------- [5]  reserved
    ;   |  |  |  |  |  |  |  |  |  +-------------------- [6]  reserved
    ;   |  |  |  |  |  |  |  |  +----------------------- [7]  reserved
    ;   |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  +-------------------------- [8]  reserved
    ;   |  |  |  |  |  |  +----------------------------- [9]  reserved
    ;   |  |  |  |  |  +-------------------------------- [10] reserved
    ;   |  |  |  |  +----------------------------------- [11] reserved
    ;   |  |  |  |
    ;   |  |  |  +-------------------------------------- [12] reserved
    ;   |  |  +----------------------------------------- [13] reserved
    ;   |  +-------------------------------------------- [14] reserved
    ;   +----------------------------------------------- [15] reserved


EMIFDIV                 .set    0X1C26
    ; EMIFDIV   Address:  0X1C26 (IO space)              EMIF Clock Divider Register
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ; |15:14:13:12|11:10: 9: 8| 7: 6: 5: 4| 3: 2: 1: 0|  <<== Bit Position
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; |r :r :r :r |r :r :r :r |r :r :r :r |r :r :r :rw|  <<== Read / Write Access
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; | 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 1|  <<== Reset Values
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-- [0]  Emif_FullRate   (0:halfrate, 1:fullrate)
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  +----- [1]  reserved
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  +-------- [2]  reserved
    ;   |  |  |  |  |  |  |  |  |  |  |  |  +----------- [3]  reserved
    ;   |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  +-------------- [4]  reserved
    ;   |  |  |  |  |  |  |  |  |  |  +----------------- [5]  reserved
    ;   |  |  |  |  |  |  |  |  |  +-------------------- [6]  reserved
    ;   |  |  |  |  |  |  |  |  +----------------------- [7]  reserved
    ;   |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  +-------------------------- [8]  reserved
    ;   |  |  |  |  |  |  +----------------------------- [9]  reserved
    ;   |  |  |  |  |  +-------------------------------- [10] reserved
    ;   |  |  |  |  +----------------------------------- [11] reserved
    ;   |  |  |  |
    ;   |  |  |  +-------------------------------------- [12] reserved
    ;   |  |  +----------------------------------------- [13] reserved
    ;   |  +-------------------------------------------- [14] reserved
    ;   +----------------------------------------------- [15] reserved
    ;
    ; ????   Address:  0x1C27 (IO space)
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ; |15:14:13:12|11:10: 9: 8| 7: 6: 5: 4| 3: 2: 1: 0|  <<== Bit Position
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; |r :r :r :r |r :r :r :r |r :r :r :r |r :r :r :r |  <<== Read / Write Access
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; | ?: ?: ?: ?| ?: ?: ?: ?| ?: ?: ?: ?| ?: ?: ?: ?|  <<== Reset Values
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-- [0]  reserved
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  +----- [1]  reserved
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  +-------- [2]  reserved
    ;   |  |  |  |  |  |  |  |  |  |  |  |  +----------- [3]  reserved
    ;   |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  +-------------- [4]  reserved
    ;   |  |  |  |  |  |  |  |  |  |  +----------------- [5]  reserved
    ;   |  |  |  |  |  |  |  |  |  +-------------------- [6]  reserved
    ;   |  |  |  |  |  |  |  |  +----------------------- [7]  reserved
    ;   |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  +-------------------------- [8]  reserved
    ;   |  |  |  |  |  |  +----------------------------- [9]  reserved
    ;   |  |  |  |  |  +-------------------------------- [10] reserved
    ;   |  |  |  |  +----------------------------------- [11] reserved
    ;   |  |  |  |
    ;   |  |  |  +-------------------------------------- [12] reserved
    ;   |  |  +----------------------------------------- [13] reserved
    ;   |  +-------------------------------------------- [14] reserved
    ;   +----------------------------------------------- [15] reserved


SLEEP_DARAM0              .set    0x1C28
    ; SLEEP_DARAM0   Address:  0x1C28 (IO space)           UMA DARAM Sleep Mode Control Register 0
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ; |15:14:13:12|11:10: 9: 8| 7: 6: 5: 4| 3: 2: 1: 0|  <<== Bit Position
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; |rw:rw:rw:rw|rw:rw:rw:rw|rw:rw:rw:rw|rw:rw:rw:rw|  <<== Read / Write Access
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; | 1: 1: 1: 1| 1: 1: 1: 1| 1: 1: 1: 1| 1: 1: 1: 1|  <<== Reset Values
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-- [0]  slpzvss_all_darams_nr   (VSS Sleep Mode:  1=disabled, 0=enabled)
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  +----- [1]  slpzvdd_all_darams_nr   (VDD Sleep Mode:  1=disabled, 0=enabled)
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  +-------- [2]  slpzvss_all_sarams_nr   (VSS Sleep Mode:  1=disabled, 0=enabled)
    ;   |  |  |  |  |  |  |  |  |  |  |  |  +----------- [3]  slpzvdd_all_sarams_nr   (VDD Sleep Mode:  1=disabled, 0=enabled)
    ;   |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  +-------------- [4]  reserved
    ;   |  |  |  |  |  |  |  |  |  |  +----------------- [5]  reserved
    ;   |  |  |  |  |  |  |  |  |  +-------------------- [6]  reserved
    ;   |  |  |  |  |  |  |  |  +----------------------- [7]  reserved
    ;   |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  +-------------------------- [8]  reserved
    ;   |  |  |  |  |  |  +----------------------------- [9]  reserved
    ;   |  |  |  |  |  +-------------------------------- [10] reserved
    ;   |  |  |  |  +----------------------------------- [11] reserved
    ;   |  |  |  |
    ;   |  |  |  +-------------------------------------- [12] reserved
    ;   |  |  +----------------------------------------- [13] reserved
    ;   |  +-------------------------------------------- [14] reserved
    ;   +----------------------------------------------- [15] reserved

    ; (Changed due to bug BTS_MD100.314)     SLEEP_DARAM0   Address:  0x1C28 (IO space)           UMA DARAM Sleep Mode Control Register 0
    ; (Changed due to bug BTS_MD100.314)     +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ; (Changed due to bug BTS_MD100.314)     |15:14:13:12|11:10: 9: 8| 7: 6: 5: 4| 3: 2: 1: 0|  <<== Bit Position
    ; (Changed due to bug BTS_MD100.314)     +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; (Changed due to bug BTS_MD100.314)     |rw:rw:rw:rw|rw:rw:rw:rw|rw:rw:rw:rw|rw:rw:rw:rw|  <<== Read / Write Access
    ; (Changed due to bug BTS_MD100.314)     +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; (Changed due to bug BTS_MD100.314)     | 1: 1: 1: 1| 1: 1: 1: 1| 1: 1: 1: 1| 1: 1: 1: 1|  <<== Reset Values
    ; (Changed due to bug BTS_MD100.314)     +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ; (Changed due to bug BTS_MD100.314)       |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
    ; (Changed due to bug BTS_MD100.314)       |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-- [0]  slpzvss_daram0_nr   (VSS Sleep Mode:  1=disabled, 0=enabled)
    ; (Changed due to bug BTS_MD100.314)       |  |  |  |  |  |  |  |  |  |  |  |  |  |  +----- [1]  slpzvdd_daram0_nr   (VDD Sleep Mode:  1=disabled, 0=enabled)
    ; (Changed due to bug BTS_MD100.314)       |  |  |  |  |  |  |  |  |  |  |  |  |  +-------- [2]  slpzvss_daram1_nr   (VSS Sleep Mode:  1=disabled, 0=enabled)
    ; (Changed due to bug BTS_MD100.314)       |  |  |  |  |  |  |  |  |  |  |  |  +----------- [3]  slpzvdd_daram1_nr   (VDD Sleep Mode:  1=disabled, 0=enabled)
    ; (Changed due to bug BTS_MD100.314)       |  |  |  |  |  |  |  |  |  |  |  |
    ; (Changed due to bug BTS_MD100.314)       |  |  |  |  |  |  |  |  |  |  |  +-------------- [4]  slpzvss_daram2_nr   (VSS Sleep Mode:  1=disabled, 0=enabled)
    ; (Changed due to bug BTS_MD100.314)       |  |  |  |  |  |  |  |  |  |  +----------------- [5]  slpzvdd_daram2_nr   (VDD Sleep Mode:  1=disabled, 0=enabled)
    ; (Changed due to bug BTS_MD100.314)       |  |  |  |  |  |  |  |  |  +-------------------- [6]  slpzvss_daram3_nr   (VSS Sleep Mode:  1=disabled, 0=enabled)
    ; (Changed due to bug BTS_MD100.314)       |  |  |  |  |  |  |  |  +----------------------- [7]  slpzvdd_daram3_nr   (VDD Sleep Mode:  1=disabled, 0=enabled)
    ; (Changed due to bug BTS_MD100.314)       |  |  |  |  |  |  |  |
    ; (Changed due to bug BTS_MD100.314)       |  |  |  |  |  |  |  +-------------------------- [8]  slpzvss_daram4_nr   (VSS Sleep Mode:  1=disabled, 0=enabled)
    ; (Changed due to bug BTS_MD100.314)       |  |  |  |  |  |  +----------------------------- [9]  slpzvdd_daram4_nr   (VDD Sleep Mode:  1=disabled, 0=enabled)
    ; (Changed due to bug BTS_MD100.314)       |  |  |  |  |  +-------------------------------- [10] slpzvss_daram5_nr   (VSS Sleep Mode:  1=disabled, 0=enabled)
    ; (Changed due to bug BTS_MD100.314)       |  |  |  |  +----------------------------------- [11] slpzvdd_daram5_nr   (VDD Sleep Mode:  1=disabled, 0=enabled)
    ; (Changed due to bug BTS_MD100.314)       |  |  |  |
    ; (Changed due to bug BTS_MD100.314)       |  |  |  +-------------------------------------- [12] slpzvss_daram6_nr   (VSS Sleep Mode:  1=disabled, 0=enabled)
    ; (Changed due to bug BTS_MD100.314)       |  |  +----------------------------------------- [13] slpzvdd_daram6_nr   (VDD Sleep Mode:  1=disabled, 0=enabled)
    ; (Changed due to bug BTS_MD100.314)       |  +-------------------------------------------- [14] slpzvss_daram7_nr   (VSS Sleep Mode:  1=disabled, 0=enabled)
    ; (Changed due to bug BTS_MD100.314)       +----------------------------------------------- [15] slpzvdd_daram7_nr   (VDD Sleep Mode:  1=disabled, 0=enabled)

SLEEP_DARAM1              .set    0x1C29
    ; (Changed due to bug BTS_MD100.314)     SLEEP_DARAM1   Address:  0x1C29 (IO space)           UMA DARAM Sleep Mode Control Register 1
    ; (Changed due to bug BTS_MD100.314)     +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ; (Changed due to bug BTS_MD100.314)     |15:14:13:12|11:10: 9: 8| 7: 6: 5: 4| 3: 2: 1: 0|  <<== Bit Position
    ; (Changed due to bug BTS_MD100.314)     +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; (Changed due to bug BTS_MD100.314)     |rw:rw:rw:rw|rw:rw:rw:rw|rw:rw:rw:rw|rw:rw:rw:rw|  <<== Read / Write Access
    ; (Changed due to bug BTS_MD100.314)     +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; (Changed due to bug BTS_MD100.314)     | 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0|  <<== Reset Values
    ; (Changed due to bug BTS_MD100.314)     +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ; (Changed due to bug BTS_MD100.314)       |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
    ; (Changed due to bug BTS_MD100.314)       |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-- [0]  reserved
    ; (Changed due to bug BTS_MD100.314)       |  |  |  |  |  |  |  |  |  |  |  |  |  |  +----- [1]  reserved
    ; (Changed due to bug BTS_MD100.314)       |  |  |  |  |  |  |  |  |  |  |  |  |  +-------- [2]  reserved
    ; (Changed due to bug BTS_MD100.314)       |  |  |  |  |  |  |  |  |  |  |  |  +----------- [3]  reserved
    ; (Changed due to bug BTS_MD100.314)       |  |  |  |  |  |  |  |  |  |  |  |
    ; (Changed due to bug BTS_MD100.314)       |  |  |  |  |  |  |  |  |  |  |  +-------------- [4]  reserved
    ; (Changed due to bug BTS_MD100.314)       |  |  |  |  |  |  |  |  |  |  +----------------- [5]  reserved
    ; (Changed due to bug BTS_MD100.314)       |  |  |  |  |  |  |  |  |  +-------------------- [6]  reserved
    ; (Changed due to bug BTS_MD100.314)       |  |  |  |  |  |  |  |  +----------------------- [7]  reserved
    ; (Changed due to bug BTS_MD100.314)       |  |  |  |  |  |  |  |
    ; (Changed due to bug BTS_MD100.314)       |  |  |  |  |  |  |  +-------------------------- [8]  reserved
    ; (Changed due to bug BTS_MD100.314)       |  |  |  |  |  |  +----------------------------- [9]  reserved
    ; (Changed due to bug BTS_MD100.314)       |  |  |  |  |  +-------------------------------- [10] reserved
    ; (Changed due to bug BTS_MD100.314)       |  |  |  |  +----------------------------------- [11] reserved
    ; (Changed due to bug BTS_MD100.314)       |  |  |  |
    ; (Changed due to bug BTS_MD100.314)       |  |  |  +-------------------------------------- [12] reserved
    ; (Changed due to bug BTS_MD100.314)       |  |  +----------------------------------------- [13] reserved
    ; (Changed due to bug BTS_MD100.314)       |  +-------------------------------------------- [14] reserved
    ; (Changed due to bug BTS_MD100.314)       +----------------------------------------------- [15] reserved

SLEEP_SARAM0              .set    0x1C2A
    ; (Changed due to bug BTS_MD100.314)     SLEEP_SARAM0   Address:  0x1C2A (IO space)           UMA SARAM Sleep Mode Control Register 0
    ; (Changed due to bug BTS_MD100.314)     +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ; (Changed due to bug BTS_MD100.314)     |15:14:13:12|11:10: 9: 8| 7: 6: 5: 4| 3: 2: 1: 0|  <<== Bit Position
    ; (Changed due to bug BTS_MD100.314)     +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; (Changed due to bug BTS_MD100.314)     |rw:rw:rw:rw|rw:rw:rw:rw|rw:rw:rw:rw|rw:rw:rw:rw|  <<== Read / Write Access
    ; (Changed due to bug BTS_MD100.314)     +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; (Changed due to bug BTS_MD100.314)     | 1: 1: 1: 1| 1: 1: 1: 1| 1: 1: 1: 1| 1: 1: 1: 1|  <<== Reset Values
    ; (Changed due to bug BTS_MD100.314)     +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ; (Changed due to bug BTS_MD100.314)       |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
    ; (Changed due to bug BTS_MD100.314)       |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-- [0]  slpzvss_saram0_nr   (VSS Sleep Mode:  1=disabled, 0=enabled)
    ; (Changed due to bug BTS_MD100.314)       |  |  |  |  |  |  |  |  |  |  |  |  |  |  +----- [1]  slpzvdd_saram0_nr   (VDD Sleep Mode:  1=disabled, 0=enabled)
    ; (Changed due to bug BTS_MD100.314)       |  |  |  |  |  |  |  |  |  |  |  |  |  +-------- [2]  slpzvss_saram1_nr   (VSS Sleep Mode:  1=disabled, 0=enabled)
    ; (Changed due to bug BTS_MD100.314)       |  |  |  |  |  |  |  |  |  |  |  |  +----------- [3]  slpzvdd_saram1_nr   (VDD Sleep Mode:  1=disabled, 0=enabled)
    ; (Changed due to bug BTS_MD100.314)       |  |  |  |  |  |  |  |  |  |  |  |
    ; (Changed due to bug BTS_MD100.314)       |  |  |  |  |  |  |  |  |  |  |  +-------------- [4]  slpzvss_saram2_nr   (VSS Sleep Mode:  1=disabled, 0=enabled)
    ; (Changed due to bug BTS_MD100.314)       |  |  |  |  |  |  |  |  |  |  +----------------- [5]  slpzvdd_saram2_nr   (VDD Sleep Mode:  1=disabled, 0=enabled)
    ; (Changed due to bug BTS_MD100.314)       |  |  |  |  |  |  |  |  |  +-------------------- [6]  slpzvss_saram3_nr   (VSS Sleep Mode:  1=disabled, 0=enabled)
    ; (Changed due to bug BTS_MD100.314)       |  |  |  |  |  |  |  |  +----------------------- [7]  slpzvdd_saram3_nr   (VDD Sleep Mode:  1=disabled, 0=enabled)
    ; (Changed due to bug BTS_MD100.314)       |  |  |  |  |  |  |  |
    ; (Changed due to bug BTS_MD100.314)       |  |  |  |  |  |  |  +-------------------------- [8]  slpzvss_saram4_nr   (VSS Sleep Mode:  1=disabled, 0=enabled)
    ; (Changed due to bug BTS_MD100.314)       |  |  |  |  |  |  +----------------------------- [9]  slpzvdd_saram4_nr   (VDD Sleep Mode:  1=disabled, 0=enabled)
    ; (Changed due to bug BTS_MD100.314)       |  |  |  |  |  +-------------------------------- [10] slpzvss_saram5_nr   (VSS Sleep Mode:  1=disabled, 0=enabled)
    ; (Changed due to bug BTS_MD100.314)       |  |  |  |  +----------------------------------- [11] slpzvdd_saram5_nr   (VDD Sleep Mode:  1=disabled, 0=enabled)
    ; (Changed due to bug BTS_MD100.314)       |  |  |  |
    ; (Changed due to bug BTS_MD100.314)       |  |  |  +-------------------------------------- [12] slpzvss_saram6_nr   (VSS Sleep Mode:  1=disabled, 0=enabled)
    ; (Changed due to bug BTS_MD100.314)       |  |  +----------------------------------------- [13] slpzvdd_saram6_nr   (VDD Sleep Mode:  1=disabled, 0=enabled)
    ; (Changed due to bug BTS_MD100.314)       |  +-------------------------------------------- [14] slpzvss_saram7_nr   (VSS Sleep Mode:  1=disabled, 0=enabled)
    ; (Changed due to bug BTS_MD100.314)       +----------------------------------------------- [15] slpzvdd_saram7_nr   (VDD Sleep Mode:  1=disabled, 0=enabled)

SLEEP_SARAM1              .set    0x1C2B
    ; (Changed due to bug BTS_MD100.314)     SLEEP_SARAM1   Address:  0x1C2B (IO space)           UMA SARAM Sleep Mode Control Register 1
    ; (Changed due to bug BTS_MD100.314)     +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ; (Changed due to bug BTS_MD100.314)     |15:14:13:12|11:10: 9: 8| 7: 6: 5: 4| 3: 2: 1: 0|  <<== Bit Position
    ; (Changed due to bug BTS_MD100.314)     +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; (Changed due to bug BTS_MD100.314)     |rw:rw:rw:rw|rw:rw:rw:rw|rw:rw:rw:rw|rw:rw:rw:rw|  <<== Read / Write Access
    ; (Changed due to bug BTS_MD100.314)     +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; (Changed due to bug BTS_MD100.314)     | 1: 1: 1: 1| 1: 1: 1: 1| 1: 1: 1: 1| 1: 1: 1: 1|  <<== Reset Values
    ; (Changed due to bug BTS_MD100.314)     +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ; (Changed due to bug BTS_MD100.314)       |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
    ; (Changed due to bug BTS_MD100.314)       |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-- [0]  slpzvss_saram8_nr   (VSS Sleep Mode:  1=disabled, 0=enabled)
    ; (Changed due to bug BTS_MD100.314)       |  |  |  |  |  |  |  |  |  |  |  |  |  |  +----- [1]  slpzvdd_saram8_nr   (VDD Sleep Mode:  1=disabled, 0=enabled)
    ; (Changed due to bug BTS_MD100.314)       |  |  |  |  |  |  |  |  |  |  |  |  |  +-------- [2]  slpzvss_saram9_nr   (VSS Sleep Mode:  1=disabled, 0=enabled)
    ; (Changed due to bug BTS_MD100.314)       |  |  |  |  |  |  |  |  |  |  |  |  +----------- [3]  slpzvdd_saram9_nr   (VDD Sleep Mode:  1=disabled, 0=enabled)
    ; (Changed due to bug BTS_MD100.314)       |  |  |  |  |  |  |  |  |  |  |  |
    ; (Changed due to bug BTS_MD100.314)       |  |  |  |  |  |  |  |  |  |  |  +-------------- [4]  slpzvss_saram10_nr  (VSS Sleep Mode:  1=disabled, 0=enabled)
    ; (Changed due to bug BTS_MD100.314)       |  |  |  |  |  |  |  |  |  |  +----------------- [5]  slpzvdd_saram10_nr  (VDD Sleep Mode:  1=disabled, 0=enabled)
    ; (Changed due to bug BTS_MD100.314)       |  |  |  |  |  |  |  |  |  +-------------------- [6]  slpzvss_saram11_nr  (VSS Sleep Mode:  1=disabled, 0=enabled)
    ; (Changed due to bug BTS_MD100.314)       |  |  |  |  |  |  |  |  +----------------------- [7]  slpzvdd_saram11_nr  (VDD Sleep Mode:  1=disabled, 0=enabled)
    ; (Changed due to bug BTS_MD100.314)       |  |  |  |  |  |  |  |
    ; (Changed due to bug BTS_MD100.314)       |  |  |  |  |  |  |  +-------------------------- [8]  slpzvss_saram12_nr  (VSS Sleep Mode:  1=disabled, 0=enabled)
    ; (Changed due to bug BTS_MD100.314)       |  |  |  |  |  |  +----------------------------- [9]  slpzvdd_saram12_nr  (VDD Sleep Mode:  1=disabled, 0=enabled)
    ; (Changed due to bug BTS_MD100.314)       |  |  |  |  |  +-------------------------------- [10] slpzvss_saram13_nr  (VSS Sleep Mode:  1=disabled, 0=enabled)
    ; (Changed due to bug BTS_MD100.314)       |  |  |  |  +----------------------------------- [11] slpzvdd_saram13_nr  (VDD Sleep Mode:  1=disabled, 0=enabled)
    ; (Changed due to bug BTS_MD100.314)       |  |  |  |
    ; (Changed due to bug BTS_MD100.314)       |  |  |  +-------------------------------------- [12] slpzvss_saram14_nr  (VSS Sleep Mode:  1=disabled, 0=enabled)
    ; (Changed due to bug BTS_MD100.314)       |  |  +----------------------------------------- [13] slpzvdd_saram14_nr  (VDD Sleep Mode:  1=disabled, 0=enabled)
    ; (Changed due to bug BTS_MD100.314)       |  +-------------------------------------------- [14] slpzvss_saram15_nr  (VSS Sleep Mode:  1=disabled, 0=enabled)
    ; (Changed due to bug BTS_MD100.314)       +----------------------------------------------- [15] slpzvdd_saram15_nr  (VDD Sleep Mode:  1=disabled, 0=enabled)

SLEEP_SARAM2              .set    0x1C2C
    ; (Changed due to bug BTS_MD100.314)     SLEEP_SARAM2   Address:  0x1C2C (IO space)           UMA SARAM Sleep Mode Control Register 2
    ; (Changed due to bug BTS_MD100.314)     +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ; (Changed due to bug BTS_MD100.314)     |15:14:13:12|11:10: 9: 8| 7: 6: 5: 4| 3: 2: 1: 0|  <<== Bit Position
    ; (Changed due to bug BTS_MD100.314)     +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; (Changed due to bug BTS_MD100.314)     |rw:rw:rw:rw|rw:rw:rw:rw|rw:rw:rw:rw|rw:rw:rw:rw|  <<== Read / Write Access
    ; (Changed due to bug BTS_MD100.314)     +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; (Changed due to bug BTS_MD100.314)     | 1: 1: 1: 1| 1: 1: 1: 1| 1: 1: 1: 1| 1: 1: 1: 1|  <<== Reset Values
    ; (Changed due to bug BTS_MD100.314)     +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ; (Changed due to bug BTS_MD100.314)       |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
    ; (Changed due to bug BTS_MD100.314)       |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-- [0]  slpzvss_saram16_nr  (VSS Sleep Mode:  1=disabled, 0=enabled)
    ; (Changed due to bug BTS_MD100.314)       |  |  |  |  |  |  |  |  |  |  |  |  |  |  +----- [1]  slpzvdd_saram16_nr  (VDD Sleep Mode:  1=disabled, 0=enabled)
    ; (Changed due to bug BTS_MD100.314)       |  |  |  |  |  |  |  |  |  |  |  |  |  +-------- [2]  slpzvss_saram17_nr  (VSS Sleep Mode:  1=disabled, 0=enabled)
    ; (Changed due to bug BTS_MD100.314)       |  |  |  |  |  |  |  |  |  |  |  |  +----------- [3]  slpzvdd_saram17_nr  (VDD Sleep Mode:  1=disabled, 0=enabled)
    ; (Changed due to bug BTS_MD100.314)       |  |  |  |  |  |  |  |  |  |  |  |
    ; (Changed due to bug BTS_MD100.314)       |  |  |  |  |  |  |  |  |  |  |  +-------------- [4]  slpzvss_saram18_nr  (VSS Sleep Mode:  1=disabled, 0=enabled)
    ; (Changed due to bug BTS_MD100.314)       |  |  |  |  |  |  |  |  |  |  +----------------- [5]  slpzvdd_saram18_nr  (VDD Sleep Mode:  1=disabled, 0=enabled)
    ; (Changed due to bug BTS_MD100.314)       |  |  |  |  |  |  |  |  |  +-------------------- [6]  slpzvss_saram19_nr  (VSS Sleep Mode:  1=disabled, 0=enabled)
    ; (Changed due to bug BTS_MD100.314)       |  |  |  |  |  |  |  |  +----------------------- [7]  slpzvdd_saram19_nr  (VDD Sleep Mode:  1=disabled, 0=enabled)
    ; (Changed due to bug BTS_MD100.314)       |  |  |  |  |  |  |  |
    ; (Changed due to bug BTS_MD100.314)       |  |  |  |  |  |  |  +-------------------------- [8]  slpzvss_saram20_nr  (VSS Sleep Mode:  1=disabled, 0=enabled)
    ; (Changed due to bug BTS_MD100.314)       |  |  |  |  |  |  +----------------------------- [9]  slpzvdd_saram20_nr  (VDD Sleep Mode:  1=disabled, 0=enabled)
    ; (Changed due to bug BTS_MD100.314)       |  |  |  |  |  +-------------------------------- [10] slpzvss_saram21_nr  (VSS Sleep Mode:  1=disabled, 0=enabled)
    ; (Changed due to bug BTS_MD100.314)       |  |  |  |  +----------------------------------- [11] slpzvdd_saram21_nr  (VDD Sleep Mode:  1=disabled, 0=enabled)
    ; (Changed due to bug BTS_MD100.314)       |  |  |  |
    ; (Changed due to bug BTS_MD100.314)       |  |  |  +-------------------------------------- [12] slpzvss_saram22_nr  (VSS Sleep Mode:  1=disabled, 0=enabled)
    ; (Changed due to bug BTS_MD100.314)       |  |  +----------------------------------------- [13] slpzvdd_saram22_nr  (VDD Sleep Mode:  1=disabled, 0=enabled)
    ; (Changed due to bug BTS_MD100.314)       |  +-------------------------------------------- [14] slpzvss_saram23_nr  (VSS Sleep Mode:  1=disabled, 0=enabled)
    ; (Changed due to bug BTS_MD100.314)       +----------------------------------------------- [15] slpzvdd_saram23_nr  (VDD Sleep Mode:  1=disabled, 0=enabled)

SLEEP_SARAM3              .set    0x1C2D
    ; (Changed due to bug BTS_MD100.314)     SLEEP_SARAM3   Address:  0x1C2D (IO space)           UMA SARAM Sleep Mode Control Register 3
    ; (Changed due to bug BTS_MD100.314)     +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ; (Changed due to bug BTS_MD100.314)     |15:14:13:12|11:10: 9: 8| 7: 6: 5: 4| 3: 2: 1: 0|  <<== Bit Position
    ; (Changed due to bug BTS_MD100.314)     +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; (Changed due to bug BTS_MD100.314)     |rw:rw:rw:rw|rw:rw:rw:rw|rw:rw:rw:rw|rw:rw:rw:rw|  <<== Read / Write Access
    ; (Changed due to bug BTS_MD100.314)     +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; (Changed due to bug BTS_MD100.314)     | 1: 1: 1: 1| 1: 1: 1: 1| 1: 1: 1: 1| 1: 1: 1: 1|  <<== Reset Values
    ; (Changed due to bug BTS_MD100.314)     +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ; (Changed due to bug BTS_MD100.314)       |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
    ; (Changed due to bug BTS_MD100.314)       |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-- [0]  slpzvss_saram24_nr  (VSS Sleep Mode:  1=disabled, 0=enabled)
    ; (Changed due to bug BTS_MD100.314)       |  |  |  |  |  |  |  |  |  |  |  |  |  |  +----- [1]  slpzvdd_saram24_nr  (VDD Sleep Mode:  1=disabled, 0=enabled)
    ; (Changed due to bug BTS_MD100.314)       |  |  |  |  |  |  |  |  |  |  |  |  |  +-------- [2]  slpzvss_saram25_nr  (VSS Sleep Mode:  1=disabled, 0=enabled)
    ; (Changed due to bug BTS_MD100.314)       |  |  |  |  |  |  |  |  |  |  |  |  +----------- [3]  slpzvdd_saram25_nr  (VDD Sleep Mode:  1=disabled, 0=enabled)
    ; (Changed due to bug BTS_MD100.314)       |  |  |  |  |  |  |  |  |  |  |  |
    ; (Changed due to bug BTS_MD100.314)       |  |  |  |  |  |  |  |  |  |  |  +-------------- [4]  slpzvss_saram26_nr  (VSS Sleep Mode:  1=disabled, 0=enabled)
    ; (Changed due to bug BTS_MD100.314)       |  |  |  |  |  |  |  |  |  |  +----------------- [5]  slpzvdd_saram26_nr  (VDD Sleep Mode:  1=disabled, 0=enabled)
    ; (Changed due to bug BTS_MD100.314)       |  |  |  |  |  |  |  |  |  +-------------------- [6]  slpzvss_saram27_nr  (VSS Sleep Mode:  1=disabled, 0=enabled)
    ; (Changed due to bug BTS_MD100.314)       |  |  |  |  |  |  |  |  +----------------------- [7]  slpzvdd_saram27_nr  (VDD Sleep Mode:  1=disabled, 0=enabled)
    ; (Changed due to bug BTS_MD100.314)       |  |  |  |  |  |  |  |
    ; (Changed due to bug BTS_MD100.314)       |  |  |  |  |  |  |  +-------------------------- [8]  slpzvss_saram28_nr  (VSS Sleep Mode:  1=disabled, 0=enabled)
    ; (Changed due to bug BTS_MD100.314)       |  |  |  |  |  |  +----------------------------- [9]  slpzvdd_saram28_nr  (VDD Sleep Mode:  1=disabled, 0=enabled)
    ; (Changed due to bug BTS_MD100.314)       |  |  |  |  |  +-------------------------------- [10] slpzvss_saram29_nr  (VSS Sleep Mode:  1=disabled, 0=enabled)
    ; (Changed due to bug BTS_MD100.314)       |  |  |  |  +----------------------------------- [11] slpzvdd_saram29_nr  (VDD Sleep Mode:  1=disabled, 0=enabled)
    ; (Changed due to bug BTS_MD100.314)       |  |  |  |
    ; (Changed due to bug BTS_MD100.314)       |  |  |  +-------------------------------------- [12] slpzvss_saram30_nr  (VSS Sleep Mode:  1=disabled, 0=enabled)
    ; (Changed due to bug BTS_MD100.314)       |  |  +----------------------------------------- [13] slpzvdd_saram30_nr  (VDD Sleep Mode:  1=disabled, 0=enabled)
    ; (Changed due to bug BTS_MD100.314)       |  +-------------------------------------------- [14] slpzvss_saram31_nr  (VSS Sleep Mode:  1=disabled, 0=enabled)
    ; (Changed due to bug BTS_MD100.314)       +----------------------------------------------- [15] slpzvdd_saram31_nr  (VDD Sleep Mode:  1=disabled, 0=enabled)

SLEEP_FFTCOP0              .set    0x1C2E
    ; SLEEP_FFTCOP0   Address:  0x1C2E (IO space)          FFTCOP Sleep Mode Control Register 0
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ; |15:14:13:12|11:10: 9: 8| 7: 6: 5: 4| 3: 2: 1: 0|  <<== Bit Position
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; |rw:rw:rw:rw|rw:rw:rw:rw|rw:rw:rw:rw|rw:rw:rw:rw|  <<== Read / Write Access
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; | 1: 1: 1: 1| 1: 1: 1: 1| 1: 1: 1: 1| 1: 1: 1: 1|  <<== Reset Values
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-- [0]  slpzvss_fftcop_anacoef_nr   (VSS Sleep Mode:  1=disabled, 0=enabled)
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  +----- [1]  slpzvdd_fftcop_anacoef_nr   (VDD Sleep Mode:  1=disabled, 0=enabled)
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  +-------- [2]  slpzvss_fftcop_anadly_nr    (VSS Sleep Mode:  1=disabled, 0=enabled)
    ;   |  |  |  |  |  |  |  |  |  |  |  |  +----------- [3]  slpzvdd_fftcop_anadly_nr    (VDD Sleep Mode:  1=disabled, 0=enabled)
    ;   |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  +-------------- [4]  slpzvss_fftcop_syncoef_nr   (VSS Sleep Mode:  1=disabled, 0=enabled)
    ;   |  |  |  |  |  |  |  |  |  |  +----------------- [5]  slpzvdd_fftcop_syncoef_nr   (VDD Sleep Mode:  1=disabled, 0=enabled)
    ;   |  |  |  |  |  |  |  |  |  +-------------------- [6]  slpzvss_fftcop_syndly_nr    (VSS Sleep Mode:  1=disabled, 0=enabled)
    ;   |  |  |  |  |  |  |  |  +----------------------- [7]  slpzvdd_fftcop_syndly_nr    (VDD Sleep Mode:  1=disabled, 0=enabled)
    ;   |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  +-------------------------- [8]  slpzvss_fftcop_memswpg0_nr  (VSS Sleep Mode:  1=disabled, 0=enabled)
    ;   |  |  |  |  |  |  +----------------------------- [9]  slpzvdd_fftcop_memswpg0_nr  (VDD Sleep Mode:  1=disabled, 0=enabled)
    ;   |  |  |  |  |  +-------------------------------- [10] slpzvss_fftcop_memswpg1_nr  (VSS Sleep Mode:  1=disabled, 0=enabled)
    ;   |  |  |  |  +----------------------------------- [11] slpzvdd_fftcop_memswpg1_nr  (VDD Sleep Mode:  1=disabled, 0=enabled)
    ;   |  |  |  |
    ;   |  |  |  +-------------------------------------- [12] slpzvss_fftcop_memswpg2_nr  (VSS Sleep Mode:  1=disabled, 0=enabled)
    ;   |  |  +----------------------------------------- [13] slpzvdd_fftcop_memswpg2_nr  (VDD Sleep Mode:  1=disabled, 0=enabled)
    ;   |  +-------------------------------------------- [14] slpzvss_fftcop_memswpg3_nr  (VSS Sleep Mode:  1=disabled, 0=enabled)
    ;   +----------------------------------------------- [15] slpzvdd_fftcop_memswpg3_nr  (VDD Sleep Mode:  1=disabled, 0=enabled)

SLEEP_FFTCOP1              .set    0x1C2F
    ; SLEEP_FFTCOP1   Address:  0x1C2F (IO space)          FFTCOP Sleep Mode Control Register 1
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ; |15:14:13:12|11:10: 9: 8| 7: 6: 5: 4| 3: 2: 1: 0|  <<== Bit Position
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; |rw:rw:rw:rw|rw:rw:rw:rw|rw:rw:rw:rw|rw:rw:rw:rw|  <<== Read / Write Access
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; | 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0|  <<== Reset Values
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-- [0]  reserved
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  +----- [1]  reserved
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  +-------- [2]  reserved
    ;   |  |  |  |  |  |  |  |  |  |  |  |  +----------- [3]  reserved
    ;   |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  +-------------- [4]  reserved
    ;   |  |  |  |  |  |  |  |  |  |  +----------------- [5]  reserved
    ;   |  |  |  |  |  |  |  |  |  +-------------------- [6]  reserved
    ;   |  |  |  |  |  |  |  |  +----------------------- [7]  reserved
    ;   |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  +-------------------------- [8]  reserved
    ;   |  |  |  |  |  |  +----------------------------- [9]  reserved
    ;   |  |  |  |  |  +-------------------------------- [10] reserved
    ;   |  |  |  |  +----------------------------------- [11] reserved
    ;   |  |  |  |
    ;   |  |  |  +-------------------------------------- [12] reserved
    ;   |  |  +----------------------------------------- [13] reserved
    ;   |  +-------------------------------------------- [14] reserved
    ;   +----------------------------------------------- [15] reserved

DMA_IFR             .set    0x1C30                      ;  DMA Interrupt Flag Register
    ; DMA_IFR             Address:  0x1C30 (IO space)       DMA Interrupt Flag Register
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ; |15:14:13:12|11:10: 9: 8| 7: 6: 5: 4| 3: 2: 1: 0|  <<== Bit Position
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; |rw:rw:rw:rw|rw:rw:rw:rw|rw:rw:rw:rw|rw:rw:rw:rw|  <<== Read / Write Access
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; | 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0|  <<== Reset Values
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |   (Writing a '1' clears the bit; writing a '0' has no effect)
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-- [0]  DMA0_CH0_INTF (0=no interrupt occured, 1=interrupt occured)
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  +----- [1]  DMA0_CH1_INTF (0=no interrupt occured, 1=interrupt occured)
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  +-------- [2]  DMA0_CH2_INTF (0=no interrupt occured, 1=interrupt occured)
    ;   |  |  |  |  |  |  |  |  |  |  |  |  +----------- [3]  DMA0_CH3_INTF (0=no interrupt occured, 1=interrupt occured)
    ;   |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  +-------------- [4]  DMA1_CH0_INTF (0=no interrupt occured, 1=interrupt occured)
    ;   |  |  |  |  |  |  |  |  |  |  +----------------- [5]  DMA1_CH1_INTF (0=no interrupt occured, 1=interrupt occured)
    ;   |  |  |  |  |  |  |  |  |  +-------------------- [6]  DMA1_CH2_INTF (0=no interrupt occured, 1=interrupt occured)
    ;   |  |  |  |  |  |  |  |  +----------------------- [7]  DMA1_CH3_INTF (0=no interrupt occured, 1=interrupt occured)
    ;   |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  +-------------------------- [8]  DMA2_CH0_INTF (0=no interrupt occured, 1=interrupt occured)
    ;   |  |  |  |  |  |  +----------------------------- [9]  DMA2_CH1_INTF (0=no interrupt occured, 1=interrupt occured)
    ;   |  |  |  |  |  +-------------------------------- [10] DMA2_CH2_INTF (0=no interrupt occured, 1=interrupt occured)
    ;   |  |  |  |  +----------------------------------- [11] DMA2_CH3_INTF (0=no interrupt occured, 1=interrupt occured)
    ;   |  |  |  |
    ;   |  |  |  +-------------------------------------- [12] DMA3_CH0_INTF (0=no interrupt occured, 1=interrupt occured)
    ;   |  |  +----------------------------------------- [13] DMA3_CH1_INTF (0=no interrupt occured, 1=interrupt occured)
    ;   |  +-------------------------------------------- [14] DMA3_CH2_INTF (0=no interrupt occured, 1=interrupt occured)
    ;   +----------------------------------------------- [15] DMA3_CH3_INTF (0=no interrupt occured, 1=interrupt occured)

DMA_MSK             .set    0x1C31                      ; DMA Interrupt Mask Flag Register
    ; DMA_MSK             Address:  0x1C31 (IO space)       DMA Interrupt Mask Flag Register
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ; |15:14:13:12|11:10: 9: 8| 7: 6: 5: 4| 3: 2: 1: 0|  <<== Bit Position
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; |rw:rw:rw:rw|rw:rw:rw:rw|rw:rw:rw:rw|rw:rw:rw:rw|  <<== Read / Write Access
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; | 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0|  <<== Reset Values
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-- [0]  DMA0_CH0_MSK (1=interrupt allowed, 0=interrupt masked/blocked)
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  +----- [1]  DMA0_CH1_MSK (1=interrupt allowed, 0=interrupt masked/blocked)
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  +-------- [2]  DMA0_CH2_MSK (1=interrupt allowed, 0=interrupt masked/blocked)
    ;   |  |  |  |  |  |  |  |  |  |  |  |  +----------- [3]  DMA0_CH3_MSK (1=interrupt allowed, 0=interrupt masked/blocked)
    ;   |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  +-------------- [4]  DMA1_CH0_MSK (1=interrupt allowed, 0=interrupt masked/blocked)
    ;   |  |  |  |  |  |  |  |  |  |  +----------------- [5]  DMA1_CH1_MSK (1=interrupt allowed, 0=interrupt masked/blocked)
    ;   |  |  |  |  |  |  |  |  |  +-------------------- [6]  DMA1_CH2_MSK (1=interrupt allowed, 0=interrupt masked/blocked)
    ;   |  |  |  |  |  |  |  |  +----------------------- [7]  DMA1_CH3_MSK (1=interrupt allowed, 0=interrupt masked/blocked)
    ;   |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  +-------------------------- [8]  DMA2_CH0_MSK (1=interrupt allowed, 0=interrupt masked/blocked)
    ;   |  |  |  |  |  |  +----------------------------- [9]  DMA2_CH1_MSK (1=interrupt allowed, 0=interrupt masked/blocked)
    ;   |  |  |  |  |  +-------------------------------- [10] DMA2_CH2_MSK (1=interrupt allowed, 0=interrupt masked/blocked)
    ;   |  |  |  |  +----------------------------------- [11] DMA2_CH3_MSK (1=interrupt allowed, 0=interrupt masked/blocked)
    ;   |  |  |  |
    ;   |  |  |  +-------------------------------------- [12] DMA3_CH0_MSK (1=interrupt allowed, 0=interrupt masked/blocked)
    ;   |  |  +----------------------------------------- [13] DMA3_CH1_MSK (1=interrupt allowed, 0=interrupt masked/blocked)
    ;   |  +-------------------------------------------- [14] DMA3_CH2_MSK (1=interrupt allowed, 0=interrupt masked/blocked)
    ;   +----------------------------------------------- [15] DMA3_CH3_MSK (1=interrupt allowed, 0=interrupt masked/blocked)

USB_CNTL            .set    0x1C32                      ; USB System Control Register
    ; USB_CNTL             Address:  0x1C32 (IO space)       USB System Control Register
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ; |15:14:13:12|11:10: 9: 8| 7: 6: 5: 4| 3: 2: 1: 0|  <<== Bit Position
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; |rw:rw:rw:rw|r :r :r :r |r :rw:r :r |rw:rw:rw:rw|  <<== Read / Write Access
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; | 1: 0: 1: 0| 0: 0: 0: 0| 0: 1: 0: 0| 1: 1: 0: 0|  <<== Reset Values
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-- [0]  USB_BYTEMODE[0]         (0:word accesses, 1:hi byte access)
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  +----- [1]  USB_BYTEMODE[1]         (0:word accesses, 1:low byte access)
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  +-------- [2]  USB_OSC_GZ              (0:normal operating mode, 1:oscillator disabled/XO is tristate/Y is low)
    ;   |  |  |  |  |  |  |  |  |  |  |  |  +----------- [3]  USB_OSC_PWRDN           (0:normal operating mode WITH internal bias resistor, 1:normal operationg mode WITHOUT internal bias resistor/resistor is external/tester mode)
    ;   |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  +-------------- [4]  reserved
    ;   |  |  |  |  |  |  |  |  |  |  +----------------- [5]  reserved
    ;   |  |  |  |  |  |  |  |  |  +-------------------- [6]  USB_NORMALDATAPOLARITY  (0:Reverse polarity of DP & DM, 1:Normal Polarity)
    ;   |  |  |  |  |  |  |  |  +----------------------- [7]  reserved
    ;   |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  +-------------------------- [8]  reserved
    ;   |  |  |  |  |  |  +----------------------------- [9]  reserved
    ;   |  |  |  |  |  +-------------------------------- [10] reserved
    ;   |  |  |  |  +----------------------------------- [11] reserved
    ;   |  |  |  |
    ;   |  |  |  +-------------------------------------- [12] USB_PLLON               (0:Normal USB behavior, 1:override USB SUSPENDM behavior and force release of PLL from suspend state)
    ;   |  |  +----------------------------------------- [13] USB_VBUSDETECTEN        (0:VBUS Comparators OFF (except sessionend comparator), 1:Comparators ON)
    ;   |  +-------------------------------------------- [14] USB_SESSENDEN           (0:VBUS SESSIONEND comparator OFF, 1:VBUS SESSIONEND comparator ON)
    ;   +----------------------------------------------- [15] USB_PD                  (0:USB powered, 1:USB powered-down)

EMIF_CNTL           .set    0x1C33                      ; EMIF System Control Register
    ; EMIF_CNTL             Address:  0x1C33 (IO space)
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ; |15:14:13:12|11:10: 9: 8| 7: 6: 5: 4| 3: 2: 1: 0|  <<== Bit Position
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; |r :r :r :r |r :r :r :r |r :r :r :r |r :r :rw:rw|  <<== Read / Write Access
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; | 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0|  <<== Reset Values
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-- [0]  EMIF_BYTEMODE[0]     (0:word accesses, 1:hi byte access)
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  +----- [1]  EMIF_BYTEMODE[1]     (0:word accesses, 1:low byte access)
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  +-------- [2]  reserved
    ;   |  |  |  |  |  |  |  |  |  |  |  |  +----------- [3]  reserved
    ;   |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  +-------------- [4]  reserved
    ;   |  |  |  |  |  |  |  |  |  |  +----------------- [5]  reserved
    ;   |  |  |  |  |  |  |  |  |  +-------------------- [6]  reserved
    ;   |  |  |  |  |  |  |  |  +----------------------- [7]  reserved
    ;   |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  +-------------------------- [8]  reserved
    ;   |  |  |  |  |  |  +----------------------------- [9]  reserved
    ;   |  |  |  |  |  +-------------------------------- [10] reserved
    ;   |  |  |  |  +----------------------------------- [11] reserved
    ;   |  |  |  |
    ;   |  |  |  +-------------------------------------- [12] reserved
    ;   |  |  +----------------------------------------- [13] reserved
    ;   |  +-------------------------------------------- [14] reserved
    ;   +----------------------------------------------- [15] reserved

BOOTMODE                .set    0x1C34
    ; BOOTMODE   Address:  0x1C34 (IO space)       Test Module's Bootmode Read Only Register
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ; |15:14:13:12|11:10: 9: 8| 7: 6: 5: 4| 3: 2: 1: 0|  <<== Bit Position
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; |r :r :r :r |r :r :r :r |r :r :r :r |r :r :r :r |  <<== Read / Write Access
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; | 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0|  <<== Reset Values (trstn)
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-- [0]  BootMode[0]   Test bootmode register value from jtag
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  +----- [1]  BootMode[1]   (used for testmodes in rom)
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  +-------- [2]  BootMode[2]
    ;   |  |  |  |  |  |  |  |  |  |  |  |  +----------- [3]  BootMode[3]
    ;   |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  +-------------- [4]  BootMode[4]
    ;   |  |  |  |  |  |  |  |  |  |  +----------------- [5]  BootMode[5]
    ;   |  |  |  |  |  |  |  |  |  +-------------------- [6]  BootMode[6]
    ;   |  |  |  |  |  |  |  |  +----------------------- [7]  BootMode[7]
    ;   |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  +-------------------------- [8]  BootMode[8]
    ;   |  |  |  |  |  |  +----------------------------- [9]  BootMode[9]
    ;   |  |  |  |  |  +-------------------------------- [10] reserved
    ;   |  |  |  |  +----------------------------------- [11] reserved
    ;   |  |  |  |
    ;   |  |  |  +-------------------------------------- [12] reserved
    ;   |  |  +----------------------------------------- [13] reserved
    ;   |  +-------------------------------------------- [14] reserved
    ;   +----------------------------------------------- [15] reserved
    ;
    ; ????   Address:  0x1C35 (IO space)
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ; |15:14:13:12|11:10: 9: 8| 7: 6: 5: 4| 3: 2: 1: 0|  <<== Bit Position
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; |r :r :r :r |r :r :r :r |r :r :r :r |r :r :r :r |  <<== Read / Write Access
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; | ?: ?: ?: ?| ?: ?: ?: ?| ?: ?: ?: ?| ?: ?: ?: ?|  <<== Reset Values
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-- [0]  reserved
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  +----- [1]  reserved
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  +-------- [2]  reserved
    ;   |  |  |  |  |  |  |  |  |  |  |  |  +----------- [3]  reserved
    ;   |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  +-------------- [4]  reserved
    ;   |  |  |  |  |  |  |  |  |  |  +----------------- [5]  reserved
    ;   |  |  |  |  |  |  |  |  |  +-------------------- [6]  reserved
    ;   |  |  |  |  |  |  |  |  +----------------------- [7]  reserved
    ;   |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  +-------------------------- [8]  reserved
    ;   |  |  |  |  |  |  +----------------------------- [9]  reserved
    ;   |  |  |  |  |  +-------------------------------- [10] reserved
    ;   |  |  |  |  +----------------------------------- [11] reserved
    ;   |  |  |  |
    ;   |  |  |  +-------------------------------------- [12] reserved
    ;   |  |  +----------------------------------------- [13] reserved
    ;   |  +-------------------------------------------- [14] reserved
    ;   +----------------------------------------------- [15] reserved



DIE_ID0                 .set    0x1C40
    ; DIE_ID0   Address:  0x1C40 (IO space)              Die ID Register 0
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ; |15:14:13:12|11:10: 9: 8| 7: 6: 5: 4| 3: 2: 1: 0|  <<== Bit Position
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; |r :r :r :r |r :r :r :r |r :r :r :r |r :r :r :r |  <<== Read / Write Access
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; | ?: ?: ?: ?| ?: ?: ?: ?| ?: ?: ?: ?| ?: ?: ?: ?|  <<== Reset Values
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-- [0]  DieID[0]   WaferX[0]
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  +----- [1]  DieID[1]   WaferX[1]
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  +-------- [2]  DieID[2]   WaferX[2]
    ;   |  |  |  |  |  |  |  |  |  |  |  |  +----------- [3]  DieID[3]   WaferX[3]
    ;   |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  +-------------- [4]  DieID[4]   WaferX[4]
    ;   |  |  |  |  |  |  |  |  |  |  +----------------- [5]  DieID[5]   WaferX[5]
    ;   |  |  |  |  |  |  |  |  |  +-------------------- [6]  DieID[6]   WaferX[6]
    ;   |  |  |  |  |  |  |  |  +----------------------- [7]  DieID[7]   WaferX[7]
    ;   |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  +-------------------------- [8]  DieID[8]   WaferX[8]
    ;   |  |  |  |  |  |  +----------------------------- [9]  DieID[9]   WaferX[9]
    ;   |  |  |  |  |  +-------------------------------- [10] DieID[10]  WaferX[10]
    ;   |  |  |  |  +----------------------------------- [11] DieID[11]  WaferX[11]
    ;   |  |  |  |
    ;   |  |  |  +-------------------------------------- [12] DieID[12]  WaferY[0]
    ;   |  |  +----------------------------------------- [13] DieID[13]  WaferY[1]
    ;   |  +-------------------------------------------- [14] DieID[14]  WaferY[2]
    ;   +----------------------------------------------- [15] DieID[15]  WaferY[3]

DIE_ID1                 .set    0x1C41
    ; DIE_ID1   Address:  0x1C41 (IO space)              Die ID Register 1
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ; |15:14:13:12|11:10: 9: 8| 7: 6: 5: 4| 3: 2: 1: 0|  <<== Bit Position
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; |r :r :r :r |r :r :r :r |r :r :r :r |r :r :r :r |  <<== Read / Write Access
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; | ?: ?: ?: ?| ?: ?: ?: ?| ?: ?: ?: ?| ?: ?: ?: ?|  <<== Reset Values
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-- [0]  DieID[16]   WaferY[4]
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  +----- [1]  DieID[17]   WaferY[5]
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  +-------- [2]  DieID[18]   WaferY[6]
    ;   |  |  |  |  |  |  |  |  |  |  |  |  +----------- [3]  DieID[19]   WaferY[7]
    ;   |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  +-------------- [4]  DieID[20]   WaferY[8]
    ;   |  |  |  |  |  |  |  |  |  |  +----------------- [5]  DieID[21]   WaferY[9]
    ;   |  |  |  |  |  |  |  |  |  +-------------------- [6]  DieID[22]   WaferY[10]
    ;   |  |  |  |  |  |  |  |  +----------------------- [7]  DieID[23]   WaferY[11]
    ;   |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  +-------------------------- [8]  DieID[24]   WaferNum[0]
    ;   |  |  |  |  |  |  +----------------------------- [9]  DieID[25]   WaferNum[1]
    ;   |  |  |  |  |  +-------------------------------- [10] DieID[26]   WaferNum[2]
    ;   |  |  |  |  +----------------------------------- [11] DieID[27]   WaferNum[3]
    ;   |  |  |  |
    ;   |  |  |  +-------------------------------------- [12] DieID[28]   WaferNum[4]
    ;   |  |  +----------------------------------------- [13] DieID[29]   WaferNum[5]
    ;   |  +-------------------------------------------- [14] DieID[30]   reserved
    ;   +----------------------------------------------- [15] DieID[31]   reserved

DIE_ID2              .set    0x1C42        ; Die ID 2 lot #
    ; DIE_ID2   Address:  0x1C42 (IO space)              Die ID Register 2
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ; |15:14:13:12|11:10: 9: 8| 7: 6: 5: 4| 3: 2: 1: 0|  <<== Bit Position
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; |r :r :r :r |r :r :r :r |r :r :r :r |r :r :r :r |  <<== Read / Write Access
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; | ?: ?: ?: ?| ?: ?: ?: ?| ?: ?: ?: ?| ?: ?: ?: ?|  <<== Reset Values
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-- [0]  DieID[32]   LotNum[0]
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  +----- [1]  DieID[33]   LotNum[1]
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  +-------- [2]  DieID[34]   LotNum[2]
    ;   |  |  |  |  |  |  |  |  |  |  |  |  +----------- [3]  DieID[35]   LotNum[3]
    ;   |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  +-------------- [4]  DieID[36]   LotNum[4]
    ;   |  |  |  |  |  |  |  |  |  |  +----------------- [5]  DieID[37]   LotNum[5]
    ;   |  |  |  |  |  |  |  |  |  +-------------------- [6]  DieID[38]   LotNum[6]
    ;   |  |  |  |  |  |  |  |  +----------------------- [7]  DieID[39]   LotNum[7]
    ;   |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  +-------------------------- [8]  DieID[40]   LotNum[8]
    ;   |  |  |  |  |  |  +----------------------------- [9]  DieID[41]   LotNum[9]
    ;   |  |  |  |  |  +-------------------------------- [10] DieID[42]   LotNum[10]
    ;   |  |  |  |  +----------------------------------- [11] DieID[43]   LotNum[11]
    ;   |  |  |  |
    ;   |  |  |  +-------------------------------------- [12] DieID[44]   LotNum[12]
    ;   |  |  +----------------------------------------- [13] DieID[45]   LotNum[13]
    ;   |  +-------------------------------------------- [14] DieID[46]   LotNum[14]
    ;   +----------------------------------------------- [15] DieID[47]   LotNum[15]

DIE_ID3                 .set    0x1C43        ; Die ID 3 designrev, fabcode1, lot #
    ; DIE_ID3   Address:  0x1C43 (IO space)              Die ID Register 3
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ; |15:14:13:12|11:10: 9: 8| 7: 6: 5: 4| 3: 2: 1: 0|  <<== Bit Position
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; |r :r :r :r |r :r :r :r |r :r :r :r |r :r :r :r |  <<== Read / Write Access
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; | ?: ?: ?: ?| ?: ?: ?: ?| ?: ?: ?: ?| ?: ?: ?: ?|  <<== Reset Values
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-- [0]  DieID[48]   LotNum[16]
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  +----- [1]  DieID[49]   LotNum[17]
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  +-------- [2]  DieID[50]   LotNum[18]
    ;   |  |  |  |  |  |  |  |  |  |  |  |  +----------- [3]  DieID[51]   LotNum[19]
    ;   |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  +-------------- [4]  DieID[52]   LotNum[20]
    ;   |  |  |  |  |  |  |  |  |  |  +----------------- [5]  DieID[53]   LotNum[21]
    ;   |  |  |  |  |  |  |  |  |  +-------------------- [6]  DieID[54]   LotNum[22]
    ;   |  |  |  |  |  |  |  |  +----------------------- [7]  DieID[55]   LotNum[23]
    ;   |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  +-------------------------- [8]  DieID[56]   FabCode1[0]
    ;   |  |  |  |  |  |  +----------------------------- [9]  DieID[57]   FabCode1[1]
    ;   |  |  |  |  |  +-------------------------------- [10] DieID[58]   FabCode1[2]
    ;   |  |  |  |  +----------------------------------- [11] DieID[59]   FabCode1[3]
    ;   |  |  |  |
    ;   |  |  |  +-------------------------------------- [12] DieID[60]   DesignRev[0]
    ;   |  |  +----------------------------------------- [13] DieID[61]   DesignRev[1]
    ;   |  +-------------------------------------------- [14] DieID[62]   DesignRev[2]
    ;   +----------------------------------------------- [15] DieID[63]   DesignRev[3]

DIE_ID4                 .set    0x1C44        ; Die ID 4 fabcode2, designrev
    ; DIE_ID4   Address:  0x1C44 (IO space)              Die ID Register 4
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ; |15:14:13:12|11:10: 9: 8| 7: 6: 5: 4| 3: 2: 1: 0|  <<== Bit Position
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; |r :r :r :r |r :r :r :r |r :r :r :r |r :r :r :r |  <<== Read / Write Access
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; | ?: ?: ?: ?| ?: ?: ?: ?| ?: ?: ?: ?| ?: ?: ?: ?|  <<== Reset Values
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-- [0]  DieID[64]   DesignRev[4]
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  +----- [1]  DieID[65]   MemoryRepair[0]
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  +-------- [2]  DieID[66]   FabCode2[0]
    ;   |  |  |  |  |  |  |  |  |  |  |  |  +----------- [3]  DieID[67]   FabCode2[1]
    ;   |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  +-------------- [4]  DieID[68]   FabCode2[2]
    ;   |  |  |  |  |  |  |  |  |  |  +----------------- [5]  DieID[69]   FabCode2[3]
    ;   |  |  |  |  |  |  |  |  |  +-------------------- [6]  DieID[70]   reserved
    ;   |  |  |  |  |  |  |  |  +----------------------- [7]  DieID[71]   reserved
    ;   |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  +-------------------------- [8]  DieID[72]   reserved
    ;   |  |  |  |  |  |  +----------------------------- [9]  DieID[73]   reserved
    ;   |  |  |  |  |  +-------------------------------- [10] DieID[74]   reserved
    ;   |  |  |  |  +----------------------------------- [11] DieID[75]   reserved
    ;   |  |  |  |
    ;   |  |  |  +-------------------------------------- [12] DieID[76]   reserved
    ;   |  |  +----------------------------------------- [13] DieID[77]   reserved
    ;   |  +-------------------------------------------- [14] DieID[78]   reserved
    ;   +----------------------------------------------- [15] DieID[79]   reserved

DIE_ID5                 .set    0x1C45        ; Die ID 5
    ; DIE_ID5   Address:  0x1C45 (IO space)              Die ID Register 5
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ; |15:14:13:12|11:10: 9: 8| 7: 6: 5: 4| 3: 2: 1: 0|  <<== Bit Position
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; |r :r :r :r |r :r :r :r |r :r :r :r |r :r :r :r |  <<== Read / Write Access
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; | ?: ?: ?: ?| ?: ?: ?: ?| ?: ?: ?: ?| ?: ?: ?: ?|  <<== Reset Values
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-- [0]  DieID[80]   reserved
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  +----- [1]  DieID[81]   reserved
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  +-------- [2]  DieID[82]   reserved
    ;   |  |  |  |  |  |  |  |  |  |  |  |  +----------- [3]  DieID[83]   reserved
    ;   |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  +-------------- [4]  DieID[84]   reserved
    ;   |  |  |  |  |  |  |  |  |  |  +----------------- [5]  DieID[85]   reserved
    ;   |  |  |  |  |  |  |  |  |  +-------------------- [6]  DieID[86]   reserved
    ;   |  |  |  |  |  |  |  |  +----------------------- [7]  DieID[87]   reserved
    ;   |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  +-------------------------- [8]  DieID[88]   reserved
    ;   |  |  |  |  |  |  +----------------------------- [9]  DieID[89]   reserved
    ;   |  |  |  |  |  +-------------------------------- [10] DieID[90]   reserved
    ;   |  |  |  |  +----------------------------------- [11] DieID[91]   reserved
    ;   |  |  |  |
    ;   |  |  |  +-------------------------------------- [12] DieID[92]   reserved
    ;   |  |  +----------------------------------------- [13] DieID[93]   reserved
    ;   |  +-------------------------------------------- [14] DieID[94]   reserved
    ;   +----------------------------------------------- [15] DieID[95]   reserved

DIE_ID6                 .set    0x1C46        ; Die ID 6
    ; DIE_ID6   Address:  0x1C46 (IO space)              Die ID Register 6
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ; |15:14:13:12|11:10: 9: 8| 7: 6: 5: 4| 3: 2: 1: 0|  <<== Bit Position
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; |r :r :r :r |r :r :r :r |r :r :r :r |r :r :r :r |  <<== Read / Write Access
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; | ?: ?: ?: ?| ?: ?: ?: ?| ?: ?: ?: ?| ?: ?: ?: ?|  <<== Reset Values
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-- [0]  DieID[96]   reserved
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  +----- [1]  DieID[97]   reserved
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  +-------- [2]  DieID[98]   reserved
    ;   |  |  |  |  |  |  |  |  |  |  |  |  +----------- [3]  DieID[99]   reserved
    ;   |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  +-------------- [4]  DieID[100]  reserved
    ;   |  |  |  |  |  |  |  |  |  |  +----------------- [5]  DieID[101]  reserved
    ;   |  |  |  |  |  |  |  |  |  +-------------------- [6]  DieID[102]  reserved
    ;   |  |  |  |  |  |  |  |  +----------------------- [7]  DieID[103]  reserved
    ;   |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  +-------------------------- [8]  DieID[104]  reserved
    ;   |  |  |  |  |  |  +----------------------------- [9]  DieID[105]  reserved
    ;   |  |  |  |  |  +-------------------------------- [10] DieID[106]  reserved
    ;   |  |  |  |  +----------------------------------- [11] DieID[107]  reserved
    ;   |  |  |  |
    ;   |  |  |  +-------------------------------------- [12] DieID[108]  reserved
    ;   |  |  +----------------------------------------- [13] DieID[109]  reserved
    ;   |  +-------------------------------------------- [14] DieID[110]  reserved
    ;   +----------------------------------------------- [15] DieID[111]  reserved

DIE_ID7                 .set    0x1C47        ; Die ID 7 checksum
    ; DIE_ID7   Address:  0x1C47 (IO space)              Die ID Register 7
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ; |15:14:13:12|11:10: 9: 8| 7: 6: 5: 4| 3: 2: 1: 0|  <<== Bit Position
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; |r :r :r :r |r :r :r :r |r :r :r :r |r :r :r :r |  <<== Read / Write Access
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; | ?: ?: ?: ?| ?: ?: ?: ?| ?: ?: ?: ?| ?: ?: ?: ?|  <<== Reset Values
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-- [0]  DieID[112]  reserved
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  +----- [1]  DieID[113]  checksum[0]
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  +-------- [2]  DieID[114]  checksum[1]
    ;   |  |  |  |  |  |  |  |  |  |  |  |  +----------- [3]  DieID[115]  checksum[2]
    ;   |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  +-------------- [4]  DieID[116]  checksum[3]
    ;   |  |  |  |  |  |  |  |  |  |  +----------------- [5]  DieID[117]  checksum[4]
    ;   |  |  |  |  |  |  |  |  |  +-------------------- [6]  DieID[118]  checksum[5]
    ;   |  |  |  |  |  |  |  |  +----------------------- [7]  DieID[119]  checksum[6]
    ;   |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  +-------------------------- [8]  DieID[120]  checksum[7]
    ;   |  |  |  |  |  |  +----------------------------- [9]  DieID[121]  checksum[8]
    ;   |  |  |  |  |  +-------------------------------- [10] DieID[122]  checksum[9]
    ;   |  |  |  |  +----------------------------------- [11] DieID[123]  checksum[10]
    ;   |  |  |  |
    ;   |  |  |  +-------------------------------------- [12] DieID[124]  checksum[11]
    ;   |  |  +----------------------------------------- [13] DieID[125]  checksum[12]
    ;   |  +-------------------------------------------- [14] DieID[126]  checksum[13]
    ;   +----------------------------------------------- [15] DieID[127]  notused

UMA_MBIST0  .set 0x1c48
    ; UMA_MBIST0   Address:  0x1C48 (IO space)          UMA MBIST Register #0
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ; |15:14:13:12|11:10: 9: 8| 7: 6: 5: 4| 3: 2: 1: 0|  <<== Bit Position
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; |rw:r :r :rw|rw:rw:rw:rw|r :r :r :r |rw:rw:rw:rw|  <<== Read / Write Access
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; | 0: 0: 0: 1| 1: 1: 1: 1| 0: 1: 0: 0| 1: 0: 1: 0|  <<== Reset Values
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-- [0]  sysreg_uma_mbist_en_tr          (0:mbist engine disabled, 1:mbist engine enabled/started)
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  +----- [1]  sysreg_uma_mbist_hold_nr        (0:request mbist controller to pause immediately, 1:mbist controller runs normally)
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  +-------- [2]  sysreg_uma_mbist_debug_tr       (0:no diagnostic datalogging, 1:enable diagnostic datalogging)
    ;   |  |  |  |  |  |  |  |  |  |  |  |  +----------- [3]  sysreg_uma_mbist_resume_tr      (0:pause at retention/iddq points, 1:continue from a retention/iddq point (ie: run normally))
    ;   |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  +-------------- [4]  gl_uma_mbist_retention_tr       (0:not at a retention point, 1:mbist engine is paused at a retention point)
    ;   |  |  |  |  |  |  |  |  |  |  +----------------- [5]  reserved
    ;   |  |  |  |  |  |  |  |  |  +-------------------- [6]  gl_uma_mbist_fail_nr            (valid only if done==1) (0:failed bist, 1:passed bist)
    ;   |  |  |  |  |  |  |  |  +----------------------- [7]  gl_uma_mbist_done_tr            (0:bist not yet done, 1:bist is done/complete)
    ;   |  |  |  |  |  |  |  |                                                              (*** WARNING *** : algselect=0000 will cause the mbist controller to report DONE & PASS immediately without doing anything!!)
    ;   |  |  |  |  |  |  |  |                                                              (Selected algos are performed in the order from AlgoSelect[0] to AlgoSelect[4].  For more detail, see:  /db/lms1/corazon/idft/MBIST_OUTPUTS/BRFS_mbist_ctlr_i0/BRFS_mbist_ctlr_i0_ic/BRFS02048032040.mba)
    ;   |  |  |  |  |  |  |  +-------------------------- [8]  AlgoSelect[0]                   (1:do it, 0:skip it.)  (Algo=BRFS02048032040_Chkrbrd)
    ;   |  |  |  |  |  |  +----------------------------- [9]  AlgoSelect[1]                   (1:do it, 0:skip it.)  (Algo=BRFS02048032040_March13N_backg0)
    ;   |  |  |  |  |  +-------------------------------- [10] AlgoSelect[2]                   (1:do it, 0:skip it.)  (Algo=BRFS02048032040_March11N_backgA)
    ;   |  |  |  |  +----------------------------------- [11] AlgoSelect[3]                   (1:do it, 0:skip it.)  (Algo=BRFS02048032040_March13N_backg3_0F_69)
    ;   |  |  |  |
    ;   |  |  |  +-------------------------------------- [12] AlgoSelect[4]                   (1:do it, 0:skip it.)  (Algo=BRFS02048032040_Addr_Decode)
    ;   |  |  +----------------------------------------- [13] reserved
    ;   |  +-------------------------------------------- [14] reserved
    ;   +----------------------------------------------- [15] force_mbist_reset_tr            (0: mbist controller not forced in reset, 1:mbist controller forced in reset)

UMA_MBIST1  .set 0x1c49
    ; UMA_MBIST1   Address:  0x1C49 (IO space)          UMA MBIST Register #1
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ; |15:14:13:12|11:10: 9: 8| 7: 6: 5: 4| 3: 2: 1: 0|  <<== Bit Position
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; |r :r :r :r |r :r :r :r |r :r :rw:rw|rw:rw:rw:rw|  <<== Read / Write Access
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; | 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0|  <<== Reset Values
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-- [0]  sysreg_uma_mbist_memsel_tr[0]
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  +----- [1]  sysreg_uma_mbist_memsel_tr[1]
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  +-------- [2]  sysreg_uma_mbist_memsel_tr[2]
    ;   |  |  |  |  |  |  |  |  |  |  |  |  +----------- [3]  sysreg_uma_mbist_memsel_tr[3]
    ;   |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  +-------------- [4]  sysreg_uma_mbist_memsel_tr[4]
    ;   |  |  |  |  |  |  |  |  |  |  +----------------- [5]  sysreg_uma_mbist_memsel_tr[5]
    ;   |  |  |  |  |  |  |  |  |  +-------------------- [6]  reserved
    ;   |  |  |  |  |  |  |  |  +----------------------- [7]  reserved
    ;   |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  +-------------------------- [8]  reserved
    ;   |  |  |  |  |  |  +----------------------------- [9]  reserved
    ;   |  |  |  |  |  +-------------------------------- [10] reserved
    ;   |  |  |  |  +----------------------------------- [11] reserved
    ;   |  |  |  |
    ;   |  |  |  +-------------------------------------- [12] reserved
    ;   |  |  +----------------------------------------- [13] reserved
    ;   |  +-------------------------------------------- [14] reserved
    ;   +----------------------------------------------- [15] reserved

USB_MBIST0               .set    0x1C4a
    ; USB_MBIST0   Address:  0x1C4a (IO space)          USB MBIST Register #0
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ; |15:14:13:12|11:10: 9: 8| 7: 6: 5: 4| 3: 2: 1: 0|  <<== Bit Position
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; |r :r :r :rw|rw:rw:rw:rw|r :r :r :r |rw:rw:rw:rw|  <<== Read / Write Access
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; | 0: 0: 0: 1| 1: 1: 1: 1| 0: 1: 0: 0| 1: 0: 1: 0|  <<== Reset Values
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |        (GL Rams are the:  ssram(GL00256032040), epram(GL01024032040), cdma_stram(GL00064128040), & qmgr(GL00064088040).  They are tested serially & return a single fail & done status.)
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-- [0]  sysreg_GL_mbist_en_tr         (0:mbist engine disabled, 1:mbist engine enabled/started)
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  +----- [1]  sysreg_GL_mbist_hold_nr       (0:request mbist controller to pause immediately, 1:mbist controller runs normally)
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  +-------- [2]  sysreg_GL_mbist_debug_tr      (0:no diagnostic datalogging, 1:enable diagnostic datalogging)
    ;   |  |  |  |  |  |  |  |  |  |  |  |  +----------- [3]  sysreg_GL_mbist_resume_tr     (0:pause at retention/iddq points, 1:continue from a retention/iddq point (ie: run normally))
    ;   |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  +-------------- [4]  gl_GL_mbist_retention_tr      (0:not at a retention point, 1:mbist engine is paused at a retention point)
    ;   |  |  |  |  |  |  |  |  |  |  +----------------- [5]  reserved
    ;   |  |  |  |  |  |  |  |  |  +-------------------- [6]  gl_GL_mbist_fail_nr           (valid only if done==1) (0:failed bist, 1:passed bist)
    ;   |  |  |  |  |  |  |  |  +----------------------- [7]  gl_GL_mbist_done_tr           (0:bist not yet done, 1:bist is done/complete)
    ;   |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  +-------------------------- [8]  sysreg_GL_mbist_algselect_tr[0]  (*** WARNING *** : algselect=0000 will cause the mbist controller to report DONE & PASS immediately without doing anything!!)
    ;   |  |  |  |  |  |  +----------------------------- [9]  sysreg_GL_mbist_algselect_tr[1]
    ;   |  |  |  |  |  +-------------------------------- [10] sysreg_GL_mbist_algselect_tr[2]
    ;   |  |  |  |  +----------------------------------- [11] sysreg_GL_mbist_algselect_tr[3]
    ;   |  |  |  |
    ;   |  |  |  +-------------------------------------- [12] sysreg_GL_mbist_algselect_tr[4]
    ;   |  |  +----------------------------------------- [13] reserved
    ;   |  +-------------------------------------------- [14] reserved
    ;   +----------------------------------------------- [15] reserved

USB_MBIST1               .set    0x1C4b
    ; USB_MBIST1   Address:  0x1C4b (IO space)          USB MBIST Register #1
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ; |15:14:13:12|11:10: 9: 8| 7: 6: 5: 4| 3: 2: 1: 0|  <<== Bit Position
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; |r :r :r :r |rw:rw:rw:rw|r :r :r :r |rw:rw:rw:rw|  <<== Read / Write Access
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; | 0: 0: 0: 0| 1: 1: 1: 1| 0: 1: 0: 0| 1: 0: 1: 0|  <<== Reset Values
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |        (BY Rams are the:  cdma_cfgram(BY00016056040), & sched(BY00064012040).  They are tested serially & return a single fail & done status.)
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-- [0]  sysreg_BY_mbist_en_tr         (0:mbist engine disabled, 1:mbist engine enabled/started)
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  +----- [1]  sysreg_BY_mbist_hold_nr       (0:request mbist controller to pause immediately, 1:mbist controller runs normally)
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  +-------- [2]  sysreg_BY_mbist_debug_tr      (0:no diagnostic datalogging, 1:enable diagnostic datalogging)
    ;   |  |  |  |  |  |  |  |  |  |  |  |  +----------- [3]  sysreg_BY_mbist_resume_tr     (0:pause at retention/iddq points, 1:continue from a retention/iddq point (ie: run normally))
    ;   |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  +-------------- [4]  gl_BY_mbist_retention_tr      (0:not at a retention point, 1:mbist engine is paused at a retention point)
    ;   |  |  |  |  |  |  |  |  |  |  +----------------- [5]  reserved
    ;   |  |  |  |  |  |  |  |  |  +-------------------- [6]  gl_BY_mbist_fail_nr           (valid only if done==1) (0:failed bist, 1:passed bist)
    ;   |  |  |  |  |  |  |  |  +----------------------- [7]  gl_BY_mbist_done_tr           (0:bist not yet done, 1:bist is done/complete)
    ;   |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  +-------------------------- [8]  sysreg_BY_mbist_algselect_tr[0]  (*** WARNING *** : algselect=0000 will cause the mbist controller to report DONE & PASS immediately without doing anything!!)
    ;   |  |  |  |  |  |  +----------------------------- [9]  sysreg_BY_mbist_algselect_tr[1]
    ;   |  |  |  |  |  +-------------------------------- [10] sysreg_BY_mbist_algselect_tr[2]
    ;   |  |  |  |  +----------------------------------- [11] sysreg_BY_mbist_algselect_tr[3]
    ;   |  |  |  |
    ;   |  |  |  +-------------------------------------- [12] reserved
    ;   |  |  +----------------------------------------- [13] reserved
    ;   |  +-------------------------------------------- [14] reserved
    ;   +----------------------------------------------- [15] reserved

LCD_MBIST               .set    0x1C4c        ; LCD MBIST Register
    ; LCD_MBIST   Address:  0x1C4c (IO space)          LCD MBIST Register
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ; |15:14:13:12|11:10: 9: 8| 7: 6: 5: 4| 3: 2: 1: 0|  <<== Bit Position
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; |r :r :r :r |rw:rw:rw:rw|r :r :r :r |rw:rw:rw:rw|  <<== Read / Write Access
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; | 0: 0: 0: 0| 1: 1: 1: 1| 0: 1: 0: 0| 1: 0: 1: 0|  <<== Reset Values
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |        (MG Rams include the LCD Palette Ram(MG00256012040) & the LCD DMA Fifo Ram(MG00064034020).  Both are tested serially & return a single fail & done status.)
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-- [0]  sysreg_MG_mbist_en_tr         (0:mbist engine disabled, 1:mbist engine enabled/started)
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  +----- [1]  sysreg_MG_mbist_hold_nr       (0:request mbist controller to pause immediately, 1:mbist controller runs normally)
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  +-------- [2]  sysreg_MG_mbist_debug_tr      (0:no diagnostic datalogging, 1:enable diagnostic datalogging)
    ;   |  |  |  |  |  |  |  |  |  |  |  |  +----------- [3]  sysreg_MG_mbist_resume_tr     (0:pause at retention/iddq points, 1:continue from a retention/iddq point (ie: run normally))
    ;   |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  +-------------- [4]  gl_MG_mbist_retention_tr      (0:not at a retention point, 1:mbist engine is paused at a retention point)
    ;   |  |  |  |  |  |  |  |  |  |  +----------------- [5]  reserved
    ;   |  |  |  |  |  |  |  |  |  +-------------------- [6]  gl_MG_mbist_fail_nr           (valid only if done==1) (0:failed bist, 1:passed bist)
    ;   |  |  |  |  |  |  |  |  +----------------------- [7]  gl_MG_mbist_done_tr           (0:bist not yet done, 1:bist is done/complete)
    ;   |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  +-------------------------- [8]  sysreg_MG_mbist_algselect_tr[0]  (*** WARNING *** : algselect=0000 will cause the mbist controller to report DONE & PASS immediately without doing anything!!)
    ;   |  |  |  |  |  |  +----------------------------- [9]  sysreg_MG_mbist_algselect_tr[1]
    ;   |  |  |  |  |  +-------------------------------- [10] sysreg_MG_mbist_algselect_tr[2]
    ;   |  |  |  |  +----------------------------------- [11] sysreg_MG_mbist_algselect_tr[3]
    ;   |  |  |  |
    ;   |  |  |  +-------------------------------------- [12] reserved
    ;   |  |  +----------------------------------------- [13] reserved
    ;   |  +-------------------------------------------- [14] reserved
    ;   +----------------------------------------------- [15] reserved

EFUSE_CTRL   .set 0x1C54
    ; EFUSE_CTRL   Address:  0x1C54 (IO space)          EFUSE CTRL Register
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ; |15:14:13:12|11:10: 9: 8| 7: 6: 5: 4| 3: 2: 1: 0|  <<== Bit Position
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; |r :r :r :r |r :r :r :r |r :r :r :r |r :r :r :rw|  <<== Read / Write Access
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; | 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0|  <<== Reset Values
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |        *** This register must be unlocked with the TEST_LOCK register before it can be written ***
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-- [0]  sys_initz       (0: holds the efuse controller in reset, 1: efuse controller released from reset)
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  +----- [1]  efc_ready       (Status of efuse controller:  0: not finished shifting the repair chain, 1: finished shifting the repair chain)
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  +-------- [2]  reserved
    ;   |  |  |  |  |  |  |  |  |  |  |  |  +----------- [3]  reserved
    ;   |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  +-------------- [4]  efc_error[0]    (Error Status of the efuse controller.  Non zero indicates an error occured while
    ;   |  |  |  |  |  |  |  |  |  |  +----------------- [5]  efc_error[1]     shifting the repair data.  Register is updated at the same time as efc_ready.
    ;   |  |  |  |  |  |  |  |  |  +-------------------- [6]  efc_error[2]     See the C027 fuse_farm controller documentation for error codes.)
    ;   |  |  |  |  |  |  |  |  +----------------------- [7]  efc_error[3]
    ;   |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  +-------------------------- [8]  efc_error[4]
    ;   |  |  |  |  |  |  +----------------------------- [9]  reserved
    ;   |  |  |  |  |  +-------------------------------- [10] reserved
    ;   |  |  |  |  +----------------------------------- [11] reserved
    ;   |  |  |  |
    ;   |  |  |  +-------------------------------------- [12] reserved
    ;   |  |  +----------------------------------------- [13] reserved
    ;   |  +-------------------------------------------- [14] reserved
    ;   +----------------------------------------------- [15] reserved

TEST_LOCK   .set 0x1C55
    ; TEST_LOCK   Address:  0x1C55 (IO space)          **Undocumented** Test Lock Register
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ; |15:14:13:12|11:10: 9: 8| 7: 6: 5: 4| 3: 2: 1: 0|  <<== Bit Position
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; |rw:rw:rw:rw|rw:rw:rw:rw|rw:rw:rw:rw|rw:rw:rw:rw|  <<== Read / Write Access
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; | 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0|  <<== Reset Values
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-- [0]  test_lock[0]    (Certain values in test_lock[15:0] unlock other test registers for writes:
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  +----- [1]  test_lock[1]        EFUSE_CTRL    : cannot be written unless unlocked first with code 0x569A
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  +-------- [2]  test_lock[2]        SET_REF_TRIM  : cannot be written unless unlocked first with code 0xC001
    ;   |  |  |  |  |  |  |  |  |  |  |  |  +----------- [3]  test_lock[3]    )
    ;   |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  +-------------- [4]  test_lock[4]    (note: the TEST_LOCK register is not self-clearing.  Software should write
    ;   |  |  |  |  |  |  |  |  |  |  +----------------- [5]  test_lock[5]           0x0000 to re-lock the test registers after they're initialized.)
    ;   |  |  |  |  |  |  |  |  |  +-------------------- [6]  test_lock[6]
    ;   |  |  |  |  |  |  |  |  +----------------------- [7]  test_lock[7]
    ;   |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  +-------------------------- [8]  test_lock[8]
    ;   |  |  |  |  |  |  +----------------------------- [9]  test_lock[9]
    ;   |  |  |  |  |  +-------------------------------- [10] test_lock[10]
    ;   |  |  |  |  +----------------------------------- [11] test_lock[11]
    ;   |  |  |  |
    ;   |  |  |  +-------------------------------------- [12] test_lock[12]
    ;   |  |  +----------------------------------------- [13] test_lock[13]
    ;   |  +-------------------------------------------- [14] test_lock[14]
    ;   +----------------------------------------------- [15] test_lock[15]
EFUSE_TRIM_CHNG_KEY     .set    0x569A
SET_REF_TRIM_CHNG_KEY   .set    0xC001

TEST_OBSERVE0        .set    0x1C56        ; Test Observation Register #0
    ; TEST_OBSERVE0   Address:  0x1C56 (IO space)
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ; |15:14:13:12|11:10: 9: 8| 7: 6: 5: 4| 3: 2: 1: 0|  <<== Bit Position
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; |r :r :r :r |r :r :r :r |r :r :r :r |r :r :r :r |  <<== Read / Write Access
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; | ?: ?: ?: ?| ?: ?: ?: ?| ?: ?: ?: ?| ?: ?: ?: ?|  <<== Reset Values
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-- [0]  JTAG_SecurityBit[0]     (read-only)
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  +----- [1]  JTAG_SecurityBit[1]     (read-only)
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  +-------- [2]  JTAG_SecurityBit[2]     (read-only)
    ;   |  |  |  |  |  |  |  |  |  |  |  |  +----------- [3]  JTAG_SecurityLocked     (read-only -- 0:unlocked, 1:locked)
    ;   |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  +-------------- [4]  reserved
    ;   |  |  |  |  |  |  |  |  |  |  +----------------- [5]  reserved
    ;   |  |  |  |  |  |  |  |  |  +-------------------- [6]  reserved
    ;   |  |  |  |  |  |  |  |  +----------------------- [7]  reserved
    ;   |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  +-------------------------- [8]  reserved
    ;   |  |  |  |  |  |  +----------------------------- [9]  reserved
    ;   |  |  |  |  |  +-------------------------------- [10] reserved
    ;   |  |  |  |  +----------------------------------- [11] reserved
    ;   |  |  |  |
    ;   |  |  |  +-------------------------------------- [12] reserved
    ;   |  |  +----------------------------------------- [13] reserved
    ;   |  +-------------------------------------------- [14] reserved
    ;   +----------------------------------------------- [15] reserved

TEST_OBSERVE1        .set    0x1C57        ; Test Observation Register #1
    ; TEST_OBSERVE1   Address:  0x1C57 (IO space)
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ; |15:14:13:12|11:10: 9: 8| 7: 6: 5: 4| 3: 2: 1: 0|  <<== Bit Position
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; |r :r :r :r |r :r :r :r |r :r :r :r |r :r :r :r |  <<== Read / Write Access
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; | ?: ?: ?: ?| ?: ?: ?: ?| ?: ?: ?: ?| ?: ?: ?: ?|  <<== Reset Values
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-- [0]  reserved
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  +----- [1]  reserved
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  +-------- [2]  reserved
    ;   |  |  |  |  |  |  |  |  |  |  |  |  +----------- [3]  reserved
    ;   |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  +-------------- [4]  reserved
    ;   |  |  |  |  |  |  |  |  |  |  +----------------- [5]  reserved
    ;   |  |  |  |  |  |  |  |  |  +-------------------- [6]  reserved
    ;   |  |  |  |  |  |  |  |  +----------------------- [7]  reserved
    ;   |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  +-------------------------- [8]  reserved
    ;   |  |  |  |  |  |  +----------------------------- [9]  reserved
    ;   |  |  |  |  |  +-------------------------------- [10] reserved
    ;   |  |  |  |  +----------------------------------- [11] reserved
    ;   |  |  |  |
    ;   |  |  |  +-------------------------------------- [12] reserved
    ;   |  |  +----------------------------------------- [13] reserved
    ;   |  +-------------------------------------------- [14] reserved
    ;   +----------------------------------------------- [15] reserved

;****************************************************************************************
;        Clock Domain Registers
;****************************************************************************************
IDLE_ICR        .set    0x0001        ; IDLE Control Register
    ; IDLE_ICR   Address:  0x0001 (IO Space)             IDLE Control Register
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ; |15:14:13:12|11:10: 9: 8| 7: 6: 5: 4| 3: 2: 1: 0|  <<== Bit Position
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; |rw:rw:rw:rw|rw:rw:rw:rw|rw:rw:rw:rw|rw:rw:rw:rw|  <<== Read / Write Access
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; | 1: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0|  <<== Reset Values
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-- [0]  CPU_IDLE          (0:active, 1:idled)
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  +----- [1]  reserved, writes should set to 1
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  +-------- [2]  reserved, writes should set to 1
    ;   |  |  |  |  |  |  |  |  |  |  |  |  +----------- [3]  reserved, writes should set to 1
    ;   |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  +-------------- [4]  CLK_IDLE  *** reserved, writes should set to 0 ***
    ;   |  |  |  |  |  |  |  |  |  |  +----------------- [5]  DPORT_IDLE        (0:active, 1:idled)
    ;   |  |  |  |  |  |  |  |  |  +-------------------- [6]  XPORT_IDLE        (0:active, 1:idled - CPUI must be idled too)
    ;   |  |  |  |  |  |  |  |  +----------------------- [7]  MPORT_IDLE        (0:active, 1:idled - DMA must be idled too)
    ;   |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  +-------------------------- [8]  IPORT_IDLE        (0:active, 1:idled)
    ;   |  |  |  |  |  |  +----------------------------- [9]  HWA_IDLE          (0:active, 1:idled)
    ;   |  |  |  |  |  +-------------------------------- [10] reserved
    ;   |  |  |  |  +----------------------------------- [11] reserved
    ;   |  |  |  |
    ;   |  |  |  +-------------------------------------- [12] reserved
    ;   |  |  +----------------------------------------- [13] reserved
    ;   |  +-------------------------------------------- [14] reserved
    ;   +----------------------------------------------- [15] reserved
IDLE_ST         .set    0x0002        ; Idle Status Register
    ; IDLE_ST   Address:  0x0002 (IO Space)              Idle Status Register
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ; |15:14:13:12|11:10: 9: 8| 7: 6: 5: 4| 3: 2: 1: 0|  <<== Bit Position
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; |r :r :r :r |r :r :r :r |r :r :r :r |r :r :r :r |  <<== Read / Write Access
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; | 1: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0|  <<== Reset Values
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-- [0]  CPUIS     (0:active, 1:idled)
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  +----- [1]  reserved
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  +-------- [2]  reserved
    ;   |  |  |  |  |  |  |  |  |  |  |  |  +----------- [3]  reserved
    ;   |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  +-------------- [4]  reserved
    ;   |  |  |  |  |  |  |  |  |  |  +----------------- [5]  DPORTIS       (0:active, 1:idled)
    ;   |  |  |  |  |  |  |  |  |  +-------------------- [6]  XPORTIS       (0:active, 1:idled)
    ;   |  |  |  |  |  |  |  |  +----------------------- [7]  MPORTIS       (0:active, 1:idled)
    ;   |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  +-------------------------- [8]  IPORTIS       (0:active, 1:idled)
    ;   |  |  |  |  |  |  +----------------------------- [9]  HWAIS         (0:active, 1:idled)
    ;   |  |  |  |  |  +-------------------------------- [10] reserved
    ;   |  |  |  |  +----------------------------------- [11] reserved
    ;   |  |  |  |
    ;   |  |  |  +-------------------------------------- [12] reserved
    ;   |  |  +----------------------------------------- [13] reserved
    ;   |  +-------------------------------------------- [14] reserved
    ;   +----------------------------------------------- [15] reserved

;----------------------------------------------------------------------------------------
;        ICR Bit Fields
;----------------------------------------------------------------------------------------
CPU_IDLE        .set    1b          ; CPU Idle Control Bit
CLK_IDLE        .set    1b<<4       ; Clock Generator Idle Control Bit
DPORT_IDLE      .set    1b<<5       ; DPORT Idle Control Bit
XPORT_IDLE      .set    1b<<6       ; XPORT Idle Control Bit
MPORT_IDLE      .set    1b<<7       ; MPORT Idle Control Bit
IPORT_IDLE      .set    1b<<8       ; IPORT Idle Control Bit
HWA_IDLE        .set    1b<<9       ; HWA Idle Control Bit
RESERVED_ICR    .set    1111110000001110b       ; Reserved bits (UMA peripheral, DMA, cache)

;----------------------------------------------------------------------------------------
;        Clock Control Register Bit Fields
;----------------------------------------------------------------------------------------
CRYSTAL             .set    0x0000      ; Selects Crystal Clock
PLL_SYSTEM          .set    0x0001      ; Selects PLL as system clock
PLL_SRC             .set    0x8000      ; Selects PLL as SRC clock
PLL_ANALOG          .set    0x4000      ; Selects PLL as Analog clock

;****************************************************************************************
;    USB/EMIF System Control Register Bit Fields
;****************************************************************************************
FULL_ACCESS         .set    00b      ; Access the whole 16-bit XPORT space 
HI_BYTE_ACCESS      .set    01b      ; Access higher byte of the 16-bit XPORT space
LO_BYTE_ACCESS      .set    10b      ; Access lower byte of the 16-bit XPORT space

USB_OSC_GZ_NORMAL    .set   0b<<2    ; Normal operating mode
USB_OSC_GZ_DISABLE   .set   1b<<2    ; Oscillator disabled/XO is tristate/Y is low
USB_OSC_INT_RESISTOR .set   0b<<3    ; Normal operating mode WITH internal bias resistor
USB_OSC_EXT_RESISTOR .set   1b<<3    ; Normal operationg mode WITHOUT internal bias resistor/resistor is external/tester mode
USB_DPDM_INVPOLARITY  .set  0b<<6    ; Reverse polarity of DP & DM
USB_DPDM_NORMPOLARITY .set  1b<<6    ; Normal Polarity of DP & DM
USB_PLLON           .set    0b<<12   ; Normal USB behavior
USB_PLLOFF          .set    1b<<12   ; Override USB SUSPENDM behavior and force release of PLL from suspend state
USB_VBUS_COMP_OFF   .set    0b<<13   ; VBUS Comparators OFF (except sessionend comparator)
USB_VBUS_COMP_ON    .set    1b<<13   ; VBUS Comparators ON
USB_SESSEND_COMP_OFF  .set  0b<<14   ; VBUS SESSIONEND comparator OFF	
USB_SESSEND_COMP_ON   .set  1b<<14   ; VBUS SESSIONEND comparator ON	
USB_PWRUP           .set    0b<<15   ; USB powered on
USB_PWRDN           .set    1b<<15   ; USB powered-down
;****************************************************************************************

;****************************************************************************************
;         DMA 0
;**************************************************************************
;        DMA0 Ch0 Register Addresses
;**************************************************************************
DMA0_CH0_SRC_LSW        .set     0x0c00    ; DMA0 Channel 0 Source LSW Address
    ; DMA0_CH0_SRC_LSW   Address:  0x0c00 (IO space)      DMA0 Channel 0 Source LSW Address
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ; |15:14:13:12|11:10: 9: 8| 7: 6: 5: 4| 3: 2: 1: 0|  <<== Bit Position
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; |rw:rw:rw:rw|rw:rw:rw:rw|rw:rw:rw:rw|rw:rw:rw:rw|  <<== Read / Write Access
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; | 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0|  <<== Reset Values
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-- [0]  DMASrcByteAddr[0]     ( Psuedo Code for setting DMA SRC/DEST Addresses:
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  +----- [1]  DMASrcByteAddr[1]      if( io_space ) {
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  +-------- [2]  DMASrcByteAddr[2]          DMASrcByteAddr[17:0] = DSP_IOPORT_ADDR;
    ;   |  |  |  |  |  |  |  |  |  |  |  |  +----------- [3]  DMASrcByteAddr[3]      } elsif( daram ) {
    ;   |  |  |  |  |  |  |  |  |  |  |  |                                               DMASrcByteAddr[17:0] = 0x10000 + DSP_BYTE_ADDR;
    ;   |  |  |  |  |  |  |  |  |  |  |  +-------------- [4]  DMASrcByteAddr[4]      } elsif( saram ) {
    ;   |  |  |  |  |  |  |  |  |  |  +----------------- [5]  DMASrcByteAddr[5]          DMASrcByteAddr[17:0] = 0x20000 + DSP_BYTE_ADDR;
    ;   |  |  |  |  |  |  |  |  |  +-------------------- [6]  DMASrcByteAddr[6]      }
    ;   |  |  |  |  |  |  |  |  +----------------------- [7]  DMASrcByteAddr[7] 
    ;   |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  +-------------------------- [8]  DMASrcByteAddr[8]      DMA0 can see: 
    ;   |  |  |  |  |  |  +----------------------------- [9]  DMASrcByteAddr[9]      DMA1 can see: 
    ;   |  |  |  |  |  +-------------------------------- [10] DMASrcByteAddr[10]     DMA2 can see: 
    ;   |  |  |  |  +----------------------------------- [11] DMASrcByteAddr[11]     DMA3 can see: )
    ;   |  |  |  |
    ;   |  |  |  +-------------------------------------- [12] DMASrcByteAddr[12]
    ;   |  |  +----------------------------------------- [13] DMASrcByteAddr[13]
    ;   |  +-------------------------------------------- [14] DMASrcByteAddr[14]
    ;   +----------------------------------------------- [15] DMASrcByteAddr[15]
DMA0_CH0_SRC_MSW        .set     0x0c01    ; DMA0 Channel 0 Source MSW Address
    ; DMA0_CH0_SRC_MSW   Address:  0x0c01 (IO space)      DMA0 Channel 0 Source MSW Address
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ; |15:14:13:12|11:10: 9: 8| 7: 6: 5: 4| 3: 2: 1: 0|  <<== Bit Position
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; |r :r :r :r |r :r :r :r |r :r :r :r |r :r :rw:rw|  <<== Read / Write Access
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; | 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0|  <<== Reset Values
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-- [0]  DMASrcByteAddr[16]
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  +----- [1]  DMASrcByteAddr[17]
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  +-------- [2]  reserved
    ;   |  |  |  |  |  |  |  |  |  |  |  |  +----------- [3]  reserved
    ;   |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  +-------------- [4]  reserved
    ;   |  |  |  |  |  |  |  |  |  |  +----------------- [5]  reserved
    ;   |  |  |  |  |  |  |  |  |  +-------------------- [6]  reserved
    ;   |  |  |  |  |  |  |  |  +----------------------- [7]  reserved
    ;   |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  +-------------------------- [8]  reserved
    ;   |  |  |  |  |  |  +----------------------------- [9]  reserved
    ;   |  |  |  |  |  +-------------------------------- [10] reserved
    ;   |  |  |  |  +----------------------------------- [11] reserved
    ;   |  |  |  |
    ;   |  |  |  +-------------------------------------- [12] reserved
    ;   |  |  +----------------------------------------- [13] reserved
    ;   |  +-------------------------------------------- [14] reserved
    ;   +----------------------------------------------- [15] reserved
DMA0_CH0_DST_LSW        .set     0x0c02    ; DMA0 Channel 0 Destination LSW Address
    ; DMA0_CH0_DST_LSW   Address:  0x0c02 (IO space)      DMA0 Channel 0 Destination LSW Address
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ; |15:14:13:12|11:10: 9: 8| 7: 6: 5: 4| 3: 2: 1: 0|  <<== Bit Position
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; |rw:rw:rw:rw|rw:rw:rw:rw|rw:rw:rw:rw|rw:rw:rw:rw|  <<== Read / Write Access
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; | 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0|  <<== Reset Values
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-- [0]  DMADestByteAddr[0]    ( Psuedo Code for setting DMA SRC/DEST Addresses:
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  +----- [1]  DMADestByteAddr[1]     if( io_space ) {
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  +-------- [2]  DMADestByteAddr[2]         DMADestByteAddr[17:0] = DSP_IOPORT_ADDR;
    ;   |  |  |  |  |  |  |  |  |  |  |  |  +----------- [3]  DMADestByteAddr[3]     } elsif( daram ) {
    ;   |  |  |  |  |  |  |  |  |  |  |  |                                              DMADestByteAddr[17:0] = 0x10000 + DSP_BYTE_ADDR;
    ;   |  |  |  |  |  |  |  |  |  |  |  +-------------- [4]  DMADestByteAddr[4]     } elsif( saram ) {
    ;   |  |  |  |  |  |  |  |  |  |  +----------------- [5]  DMADestByteAddr[5]         DMADestByteAddr[17:0] = 0x20000 + DSP_BYTE_ADDR;
    ;   |  |  |  |  |  |  |  |  |  +-------------------- [6]  DMADestByteAddr[6]     }
    ;   |  |  |  |  |  |  |  |  +----------------------- [7]  DMADestByteAddr[7] 
    ;   |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  +-------------------------- [8]  DMADestByteAddr[8]      DMA0 can see: 
    ;   |  |  |  |  |  |  +----------------------------- [9]  DMADestByteAddr[9]      DMA1 can see: 
    ;   |  |  |  |  |  +-------------------------------- [10] DMADestByteAddr[10]     DMA2 can see: 
    ;   |  |  |  |  +----------------------------------- [11] DMADestByteAddr[11]     DMA3 can see: )
    ;   |  |  |  |
    ;   |  |  |  +-------------------------------------- [12] DMADestByteAddr[12]
    ;   |  |  +----------------------------------------- [13] DMADestByteAddr[13]
    ;   |  +-------------------------------------------- [14] DMADestByteAddr[14]
    ;   +----------------------------------------------- [15] DMADestByteAddr[15]
DMA0_CH0_DST_MSW        .set     0x0c03    ; DMA0 Channel 0 Destination MSW Address
    ; DMA0_CH0_DST_MSW   Address:  0x0c03 (IO space)      DMA0 Channel 0 Destination MSW Address
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ; |15:14:13:12|11:10: 9: 8| 7: 6: 5: 4| 3: 2: 1: 0|  <<== Bit Position
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; |r :r :r :r |r :r :r :r |r :r :r :r |r :r :rw:rw|  <<== Read / Write Access
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; | 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0|  <<== Reset Values
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-- [0]  DMADestByteAddr[16]
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  +----- [1]  DMADestByteAddr[17]
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  +-------- [2]  reserved
    ;   |  |  |  |  |  |  |  |  |  |  |  |  +----------- [3]  reserved
    ;   |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  +-------------- [4]  reserved
    ;   |  |  |  |  |  |  |  |  |  |  +----------------- [5]  reserved
    ;   |  |  |  |  |  |  |  |  |  +-------------------- [6]  reserved
    ;   |  |  |  |  |  |  |  |  +----------------------- [7]  reserved
    ;   |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  +-------------------------- [8]  reserved
    ;   |  |  |  |  |  |  +----------------------------- [9]  reserved
    ;   |  |  |  |  |  +-------------------------------- [10] reserved
    ;   |  |  |  |  +----------------------------------- [11] reserved
    ;   |  |  |  |
    ;   |  |  |  +-------------------------------------- [12] reserved
    ;   |  |  +----------------------------------------- [13] reserved
    ;   |  +-------------------------------------------- [14] reserved
    ;   +----------------------------------------------- [15] reserved
DMA0_CH0_TC_LEN         .set     0x0c04    ; DMA0 Channel 0 Length / Transfer Control LSW Register
    ; DMA0_CH0_TC_LEN   Address:  0x0c04 (IO space)      DMA0 Channel 0 Length / Transfer Control LSW Register
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ; |15:14:13:12|11:10: 9: 8| 7: 6: 5: 4| 3: 2: 1: 0|  <<== Bit Position
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; |rw:rw:rw:rw|rw:rw:rw:rw|rw:rw:rw:rw|rw:rw:r :r |  <<== Read / Write Access
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; | 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0|  <<== Reset Values
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |   ( XferLength[15:0] = number of bytes to be transfered)
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-- [0]  XferLength[0]
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  +----- [1]  XferLength[1]
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  +-------- [2]  XferLength[2]
    ;   |  |  |  |  |  |  |  |  |  |  |  |  +----------- [3]  XferLength[3]
    ;   |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  +-------------- [4]  XferLength[4]
    ;   |  |  |  |  |  |  |  |  |  |  +----------------- [5]  XferLength[5]
    ;   |  |  |  |  |  |  |  |  |  +-------------------- [6]  XferLength[6]
    ;   |  |  |  |  |  |  |  |  +----------------------- [7]  XferLength[7]
    ;   |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  +-------------------------- [8]  XferLength[8]
    ;   |  |  |  |  |  |  +----------------------------- [9]  XferLength[9]
    ;   |  |  |  |  |  +-------------------------------- [10] XferLength[10]
    ;   |  |  |  |  +----------------------------------- [11] XferLength[11]
    ;   |  |  |  |
    ;   |  |  |  +-------------------------------------- [12] XferLength[12]
    ;   |  |  +----------------------------------------- [13] XferLength[13]
    ;   |  +-------------------------------------------- [14] XferLength[14]
    ;   +----------------------------------------------- [15] XferLength[15]
DMA0_CH0_TC_MSW         .set     0x0c05    ; DMA0 Channel 0 Transfer Control MSW Register
    ; DMA0_CH0_TC_MSW   Address:  0x0c05 (IO space)      DMA0 Channel 0 Transfer Control MSW Register
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ; |15:14:13:12|11:10: 9: 8| 7: 6: 5: 4| 3: 2: 1: 0|  <<== Bit Position
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; |rw:rw:rw:rw|r :r :rw:rw|rw:rw:rw:rw|rw:r :rw:rw|  <<== Read / Write Access
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; | 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0|  <<== Reset Values
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+                     
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |                      
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-- [0]  SourceSize[0]      Source Data Size:
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  +----- [1]  SourceSize[1]      (00: 32-bit, 01: 16-bit, 10: 8-bit,  11: Reserved)
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  +-------- [2]  Sync               (1: DMA transfers one burst-mode length of 32-bit words per one peripheral event, 0: DMA transfers not controlled by peripheral events)
    ;   |  |  |  |  |  |  |  |  |  |  |  |  +----------- [3]  BurstMode[0]       (000:1 32bit word burst, 001:2 32bit word burst,
    ;   |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  +-------------- [4]  BurstMode[1]        010:4 32bit word burst, 011:8 32bit word burst,
    ;   |  |  |  |  |  |  |  |  |  |  +----------------- [5]  BurstMode[2]        100:16 32bit word burst, others:reserved)
    ;   |  |  |  |  |  |  |  |  |  +-------------------- [6]  SrcAddrMode[0]     (00:autoincr, 10:src addr is fixed, others:reserved)
    ;   |  |  |  |  |  |  |  |  +----------------------- [7]  SrcAddrMode[1]
    ;   |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  +-------------------------- [8]  DestAddrMode[0]    (00:autoincr, 10:dest addr is fixed, others:reserved)
    ;   |  |  |  |  |  |  +----------------------------- [9]  DestAddrMode[1]
    ;   |  |  |  |  |  +-------------------------------- [10] DestSize[0]        Destination data size:
    ;   |  |  |  |  +----------------------------------- [11] DestSize[1]        (00: 32-bit, 01: 16-bit, 10: 8-bit,  11: Reserved)
    ;   |  |  |  |
    ;   |  |  |  +-------------------------------------- [12] AutoReload        (0:disabled, to restart DMA set start bit = 1; 1:enabled, to stop DMA from reloading set start bit = 0 )
    ;   |  |  +----------------------------------------- [13] InterruptEn       (0:no interrupts generated, 1:interrupt generated when xfer complete)
    ;   |  +-------------------------------------------- [14] Status            (0:channel inactive, 1:channel active)
    ;   +----------------------------------------------- [15] Start/Stop        (0:stops after burst is complete, 1:starts block xfer)

;**************************************************************************
;        DMA0 Ch1 Register Addresses
;**************************************************************************
DMA0_CH1_SRC_LSW        .set     0x0c20    ; DMA0 Channel 1 Source LSW Address
    ; DMA0_CH1_SRC_LSW   Address:  0x0c20 (IO space)      DMA0 Channel 1 Source LSW Address
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ; |15:14:13:12|11:10: 9: 8| 7: 6: 5: 4| 3: 2: 1: 0|  <<== Bit Position
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; |rw:rw:rw:rw|rw:rw:rw:rw|rw:rw:rw:rw|rw:rw:rw:rw|  <<== Read / Write Access
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; | 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0|  <<== Reset Values
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-- [0]  DMASrcByteAddr[0]     ( Psuedo Code for setting DMA SRC/DEST Addresses:
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  +----- [1]  DMASrcByteAddr[1]      if( io_space ) {
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  +-------- [2]  DMASrcByteAddr[2]          DMASrcByteAddr[17:0] = DSP_IOPORT_ADDR;
    ;   |  |  |  |  |  |  |  |  |  |  |  |  +----------- [3]  DMASrcByteAddr[3]      } elsif( daram ) {
    ;   |  |  |  |  |  |  |  |  |  |  |  |                                               DMASrcByteAddr[17:0] = 0x10000 + DSP_BYTE_ADDR;
    ;   |  |  |  |  |  |  |  |  |  |  |  +-------------- [4]  DMASrcByteAddr[4]      } elsif( saram ) {
    ;   |  |  |  |  |  |  |  |  |  |  +----------------- [5]  DMASrcByteAddr[5]          DMASrcByteAddr[17:0] = 0x20000 + DSP_BYTE_ADDR;
    ;   |  |  |  |  |  |  |  |  |  +-------------------- [6]  DMASrcByteAddr[6]      }
    ;   |  |  |  |  |  |  |  |  +----------------------- [7]  DMASrcByteAddr[7] 
    ;   |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  +-------------------------- [8]  DMASrcByteAddr[8]      DMA0 can see: 
    ;   |  |  |  |  |  |  +----------------------------- [9]  DMASrcByteAddr[9]      DMA1 can see: 
    ;   |  |  |  |  |  +-------------------------------- [10] DMASrcByteAddr[10]   DMA2 can see: 
    ;   |  |  |  |  +----------------------------------- [11] DMASrcByteAddr[11]   DMA3 can see: )
    ;   |  |  |  |
    ;   |  |  |  +-------------------------------------- [12] DMASrcByteAddr[12]
    ;   |  |  +----------------------------------------- [13] DMASrcByteAddr[13]
    ;   |  +-------------------------------------------- [14] DMASrcByteAddr[14]
    ;   +----------------------------------------------- [15] DMASrcByteAddr[15]
DMA0_CH1_SRC_MSW        .set     0x0c21    ; DMA0 Channel 1 Source MSW Address
    ; DMA0_CH1_SRC_MSW   Address:  0x0c21 (IO space)      DMA0 Channel 1 Source MSW Address
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ; |15:14:13:12|11:10: 9: 8| 7: 6: 5: 4| 3: 2: 1: 0|  <<== Bit Position
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; |r :r :r :r |r :r :r :r |r :r :r :r |r :r :rw:rw|  <<== Read / Write Access
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; | 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0|  <<== Reset Values
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-- [0]  DMASrcByteAddr[16]
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  +----- [1]  DMASrcByteAddr[17]
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  +-------- [2]  reserved
    ;   |  |  |  |  |  |  |  |  |  |  |  |  +----------- [3]  reserved
    ;   |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  +-------------- [4]  reserved
    ;   |  |  |  |  |  |  |  |  |  |  +----------------- [5]  reserved
    ;   |  |  |  |  |  |  |  |  |  +-------------------- [6]  reserved
    ;   |  |  |  |  |  |  |  |  +----------------------- [7]  reserved
    ;   |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  +-------------------------- [8]  reserved
    ;   |  |  |  |  |  |  +----------------------------- [9]  reserved
    ;   |  |  |  |  |  +-------------------------------- [10] reserved
    ;   |  |  |  |  +----------------------------------- [11] reserved
    ;   |  |  |  |
    ;   |  |  |  +-------------------------------------- [12] reserved
    ;   |  |  +----------------------------------------- [13] reserved
    ;   |  +-------------------------------------------- [14] reserved
    ;   +----------------------------------------------- [15] reserved
DMA0_CH1_DST_LSW        .set     0x0c22    ; DMA0 Channel 1 Destination LSW Address
    ; DMA0_CH1_DST_LSW   Address:  0x0c22 (IO space)      DMA0 Channel 1 Destination LSW Address
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ; |15:14:13:12|11:10: 9: 8| 7: 6: 5: 4| 3: 2: 1: 0|  <<== Bit Position
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; |rw:rw:rw:rw|rw:rw:rw:rw|rw:rw:rw:rw|rw:rw:rw:rw|  <<== Read / Write Access
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; | 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0|  <<== Reset Values
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-- [0]  DMADestByteAddr[0]    ( Psuedo Code for setting DMA SRC/DEST Addresses:
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  +----- [1]  DMADestByteAddr[1]     if( io_space ) {
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  +-------- [2]  DMADestByteAddr[2]         DMADestByteAddr[17:0] = DSP_IOPORT_ADDR;
    ;   |  |  |  |  |  |  |  |  |  |  |  |  +----------- [3]  DMADestByteAddr[3]     } elsif( daram ) {
    ;   |  |  |  |  |  |  |  |  |  |  |  |                                              DMADestByteAddr[17:0] = 0x10000 + DSP_BYTE_ADDR;
    ;   |  |  |  |  |  |  |  |  |  |  |  +-------------- [4]  DMADestByteAddr[4]     } elsif( saram ) {
    ;   |  |  |  |  |  |  |  |  |  |  +----------------- [5]  DMADestByteAddr[5]         DMADestByteAddr[17:0] = 0x20000 + DSP_BYTE_ADDR;
    ;   |  |  |  |  |  |  |  |  |  +-------------------- [6]  DMADestByteAddr[6]     }
    ;   |  |  |  |  |  |  |  |  +----------------------- [7]  DMADestByteAddr[7] 
    ;   |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  +-------------------------- [8]  DMADestByteAddr[8]      DMA0 can see: 
    ;   |  |  |  |  |  |  +----------------------------- [9]  DMADestByteAddr[9]      DMA1 can see: 
    ;   |  |  |  |  |  +-------------------------------- [10] DMADestByteAddr[10]   DMA2 can see: 
    ;   |  |  |  |  +----------------------------------- [11] DMADestByteAddr[11]   DMA3 can see: )
    ;   |  |  |  |
    ;   |  |  |  +-------------------------------------- [12] DMADestByteAddr[12]
    ;   |  |  +----------------------------------------- [13] DMADestByteAddr[13]
    ;   |  +-------------------------------------------- [14] DMADestByteAddr[14]
    ;   +----------------------------------------------- [15] DMADestByteAddr[15]
DMA0_CH1_DST_MSW        .set     0x0c23    ; DMA0 Channel 1 Destination MSW Address
    ; DMA0_CH1_DST_MSW   Address:  0x0c23 (IO space)      DMA0 Channel 1 Destination MSW Address
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ; |15:14:13:12|11:10: 9: 8| 7: 6: 5: 4| 3: 2: 1: 0|  <<== Bit Position
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; |r :r :r :r |r :r :r :r |r :r :r :r |r :r :rw:rw|  <<== Read / Write Access
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; | 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0|  <<== Reset Values
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-- [0]  DMADestByteAddr[16]
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  +----- [1]  DMADestByteAddr[17]
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  +-------- [2]  reserved
    ;   |  |  |  |  |  |  |  |  |  |  |  |  +----------- [3]  reserved
    ;   |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  +-------------- [4]  reserved
    ;   |  |  |  |  |  |  |  |  |  |  +----------------- [5]  reserved
    ;   |  |  |  |  |  |  |  |  |  +-------------------- [6]  reserved
    ;   |  |  |  |  |  |  |  |  +----------------------- [7]  reserved
    ;   |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  +-------------------------- [8]  reserved
    ;   |  |  |  |  |  |  +----------------------------- [9]  reserved
    ;   |  |  |  |  |  +-------------------------------- [10] reserved
    ;   |  |  |  |  +----------------------------------- [11] reserved
    ;   |  |  |  |
    ;   |  |  |  +-------------------------------------- [12] reserved
    ;   |  |  +----------------------------------------- [13] reserved
    ;   |  +-------------------------------------------- [14] reserved
    ;   +----------------------------------------------- [15] reserved
DMA0_CH1_TC_LEN         .set     0x0c24    ; DMA0 Channel 1 Length / Transfer Control LSW Register
    ; DMA0_CH1_TC_LEN   Address:  0x0c24 (IO space)      DMA0 Channel 1 Length / Transfer Control LSW Register
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ; |15:14:13:12|11:10: 9: 8| 7: 6: 5: 4| 3: 2: 1: 0|  <<== Bit Position
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; |rw:rw:rw:rw|rw:rw:rw:rw|rw:rw:rw:rw|rw:rw:r :r |  <<== Read / Write Access
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; | 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0|  <<== Reset Values
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  ( XferLength[15:0] = number of bytes to be transfered)
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +--[0]  XferLength[0]
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-----[1]  XferLength[1]
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  +--------[2]  XferLength[2]
    ;   |  |  |  |  |  |  |  |  |  |  |  |  +-----------[3]  XferLength[3]
    ;   |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  +--------------[4]  XferLength[4]
    ;   |  |  |  |  |  |  |  |  |  |  +-----------------[5]  XferLength[5]
    ;   |  |  |  |  |  |  |  |  |  +--------------------[6]  XferLength[6]
    ;   |  |  |  |  |  |  |  |  +-----------------------[7]  XferLength[7]
    ;   |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  +--------------------------[8]  XferLength[8]
    ;   |  |  |  |  |  |  +-----------------------------[9]  XferLength[9]
    ;   |  |  |  |  |  +--------------------------------[10] XferLength[10]
    ;   |  |  |  |  +-----------------------------------[11] XferLength[11]
    ;   |  |  |  |
    ;   |  |  |  +--------------------------------------[12] XferLength[12]
    ;   |  |  +-----------------------------------------[13] XferLength[13]
    ;   |  +--------------------------------------------[14] XferLength[14]
    ;   +-----------------------------------------------[15] XferLength[15]
DMA0_CH1_TC_MSW         .set     0x0c25    ; DMA0 Channel 1 Transfer Control MSW Register
    ; DMA0_CH1_TC_MSW   Address:  0x0c25 (IO space)      DMA0 Channel 1 Transfer Control MSW Register
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ; |15:14:13:12|11:10: 9: 8| 7: 6: 5: 4| 3: 2: 1: 0|  <<== Bit Position
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; |rw:rw:rw:rw|r :r :rw:rw|rw:rw:rw:rw|rw:r :rw:rw|  <<== Read / Write Access
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; | 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0|  <<== Reset Values
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-- [0]  SourceSize[0]      Source Data Size:
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  +----- [1]  SourceSize[1]      (00: 32-bit, 01: 16-bit, 10: 8-bit,  11: Reserved)
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  +-------- [2]  Sync               (1: DMA transfers one burst-mode length of 32-bit words per one peripheral event, 0: DMA transfers not controlled by peripheral events)
    ;   |  |  |  |  |  |  |  |  |  |  |  |  +----------- [3]  BurstMode[0]       (000:1 32bit word burst, 001:2 32bit word burst,
    ;   |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  +-------------- [4]  BurstMode[1]        010:4 32bit word burst, 011:8 32bit word burst,
    ;   |  |  |  |  |  |  |  |  |  |  +----------------- [5]  BurstMode[2]        100:16 32bit word burst, others:reserved)
    ;   |  |  |  |  |  |  |  |  |  +-------------------- [6]  SrcAddrMode[0]     (00:autoincr, 10:src addr is fixed, others:reserved)
    ;   |  |  |  |  |  |  |  |  +----------------------- [7]  SrcAddrMode[1]
    ;   |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  +-------------------------- [8]  DestAddrMode[0]    (00:autoincr, 10:dest addr is fixed, others:reserved)
    ;   |  |  |  |  |  |  +----------------------------- [9]  DestAddrMode[1]
    ;   |  |  |  |  |  +-------------------------------- [10] DestSize[0]        Destination data size:
    ;   |  |  |  |  +----------------------------------- [11] DestSize[1]        (00: 32-bit, 01: 16-bit, 10: 8-bit,  11: Reserved)
    ;   |  |  |  |
    ;   |  |  |  +-------------------------------------- [12] AutoReload        (0:disabled, to restart DMA set start bit = 1; 1:enabled, to stop DMA from reloading set start bit = 0 )
    ;   |  |  +----------------------------------------- [13] InterruptEn       (0:no interrupts generated, 1:interrupt generated when xfer complete)
    ;   |  +-------------------------------------------- [14] Status            (0:channel inactive, 1:channel active)
    ;   +----------------------------------------------- [15] Start/Stop        (0:stops after burst is complete, 1:starts block xfer)

;**************************************************************************
;        DMA0 Ch2 Register Addresses
;**************************************************************************
DMA0_CH2_SRC_LSW        .set     0x0c40    ; DMA0 Channel 2 Source LSW Address
    ; DMA0_CH2_SRC_LSW   Address:  0x0c40 (IO space)      DMA0 Channel 2 Source LSW Address
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ; |15:14:13:12|11:10: 9: 8| 7: 6: 5: 4| 3: 2: 1: 0|  <<== Bit Position
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; |rw:rw:rw:rw|rw:rw:rw:rw|rw:rw:rw:rw|rw:rw:rw:rw|  <<== Read / Write Access
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; | 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0|  <<== Reset Values
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-- [0]  DMASrcByteAddr[0]     ( Psuedo Code for setting DMA SRC/DEST Addresses:
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  +----- [1]  DMASrcByteAddr[1]      if( io_space ) {
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  +-------- [2]  DMASrcByteAddr[2]          DMASrcByteAddr[17:0] = DSP_IOPORT_ADDR;
    ;   |  |  |  |  |  |  |  |  |  |  |  |  +----------- [3]  DMASrcByteAddr[3]      } elsif( daram ) {
    ;   |  |  |  |  |  |  |  |  |  |  |  |                                               DMASrcByteAddr[17:0] = 0x10000 + DSP_BYTE_ADDR;
    ;   |  |  |  |  |  |  |  |  |  |  |  +-------------- [4]  DMASrcByteAddr[4]      } elsif( saram ) {
    ;   |  |  |  |  |  |  |  |  |  |  +----------------- [5]  DMASrcByteAddr[5]          DMASrcByteAddr[17:0] = 0x20000 + DSP_BYTE_ADDR;
    ;   |  |  |  |  |  |  |  |  |  +-------------------- [6]  DMASrcByteAddr[6]      }
    ;   |  |  |  |  |  |  |  |  +----------------------- [7]  DMASrcByteAddr[7] 
    ;   |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  +-------------------------- [8]  DMASrcByteAddr[8]      DMA0 can see: 
    ;   |  |  |  |  |  |  +----------------------------- [9]  DMASrcByteAddr[9]      DMA1 can see: 
    ;   |  |  |  |  |  +-------------------------------- [10] DMASrcByteAddr[10]   DMA2 can see: 
    ;   |  |  |  |  +----------------------------------- [11] DMASrcByteAddr[11]   DMA3 can see: )
    ;   |  |  |  |
    ;   |  |  |  +-------------------------------------- [12] DMASrcByteAddr[12]
    ;   |  |  +----------------------------------------- [13] DMASrcByteAddr[13]
    ;   |  +-------------------------------------------- [14] DMASrcByteAddr[14]
    ;   +----------------------------------------------- [15] DMASrcByteAddr[15]
DMA0_CH2_SRC_MSW        .set     0x0c41    ; DMA0 Channel 2 Source MSW Address
    ; DMA0_CH2_SRC_MSW   Address:  0x0c41 (IO space)      DMA0 Channel 2 Source MSW Address
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ; |15:14:13:12|11:10: 9: 8| 7: 6: 5: 4| 3: 2: 1: 0|  <<== Bit Position
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; |r :r :r :r |r :r :r :r |r :r :r :r |r :r :rw:rw|  <<== Read / Write Access
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; | 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0|  <<== Reset Values
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-- [0]  DMASrcByteAddr[16]
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  +----- [1]  DMASrcByteAddr[17]
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  +-------- [2]  reserved
    ;   |  |  |  |  |  |  |  |  |  |  |  |  +----------- [3]  reserved
    ;   |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  +-------------- [4]  reserved
    ;   |  |  |  |  |  |  |  |  |  |  +----------------- [5]  reserved
    ;   |  |  |  |  |  |  |  |  |  +-------------------- [6]  reserved
    ;   |  |  |  |  |  |  |  |  +----------------------- [7]  reserved
    ;   |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  +-------------------------- [8]  reserved
    ;   |  |  |  |  |  |  +----------------------------- [9]  reserved
    ;   |  |  |  |  |  +-------------------------------- [10] reserved
    ;   |  |  |  |  +----------------------------------- [11] reserved
    ;   |  |  |  |
    ;   |  |  |  +-------------------------------------- [12] reserved
    ;   |  |  +----------------------------------------- [13] reserved
    ;   |  +-------------------------------------------- [14] reserved
    ;   +----------------------------------------------- [15] reserved
DMA0_CH2_DST_LSW        .set     0x0c42    ; DMA0 Channel 2 Destination LSW Address
    ; DMA0_CH2_DST_LSW   Address:  0x0c42 (IO space)      DMA0 Channel 2 Destination LSW Address
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ; |15:14:13:12|11:10: 9: 8| 7: 6: 5: 4| 3: 2: 1: 0|  <<== Bit Position
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; |rw:rw:rw:rw|rw:rw:rw:rw|rw:rw:rw:rw|rw:rw:rw:rw|  <<== Read / Write Access
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; | 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0|  <<== Reset Values
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-- [0]  DMADestByteAddr[0]    ( Psuedo Code for setting DMA SRC/DEST Addresses:
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  +----- [1]  DMADestByteAddr[1]     if( io_space ) {
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  +-------- [2]  DMADestByteAddr[2]         DMADestByteAddr[17:0] = DSP_IOPORT_ADDR;
    ;   |  |  |  |  |  |  |  |  |  |  |  |  +----------- [3]  DMADestByteAddr[3]     } elsif( daram ) {
    ;   |  |  |  |  |  |  |  |  |  |  |  |                                              DMADestByteAddr[17:0] = 0x10000 + DSP_BYTE_ADDR;
    ;   |  |  |  |  |  |  |  |  |  |  |  +-------------- [4]  DMADestByteAddr[4]     } elsif( saram ) {
    ;   |  |  |  |  |  |  |  |  |  |  +----------------- [5]  DMADestByteAddr[5]         DMADestByteAddr[17:0] = 0x20000 + DSP_BYTE_ADDR;
    ;   |  |  |  |  |  |  |  |  |  +-------------------- [6]  DMADestByteAddr[6]     }
    ;   |  |  |  |  |  |  |  |  +----------------------- [7]  DMADestByteAddr[7] 
    ;   |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  +-------------------------- [8]  DMADestByteAddr[8]      DMA0 can see: 
    ;   |  |  |  |  |  |  +----------------------------- [9]  DMADestByteAddr[9]      DMA1 can see: 
    ;   |  |  |  |  |  +-------------------------------- [10] DMADestByteAddr[10]   DMA2 can see: 
    ;   |  |  |  |  +----------------------------------- [11] DMADestByteAddr[11]   DMA3 can see: )
    ;   |  |  |  |
    ;   |  |  |  +-------------------------------------- [12] DMADestByteAddr[12]
    ;   |  |  +----------------------------------------- [13] DMADestByteAddr[13]
    ;   |  +-------------------------------------------- [14] DMADestByteAddr[14]
    ;   +----------------------------------------------- [15] DMADestByteAddr[15]
DMA0_CH2_DST_MSW        .set     0x0c43    ; DMA0 Channel 2 Destination MSW Address
    ; DMA0_CH2_DST_MSW   Address:  0x0c43 (IO space)      DMA0 Channel 2 Destination MSW Address
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ; |15:14:13:12|11:10: 9: 8| 7: 6: 5: 4| 3: 2: 1: 0|  <<== Bit Position
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; |r :r :r :r |r :r :r :r |r :r :r :r |r :r :rw:rw|  <<== Read / Write Access
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; | 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0|  <<== Reset Values
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-- [0]  DMADestByteAddr[16]
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  +----- [1]  DMADestByteAddr[17]
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  +-------- [2]  reserved
    ;   |  |  |  |  |  |  |  |  |  |  |  |  +----------- [3]  reserved
    ;   |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  +-------------- [4]  reserved
    ;   |  |  |  |  |  |  |  |  |  |  +----------------- [5]  reserved
    ;   |  |  |  |  |  |  |  |  |  +-------------------- [6]  reserved
    ;   |  |  |  |  |  |  |  |  +----------------------- [7]  reserved
    ;   |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  +-------------------------- [8]  reserved
    ;   |  |  |  |  |  |  +----------------------------- [9]  reserved
    ;   |  |  |  |  |  +-------------------------------- [10] reserved
    ;   |  |  |  |  +----------------------------------- [11] reserved
    ;   |  |  |  |
    ;   |  |  |  +-------------------------------------- [12] reserved
    ;   |  |  +----------------------------------------- [13] reserved
    ;   |  +-------------------------------------------- [14] reserved
    ;   +----------------------------------------------- [15] reserved
DMA0_CH2_TC_LEN         .set     0x0c44    ; DMA0 Channel 2 Length / Transfer Control LSW Register
    ; DMA0_CH2_TC_LEN   Address:  0x0c44 (IO space)      DMA0 Channel 2 Length / Transfer Control LSW Register
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ; |15:14:13:12|11:10: 9: 8| 7: 6: 5: 4| 3: 2: 1: 0|  <<== Bit Position
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; |rw:rw:rw:rw|rw:rw:rw:rw|rw:rw:rw:rw|rw:rw:r :r |  <<== Read / Write Access
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; | 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0|  <<== Reset Values
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |   ( XferLength[15:0] = number of bytes to be transfered)
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-- [0]  XferLength[0]
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  +----- [1]  XferLength[1]
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  +-------- [2]  XferLength[2]
    ;   |  |  |  |  |  |  |  |  |  |  |  |  +----------- [3]  XferLength[3]
    ;   |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  +-------------- [4]  XferLength[4]
    ;   |  |  |  |  |  |  |  |  |  |  +----------------- [5]  XferLength[5]
    ;   |  |  |  |  |  |  |  |  |  +-------------------- [6]  XferLength[6]
    ;   |  |  |  |  |  |  |  |  +----------------------- [7]  XferLength[7]
    ;   |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  +-------------------------- [8]  XferLength[8]
    ;   |  |  |  |  |  |  +----------------------------- [9]  XferLength[9]
    ;   |  |  |  |  |  +-------------------------------- [10] XferLength[10]
    ;   |  |  |  |  +----------------------------------- [11] XferLength[11]
    ;   |  |  |  |
    ;   |  |  |  +-------------------------------------- [12] XferLength[12]
    ;   |  |  +----------------------------------------- [13] XferLength[13]
    ;   |  +-------------------------------------------- [14] XferLength[14]
    ;   +----------------------------------------------- [15] XferLength[15]
DMA0_CH2_TC_MSW         .set     0x0c45    ; DMA0 Channel 2 Transfer Control MSW Register
    ; DMA0_CH2_TC_MSW   Address:  0x0c45 (IO space)      DMA0 Channel 2 Transfer Control MSW Register
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ; |15:14:13:12|11:10: 9: 8| 7: 6: 5: 4| 3: 2: 1: 0|  <<== Bit Position
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; |rw:rw:rw:rw|r :r :rw:rw|rw:rw:rw:rw|rw:r :rw:rw|  <<== Read / Write Access
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; | 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0|  <<== Reset Values
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-- [0]  SourceSize[0]      Source Data Size:
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  +----- [1]  SourceSize[1]      (00: 32-bit, 01: 16-bit, 10: 8-bit,  11: Reserved)
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  +-------- [2]  Sync               (1: DMA transfers one burst-mode length of 32-bit words per one peripheral event, 0: DMA transfers not controlled by peripheral events)
    ;   |  |  |  |  |  |  |  |  |  |  |  |  +----------- [3]  BurstMode[0]       (000:1 32bit word burst, 001:2 32bit word burst,
    ;   |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  +-------------- [4]  BurstMode[1]        010:4 32bit word burst, 011:8 32bit word burst,
    ;   |  |  |  |  |  |  |  |  |  |  +----------------- [5]  BurstMode[2]        100:16 32bit word burst, others:reserved)
    ;   |  |  |  |  |  |  |  |  |  +-------------------- [6]  SrcAddrMode[0]     (00:autoincr, 10:src addr is fixed, others:reserved)
    ;   |  |  |  |  |  |  |  |  +----------------------- [7]  SrcAddrMode[1]
    ;   |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  +-------------------------- [8]  DestAddrMode[0]    (00:autoincr, 10:dest addr is fixed, others:reserved)
    ;   |  |  |  |  |  |  +----------------------------- [9]  DestAddrMode[1]
    ;   |  |  |  |  |  +-------------------------------- [10] DestSize[0]        Destination data size:
    ;   |  |  |  |  +----------------------------------- [11] DestSize[1]        (00: 32-bit, 01: 16-bit, 10: 8-bit,  11: Reserved)
    ;   |  |  |  |
    ;   |  |  |  +-------------------------------------- [12] AutoReload        (0:disabled, to restart DMA set start bit = 1; 1:enabled, to stop DMA from reloading set start bit = 0 )
    ;   |  |  +----------------------------------------- [13] InterruptEn       (0:no interrupts generated, 1:interrupt generated when xfer complete)
    ;   |  +-------------------------------------------- [14] Status            (0:channel inactive, 1:channel active)
    ;   +----------------------------------------------- [15] Start/Stop        (0:stops after burst is complete, 1:starts block xfer)

;**************************************************************************
;        DMA0 Ch3 Register Addresses
;**************************************************************************
DMA0_CH3_SRC_LSW        .set     0x0c60    ; DMA0 Channel 3 Source LSW Address
    ; DMA0_CH3_SRC_LSW   Address:  0x0c60 (IO space)      DMA0 Channel 3 Source LSW Address
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ; |15:14:13:12|11:10: 9: 8| 7: 6: 5: 4| 3: 2: 1: 0|  <<== Bit Position
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; |rw:rw:rw:rw|rw:rw:rw:rw|rw:rw:rw:rw|rw:rw:rw:rw|  <<== Read / Write Access
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; | 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0|  <<== Reset Values
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-- [0]  DMASrcByteAddr[0]     ( Psuedo Code for setting DMA SRC/DEST Addresses:
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  +----- [1]  DMASrcByteAddr[1]      if( io_space ) {
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  +-------- [2]  DMASrcByteAddr[2]          DMASrcByteAddr[17:0] = DSP_IOPORT_ADDR;
    ;   |  |  |  |  |  |  |  |  |  |  |  |  +----------- [3]  DMASrcByteAddr[3]      } elsif( daram ) {
    ;   |  |  |  |  |  |  |  |  |  |  |  |                                               DMASrcByteAddr[17:0] = 0x10000 + DSP_BYTE_ADDR;
    ;   |  |  |  |  |  |  |  |  |  |  |  +-------------- [4]  DMASrcByteAddr[4]      } elsif( saram ) {
    ;   |  |  |  |  |  |  |  |  |  |  +----------------- [5]  DMASrcByteAddr[5]          DMASrcByteAddr[17:0] = 0x20000 + DSP_BYTE_ADDR;
    ;   |  |  |  |  |  |  |  |  |  +-------------------- [6]  DMASrcByteAddr[6]      }
    ;   |  |  |  |  |  |  |  |  +----------------------- [7]  DMASrcByteAddr[7] 
    ;   |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  +-------------------------- [8]  DMASrcByteAddr[8]      DMA0 can see: 
    ;   |  |  |  |  |  |  +----------------------------- [9]  DMASrcByteAddr[9]      DMA1 can see: 
    ;   |  |  |  |  |  +-------------------------------- [10] DMASrcByteAddr[10]   DMA2 can see: 
    ;   |  |  |  |  +----------------------------------- [11] DMASrcByteAddr[11]   DMA3 can see: )
    ;   |  |  |  |
    ;   |  |  |  +-------------------------------------- [12] DMASrcByteAddr[12]
    ;   |  |  +----------------------------------------- [13] DMASrcByteAddr[13]
    ;   |  +-------------------------------------------- [14] DMASrcByteAddr[14]
    ;   +----------------------------------------------- [15] DMASrcByteAddr[15]
DMA0_CH3_SRC_MSW        .set     0x0c61    ; DMA0 Channel 3 Source MSW Address
    ; DMA0_CH3_SRC_MSW   Address:  0x0c61 (IO space)      DMA0 Channel 3 Source MSW Address
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ; |15:14:13:12|11:10: 9: 8| 7: 6: 5: 4| 3: 2: 1: 0|  <<== Bit Position
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; |r :r :r :r |r :r :r :r |r :r :r :r |r :r :rw:rw|  <<== Read / Write Access
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; | 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0|  <<== Reset Values
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-- [0]  DMASrcByteAddr[16]
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  +----- [1]  DMASrcByteAddr[17]
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  +-------- [2]  reserved
    ;   |  |  |  |  |  |  |  |  |  |  |  |  +----------- [3]  reserved
    ;   |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  +-------------- [4]  reserved
    ;   |  |  |  |  |  |  |  |  |  |  +----------------- [5]  reserved
    ;   |  |  |  |  |  |  |  |  |  +-------------------- [6]  reserved
    ;   |  |  |  |  |  |  |  |  +----------------------- [7]  reserved
    ;   |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  +-------------------------- [8]  reserved
    ;   |  |  |  |  |  |  +----------------------------- [9]  reserved
    ;   |  |  |  |  |  +-------------------------------- [10] reserved
    ;   |  |  |  |  +----------------------------------- [11] reserved
    ;   |  |  |  |
    ;   |  |  |  +-------------------------------------- [12] reserved
    ;   |  |  +----------------------------------------- [13] reserved
    ;   |  +-------------------------------------------- [14] reserved
    ;   +----------------------------------------------- [15] reserved
DMA0_CH3_DST_LSW        .set     0x0c62    ; DMA0 Channel 3 Destination LSW Address
    ; DMA0_CH3_DST_LSW   Address:  0x0c62 (IO space)      DMA0 Channel 3 Destination LSW Address
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ; |15:14:13:12|11:10: 9: 8| 7: 6: 5: 4| 3: 2: 1: 0|  <<== Bit Position
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; |rw:rw:rw:rw|rw:rw:rw:rw|rw:rw:rw:rw|rw:rw:rw:rw|  <<== Read / Write Access
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; | 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0|  <<== Reset Values
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-- [0]  DMADestByteAddr[0]    ( Psuedo Code for setting DMA SRC/DEST Addresses:
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  +----- [1]  DMADestByteAddr[1]     if( io_space ) {
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  +-------- [2]  DMADestByteAddr[2]         DMADestByteAddr[17:0] = DSP_IOPORT_ADDR;
    ;   |  |  |  |  |  |  |  |  |  |  |  |  +----------- [3]  DMADestByteAddr[3]     } elsif( daram ) {
    ;   |  |  |  |  |  |  |  |  |  |  |  |                                              DMADestByteAddr[17:0] = 0x10000 + DSP_BYTE_ADDR;
    ;   |  |  |  |  |  |  |  |  |  |  |  +-------------- [4]  DMADestByteAddr[4]     } elsif( saram ) {
    ;   |  |  |  |  |  |  |  |  |  |  +----------------- [5]  DMADestByteAddr[5]         DMADestByteAddr[17:0] = 0x20000 + DSP_BYTE_ADDR;
    ;   |  |  |  |  |  |  |  |  |  +-------------------- [6]  DMADestByteAddr[6]     }
    ;   |  |  |  |  |  |  |  |  +----------------------- [7]  DMADestByteAddr[7] 
    ;   |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  +-------------------------- [8]  DMADestByteAddr[8]      DMA0 can see: 
    ;   |  |  |  |  |  |  +----------------------------- [9]  DMADestByteAddr[9]      DMA1 can see: 
    ;   |  |  |  |  |  +-------------------------------- [10] DMADestByteAddr[10]     DMA2 can see: 
    ;   |  |  |  |  +----------------------------------- [11] DMADestByteAddr[11]     DMA3 can see: )
    ;   |  |  |  |
    ;   |  |  |  +-------------------------------------- [12] DMADestByteAddr[12]
    ;   |  |  +----------------------------------------- [13] DMADestByteAddr[13]
    ;   |  +-------------------------------------------- [14] DMADestByteAddr[14]
    ;   +----------------------------------------------- [15] DMADestByteAddr[15]
DMA0_CH3_DST_MSW        .set     0x0c63    ; DMA0 Channel 3 Destination MSW Address
    ; DMA0_CH3_DST_MSW   Address:  0x0c63 (IO space)      DMA0 Channel 3 Destination MSW Address
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ; |15:14:13:12|11:10: 9: 8| 7: 6: 5: 4| 3: 2: 1: 0|  <<== Bit Position
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; |r :r :r :r |r :r :r :r |r :r :r :r |r :r :rw:rw|  <<== Read / Write Access
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; | 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0|  <<== Reset Values
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-- [0]  DMADestByteAddr[16]
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  +----- [1]  DMADestByteAddr[17]
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  +-------- [2]  reserved
    ;   |  |  |  |  |  |  |  |  |  |  |  |  +----------- [3]  reserved
    ;   |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  +-------------- [4]  reserved
    ;   |  |  |  |  |  |  |  |  |  |  +----------------- [5]  reserved
    ;   |  |  |  |  |  |  |  |  |  +-------------------- [6]  reserved
    ;   |  |  |  |  |  |  |  |  +----------------------- [7]  reserved
    ;   |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  +-------------------------- [8]  reserved
    ;   |  |  |  |  |  |  +----------------------------- [9]  reserved
    ;   |  |  |  |  |  +-------------------------------- [10] reserved
    ;   |  |  |  |  +----------------------------------- [11] reserved
    ;   |  |  |  |
    ;   |  |  |  +-------------------------------------- [12] reserved
    ;   |  |  +----------------------------------------- [13] reserved
    ;   |  +-------------------------------------------- [14] reserved
    ;   +----------------------------------------------- [15] reserved
DMA0_CH3_TC_LEN         .set     0x0c64    ; DMA0 Channel 3 Length / Transfer Control LSW Register
    ; DMA0_CH3_TC_LEN   Address:  0x0c64 (IO space)      DMA0 Channel 3 Length / Transfer Control LSW Register
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ; |15:14:13:12|11:10: 9: 8| 7: 6: 5: 4| 3: 2: 1: 0|  <<== Bit Position
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; |rw:rw:rw:rw|rw:rw:rw:rw|rw:rw:rw:rw|rw:rw:r :r |  <<== Read / Write Access
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; | 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0|  <<== Reset Values
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |   ( XferLength[15:0] = number of bytes to be transfered)
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-- [0]  XferLength[0]
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  +----- [1]  XferLength[1]
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  +-------- [2]  XferLength[2]
    ;   |  |  |  |  |  |  |  |  |  |  |  |  +----------- [3]  XferLength[3]
    ;   |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  +-------------- [4]  XferLength[4]
    ;   |  |  |  |  |  |  |  |  |  |  +----------------- [5]  XferLength[5]
    ;   |  |  |  |  |  |  |  |  |  +-------------------- [6]  XferLength[6]
    ;   |  |  |  |  |  |  |  |  +----------------------- [7]  XferLength[7]
    ;   |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  +-------------------------- [8]  XferLength[8]
    ;   |  |  |  |  |  |  +----------------------------- [9]  XferLength[9]
    ;   |  |  |  |  |  +-------------------------------- [10] XferLength[10]
    ;   |  |  |  |  +----------------------------------- [11] XferLength[11]
    ;   |  |  |  |
    ;   |  |  |  +-------------------------------------- [12] XferLength[12]
    ;   |  |  +----------------------------------------- [13] XferLength[13]
    ;   |  +-------------------------------------------- [14] XferLength[14]
    ;   +----------------------------------------------- [15] XferLength[15]
DMA0_CH3_TC_MSW         .set     0x0c65    ; DMA0 Channel 3 Transfer Control MSW Register
    ; DMA0_CH3_TC_MSW   Address:  0x0c65 (IO space)      DMA0 Channel 3 Transfer Control MSW Register
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ; |15:14:13:12|11:10: 9: 8| 7: 6: 5: 4| 3: 2: 1: 0|  <<== Bit Position
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; |rw:rw:rw:rw|r :r :rw:rw|rw:rw:rw:rw|rw:r :rw:rw|  <<== Read / Write Access
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; | 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0|  <<== Reset Values
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +--  [0]  SourceSize[0]      Source Data Size:
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-----  [1]  SourceSize[1]      (00: 32-bit, 01: 16-bit, 10: 8-bit,  11: Reserved)
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  +--------  [2]  Sync               (1: DMA transfers one burst-mode length of 32-bit words per one peripheral event, 0: DMA transfers not controlled by peripheral events)
    ;   |  |  |  |  |  |  |  |  |  |  |  |  +-----------  [3]  BurstMode[0]       (000:1 32bit word burst, 001:2 32bit word burst,
    ;   |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  +--------------  [4]  BurstMode[1]        010:4 32bit word burst, 011:8 32bit word burst,
    ;   |  |  |  |  |  |  |  |  |  |  +-----------------  [5]  BurstMode[2]        100:16 32bit word burst, others:reserved)
    ;   |  |  |  |  |  |  |  |  |  +--------------------  [6]  SrcAddrMode[0]     (00:autoincr, 10:src addr is fixed, others:reserved)
    ;   |  |  |  |  |  |  |  |  +-----------------------  [7]  SrcAddrMode[1]
    ;   |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  +--------------------------  [8]  DestAddrMode[0]    (00:autoincr, 10:dest addr is fixed, others:reserved)
    ;   |  |  |  |  |  |  +-----------------------------  [9]  DestAddrMode[1]
    ;   |  |  |  |  |  +--------------------------------  [10] DestSize[0]        Destination data size:
    ;   |  |  |  |  +-----------------------------------  [11] DestSize[1]        (00: 32-bit, 01: 16-bit, 10: 8-bit,  11: Reserved)
    ;   |  |  |  |
    ;   |  |  |  +--------------------------------------  [12] AutoReload        (0:disabled, to restart DMA set start bit = 1; 1:enabled, to stop DMA from reloading set start bit = 0 )
    ;   |  |  +-----------------------------------------  [13] InterruptEn       (0:no interrupts generated, 1:interrupt generated when xfer complete)
    ;   |  +--------------------------------------------  [14] Status            (0:channel inactive, 1:channel active)
    ;   +-----------------------------------------------  [15] Start/Stop        (0:stops after burst is complete, 1:starts block xfer)
;****************************************************************************************

;****************************************************************************************
;         DMA 1
;**************************************************************************
;        DMA1 Ch0 Register Addresses
;**************************************************************************
DMA1_CH0_SRC_LSW        .set     0x0D00    ; DMA1 Channel 0 Source LSW Address
    ; DMA1_CH0_SRC_LSW   Address:  0x0D00 (IO space)      DMA1 Channel 0 Source LSW Address
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ; |15:14:13:12|11:10: 9: 8| 7: 6: 5: 4| 3: 2: 1: 0|  <<== Bit Position
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; |rw:rw:rw:rw|rw:rw:rw:rw|rw:rw:rw:rw|rw:rw:rw:rw|  <<== Read / Write Access
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; | 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0|  <<== Reset Values
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-- [0]  DMASrcByteAddr[0]     ( Psuedo Code for setting DMA SRC/DEST Addresses:
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  +----- [1]  DMASrcByteAddr[1]      if( io_space ) {
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  +-------- [2]  DMASrcByteAddr[2]          DMASrcByteAddr[17:0] = DSP_IOPORT_ADDR;
    ;   |  |  |  |  |  |  |  |  |  |  |  |  +----------- [3]  DMASrcByteAddr[3]      } elsif( daram ) {
    ;   |  |  |  |  |  |  |  |  |  |  |  |                                               DMASrcByteAddr[17:0] = 0x10000 + DSP_BYTE_ADDR;
    ;   |  |  |  |  |  |  |  |  |  |  |  +-------------- [4]  DMASrcByteAddr[4]      } elsif( saram ) {
    ;   |  |  |  |  |  |  |  |  |  |  +----------------- [5]  DMASrcByteAddr[5]          DMASrcByteAddr[17:0] = 0x20000 + DSP_BYTE_ADDR;
    ;   |  |  |  |  |  |  |  |  |  +-------------------- [6]  DMASrcByteAddr[6]      }
    ;   |  |  |  |  |  |  |  |  +----------------------- [7]  DMASrcByteAddr[7] 
    ;   |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  +-------------------------- [8]  DMASrcByteAddr[8]      DMA0 can see: 
    ;   |  |  |  |  |  |  +----------------------------- [9]  DMASrcByteAddr[9]      DMA1 can see: 
    ;   |  |  |  |  |  +-------------------------------- [10] DMASrcByteAddr[10]     DMA2 can see: 
    ;   |  |  |  |  +----------------------------------- [11] DMASrcByteAddr[11]     DMA3 can see: )
    ;   |  |  |  |
    ;   |  |  |  +-------------------------------------- [12] DMASrcByteAddr[12]
    ;   |  |  +----------------------------------------- [13] DMASrcByteAddr[13]
    ;   |  +-------------------------------------------- [14] DMASrcByteAddr[14]
    ;   +----------------------------------------------- [15] DMASrcByteAddr[15]
DMA1_CH0_SRC_MSW        .set     0x0D01    ; DMA1 Channel 0 Source MSW Address
    ; DMA1_CH0_SRC_MSW   Address:  0x0D01 (IO space)      DMA1 Channel 0 Source MSW Address
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ; |15:14:13:12|11:10: 9: 8| 7: 6: 5: 4| 3: 2: 1: 0|  <<== Bit Position
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; |r :r :r :r |r :r :r :r |r :r :r :r |r :r :rw:rw|  <<== Read / Write Access
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; | 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0|  <<== Reset Values
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-- [0]  DMASrcByteAddr[16]
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  +----- [1]  DMASrcByteAddr[17]
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  +-------- [2]  reserved
    ;   |  |  |  |  |  |  |  |  |  |  |  |  +----------- [3]  reserved
    ;   |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  +-------------- [4]  reserved
    ;   |  |  |  |  |  |  |  |  |  |  +----------------- [5]  reserved
    ;   |  |  |  |  |  |  |  |  |  +-------------------- [6]  reserved
    ;   |  |  |  |  |  |  |  |  +----------------------- [7]  reserved
    ;   |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  +-------------------------- [8]  reserved
    ;   |  |  |  |  |  |  +----------------------------- [9]  reserved
    ;   |  |  |  |  |  +-------------------------------- [10] reserved
    ;   |  |  |  |  +----------------------------------- [11] reserved
    ;   |  |  |  |
    ;   |  |  |  +-------------------------------------- [12] reserved
    ;   |  |  +----------------------------------------- [13] reserved
    ;   |  +-------------------------------------------- [14] reserved
    ;   +----------------------------------------------- [15] reserved
DMA1_CH0_DST_LSW        .set     0x0D02    ; DMA1 Channel 0 Destination LSW Address
    ; DMA1_CH0_DST_LSW   Address:  0x0D02 (IO space)      DMA1 Channel 0 Destination LSW Address
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ; |15:14:13:12|11:10: 9: 8| 7: 6: 5: 4| 3: 2: 1: 0|  <<== Bit Position
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; |rw:rw:rw:rw|rw:rw:rw:rw|rw:rw:rw:rw|rw:rw:rw:rw|  <<== Read / Write Access
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; | 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0|  <<== Reset Values
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-- [0]  DMADestByteAddr[0]    ( Psuedo Code for setting DMA SRC/DEST Addresses:
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  +----- [1]  DMADestByteAddr[1]     if( io_space ) {
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  +-------- [2]  DMADestByteAddr[2]         DMADestByteAddr[17:0] = DSP_IOPORT_ADDR;
    ;   |  |  |  |  |  |  |  |  |  |  |  |  +----------- [3]  DMADestByteAddr[3]     } elsif( daram ) {
    ;   |  |  |  |  |  |  |  |  |  |  |  |                                              DMADestByteAddr[17:0] = 0x10000 + DSP_BYTE_ADDR;
    ;   |  |  |  |  |  |  |  |  |  |  |  +-------------- [4]  DMADestByteAddr[4]     } elsif( saram ) {
    ;   |  |  |  |  |  |  |  |  |  |  +----------------- [5]  DMADestByteAddr[5]         DMADestByteAddr[17:0] = 0x20000 + DSP_BYTE_ADDR;
    ;   |  |  |  |  |  |  |  |  |  +-------------------- [6]  DMADestByteAddr[6]     }
    ;   |  |  |  |  |  |  |  |  +----------------------- [7]  DMADestByteAddr[7] 
    ;   |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  +-------------------------- [8]  DMADestByteAddr[8]      DMA0 can see: 
    ;   |  |  |  |  |  |  +----------------------------- [9]  DMADestByteAddr[9]      DMA1 can see: 
    ;   |  |  |  |  |  +-------------------------------- [10] DMADestByteAddr[10]     DMA2 can see: 
    ;   |  |  |  |  +----------------------------------- [11] DMADestByteAddr[11]     DMA3 can see: )
    ;   |  |  |  |
    ;   |  |  |  +-------------------------------------- [12] DMADestByteAddr[12]
    ;   |  |  +----------------------------------------- [13] DMADestByteAddr[13]
    ;   |  +-------------------------------------------- [14] DMADestByteAddr[14]
    ;   +----------------------------------------------- [15] DMADestByteAddr[15]
DMA1_CH0_DST_MSW        .set     0x0D03    ; DMA1 Channel 0 Destination MSW Address
    ; DMA1_CH0_DST_MSW   Address:  0x0D03 (IO space)      DMA1 Channel 0 Destination MSW Address
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ; |15:14:13:12|11:10: 9: 8| 7: 6: 5: 4| 3: 2: 1: 0|  <<== Bit Position
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; |r :r :r :r |r :r :r :r |r :r :r :r |r :r :rw:rw|  <<== Read / Write Access
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; | 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0|  <<== Reset Values
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-- [0]  DMADestByteAddr[16]
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  +----- [1]  DMADestByteAddr[17]
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  +-------- [2]  reserved
    ;   |  |  |  |  |  |  |  |  |  |  |  |  +----------- [3]  reserved
    ;   |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  +-------------- [4]  reserved
    ;   |  |  |  |  |  |  |  |  |  |  +----------------- [5]  reserved
    ;   |  |  |  |  |  |  |  |  |  +-------------------- [6]  reserved
    ;   |  |  |  |  |  |  |  |  +----------------------- [7]  reserved
    ;   |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  +-------------------------- [8]  reserved
    ;   |  |  |  |  |  |  +----------------------------- [9]  reserved
    ;   |  |  |  |  |  +-------------------------------- [10] reserved
    ;   |  |  |  |  +----------------------------------- [11] reserved
    ;   |  |  |  |
    ;   |  |  |  +-------------------------------------- [12] reserved
    ;   |  |  +----------------------------------------- [13] reserved
    ;   |  +-------------------------------------------- [14] reserved
    ;   +----------------------------------------------- [15] reserved
DMA1_CH0_TC_LEN         .set     0x0D04    ; DMA1 Channel 0 Length / Transfer Control LSW Register
    ; DMA1_CH0_TC_LEN   Address:  0x0D04 (IO space)      DMA1 Channel 0 Length / Transfer Control LSW Register
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ; |15:14:13:12|11:10: 9: 8| 7: 6: 5: 4| 3: 2: 1: 0|  <<== Bit Position
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; |rw:rw:rw:rw|rw:rw:rw:rw|rw:rw:rw:rw|rw:rw:r :r |  <<== Read / Write Access
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; | 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0|  <<== Reset Values
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |   ( XferLength[15:0] = number of bytes to be transfered)
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-- [0]  XferLength[0]
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  +----- [1]  XferLength[1]
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  +-------- [2]  XferLength[2]
    ;   |  |  |  |  |  |  |  |  |  |  |  |  +----------- [3]  XferLength[3]
    ;   |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  +-------------- [4]  XferLength[4]
    ;   |  |  |  |  |  |  |  |  |  |  +----------------- [5]  XferLength[5]
    ;   |  |  |  |  |  |  |  |  |  +-------------------- [6]  XferLength[6]
    ;   |  |  |  |  |  |  |  |  +----------------------- [7]  XferLength[7]
    ;   |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  +-------------------------- [8]  XferLength[8]
    ;   |  |  |  |  |  |  +----------------------------- [9]  XferLength[9]
    ;   |  |  |  |  |  +-------------------------------- [10] XferLength[10]
    ;   |  |  |  |  +----------------------------------- [11] XferLength[11]
    ;   |  |  |  |
    ;   |  |  |  +-------------------------------------- [12] XferLength[12]
    ;   |  |  +----------------------------------------- [13] XferLength[13]
    ;   |  +-------------------------------------------- [14] XferLength[14]
    ;   +----------------------------------------------- [15] XferLength[15]
DMA1_CH0_TC_MSW         .set     0x0D05    ; DMA1 Channel 0 Transfer Control MSW Register
    ; DMA1_CH0_TC_MSW   Address:  0x0D05 (IO space)      DMA1 Channel 0 Transfer Control MSW Register
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ; |15:14:13:12|11:10: 9: 8| 7: 6: 5: 4| 3: 2: 1: 0|  <<== Bit Position
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; |rw:rw:rw:rw|r :r :rw:rw|rw:rw:rw:rw|rw:r :rw:rw|  <<== Read / Write Access
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; | 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0|  <<== Reset Values
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-- [0]  SourceSize[0]      Source Data Size:
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  +----- [1]  SourceSize[1]      (00: 32-bit, 01: 16-bit, 10: 8-bit,  11: Reserved)
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  +-------- [2]  Sync               (1: DMA transfers one burst-mode length of 32-bit words per one peripheral event, 0: DMA transfers not controlled by peripheral events)
    ;   |  |  |  |  |  |  |  |  |  |  |  |  +----------- [3]  BurstMode[0]       (000:1 32bit word burst, 001:2 32bit word burst,
    ;   |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  +-------------- [4]  BurstMode[1]        010:4 32bit word burst, 011:8 32bit word burst,
    ;   |  |  |  |  |  |  |  |  |  |  +----------------- [5]  BurstMode[2]        100:16 32bit word burst, others:reserved)
    ;   |  |  |  |  |  |  |  |  |  +-------------------- [6]  SrcAddrMode[0]     (00:autoincr, 10:src addr is fixed, others:reserved)
    ;   |  |  |  |  |  |  |  |  +----------------------- [7]  SrcAddrMode[1]
    ;   |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  +-------------------------- [8]  DestAddrMode[0]    (00:autoincr, 10:dest addr is fixed, others:reserved)
    ;   |  |  |  |  |  |  +----------------------------- [9]  DestAddrMode[1]
    ;   |  |  |  |  |  +-------------------------------- [10] DestSize[0]        Destination data size:
    ;   |  |  |  |  +----------------------------------- [11] DestSize[1]        (00: 32-bit, 01: 16-bit, 10: 8-bit,  11: Reserved)
    ;   |  |  |  |
    ;   |  |  |  +-------------------------------------- [12] AutoReload        (0:disabled, to restart DMA set start bit = 1; 1:enabled, to stop DMA from reloading set start bit = 0 )
    ;   |  |  +----------------------------------------- [13] InterruptEn       (0:no interrupts generated, 1:interrupt generated when xfer complete)
    ;   |  +-------------------------------------------- [14] Status            (0:channel inactive, 1:channel active)
    ;   +----------------------------------------------- [15] Start/Stop        (0:stops after burst is complete, 1:starts block xfer)


;**************************************************************************
;        DMA1 Ch1 Register Addresses
;**************************************************************************
DMA1_CH1_SRC_LSW        .set     0x0D20    ; DMA1 Channel 1 Source LSW Address
    ; DMA1_CH1_SRC_LSW   Address:  0x0D20 (IO space)      DMA1 Channel 1 Source LSW Address
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ; |15:14:13:12|11:10: 9: 8| 7: 6: 5: 4| 3: 2: 1: 0|  <<== Bit Position
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; |rw:rw:rw:rw|rw:rw:rw:rw|rw:rw:rw:rw|rw:rw:rw:rw|  <<== Read / Write Access
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; | 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0|  <<== Reset Values
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-- [0]  DMASrcByteAddr[0]     ( Psuedo Code for setting DMA SRC/DEST Addresses:
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  +----- [1]  DMASrcByteAddr[1]      if( io_space ) {
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  +-------- [2]  DMASrcByteAddr[2]          DMASrcByteAddr[17:0] = DSP_IOPORT_ADDR;
    ;   |  |  |  |  |  |  |  |  |  |  |  |  +----------- [3]  DMASrcByteAddr[3]      } elsif( daram ) {
    ;   |  |  |  |  |  |  |  |  |  |  |  |                                               DMASrcByteAddr[17:0] = 0x10000 + DSP_BYTE_ADDR;
    ;   |  |  |  |  |  |  |  |  |  |  |  +-------------- [4]  DMASrcByteAddr[4]      } elsif( saram ) {
    ;   |  |  |  |  |  |  |  |  |  |  +----------------- [5]  DMASrcByteAddr[5]          DMASrcByteAddr[17:0] = 0x20000 + DSP_BYTE_ADDR;
    ;   |  |  |  |  |  |  |  |  |  +-------------------- [6]  DMASrcByteAddr[6]      }
    ;   |  |  |  |  |  |  |  |  +----------------------- [7]  DMASrcByteAddr[7]
    ;   |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  +-------------------------- [8]  DMASrcByteAddr[8]      DMA0 can see: 
    ;   |  |  |  |  |  |  +----------------------------- [9]  DMASrcByteAddr[9]      DMA1 can see: 
    ;   |  |  |  |  |  +-------------------------------- [10] DMASrcByteAddr[10]     DMA2 can see: 
    ;   |  |  |  |  +----------------------------------- [11] DMASrcByteAddr[11]     DMA3 can see: )
    ;   |  |  |  |
    ;   |  |  |  +-------------------------------------- [12] DMASrcByteAddr[12]
    ;   |  |  +----------------------------------------- [13] DMASrcByteAddr[13]
    ;   |  +-------------------------------------------- [14] DMASrcByteAddr[14]
    ;   +----------------------------------------------- [15] DMASrcByteAddr[15]
DMA1_CH1_SRC_MSW        .set     0x0D21    ; DMA1 Channel 1 Source MSW Address
    ; DMA1_CH1_SRC_MSW   Address:  0x0D21 (IO space)      DMA1 Channel 1 Source MSW Address
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ; |15:14:13:12|11:10: 9: 8| 7: 6: 5: 4| 3: 2: 1: 0|  <<== Bit Position
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; |r :r :r :r |r :r :r :r |r :r :r :r |r :r :rw:rw|  <<== Read / Write Access
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; | 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0|  <<== Reset Values
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-- [0]  DMASrcByteAddr[16]
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  +----- [1]  DMASrcByteAddr[17]
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  +-------- [2]  reserved
    ;   |  |  |  |  |  |  |  |  |  |  |  |  +----------- [3]  reserved
    ;   |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  +-------------- [4]  reserved
    ;   |  |  |  |  |  |  |  |  |  |  +----------------- [5]  reserved
    ;   |  |  |  |  |  |  |  |  |  +-------------------- [6]  reserved
    ;   |  |  |  |  |  |  |  |  +----------------------- [7]  reserved
    ;   |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  +-------------------------- [8]  reserved
    ;   |  |  |  |  |  |  +----------------------------- [9]  reserved
    ;   |  |  |  |  |  +-------------------------------- [10] reserved
    ;   |  |  |  |  +----------------------------------- [11] reserved
    ;   |  |  |  |
    ;   |  |  |  +-------------------------------------- [12] reserved
    ;   |  |  +----------------------------------------- [13] reserved
    ;   |  +-------------------------------------------- [14] reserved
    ;   +----------------------------------------------- [15] reserved
DMA1_CH1_DST_LSW        .set     0x0D22    ; DMA1 Channel 1 Destination LSW Address
    ; DMA1_CH1_DST_LSW   Address:  0x0D02 (IO space)      DMA1 Channel 1 Destination LSW Address
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ; |15:14:13:12|11:10: 9: 8| 7: 6: 5: 4| 3: 2: 1: 0|  <<== Bit Position
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; |rw:rw:rw:rw|rw:rw:rw:rw|rw:rw:rw:rw|rw:rw:rw:rw|  <<== Read / Write Access
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; | 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0|  <<== Reset Values
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-- [0]  DMADestByteAddr[0]    ( Psuedo Code for setting DMA SRC/DEST Addresses:
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  +----- [1]  DMADestByteAddr[1]     if( io_space ) {
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  +-------- [2]  DMADestByteAddr[2]         DMADestByteAddr[17:0] = DSP_IOPORT_ADDR;
    ;   |  |  |  |  |  |  |  |  |  |  |  |  +----------- [3]  DMADestByteAddr[3]     } elsif( daram ) {
    ;   |  |  |  |  |  |  |  |  |  |  |  |                                              DMADestByteAddr[17:0] = 0x10000 + DSP_BYTE_ADDR;
    ;   |  |  |  |  |  |  |  |  |  |  |  +-------------- [4]  DMADestByteAddr[4]     } elsif( saram ) {
    ;   |  |  |  |  |  |  |  |  |  |  +----------------- [5]  DMADestByteAddr[5]         DMADestByteAddr[17:0] = 0x20000 + DSP_BYTE_ADDR;
    ;   |  |  |  |  |  |  |  |  |  +-------------------- [6]  DMADestByteAddr[6]     }
    ;   |  |  |  |  |  |  |  |  +----------------------- [7]  DMADestByteAddr[7] 
    ;   |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  +-------------------------- [8]  DMADestByteAddr[8]      DMA0 can see: 
    ;   |  |  |  |  |  |  +----------------------------- [9]  DMADestByteAddr[9]      DMA1 can see: 
    ;   |  |  |  |  |  +-------------------------------- [10] DMADestByteAddr[10]     DMA2 can see: 
    ;   |  |  |  |  +----------------------------------- [11] DMADestByteAddr[11]     DMA3 can see: )
    ;   |  |  |  |
    ;   |  |  |  +-------------------------------------- [12] DMADestByteAddr[12]
    ;   |  |  +----------------------------------------- [13] DMADestByteAddr[13]
    ;   |  +-------------------------------------------- [14] DMADestByteAddr[14]
    ;   +----------------------------------------------- [15] DMADestByteAddr[15]
DMA1_CH1_DST_MSW        .set     0x0D23    ; DMA1 Channel 1 Destination MSW Address
    ; DMA1_CH1_DST_MSW   Address:  0x0D23 (IO space)      DMA1 Channel 1 Destination MSW Address
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ; |15:14:13:12|11:10: 9: 8| 7: 6: 5: 4| 3: 2: 1: 0|  <<== Bit Position
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; |r :r :r :r |r :r :r :r |r :r :r :r |r :r :rw:rw|  <<== Read / Write Access
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; | 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0|  <<== Reset Values
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-- [0]  DMADestByteAddr[16]
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  +----- [1]  DMADestByteAddr[17]
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  +-------- [2]  reserved
    ;   |  |  |  |  |  |  |  |  |  |  |  |  +----------- [3]  reserved
    ;   |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  +-------------- [4]  reserved
    ;   |  |  |  |  |  |  |  |  |  |  +----------------- [5]  reserved
    ;   |  |  |  |  |  |  |  |  |  +-------------------- [6]  reserved
    ;   |  |  |  |  |  |  |  |  +----------------------- [7]  reserved
    ;   |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  +-------------------------- [8]  reserved
    ;   |  |  |  |  |  |  +----------------------------- [9]  reserved
    ;   |  |  |  |  |  +-------------------------------- [10] reserved
    ;   |  |  |  |  +----------------------------------- [11] reserved
    ;   |  |  |  |
    ;   |  |  |  +-------------------------------------- [12] reserved
    ;   |  |  +----------------------------------------- [13] reserved
    ;   |  +-------------------------------------------- [14] reserved
    ;   +----------------------------------------------- [15] reserved
DMA1_CH1_TC_LEN         .set     0x0D24    ; DMA1 Channel 1 Length / Transfer Control LSW Register
    ; DMA1_CH1_TC_LEN   Address:  0x0D04 (IO space)      DMA1 Channel 1 Length / Transfer Control LSW Register
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ; |15:14:13:12|11:10: 9: 8| 7: 6: 5: 4| 3: 2: 1: 0|  <<== Bit Position
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; |rw:rw:rw:rw|rw:rw:rw:rw|rw:rw:rw:rw|rw:rw:r :r |  <<== Read / Write Access
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; | 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0|  <<== Reset Values
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |   ( XferLength[15:0] = number of bytes to be transfered)
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-- [0]  XferLength[0]
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  +----- [1]  XferLength[1]
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  +-------- [2]  XferLength[2]
    ;   |  |  |  |  |  |  |  |  |  |  |  |  +----------- [3]  XferLength[3]
    ;   |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  +-------------- [4]  XferLength[4]
    ;   |  |  |  |  |  |  |  |  |  |  +----------------- [5]  XferLength[5]
    ;   |  |  |  |  |  |  |  |  |  +-------------------- [6]  XferLength[6]
    ;   |  |  |  |  |  |  |  |  +----------------------- [7]  XferLength[7]
    ;   |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  +-------------------------- [8]  XferLength[8]
    ;   |  |  |  |  |  |  +----------------------------- [9]  XferLength[9]
    ;   |  |  |  |  |  +-------------------------------- [10] XferLength[10]
    ;   |  |  |  |  +----------------------------------- [11] XferLength[11]
    ;   |  |  |  |
    ;   |  |  |  +-------------------------------------- [12] XferLength[12]
    ;   |  |  +----------------------------------------- [13] XferLength[13]
    ;   |  +-------------------------------------------- [14] XferLength[14]
    ;   +----------------------------------------------- [15] XferLength[15]
DMA1_CH1_TC_MSW         .set     0x0D25    ; DMA1 Channel 1 Transfer Control MSW Register
    ; DMA1_CH1_TC_MSW   Address:  0x0D25 (IO space)      DMA1 Channel 1 Transfer Control MSW Register
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ; |15:14:13:12|11:10: 9: 8| 7: 6: 5: 4| 3: 2: 1: 0|  <<== Bit Position
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; |rw:rw:rw:rw|r :r :rw:rw|rw:rw:rw:rw|rw:r :rw:rw|  <<== Read / Write Access
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; | 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0|  <<== Reset Values
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +--  [0]  SourceSize[0]      Source Data Size:
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-----  [1]  SourceSize[1]      (00: 32-bit, 01: 16-bit, 10: 8-bit,  11: Reserved)
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  +--------  [2]  Sync               (1: DMA transfers one burst-mode length of 32-bit words per one peripheral event, 0: DMA transfers not controlled by peripheral events)
    ;   |  |  |  |  |  |  |  |  |  |  |  |  +-----------  [3]  BurstMode[0]       (000:1 32bit word burst, 001:2 32bit word burst,
    ;   |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  +--------------  [4]  BurstMode[1]        010:4 32bit word burst, 011:8 32bit word burst,
    ;   |  |  |  |  |  |  |  |  |  |  +-----------------  [5]  BurstMode[2]        100:16 32bit word burst, others:reserved)
    ;   |  |  |  |  |  |  |  |  |  +--------------------  [6]  SrcAddrMode[0]     (00:autoincr, 10:src addr is fixed, others:reserved)
    ;   |  |  |  |  |  |  |  |  +-----------------------  [7]  SrcAddrMode[1]
    ;   |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  +--------------------------  [8]  DestAddrMode[0]    (00:autoincr, 10:dest addr is fixed, others:reserved)
    ;   |  |  |  |  |  |  +-----------------------------  [9]  DestAddrMode[1]
    ;   |  |  |  |  |  +--------------------------------  [10] DestSize[0]        Destination data size:
    ;   |  |  |  |  +-----------------------------------  [11] DestSize[1]        (00: 32-bit, 01: 16-bit, 10: 8-bit,  11: Reserved)
    ;   |  |  |  |
    ;   |  |  |  +--------------------------------------  [12] AutoReload        (0:disabled, to restart DMA set start bit = 1; 1:enabled, to stop DMA from reloading set start bit = 0 )
    ;   |  |  +-----------------------------------------  [13] InterruptEn       (0:no interrupts generated, 1:interrupt generated when xfer complete)
    ;   |  +--------------------------------------------  [14] Status            (0:channel inactive, 1:channel active)
    ;   +-----------------------------------------------  [15] Start/Stop        (0:stops after burst is complete, 1:starts block xfer)

;**************************************************************************
;        DMA1 Ch2 Register Addresses
;**************************************************************************
DMA1_CH2_SRC_LSW        .set     0x0D40    ; DMA1 Channel 2 Source LSW Address
    ; DMA1_CH2_SRC_LSW   Address:  0x0D40 (IO space)      DMA1 Channel 2 Source LSW Address
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ; |15:14:13:12|11:10: 9: 8| 7: 6: 5: 4| 3: 2: 1: 0|  <<== Bit Position
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; |rw:rw:rw:rw|rw:rw:rw:rw|rw:rw:rw:rw|rw:rw:rw:rw|  <<== Read / Write Access
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; | 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0|  <<== Reset Values
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-- [0]  DMASrcByteAddr[0]     ( Psuedo Code for setting DMA SRC/DEST Addresses:
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  +----- [1]  DMASrcByteAddr[1]      if( io_space ) {
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  +-------- [2]  DMASrcByteAddr[2]          DMASrcByteAddr[17:0] = DSP_IOPORT_ADDR;
    ;   |  |  |  |  |  |  |  |  |  |  |  |  +----------- [3]  DMASrcByteAddr[3]      } elsif( daram ) {
    ;   |  |  |  |  |  |  |  |  |  |  |  |                                               DMASrcByteAddr[17:0] = 0x10000 + DSP_BYTE_ADDR;
    ;   |  |  |  |  |  |  |  |  |  |  |  +-------------- [4]  DMASrcByteAddr[4]      } elsif( saram ) {
    ;   |  |  |  |  |  |  |  |  |  |  +----------------- [5]  DMASrcByteAddr[5]          DMASrcByteAddr[17:0] = 0x20000 + DSP_BYTE_ADDR;
    ;   |  |  |  |  |  |  |  |  |  +-------------------- [6]  DMASrcByteAddr[6]      }
    ;   |  |  |  |  |  |  |  |  +----------------------- [7]  DMASrcByteAddr[7] 
    ;   |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  +-------------------------- [8]  DMASrcByteAddr[8]      DMA0 can see: 
    ;   |  |  |  |  |  |  +----------------------------- [9]  DMASrcByteAddr[9]      DMA1 can see: 
    ;   |  |  |  |  |  +-------------------------------- [10] DMASrcByteAddr[10]     DMA2 can see: 
    ;   |  |  |  |  +----------------------------------- [11] DMASrcByteAddr[11]     DMA3 can see: )
    ;   |  |  |  |
    ;   |  |  |  +-------------------------------------- [12] DMASrcByteAddr[12]
    ;   |  |  +----------------------------------------- [13] DMASrcByteAddr[13]
    ;   |  +-------------------------------------------- [14] DMASrcByteAddr[14]
    ;   +----------------------------------------------- [15] DMASrcByteAddr[15]
DMA1_CH2_SRC_MSW        .set     0x0D41    ; DMA1 Channel 2 Source MSW Address
    ; DMA1_CH2_SRC_MSW   Address:  0x0D41 (IO space)      DMA1 Channel 2 Source MSW Address
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ; |15:14:13:12|11:10: 9: 8| 7: 6: 5: 4| 3: 2: 1: 0|  <<== Bit Position
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; |r :r :r :r |r :r :r :r |r :r :r :r |r :r :rw:rw|  <<== Read / Write Access
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; | 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0|  <<== Reset Values
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-- [0]  DMASrcByteAddr[16]
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  +----- [1]  DMASrcByteAddr[17]
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  +-------- [2]  reserved
    ;   |  |  |  |  |  |  |  |  |  |  |  |  +----------- [3]  reserved
    ;   |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  +-------------- [4]  reserved
    ;   |  |  |  |  |  |  |  |  |  |  +----------------- [5]  reserved
    ;   |  |  |  |  |  |  |  |  |  +-------------------- [6]  reserved
    ;   |  |  |  |  |  |  |  |  +----------------------- [7]  reserved
    ;   |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  +-------------------------- [8]  reserved
    ;   |  |  |  |  |  |  +----------------------------- [9]  reserved
    ;   |  |  |  |  |  +-------------------------------- [10] reserved
    ;   |  |  |  |  +----------------------------------- [11] reserved
    ;   |  |  |  |
    ;   |  |  |  +-------------------------------------- [12] reserved
    ;   |  |  +----------------------------------------- [13] reserved
    ;   |  +-------------------------------------------- [14] reserved
    ;   +----------------------------------------------- [15] reserved
DMA1_CH2_DST_LSW        .set     0x0D42    ; DMA1 Channel 2 Destination LSW Address
    ; DMA1_CH2_DST_LSW   Address:  0x0D42 (IO space)      DMA1 Channel 2 Destination LSW Address
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ; |15:14:13:12|11:10: 9: 8| 7: 6: 5: 4| 3: 2: 1: 0|  <<== Bit Position
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; |rw:rw:rw:rw|rw:rw:rw:rw|rw:rw:rw:rw|rw:rw:rw:rw|  <<== Read / Write Access
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; | 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0|  <<== Reset Values
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-- [0]  DMADestByteAddr[0]    ( Psuedo Code for setting DMA SRC/DEST Addresses:
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  +----- [1]  DMADestByteAddr[1]     if( io_space ) {
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  +-------- [2]  DMADestByteAddr[2]         DMADestByteAddr[17:0] = DSP_IOPORT_ADDR;
    ;   |  |  |  |  |  |  |  |  |  |  |  |  +----------- [3]  DMADestByteAddr[3]     } elsif( daram ) {
    ;   |  |  |  |  |  |  |  |  |  |  |  |                                              DMADestByteAddr[17:0] = 0x10000 + DSP_BYTE_ADDR;
    ;   |  |  |  |  |  |  |  |  |  |  |  +-------------- [4]  DMADestByteAddr[4]     } elsif( saram ) {
    ;   |  |  |  |  |  |  |  |  |  |  +----------------- [5]  DMADestByteAddr[5]         DMADestByteAddr[17:0] = 0x20000 + DSP_BYTE_ADDR;
    ;   |  |  |  |  |  |  |  |  |  +-------------------- [6]  DMADestByteAddr[6]     }
    ;   |  |  |  |  |  |  |  |  +----------------------- [7]  DMADestByteAddr[7] 
    ;   |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  +-------------------------- [8]  DMADestByteAddr[8]      DMA0 can see: 
    ;   |  |  |  |  |  |  +----------------------------- [9]  DMADestByteAddr[9]      DMA1 can see: 
    ;   |  |  |  |  |  +-------------------------------- [10] DMADestByteAddr[10]     DMA2 can see: 
    ;   |  |  |  |  +----------------------------------- [11] DMADestByteAddr[11]     DMA3 can see: )
    ;   |  |  |  |
    ;   |  |  |  +-------------------------------------- [12] DMADestByteAddr[12]
    ;   |  |  +----------------------------------------- [13] DMADestByteAddr[13]
    ;   |  +-------------------------------------------- [14] DMADestByteAddr[14]
    ;   +----------------------------------------------- [15] DMADestByteAddr[15]
DMA1_CH2_DST_MSW        .set     0x0D43    ; DMA1 Channel 2 Destination MSW Address
    ; DMA1_CH2_DST_MSW   Address:  0x0D43 (IO space)      DMA1 Channel 2 Destination MSW Address
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ; |15:14:13:12|11:10: 9: 8| 7: 6: 5: 4| 3: 2: 1: 0|  <<== Bit Position
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; |r :r :r :r |r :r :r :r |r :r :r :r |r :r :rw:rw|  <<== Read / Write Access
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; | 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0|  <<== Reset Values
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-- [0]  DMADestByteAddr[16]
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  +----- [1]  DMADestByteAddr[17]
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  +-------- [2]  reserved
    ;   |  |  |  |  |  |  |  |  |  |  |  |  +----------- [3]  reserved
    ;   |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  +-------------- [4]  reserved
    ;   |  |  |  |  |  |  |  |  |  |  +----------------- [5]  reserved
    ;   |  |  |  |  |  |  |  |  |  +-------------------- [6]  reserved
    ;   |  |  |  |  |  |  |  |  +----------------------- [7]  reserved
    ;   |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  +-------------------------- [8]  reserved
    ;   |  |  |  |  |  |  +----------------------------- [9]  reserved
    ;   |  |  |  |  |  +-------------------------------- [10] reserved
    ;   |  |  |  |  +----------------------------------- [11] reserved
    ;   |  |  |  |
    ;   |  |  |  +-------------------------------------- [12] reserved
    ;   |  |  +----------------------------------------- [13] reserved
    ;   |  +-------------------------------------------- [14] reserved
    ;   +----------------------------------------------- [15] reserved
DMA1_CH2_TC_LEN         .set     0x0D44    ; DMA1 Destination Address
    ; DMA1_CH2_TC_LEN   Address:  0x0D44 (IO space)      DMA1 Channel 2 Length / Transfer Control LSW Register
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ; |15:14:13:12|11:10: 9: 8| 7: 6: 5: 4| 3: 2: 1: 0|  <<== Bit Position
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; |rw:rw:rw:rw|rw:rw:rw:rw|rw:rw:rw:rw|rw:rw:r :r |  <<== Read / Write Access
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; | 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0|  <<== Reset Values
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |   ( XferLength[15:0] = number of bytes to be transfered)
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-- [0]  XferLength[0]
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  +----- [1]  XferLength[1]
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  +-------- [2]  XferLength[2]
    ;   |  |  |  |  |  |  |  |  |  |  |  |  +----------- [3]  XferLength[3]
    ;   |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  +-------------- [4]  XferLength[4]
    ;   |  |  |  |  |  |  |  |  |  |  +----------------- [5]  XferLength[5]
    ;   |  |  |  |  |  |  |  |  |  +-------------------- [6]  XferLength[6]
    ;   |  |  |  |  |  |  |  |  +----------------------- [7]  XferLength[7]
    ;   |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  +-------------------------- [8]  XferLength[8]
    ;   |  |  |  |  |  |  +----------------------------- [9]  XferLength[9]
    ;   |  |  |  |  |  +-------------------------------- [10] XferLength[10]
    ;   |  |  |  |  +----------------------------------- [11] XferLength[11]
    ;   |  |  |  |
    ;   |  |  |  +-------------------------------------- [12] XferLength[12]
    ;   |  |  +----------------------------------------- [13] XferLength[13]
    ;   |  +-------------------------------------------- [14] XferLength[14]
    ;   +----------------------------------------------- [15] XferLength[15]
DMA1_CH2_TC_MSW         .set     0x0D45    ; DMA1 Channel 2 Transfer Control MSW Register
    ; DMA1_CH2_TC_MSW   Address:  0x0D45 (IO space)      DMA1 Channel 2 Transfer Control MSW Register
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ; |15:14:13:12|11:10: 9: 8| 7: 6: 5: 4| 3: 2: 1: 0|  <<== Bit Position
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; |rw:rw:rw:rw|r :r :rw:rw|rw:rw:rw:rw|rw:r :rw:rw|  <<== Read / Write Access
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; | 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0|  <<== Reset Values
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +--  [0]  SourceSize[0]      Source Data Size:
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-----  [1]  SourceSize[1]      (00: 32-bit, 01: 16-bit, 10: 8-bit,  11: Reserved)
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  +--------  [2]  Sync               (1: DMA transfers one burst-mode length of 32-bit words per one peripheral event, 0: DMA transfers not controlled by peripheral events)
    ;   |  |  |  |  |  |  |  |  |  |  |  |  +-----------  [3]  BurstMode[0]       (000:1 32bit word burst, 001:2 32bit word burst,
    ;   |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  +--------------  [4]  BurstMode[1]        010:4 32bit word burst, 011:8 32bit word burst,
    ;   |  |  |  |  |  |  |  |  |  |  +-----------------  [5]  BurstMode[2]        100:16 32bit word burst, others:reserved)
    ;   |  |  |  |  |  |  |  |  |  +--------------------  [6]  SrcAddrMode[0]     (00:autoincr, 10:src addr is fixed, others:reserved)
    ;   |  |  |  |  |  |  |  |  +-----------------------  [7]  SrcAddrMode[1]
    ;   |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  +--------------------------  [8]  DestAddrMode[0]    (00:autoincr, 10:dest addr is fixed, others:reserved)
    ;   |  |  |  |  |  |  +-----------------------------  [9]  DestAddrMode[1]
    ;   |  |  |  |  |  +--------------------------------  [10] DestSize[0]        Destination data size:
    ;   |  |  |  |  +-----------------------------------  [11] DestSize[1]        (00: 32-bit, 01: 16-bit, 10: 8-bit,  11: Reserved)
    ;   |  |  |  |
    ;   |  |  |  +--------------------------------------  [12] AutoReload        (0:disabled, to restart DMA set start bit = 1; 1:enabled, to stop DMA from reloading set start bit = 0 )
    ;   |  |  +-----------------------------------------  [13] InterruptEn       (0:no interrupts generated, 1:interrupt generated when xfer complete)
    ;   |  +--------------------------------------------  [14] Status            (0:channel inactive, 1:channel active)
    ;   +-----------------------------------------------  [15] Start/Stop        (0:stops after burst is complete, 1:starts block xfer)

;**************************************************************************
;        DMA1 Ch3 Register Addresses
;**************************************************************************
DMA1_CH3_SRC_LSW        .set     0x0D60    ; DMA1 Channel 3 Source LSW Address
    ; DMA1_CH3_SRC_LSW   Address:  0x0D60 (IO space)      DMA1 Channel 3 Source LSW Address
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ; |15:14:13:12|11:10: 9: 8| 7: 6: 5: 4| 3: 2: 1: 0|  <<== Bit Position
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; |rw:rw:rw:rw|rw:rw:rw:rw|rw:rw:rw:rw|rw:rw:rw:rw|  <<== Read / Write Access
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; | 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0|  <<== Reset Values
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-- [0]  DMASrcByteAddr[0]     ( Psuedo Code for setting DMA SRC/DEST Addresses:
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  +----- [1]  DMASrcByteAddr[1]      if( io_space ) {
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  +-------- [2]  DMASrcByteAddr[2]          DMASrcByteAddr[17:0] = DSP_IOPORT_ADDR;
    ;   |  |  |  |  |  |  |  |  |  |  |  |  +----------- [3]  DMASrcByteAddr[3]      } elsif( daram ) {
    ;   |  |  |  |  |  |  |  |  |  |  |  |                                               DMASrcByteAddr[17:0] = 0x10000 + DSP_BYTE_ADDR;
    ;   |  |  |  |  |  |  |  |  |  |  |  +-------------- [4]  DMASrcByteAddr[4]      } elsif( saram ) {
    ;   |  |  |  |  |  |  |  |  |  |  +----------------- [5]  DMASrcByteAddr[5]          DMASrcByteAddr[17:0] = 0x20000 + DSP_BYTE_ADDR;
    ;   |  |  |  |  |  |  |  |  |  +-------------------- [6]  DMASrcByteAddr[6]      }
    ;   |  |  |  |  |  |  |  |  +----------------------- [7]  DMASrcByteAddr[7] 
    ;   |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  +-------------------------- [8]  DMASrcByteAddr[8]      DMA0 can see: 
    ;   |  |  |  |  |  |  +----------------------------- [9]  DMASrcByteAddr[9]      DMA1 can see: 
    ;   |  |  |  |  |  +-------------------------------- [10] DMASrcByteAddr[10]     DMA2 can see: 
    ;   |  |  |  |  +----------------------------------- [11] DMASrcByteAddr[11]     DMA3 can see: )
    ;   |  |  |  |
    ;   |  |  |  +-------------------------------------- [12] DMASrcByteAddr[12]
    ;   |  |  +----------------------------------------- [13] DMASrcByteAddr[13]
    ;   |  +-------------------------------------------- [14] DMASrcByteAddr[14]
    ;   +----------------------------------------------- [15] DMASrcByteAddr[15]
DMA1_CH3_SRC_MSW        .set     0x0D61    ; DMA1 Channel 3 Source MSW Address
    ; DMA1_CH3_SRC_MSW   Address:  0x0D61 (IO space)      DMA1 Channel 3 Source MSW Address
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ; |15:14:13:12|11:10: 9: 8| 7: 6: 5: 4| 3: 2: 1: 0|  <<== Bit Position
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; |r :r :r :r |r :r :r :r |r :r :r :r |r :r :rw:rw|  <<== Read / Write Access
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; | 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0|  <<== Reset Values
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-- [0]  DMASrcByteAddr[16]
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  +----- [1]  DMASrcByteAddr[17]
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  +-------- [2]  reserved
    ;   |  |  |  |  |  |  |  |  |  |  |  |  +----------- [3]  reserved
    ;   |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  +-------------- [4]  reserved
    ;   |  |  |  |  |  |  |  |  |  |  +----------------- [5]  reserved
    ;   |  |  |  |  |  |  |  |  |  +-------------------- [6]  reserved
    ;   |  |  |  |  |  |  |  |  +----------------------- [7]  reserved
    ;   |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  +-------------------------- [8]  reserved
    ;   |  |  |  |  |  |  +----------------------------- [9]  reserved
    ;   |  |  |  |  |  +-------------------------------- [10] reserved
    ;   |  |  |  |  +----------------------------------- [11] reserved
    ;   |  |  |  |
    ;   |  |  |  +-------------------------------------- [12] reserved
    ;   |  |  +----------------------------------------- [13] reserved
    ;   |  +-------------------------------------------- [14] reserved
    ;   +----------------------------------------------- [15] reserved
DMA1_CH3_DST_LSW        .set     0x0D62    ; DMA1 Channel 3 Destination LSW Address
    ; DMA1_CH3_DST_LSW   Address:  0x0D62 (IO space)      DMA1 Channel 3 Destination LSW Address
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ; |15:14:13:12|11:10: 9: 8| 7: 6: 5: 4| 3: 2: 1: 0|  <<== Bit Position
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; |rw:rw:rw:rw|rw:rw:rw:rw|rw:rw:rw:rw|rw:rw:rw:rw|  <<== Read / Write Access
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; | 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0|  <<== Reset Values
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-- [0]  DMADestByteAddr[0]    ( Psuedo Code for setting DMA SRC/DEST Addresses:
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  +----- [1]  DMADestByteAddr[1]     if( io_space ) {
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  +-------- [2]  DMADestByteAddr[2]         DMADestByteAddr[17:0] = DSP_IOPORT_ADDR;
    ;   |  |  |  |  |  |  |  |  |  |  |  |  +----------- [3]  DMADestByteAddr[3]     } elsif( daram ) {
    ;   |  |  |  |  |  |  |  |  |  |  |  |                                              DMADestByteAddr[17:0] = 0x10000 + DSP_BYTE_ADDR;
    ;   |  |  |  |  |  |  |  |  |  |  |  +-------------- [4]  DMADestByteAddr[4]     } elsif( saram ) {
    ;   |  |  |  |  |  |  |  |  |  |  +----------------- [5]  DMADestByteAddr[5]         DMADestByteAddr[17:0] = 0x20000 + DSP_BYTE_ADDR;
    ;   |  |  |  |  |  |  |  |  |  +-------------------- [6]  DMADestByteAddr[6]     }
    ;   |  |  |  |  |  |  |  |  +----------------------- [7]  DMADestByteAddr[7] 
    ;   |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  +-------------------------- [8]  DMADestByteAddr[8]      DMA0 can see: 
    ;   |  |  |  |  |  |  +----------------------------- [9]  DMADestByteAddr[9]      DMA1 can see: 
    ;   |  |  |  |  |  +-------------------------------- [10] DMADestByteAddr[10]     DMA2 can see: 
    ;   |  |  |  |  +----------------------------------- [11] DMADestByteAddr[11]     DMA3 can see: )
    ;   |  |  |  |
    ;   |  |  |  +-------------------------------------- [12] DMADestByteAddr[12]
    ;   |  |  +----------------------------------------- [13] DMADestByteAddr[13]
    ;   |  +-------------------------------------------- [14] DMADestByteAddr[14]
    ;   +----------------------------------------------- [15] DMADestByteAddr[15]
DMA1_CH3_DST_MSW        .set     0x0D63    ; DMA1 Channel 3 Destination MSW Address
    ; DMA1_CH3_DST_MSW   Address:  0x0D63 (IO space)      DMA1 Channel 3 Destination MSW Address
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ; |15:14:13:12|11:10: 9: 8| 7: 6: 5: 4| 3: 2: 1: 0|  <<== Bit Position
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; |r :r :r :r |r :r :r :r |r :r :r :r |r :r :rw:rw|  <<== Read / Write Access
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; | 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0|  <<== Reset Values
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-- [0]  DMADestByteAddr[16]
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  +----- [1]  DMADestByteAddr[17]
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  +-------- [2]  reserved
    ;   |  |  |  |  |  |  |  |  |  |  |  |  +----------- [3]  reserved
    ;   |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  +-------------- [4]  reserved
    ;   |  |  |  |  |  |  |  |  |  |  +----------------- [5]  reserved
    ;   |  |  |  |  |  |  |  |  |  +-------------------- [6]  reserved
    ;   |  |  |  |  |  |  |  |  +----------------------- [7]  reserved
    ;   |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  +-------------------------- [8]  reserved
    ;   |  |  |  |  |  |  +----------------------------- [9]  reserved
    ;   |  |  |  |  |  +-------------------------------- [10] reserved
    ;   |  |  |  |  +----------------------------------- [11] reserved
    ;   |  |  |  |
    ;   |  |  |  +-------------------------------------- [12] reserved
    ;   |  |  +----------------------------------------- [13] reserved
    ;   |  +-------------------------------------------- [14] reserved
    ;   +----------------------------------------------- [15] reserved
DMA1_CH3_TC_LEN         .set     0x0D64    ; DMA1 Destination Address
    ; DMA1_CH3_TC_LEN   Address:  0x0D64 (IO space)      DMA1 Channel 3 Length / Transfer Control LSW Register
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ; |15:14:13:12|11:10: 9: 8| 7: 6: 5: 4| 3: 2: 1: 0|  <<== Bit Position
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; |rw:rw:rw:rw|rw:rw:rw:rw|rw:rw:rw:rw|rw:rw:r :r |  <<== Read / Write Access
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; | 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0|  <<== Reset Values
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |   ( XferLength[15:0] = number of bytes to be transfered)
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-- [0]  XferLength[0]
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  +----- [1]  XferLength[1]
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  +-------- [2]  XferLength[2]
    ;   |  |  |  |  |  |  |  |  |  |  |  |  +----------- [3]  XferLength[3]
    ;   |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  +-------------- [4]  XferLength[4]
    ;   |  |  |  |  |  |  |  |  |  |  +----------------- [5]  XferLength[5]
    ;   |  |  |  |  |  |  |  |  |  +-------------------- [6]  XferLength[6]
    ;   |  |  |  |  |  |  |  |  +----------------------- [7]  XferLength[7]
    ;   |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  +-------------------------- [8]  XferLength[8]
    ;   |  |  |  |  |  |  +----------------------------- [9]  XferLength[9]
    ;   |  |  |  |  |  +-------------------------------- [10] XferLength[10]
    ;   |  |  |  |  +----------------------------------- [11] XferLength[11]
    ;   |  |  |  |
    ;   |  |  |  +-------------------------------------- [12] XferLength[12]
    ;   |  |  +----------------------------------------- [13] XferLength[13]
    ;   |  +-------------------------------------------- [14] XferLength[14]
    ;   +----------------------------------------------- [15] XferLength[15]
DMA1_CH3_TC_MSW         .set     0x0D65    ; DMA1 Channel 0 Transfer Control MSW Register
    ; DMA1_CH3_TC_MSW   Address:  0x0D65 (IO space)      DMA1 Channel 3 Transfer Control MSW Register
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ; |15:14:13:12|11:10: 9: 8| 7: 6: 5: 4| 3: 2: 1: 0|  <<== Bit Position
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; |rw:rw:rw:rw|r :r :rw:rw|rw:rw:rw:rw|rw:r :rw:rw|  <<== Read / Write Access
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; | 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0|  <<== Reset Values
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-- [0]  SourceSize[0]      Source Data Size:
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  +----- [1]  SourceSize[1]      (00: 32-bit, 01: 16-bit, 10: 8-bit,  11: Reserved)
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  +-------- [2]  Sync               (1: DMA transfers one burst-mode length of 32-bit words per one peripheral event, 0: DMA transfers not controlled by peripheral events)
    ;   |  |  |  |  |  |  |  |  |  |  |  |  +----------- [3]  BurstMode[0]       (000:1 32bit word burst, 001:2 32bit word burst,
    ;   |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  +-------------- [4]  BurstMode[1]        010:4 32bit word burst, 011:8 32bit word burst,
    ;   |  |  |  |  |  |  |  |  |  |  +----------------- [5]  BurstMode[2]        100:16 32bit word burst, others:reserved)
    ;   |  |  |  |  |  |  |  |  |  +-------------------- [6]  SrcAddrMode[0]     (00:autoincr, 10:src addr is fixed, others:reserved)
    ;   |  |  |  |  |  |  |  |  +----------------------- [7]  SrcAddrMode[1]
    ;   |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  +-------------------------- [8]  DestAddrMode[0]    (00:autoincr, 10:dest addr is fixed, others:reserved)
    ;   |  |  |  |  |  |  +----------------------------- [9]  DestAddrMode[1]
    ;   |  |  |  |  |  +-------------------------------- [10] DestSize[0]        Destination data size:
    ;   |  |  |  |  +----------------------------------- [11] DestSize[1]        (00: 32-bit, 01: 16-bit, 10: 8-bit,  11: Reserved)
    ;   |  |  |  |
    ;   |  |  |  +-------------------------------------- [12] AutoReload        (0:disabled, to restart DMA set start bit = 1; 1:enabled, to stop DMA from reloading set start bit = 0 )
    ;   |  |  +----------------------------------------- [13] InterruptEn       (0:no interrupts generated, 1:interrupt generated when xfer complete)
    ;   |  +-------------------------------------------- [14] Status            (0:channel inactive, 1:channel active)
    ;   +----------------------------------------------- [15] Start/Stop        (0:stops after burst is complete, 1:starts block xfer)
;****************************************************************************************

;****************************************************************************************
;         DMA 2
;**************************************************************************
;        DMA2 Ch0 Register Addresses
;**************************************************************************
DMA2_CH0_SRC_LSW        .set     0x0E00    ; DMA2 Channel 0 Source LSW Address
    ; DMA2_CH0_SRC_LSW   Address:  0x0E00 (IO space)      DMA2 Channel 0 Source LSW Address
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ; |15:14:13:12|11:10: 9: 8| 7: 6: 5: 4| 3: 2: 1: 0|  <<== Bit Position
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; |rw:rw:rw:rw|rw:rw:rw:rw|rw:rw:rw:rw|rw:rw:rw:rw|  <<== Read / Write Access
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; | 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0|  <<== Reset Values
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-- [0]  DMASrcByteAddr[0]     ( Psuedo Code for setting DMA SRC/DEST Addresses:
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  +----- [1]  DMASrcByteAddr[1]      if( io_space ) {
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  +-------- [2]  DMASrcByteAddr[2]          DMASrcByteAddr[17:0] = DSP_IOPORT_ADDR;
    ;   |  |  |  |  |  |  |  |  |  |  |  |  +----------- [3]  DMASrcByteAddr[3]      } elsif( daram ) {
    ;   |  |  |  |  |  |  |  |  |  |  |  |                                               DMASrcByteAddr[17:0] = 0x10000 + DSP_BYTE_ADDR;
    ;   |  |  |  |  |  |  |  |  |  |  |  +-------------- [4]  DMASrcByteAddr[4]      } elsif( saram ) {
    ;   |  |  |  |  |  |  |  |  |  |  +----------------- [5]  DMASrcByteAddr[5]          DMASrcByteAddr[17:0] = 0x20000 + DSP_BYTE_ADDR;
    ;   |  |  |  |  |  |  |  |  |  +-------------------- [6]  DMASrcByteAddr[6]      }
    ;   |  |  |  |  |  |  |  |  +----------------------- [7]  DMASrcByteAddr[7] 
    ;   |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  +-------------------------- [8]  DMASrcByteAddr[8]      DMA0 can see: 
    ;   |  |  |  |  |  |  +----------------------------- [9]  DMASrcByteAddr[9]      DMA1 can see: 
    ;   |  |  |  |  |  +-------------------------------- [10] DMASrcByteAddr[10]     DMA2 can see: 
    ;   |  |  |  |  +----------------------------------- [11] DMASrcByteAddr[11]     DMA3 can see: )
    ;   |  |  |  |
    ;   |  |  |  +-------------------------------------- [12] DMASrcByteAddr[12]
    ;   |  |  +----------------------------------------- [13] DMASrcByteAddr[13]
    ;   |  +-------------------------------------------- [14] DMASrcByteAddr[14]
    ;   +----------------------------------------------- [15] DMASrcByteAddr[15]
DMA2_CH0_SRC_MSW        .set     0x0E01    ; DMA2 Channel 0 Source MSW Address
    ; DMA2_CH0_SRC_MSW   Address:  0x0E01 (IO space)      DMA2 Channel 0 Source MSW Address
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ; |15:14:13:12|11:10: 9: 8| 7: 6: 5: 4| 3: 2: 1: 0|  <<== Bit Position
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; |r :r :r :r |r :r :r :r |r :r :r :r |r :r :rw:rw|  <<== Read / Write Access
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; | 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0|  <<== Reset Values
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-- [0]  DMASrcByteAddr[16]
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  +----- [1]  DMASrcByteAddr[17]
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  +-------- [2]  reserved
    ;   |  |  |  |  |  |  |  |  |  |  |  |  +----------- [3]  reserved
    ;   |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  +-------------- [4]  reserved
    ;   |  |  |  |  |  |  |  |  |  |  +----------------- [5]  reserved
    ;   |  |  |  |  |  |  |  |  |  +-------------------- [6]  reserved
    ;   |  |  |  |  |  |  |  |  +----------------------- [7]  reserved
    ;   |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  +-------------------------- [8]  reserved
    ;   |  |  |  |  |  |  +----------------------------- [9]  reserved
    ;   |  |  |  |  |  +-------------------------------- [10] reserved
    ;   |  |  |  |  +----------------------------------- [11] reserved
    ;   |  |  |  |
    ;   |  |  |  +-------------------------------------- [12] reserved
    ;   |  |  +----------------------------------------- [13] reserved
    ;   |  +-------------------------------------------- [14] reserved
    ;   +----------------------------------------------- [15] reserved
DMA2_CH0_DST_LSW        .set     0x0E02    ; DMA2 Channel 0 Destination LSW Address
    ; DMA2_CH0_DST_LSW   Address:  0x0E02 (IO space)      DMA2 Channel 0 Destination LSW Address
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ; |15:14:13:12|11:10: 9: 8| 7: 6: 5: 4| 3: 2: 1: 0|  <<== Bit Position
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; |rw:rw:rw:rw|rw:rw:rw:rw|rw:rw:rw:rw|rw:rw:rw:rw|  <<== Read / Write Access
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; | 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0|  <<== Reset Values
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-- [0]  DMADestByteAddr[0]    ( Psuedo Code for setting DMA SRC/DEST Addresses:
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  +----- [1]  DMADestByteAddr[1]     if( io_space ) {
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  +-------- [2]  DMADestByteAddr[2]         DMADestByteAddr[17:0] = DSP_IOPORT_ADDR;
    ;   |  |  |  |  |  |  |  |  |  |  |  |  +----------- [3]  DMADestByteAddr[3]     } elsif( daram ) {
    ;   |  |  |  |  |  |  |  |  |  |  |  |                                              DMADestByteAddr[17:0] = 0x10000 + DSP_BYTE_ADDR;
    ;   |  |  |  |  |  |  |  |  |  |  |  +-------------- [4]  DMADestByteAddr[4]     } elsif( saram ) {
    ;   |  |  |  |  |  |  |  |  |  |  +----------------- [5]  DMADestByteAddr[5]         DMADestByteAddr[17:0] = 0x20000 + DSP_BYTE_ADDR;
    ;   |  |  |  |  |  |  |  |  |  +-------------------- [6]  DMADestByteAddr[6]     }
    ;   |  |  |  |  |  |  |  |  +----------------------- [7]  DMADestByteAddr[7] 
    ;   |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  +-------------------------- [8]  DMADestByteAddr[8]      DMA0 can see: 
    ;   |  |  |  |  |  |  +----------------------------- [9]  DMADestByteAddr[9]      DMA1 can see: 
    ;   |  |  |  |  |  +-------------------------------- [10] DMADestByteAddr[10]     DMA2 can see: 
    ;   |  |  |  |  +----------------------------------- [11] DMADestByteAddr[11]     DMA3 can see: )
    ;   |  |  |  |
    ;   |  |  |  +-------------------------------------- [12] DMADestByteAddr[12]
    ;   |  |  +----------------------------------------- [13] DMADestByteAddr[13]
    ;   |  +-------------------------------------------- [14] DMADestByteAddr[14]
    ;   +----------------------------------------------- [15] DMADestByteAddr[15]
DMA2_CH0_DST_MSW        .set     0x0E03    ; DMA2 Channel 0 Destination MSW Address
    ; DMA2_CH0_DST_MSW   Address:  0x0E03 (IO space)      DMA2 Channel 0 Destination MSW Address
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ; |15:14:13:12|11:10: 9: 8| 7: 6: 5: 4| 3: 2: 1: 0|  <<== Bit Position
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; |r :r :r :r |r :r :r :r |r :r :r :r |r :r :rw:rw|  <<== Read / Write Access
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; | 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0|  <<== Reset Values
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-- [0]  DMADestByteAddr[16]
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  +----- [1]  DMADestByteAddr[17]
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  +-------- [2]  reserved
    ;   |  |  |  |  |  |  |  |  |  |  |  |  +----------- [3]  reserved
    ;   |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  +-------------- [4]  reserved
    ;   |  |  |  |  |  |  |  |  |  |  +----------------- [5]  reserved
    ;   |  |  |  |  |  |  |  |  |  +-------------------- [6]  reserved
    ;   |  |  |  |  |  |  |  |  +----------------------- [7]  reserved
    ;   |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  +-------------------------- [8]  reserved
    ;   |  |  |  |  |  |  +----------------------------- [9]  reserved
    ;   |  |  |  |  |  +-------------------------------- [10] reserved
    ;   |  |  |  |  +----------------------------------- [11] reserved
    ;   |  |  |  |
    ;   |  |  |  +-------------------------------------- [12] reserved
    ;   |  |  +----------------------------------------- [13] reserved
    ;   |  +-------------------------------------------- [14] reserved
    ;   +----------------------------------------------- [15] reserved
DMA2_CH0_TC_LEN         .set     0x0E04    ; DMA2 Channel 0 Length / Transfer Control LSW Register
    ; DMA2_CH0_TC_LEN   Address:  0x0E04 (IO space)      DMA2 Channel 0 Length / Transfer Control LSW Register
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ; |15:14:13:12|11:10: 9: 8| 7: 6: 5: 4| 3: 2: 1: 0|  <<== Bit Position
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; |rw:rw:rw:rw|rw:rw:rw:rw|rw:rw:rw:rw|rw:rw:r :r |  <<== Read / Write Access
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; | 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0|  <<== Reset Values
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |   ( XferLength[15:0] = number of bytes to be transfered)
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-- [0]  XferLength[0]
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  +----- [1]  XferLength[1]
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  +-------- [2]  XferLength[2]
    ;   |  |  |  |  |  |  |  |  |  |  |  |  +----------- [3]  XferLength[3]
    ;   |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  +-------------- [4]  XferLength[4]
    ;   |  |  |  |  |  |  |  |  |  |  +----------------- [5]  XferLength[5]
    ;   |  |  |  |  |  |  |  |  |  +-------------------- [6]  XferLength[6]
    ;   |  |  |  |  |  |  |  |  +----------------------- [7]  XferLength[7]
    ;   |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  +-------------------------- [8]  XferLength[8]
    ;   |  |  |  |  |  |  +----------------------------- [9]  XferLength[9]
    ;   |  |  |  |  |  +-------------------------------- [10] XferLength[10]
    ;   |  |  |  |  +----------------------------------- [11] XferLength[11]
    ;   |  |  |  |
    ;   |  |  |  +-------------------------------------- [12] XferLength[12]
    ;   |  |  +----------------------------------------- [13] XferLength[13]
    ;   |  +-------------------------------------------- [14] XferLength[14]
    ;   +----------------------------------------------- [15] XferLength[15]
DMA2_CH0_TC_MSW         .set     0x0E05    ; DMA2 Channel 0 Transfer Control MSW Register
    ; DMA2_CH0_TC_MSW   Address:  0x0E05 (IO space)      DMA2 Channel 0 Transfer Control MSW Register
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ; |15:14:13:12|11:10: 9: 8| 7: 6: 5: 4| 3: 2: 1: 0|  <<== Bit Position
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; |rw:rw:rw:rw|r :r :rw:rw|rw:rw:rw:rw|rw:r :rw:rw|  <<== Read / Write Access
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; | 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0|  <<== Reset Values
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-- [0]  SourceSize[0]      Source Data Size:
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  +----- [1]  SourceSize[1]      (00: 32-bit, 01: 16-bit, 10: 8-bit,  11: Reserved)
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  +-------- [2]  Sync               (1: DMA transfers one burst-mode length of 32-bit words per one peripheral event, 0: DMA transfers not controlled by peripheral events)
    ;   |  |  |  |  |  |  |  |  |  |  |  |  +----------- [3]  BurstMode[0]       (000:1 32bit word burst, 001:2 32bit word burst,
    ;   |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  +-------------- [4]  BurstMode[1]        010:4 32bit word burst, 011:8 32bit word burst,
    ;   |  |  |  |  |  |  |  |  |  |  +----------------- [5]  BurstMode[2]        100:16 32bit word burst, others:reserved)
    ;   |  |  |  |  |  |  |  |  |  +-------------------- [6]  SrcAddrMode[0]     (00:autoincr, 10:src addr is fixed, others:reserved)
    ;   |  |  |  |  |  |  |  |  +----------------------- [7]  SrcAddrMode[1]
    ;   |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  +-------------------------- [8]  DestAddrMode[0]    (00:autoincr, 10:dest addr is fixed, others:reserved)
    ;   |  |  |  |  |  |  +----------------------------- [9]  DestAddrMode[1]
    ;   |  |  |  |  |  +-------------------------------- [10] DestSize[0]        Destination data size:
    ;   |  |  |  |  +----------------------------------- [11] DestSize[1]        (00: 32-bit, 01: 16-bit, 10: 8-bit,  11: Reserved)
    ;   |  |  |  |
    ;   |  |  |  +-------------------------------------- [12] AutoReload        (0:disabled, to restart DMA set start bit = 1; 1:enabled, to stop DMA from reloading set start bit = 0 )
    ;   |  |  +----------------------------------------- [13] InterruptEn       (0:no interrupts generated, 1:interrupt generated when xfer complete)
    ;   |  +-------------------------------------------- [14] Status            (0:channel inactive, 1:channel active)
    ;   +----------------------------------------------- [15] Start/Stop        (0:stops after burst is complete, 1:starts block xfer)


;**************************************************************************
;        DMA2 Ch1 Register Addresses
;**************************************************************************
DMA2_CH1_SRC_LSW        .set     0x0E20    ; DMA2 Channel 1 Source LSW Address
    ; DMA2_CH1_SRC_LSW   Address:  0x0E20 (IO space)      DMA2 Channel 1 Source LSW Address
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ; |15:14:13:12|11:10: 9: 8| 7: 6: 5: 4| 3: 2: 1: 0|  <<== Bit Position
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; |rw:rw:rw:rw|rw:rw:rw:rw|rw:rw:rw:rw|rw:rw:rw:rw|  <<== Read / Write Access
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; | 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0|  <<== Reset Values
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-- [0]  DMASrcByteAddr[0]     ( Psuedo Code for setting DMA SRC/DEST Addresses:
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  +----- [1]  DMASrcByteAddr[1]      if( io_space ) {
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  +-------- [2]  DMASrcByteAddr[2]          DMASrcByteAddr[17:0] = DSP_IOPORT_ADDR;
    ;   |  |  |  |  |  |  |  |  |  |  |  |  +----------- [3]  DMASrcByteAddr[3]      } elsif( daram ) {
    ;   |  |  |  |  |  |  |  |  |  |  |  |                                               DMASrcByteAddr[17:0] = 0x10000 + DSP_BYTE_ADDR;
    ;   |  |  |  |  |  |  |  |  |  |  |  +-------------- [4]  DMASrcByteAddr[4]      } elsif( saram ) {
    ;   |  |  |  |  |  |  |  |  |  |  +----------------- [5]  DMASrcByteAddr[5]          DMASrcByteAddr[17:0] = 0x20000 + DSP_BYTE_ADDR;
    ;   |  |  |  |  |  |  |  |  |  +-------------------- [6]  DMASrcByteAddr[6]      }
    ;   |  |  |  |  |  |  |  |  +----------------------- [7]  DMASrcByteAddr[7]
    ;   |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  +-------------------------- [8]  DMASrcByteAddr[8]      DMA0 can see: 
    ;   |  |  |  |  |  |  +----------------------------- [9]  DMASrcByteAddr[9]      DMA1 can see: 
    ;   |  |  |  |  |  +-------------------------------- [10] DMASrcByteAddr[10]     DMA2 can see: 
    ;   |  |  |  |  +----------------------------------- [11] DMASrcByteAddr[11]     DMA3 can see: )
    ;   |  |  |  |
    ;   |  |  |  +-------------------------------------- [12] DMASrcByteAddr[12]
    ;   |  |  +----------------------------------------- [13] DMASrcByteAddr[13]
    ;   |  +-------------------------------------------- [14] DMASrcByteAddr[14]
    ;   +----------------------------------------------- [15] DMASrcByteAddr[15]
DMA2_CH1_SRC_MSW        .set     0x0E21    ; DMA2 Channel 1 Source MSW Address
    ; DMA2_CH1_SRC_MSW   Address:  0x0E21 (IO space)      DMA2 Channel 1 Source MSW Address
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ; |15:14:13:12|11:10: 9: 8| 7: 6: 5: 4| 3: 2: 1: 0|  <<== Bit Position
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; |r :r :r :r |r :r :r :r |r :r :r :r |r :r :rw:rw|  <<== Read / Write Access
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; | 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0|  <<== Reset Values
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-- [0]  DMASrcByteAddr[16]
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  +----- [1]  DMASrcByteAddr[17]
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  +-------- [2]  reserved
    ;   |  |  |  |  |  |  |  |  |  |  |  |  +----------- [3]  reserved
    ;   |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  +-------------- [4]  reserved
    ;   |  |  |  |  |  |  |  |  |  |  +----------------- [5]  reserved
    ;   |  |  |  |  |  |  |  |  |  +-------------------- [6]  reserved
    ;   |  |  |  |  |  |  |  |  +----------------------- [7]  reserved
    ;   |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  +-------------------------- [8]  reserved
    ;   |  |  |  |  |  |  +----------------------------- [9]  reserved
    ;   |  |  |  |  |  +-------------------------------- [10] reserved
    ;   |  |  |  |  +----------------------------------- [11] reserved
    ;   |  |  |  |
    ;   |  |  |  +-------------------------------------- [12] reserved
    ;   |  |  +----------------------------------------- [13] reserved
    ;   |  +-------------------------------------------- [14] reserved
    ;   +----------------------------------------------- [15] reserved
DMA2_CH1_DST_LSW        .set     0x0E22    ; DMA2 Channel 1 Destination LSW Address
    ; DMA2_CH1_DST_LSW   Address:  0x0E02 (IO space)      DMA2 Channel 1 Destination LSW Address
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ; |15:14:13:12|11:10: 9: 8| 7: 6: 5: 4| 3: 2: 1: 0|  <<== Bit Position
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; |rw:rw:rw:rw|rw:rw:rw:rw|rw:rw:rw:rw|rw:rw:rw:rw|  <<== Read / Write Access
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; | 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0|  <<== Reset Values
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-- [0]  DMADestByteAddr[0]    ( Psuedo Code for setting DMA SRC/DEST Addresses:
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  +----- [1]  DMADestByteAddr[1]     if( io_space ) {
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  +-------- [2]  DMADestByteAddr[2]         DMADestByteAddr[17:0] = DSP_IOPORT_ADDR;
    ;   |  |  |  |  |  |  |  |  |  |  |  |  +----------- [3]  DMADestByteAddr[3]     } elsif( daram ) {
    ;   |  |  |  |  |  |  |  |  |  |  |  |                                              DMADestByteAddr[17:0] = 0x10000 + DSP_BYTE_ADDR;
    ;   |  |  |  |  |  |  |  |  |  |  |  +-------------- [4]  DMADestByteAddr[4]     } elsif( saram ) {
    ;   |  |  |  |  |  |  |  |  |  |  +----------------- [5]  DMADestByteAddr[5]         DMADestByteAddr[17:0] = 0x20000 + DSP_BYTE_ADDR;
    ;   |  |  |  |  |  |  |  |  |  +-------------------- [6]  DMADestByteAddr[6]     }
    ;   |  |  |  |  |  |  |  |  +----------------------- [7]  DMADestByteAddr[7] 
    ;   |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  +-------------------------- [8]  DMADestByteAddr[8]      DMA0 can see: 
    ;   |  |  |  |  |  |  +----------------------------- [9]  DMADestByteAddr[9]      DMA1 can see: 
    ;   |  |  |  |  |  +-------------------------------- [10] DMADestByteAddr[10]     DMA2 can see: 
    ;   |  |  |  |  +----------------------------------- [11] DMADestByteAddr[11]     DMA3 can see: )
    ;   |  |  |  |
    ;   |  |  |  +-------------------------------------- [12] DMADestByteAddr[12]
    ;   |  |  +----------------------------------------- [13] DMADestByteAddr[13]
    ;   |  +-------------------------------------------- [14] DMADestByteAddr[14]
    ;   +----------------------------------------------- [15] DMADestByteAddr[15]
DMA2_CH1_DST_MSW        .set     0x0E23    ; DMA2 Channel 1 Destination MSW Address
    ; DMA2_CH1_DST_MSW   Address:  0x0E23 (IO space)      DMA2 Channel 1 Destination MSW Address
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ; |15:14:13:12|11:10: 9: 8| 7: 6: 5: 4| 3: 2: 1: 0|  <<== Bit Position
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; |r :r :r :r |r :r :r :r |r :r :r :r |r :r :rw:rw|  <<== Read / Write Access
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; | 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0|  <<== Reset Values
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-- [0]  DMADestByteAddr[16]
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  +----- [1]  DMADestByteAddr[17]
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  +-------- [2]  reserved
    ;   |  |  |  |  |  |  |  |  |  |  |  |  +----------- [3]  reserved
    ;   |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  +-------------- [4]  reserved
    ;   |  |  |  |  |  |  |  |  |  |  +----------------- [5]  reserved
    ;   |  |  |  |  |  |  |  |  |  +-------------------- [6]  reserved
    ;   |  |  |  |  |  |  |  |  +----------------------- [7]  reserved
    ;   |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  +-------------------------- [8]  reserved
    ;   |  |  |  |  |  |  +----------------------------- [9]  reserved
    ;   |  |  |  |  |  +-------------------------------- [10] reserved
    ;   |  |  |  |  +----------------------------------- [11] reserved
    ;   |  |  |  |
    ;   |  |  |  +-------------------------------------- [12] reserved
    ;   |  |  +----------------------------------------- [13] reserved
    ;   |  +-------------------------------------------- [14] reserved
    ;   +----------------------------------------------- [15] reserved
DMA2_CH1_TC_LEN         .set     0x0E24    ; DMA2 Channel 1 Length / Transfer Control LSW Register
    ; DMA2_CH1_TC_LEN   Address:  0x0E04 (IO space)      DMA2 Channel 1 Length / Transfer Control LSW Register
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ; |15:14:13:12|11:10: 9: 8| 7: 6: 5: 4| 3: 2: 1: 0|  <<== Bit Position
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; |rw:rw:rw:rw|rw:rw:rw:rw|rw:rw:rw:rw|rw:rw:r :r |  <<== Read / Write Access
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; | 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0|  <<== Reset Values
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |   ( XferLength[15:0] = number of bytes to be transfered)
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-- [0]  XferLength[0]
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  +----- [1]  XferLength[1]
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  +-------- [2]  XferLength[2]
    ;   |  |  |  |  |  |  |  |  |  |  |  |  +----------- [3]  XferLength[3]
    ;   |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  +-------------- [4]  XferLength[4]
    ;   |  |  |  |  |  |  |  |  |  |  +----------------- [5]  XferLength[5]
    ;   |  |  |  |  |  |  |  |  |  +-------------------- [6]  XferLength[6]
    ;   |  |  |  |  |  |  |  |  +----------------------- [7]  XferLength[7]
    ;   |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  +-------------------------- [8]  XferLength[8]
    ;   |  |  |  |  |  |  +----------------------------- [9]  XferLength[9]
    ;   |  |  |  |  |  +-------------------------------- [10] XferLength[10]
    ;   |  |  |  |  +----------------------------------- [11] XferLength[11]
    ;   |  |  |  |
    ;   |  |  |  +-------------------------------------- [12] XferLength[12]
    ;   |  |  +----------------------------------------- [13] XferLength[13]
    ;   |  +-------------------------------------------- [14] XferLength[14]
    ;   +----------------------------------------------- [15] XferLength[15]
DMA2_CH1_TC_MSW         .set     0x0E25    ; DMA2 Channel 1 Transfer Control MSW Register
    ; DMA2_CH1_TC_MSW   Address:  0x0E25 (IO space)      DMA2 Channel 1 Transfer Control MSW Register
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ; |15:14:13:12|11:10: 9: 8| 7: 6: 5: 4| 3: 2: 1: 0|  <<== Bit Position
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; |rw:rw:rw:rw|r :r :rw:rw|rw:rw:rw:rw|rw:r :rw:rw|  <<== Read / Write Access
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; | 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0|  <<== Reset Values
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-- [0]  SourceSize[0]      Source Data Size:
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  +----- [1]  SourceSize[1]      (00: 32-bit, 01: 16-bit, 10: 8-bit,  11: Reserved)
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  +-------- [2]  Sync               (1: DMA transfers one burst-mode length of 32-bit words per one peripheral event, 0: DMA transfers not controlled by peripheral events)
    ;   |  |  |  |  |  |  |  |  |  |  |  |  +----------- [3]  BurstMode[0]       (000:1 32bit word burst, 001:2 32bit word burst,
    ;   |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  +-------------- [4]  BurstMode[1]        010:4 32bit word burst, 011:8 32bit word burst,
    ;   |  |  |  |  |  |  |  |  |  |  +----------------- [5]  BurstMode[2]        100:16 32bit word burst, others:reserved)
    ;   |  |  |  |  |  |  |  |  |  +-------------------- [6]  SrcAddrMode[0]     (00:autoincr, 10:src addr is fixed, others:reserved)
    ;   |  |  |  |  |  |  |  |  +----------------------- [7]  SrcAddrMode[1]
    ;   |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  +-------------------------- [8]  DestAddrMode[0]    (00:autoincr, 10:dest addr is fixed, others:reserved)
    ;   |  |  |  |  |  |  +----------------------------- [9]  DestAddrMode[1]
    ;   |  |  |  |  |  +-------------------------------- [10] DestSize[0]        Destination data size:
    ;   |  |  |  |  +----------------------------------- [11] DestSize[1]        (00: 32-bit, 01: 16-bit, 10: 8-bit,  11: Reserved)
    ;   |  |  |  |
    ;   |  |  |  +-------------------------------------- [12] AutoReload        (0:disabled, to restart DMA set start bit = 1; 1:enabled, to stop DMA from reloading set start bit = 0 )
    ;   |  |  +----------------------------------------- [13] InterruptEn       (0:no interrupts generated, 1:interrupt generated when xfer complete)
    ;   |  +-------------------------------------------- [14] Status            (0:channel inactive, 1:channel active)
    ;   +----------------------------------------------- [15] Start/Stop        (0:stops after burst is complete, 1:starts block xfer)

;**************************************************************************
;        DMA2 Ch2 Register Addresses
;**************************************************************************
DMA2_CH2_SRC_LSW        .set     0x0E40    ; DMA2 Channel 2 Source LSW Address
    ; DMA2_CH2_SRC_LSW   Address:  0x0E40 (IO space)      DMA2 Channel 2 Source LSW Address
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ; |15:14:13:12|11:10: 9: 8| 7: 6: 5: 4| 3: 2: 1: 0|  <<== Bit Position
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; |rw:rw:rw:rw|rw:rw:rw:rw|rw:rw:rw:rw|rw:rw:rw:rw|  <<== Read / Write Access
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; | 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0|  <<== Reset Values
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-- [0]  DMASrcByteAddr[0]     ( Psuedo Code for setting DMA SRC/DEST Addresses:
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  +----- [1]  DMASrcByteAddr[1]      if( io_space ) {
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  +-------- [2]  DMASrcByteAddr[2]          DMASrcByteAddr[17:0] = DSP_IOPORT_ADDR;
    ;   |  |  |  |  |  |  |  |  |  |  |  |  +----------- [3]  DMASrcByteAddr[3]      } elsif( daram ) {
    ;   |  |  |  |  |  |  |  |  |  |  |  |                                               DMASrcByteAddr[17:0] = 0x10000 + DSP_BYTE_ADDR;
    ;   |  |  |  |  |  |  |  |  |  |  |  +-------------- [4]  DMASrcByteAddr[4]      } elsif( saram ) {
    ;   |  |  |  |  |  |  |  |  |  |  +----------------- [5]  DMASrcByteAddr[5]          DMASrcByteAddr[17:0] = 0x20000 + DSP_BYTE_ADDR;
    ;   |  |  |  |  |  |  |  |  |  +-------------------- [6]  DMASrcByteAddr[6]      }
    ;   |  |  |  |  |  |  |  |  +----------------------- [7]  DMASrcByteAddr[7] 
    ;   |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  +-------------------------- [8]  DMASrcByteAddr[8]      DMA0 can see: 
    ;   |  |  |  |  |  |  +----------------------------- [9]  DMASrcByteAddr[9]      DMA1 can see: 
    ;   |  |  |  |  |  +-------------------------------- [10] DMASrcByteAddr[10]     DMA2 can see: 
    ;   |  |  |  |  +----------------------------------- [11] DMASrcByteAddr[11]     DMA3 can see: )
    ;   |  |  |  |
    ;   |  |  |  +-------------------------------------- [12] DMASrcByteAddr[12]
    ;   |  |  +----------------------------------------- [13] DMASrcByteAddr[13]
    ;   |  +-------------------------------------------- [14] DMASrcByteAddr[14]
    ;   +----------------------------------------------- [15] DMASrcByteAddr[15]
DMA2_CH2_SRC_MSW        .set     0x0E41    ; DMA2 Channel 2 Source MSW Address
    ; DMA2_CH2_SRC_MSW   Address:  0x0E41 (IO space)      DMA2 Channel 2 Source MSW Address
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ; |15:14:13:12|11:10: 9: 8| 7: 6: 5: 4| 3: 2: 1: 0|  <<== Bit Position
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; |r :r :r :r |r :r :r :r |r :r :r :r |r :r :rw:rw|  <<== Read / Write Access
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; | 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0|  <<== Reset Values
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-- [0]  DMASrcByteAddr[16]
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  +----- [1]  DMASrcByteAddr[17]
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  +-------- [2]  reserved
    ;   |  |  |  |  |  |  |  |  |  |  |  |  +----------- [3]  reserved
    ;   |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  +-------------- [4]  reserved
    ;   |  |  |  |  |  |  |  |  |  |  +----------------- [5]  reserved
    ;   |  |  |  |  |  |  |  |  |  +-------------------- [6]  reserved
    ;   |  |  |  |  |  |  |  |  +----------------------- [7]  reserved
    ;   |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  +-------------------------- [8]  reserved
    ;   |  |  |  |  |  |  +----------------------------- [9]  reserved
    ;   |  |  |  |  |  +-------------------------------- [10] reserved
    ;   |  |  |  |  +----------------------------------- [11] reserved
    ;   |  |  |  |
    ;   |  |  |  +-------------------------------------- [12] reserved
    ;   |  |  +----------------------------------------- [13] reserved
    ;   |  +-------------------------------------------- [14] reserved
    ;   +----------------------------------------------- [15] reserved
DMA2_CH2_DST_LSW        .set     0x0E42    ; DMA2 Channel 2 Destination LSW Address
    ; DMA2_CH2_DST_LSW   Address:  0x0E42 (IO space)      DMA2 Channel 2 Destination LSW Address
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ; |15:14:13:12|11:10: 9: 8| 7: 6: 5: 4| 3: 2: 1: 0|  <<== Bit Position
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; |rw:rw:rw:rw|rw:rw:rw:rw|rw:rw:rw:rw|rw:rw:rw:rw|  <<== Read / Write Access
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; | 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0|  <<== Reset Values
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-- [0]  DMADestByteAddr[0]    ( Psuedo Code for setting DMA SRC/DEST Addresses:
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  +----- [1]  DMADestByteAddr[1]     if( io_space ) {
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  +-------- [2]  DMADestByteAddr[2]         DMADestByteAddr[17:0] = DSP_IOPORT_ADDR;
    ;   |  |  |  |  |  |  |  |  |  |  |  |  +----------- [3]  DMADestByteAddr[3]     } elsif( daram ) {
    ;   |  |  |  |  |  |  |  |  |  |  |  |                                              DMADestByteAddr[17:0] = 0x10000 + DSP_BYTE_ADDR;
    ;   |  |  |  |  |  |  |  |  |  |  |  +-------------- [4]  DMADestByteAddr[4]     } elsif( saram ) {
    ;   |  |  |  |  |  |  |  |  |  |  +----------------- [5]  DMADestByteAddr[5]         DMADestByteAddr[17:0] = 0x20000 + DSP_BYTE_ADDR;
    ;   |  |  |  |  |  |  |  |  |  +-------------------- [6]  DMADestByteAddr[6]     }
    ;   |  |  |  |  |  |  |  |  +----------------------- [7]  DMADestByteAddr[7] 
    ;   |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  +-------------------------- [8]  DMADestByteAddr[8]      DMA0 can see: 
    ;   |  |  |  |  |  |  +----------------------------- [9]  DMADestByteAddr[9]      DMA1 can see: 
    ;   |  |  |  |  |  +-------------------------------- [10] DMADestByteAddr[10]     DMA2 can see: 
    ;   |  |  |  |  +----------------------------------- [11] DMADestByteAddr[11]     DMA3 can see: )
    ;   |  |  |  |
    ;   |  |  |  +-------------------------------------- [12] DMADestByteAddr[12]
    ;   |  |  +----------------------------------------- [13] DMADestByteAddr[13]
    ;   |  +-------------------------------------------- [14] DMADestByteAddr[14]
    ;   +----------------------------------------------- [15] DMADestByteAddr[15]
DMA2_CH2_DST_MSW        .set     0x0E43    ; DMA2 Channel 2 Destination MSW Address
    ; DMA2_CH2_DST_MSW   Address:  0x0E43 (IO space)      DMA2 Channel 2 Destination MSW Address
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ; |15:14:13:12|11:10: 9: 8| 7: 6: 5: 4| 3: 2: 1: 0|  <<== Bit Position
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; |r :r :r :r |r :r :r :r |r :r :r :r |r :r :rw:rw|  <<== Read / Write Access
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; | 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0|  <<== Reset Values
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-- [0]  DMADestByteAddr[16]
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  +----- [1]  DMADestByteAddr[17]
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  +-------- [2]  reserved
    ;   |  |  |  |  |  |  |  |  |  |  |  |  +----------- [3]  reserved
    ;   |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  +-------------- [4]  reserved
    ;   |  |  |  |  |  |  |  |  |  |  +----------------- [5]  reserved
    ;   |  |  |  |  |  |  |  |  |  +-------------------- [6]  reserved
    ;   |  |  |  |  |  |  |  |  +----------------------- [7]  reserved
    ;   |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  +-------------------------- [8]  reserved
    ;   |  |  |  |  |  |  +----------------------------- [9]  reserved
    ;   |  |  |  |  |  +-------------------------------- [10] reserved
    ;   |  |  |  |  +----------------------------------- [11] reserved
    ;   |  |  |  |
    ;   |  |  |  +-------------------------------------- [12] reserved
    ;   |  |  +----------------------------------------- [13] reserved
    ;   |  +-------------------------------------------- [14] reserved
    ;   +----------------------------------------------- [15] reserved
DMA2_CH2_TC_LEN         .set     0x0E44    ; DMA2 Destination Address
    ; DMA2_CH2_TC_LEN   Address:  0x0E44 (IO space)      DMA2 Channel 2 Length / Transfer Control LSW Register
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ; |15:14:13:12|11:10: 9: 8| 7: 6: 5: 4| 3: 2: 1: 0|  <<== Bit Position
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; |rw:rw:rw:rw|rw:rw:rw:rw|rw:rw:rw:rw|rw:rw:r :r |  <<== Read / Write Access
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; | 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0|  <<== Reset Values
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |   ( XferLength[15:0] = number of bytes to be transfered)
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-- [0]  XferLength[0]
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  +----- [1]  XferLength[1]
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  +-------- [2]  XferLength[2]
    ;   |  |  |  |  |  |  |  |  |  |  |  |  +----------- [3]  XferLength[3]
    ;   |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  +-------------- [4]  XferLength[4]
    ;   |  |  |  |  |  |  |  |  |  |  +----------------- [5]  XferLength[5]
    ;   |  |  |  |  |  |  |  |  |  +-------------------- [6]  XferLength[6]
    ;   |  |  |  |  |  |  |  |  +----------------------- [7]  XferLength[7]
    ;   |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  +-------------------------- [8]  XferLength[8]
    ;   |  |  |  |  |  |  +----------------------------- [9]  XferLength[9]
    ;   |  |  |  |  |  +-------------------------------- [10] XferLength[10]
    ;   |  |  |  |  +----------------------------------- [11] XferLength[11]
    ;   |  |  |  |
    ;   |  |  |  +-------------------------------------- [12] XferLength[12]
    ;   |  |  +----------------------------------------- [13] XferLength[13]
    ;   |  +-------------------------------------------- [14] XferLength[14]
    ;   +----------------------------------------------- [15] XferLength[15]
DMA2_CH2_TC_MSW         .set     0x0E45    ; DMA2 Channel 2 Transfer Control MSW Register
    ; DMA2_CH2_TC_MSW   Address:  0x0E45 (IO space)      DMA2 Channel 2 Transfer Control MSW Register
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ; |15:14:13:12|11:10: 9: 8| 7: 6: 5: 4| 3: 2: 1: 0|  <<== Bit Position
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; |rw:rw:rw:rw|r :r :rw:rw|rw:rw:rw:rw|rw:r :rw:rw|  <<== Read / Write Access
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; | 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0|  <<== Reset Values
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-- [0]  SourceSize[0]      Source Data Size:
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  +----- [1]  SourceSize[1]      (00: 32-bit, 01: 16-bit, 10: 8-bit,  11: Reserved)
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  +-------- [2]  Sync               (1: DMA transfers one burst-mode length of 32-bit words per one peripheral event, 0: DMA transfers not controlled by peripheral events)
    ;   |  |  |  |  |  |  |  |  |  |  |  |  +----------- [3]  BurstMode[0]       (000:1 32bit word burst, 001:2 32bit word burst,
    ;   |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  +-------------- [4]  BurstMode[1]        010:4 32bit word burst, 011:8 32bit word burst,
    ;   |  |  |  |  |  |  |  |  |  |  +----------------- [5]  BurstMode[2]        100:16 32bit word burst, others:reserved)
    ;   |  |  |  |  |  |  |  |  |  +-------------------- [6]  SrcAddrMode[0]     (00:autoincr, 10:src addr is fixed, others:reserved)
    ;   |  |  |  |  |  |  |  |  +----------------------- [7]  SrcAddrMode[1]
    ;   |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  +-------------------------- [8]  DestAddrMode[0]    (00:autoincr, 10:dest addr is fixed, others:reserved)
    ;   |  |  |  |  |  |  +----------------------------- [9]  DestAddrMode[1]
    ;   |  |  |  |  |  +-------------------------------- [10] DestSize[0]        Destination data size:
    ;   |  |  |  |  +----------------------------------- [11] DestSize[1]        (00: 32-bit, 01: 16-bit, 10: 8-bit,  11: Reserved)
    ;   |  |  |  |
    ;   |  |  |  +-------------------------------------- [12] AutoReload        (0:disabled, to restart DMA set start bit = 1; 1:enabled, to stop DMA from reloading set start bit = 0 )
    ;   |  |  +----------------------------------------- [13] InterruptEn       (0:no interrupts generated, 1:interrupt generated when xfer complete)
    ;   |  +-------------------------------------------- [14] Status            (0:channel inactive, 1:channel active)
    ;   +----------------------------------------------- [15] Start/Stop        (0:stops after burst is complete, 1:starts block xfer)

;**************************************************************************
;        DMA2 Ch3 Register Addresses
;**************************************************************************
DMA2_CH3_SRC_LSW        .set     0x0E60    ; DMA2 Channel 3 Source LSW Address
    ; DMA2_CH3_SRC_LSW   Address:  0x0E60 (IO space)      DMA2 Channel 3 Source LSW Address
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ; |15:14:13:12|11:10: 9: 8| 7: 6: 5: 4| 3: 2: 1: 0|  <<== Bit Position
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; |rw:rw:rw:rw|rw:rw:rw:rw|rw:rw:rw:rw|rw:rw:rw:rw|  <<== Read / Write Access
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; | 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0|  <<== Reset Values
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-- [0]  DMASrcByteAddr[0]     ( Psuedo Code for setting DMA SRC/DEST Addresses:
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  +----- [1]  DMASrcByteAddr[1]      if( io_space ) {
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  +-------- [2]  DMASrcByteAddr[2]          DMASrcByteAddr[17:0] = DSP_IOPORT_ADDR;
    ;   |  |  |  |  |  |  |  |  |  |  |  |  +----------- [3]  DMASrcByteAddr[3]      } elsif( daram ) {
    ;   |  |  |  |  |  |  |  |  |  |  |  |                                               DMASrcByteAddr[17:0] = 0x10000 + DSP_BYTE_ADDR;
    ;   |  |  |  |  |  |  |  |  |  |  |  +-------------- [4]  DMASrcByteAddr[4]      } elsif( saram ) {
    ;   |  |  |  |  |  |  |  |  |  |  +----------------- [5]  DMASrcByteAddr[5]          DMASrcByteAddr[17:0] = 0x20000 + DSP_BYTE_ADDR;
    ;   |  |  |  |  |  |  |  |  |  +-------------------- [6]  DMASrcByteAddr[6]      }
    ;   |  |  |  |  |  |  |  |  +----------------------- [7]  DMASrcByteAddr[7] 
    ;   |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  +-------------------------- [8]  DMASrcByteAddr[8]      DMA0 can see: 
    ;   |  |  |  |  |  |  +----------------------------- [9]  DMASrcByteAddr[9]      DMA1 can see: 
    ;   |  |  |  |  |  +-------------------------------- [10] DMASrcByteAddr[10]     DMA2 can see: 
    ;   |  |  |  |  +----------------------------------- [11] DMASrcByteAddr[11]     DMA3 can see: )
    ;   |  |  |  |
    ;   |  |  |  +-------------------------------------- [12] DMASrcByteAddr[12]
    ;   |  |  +----------------------------------------- [13] DMASrcByteAddr[13]
    ;   |  +-------------------------------------------- [14] DMASrcByteAddr[14]
    ;   +----------------------------------------------- [15] DMASrcByteAddr[15]
DMA2_CH3_SRC_MSW        .set     0x0E61    ; DMA2 Channel 3 Source MSW Address
    ; DMA2_CH3_SRC_MSW   Address:  0x0E61 (IO space)      DMA2 Channel 3 Source MSW Address
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ; |15:14:13:12|11:10: 9: 8| 7: 6: 5: 4| 3: 2: 1: 0|  <<== Bit Position
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; |r :r :r :r |r :r :r :r |r :r :r :r |r :r :rw:rw|  <<== Read / Write Access
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; | 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0|  <<== Reset Values
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-- [0]  DMASrcByteAddr[16]
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  +----- [1]  DMASrcByteAddr[17]
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  +-------- [2]  reserved
    ;   |  |  |  |  |  |  |  |  |  |  |  |  +----------- [3]  reserved
    ;   |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  +-------------- [4]  reserved
    ;   |  |  |  |  |  |  |  |  |  |  +----------------- [5]  reserved
    ;   |  |  |  |  |  |  |  |  |  +-------------------- [6]  reserved
    ;   |  |  |  |  |  |  |  |  +----------------------- [7]  reserved
    ;   |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  +-------------------------- [8]  reserved
    ;   |  |  |  |  |  |  +----------------------------- [9]  reserved
    ;   |  |  |  |  |  +-------------------------------- [10] reserved
    ;   |  |  |  |  +----------------------------------- [11] reserved
    ;   |  |  |  |
    ;   |  |  |  +-------------------------------------- [12] reserved
    ;   |  |  +----------------------------------------- [13] reserved
    ;   |  +-------------------------------------------- [14] reserved
    ;   +----------------------------------------------- [15] reserved
DMA2_CH3_DST_LSW        .set     0x0E62    ; DMA2 Channel 3 Destination LSW Address
    ; DMA2_CH3_DST_LSW   Address:  0x0E62 (IO space)      DMA2 Channel 3 Destination LSW Address
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ; |15:14:13:12|11:10: 9: 8| 7: 6: 5: 4| 3: 2: 1: 0|  <<== Bit Position
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; |rw:rw:rw:rw|rw:rw:rw:rw|rw:rw:rw:rw|rw:rw:rw:rw|  <<== Read / Write Access
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; | 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0|  <<== Reset Values
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-- [0]  DMADestByteAddr[0]    ( Psuedo Code for setting DMA SRC/DEST Addresses:
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  +----- [1]  DMADestByteAddr[1]     if( io_space ) {
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  +-------- [2]  DMADestByteAddr[2]         DMADestByteAddr[17:0] = DSP_IOPORT_ADDR;
    ;   |  |  |  |  |  |  |  |  |  |  |  |  +----------- [3]  DMADestByteAddr[3]     } elsif( daram ) {
    ;   |  |  |  |  |  |  |  |  |  |  |  |                                              DMADestByteAddr[17:0] = 0x10000 + DSP_BYTE_ADDR;
    ;   |  |  |  |  |  |  |  |  |  |  |  +-------------- [4]  DMADestByteAddr[4]     } elsif( saram ) {
    ;   |  |  |  |  |  |  |  |  |  |  +----------------- [5]  DMADestByteAddr[5]         DMADestByteAddr[17:0] = 0x20000 + DSP_BYTE_ADDR;
    ;   |  |  |  |  |  |  |  |  |  +-------------------- [6]  DMADestByteAddr[6]     }
    ;   |  |  |  |  |  |  |  |  +----------------------- [7]  DMADestByteAddr[7] 
    ;   |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  +-------------------------- [8]  DMADestByteAddr[8]      DMA0 can see: 
    ;   |  |  |  |  |  |  +----------------------------- [9]  DMADestByteAddr[9]      DMA1 can see: 
    ;   |  |  |  |  |  +-------------------------------- [10] DMADestByteAddr[10]     DMA2 can see: 
    ;   |  |  |  |  +----------------------------------- [11] DMADestByteAddr[11]     DMA3 can see: )
    ;   |  |  |  |
    ;   |  |  |  +-------------------------------------- [12] DMADestByteAddr[12]
    ;   |  |  +----------------------------------------- [13] DMADestByteAddr[13]
    ;   |  +-------------------------------------------- [14] DMADestByteAddr[14]
    ;   +----------------------------------------------- [15] DMADestByteAddr[15]
DMA2_CH3_DST_MSW        .set     0x0E63    ; DMA2 Channel 3 Destination MSW Address
    ; DMA2_CH3_DST_MSW   Address:  0x0E63 (IO space)      DMA2 Channel 3 Destination MSW Address
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ; |15:14:13:12|11:10: 9: 8| 7: 6: 5: 4| 3: 2: 1: 0|  <<== Bit Position
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; |r :r :r :r |r :r :r :r |r :r :r :r |r :r :rw:rw|  <<== Read / Write Access
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; | 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0|  <<== Reset Values
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-- [0]  DMADestByteAddr[16]
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  +----- [1]  DMADestByteAddr[17]
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  +-------- [2]  reserved
    ;   |  |  |  |  |  |  |  |  |  |  |  |  +----------- [3]  reserved
    ;   |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  +-------------- [4]  reserved
    ;   |  |  |  |  |  |  |  |  |  |  +----------------- [5]  reserved
    ;   |  |  |  |  |  |  |  |  |  +-------------------- [6]  reserved
    ;   |  |  |  |  |  |  |  |  +----------------------- [7]  reserved
    ;   |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  +-------------------------- [8]  reserved
    ;   |  |  |  |  |  |  +----------------------------- [9]  reserved
    ;   |  |  |  |  |  +-------------------------------- [10] reserved
    ;   |  |  |  |  +----------------------------------- [11] reserved
    ;   |  |  |  |
    ;   |  |  |  +-------------------------------------- [12] reserved
    ;   |  |  +----------------------------------------- [13] reserved
    ;   |  +-------------------------------------------- [14] reserved
    ;   +----------------------------------------------- [15] reserved
DMA2_CH3_TC_LEN         .set     0x0E64    ; DMA2 Destination Address
    ; DMA2_CH3_TC_LEN   Address:  0x0E64 (IO space)      DMA2 Channel 3 Length / Transfer Control LSW Register
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ; |15:14:13:12|11:10: 9: 8| 7: 6: 5: 4| 3: 2: 1: 0|  <<== Bit Position
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; |rw:rw:rw:rw|rw:rw:rw:rw|rw:rw:rw:rw|rw:rw:r :r |  <<== Read / Write Access
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; | 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0|  <<== Reset Values
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |   ( XferLength[15:0] = number of bytes to be transfered)
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-- [0]  XferLength[0]
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  +----- [1]  XferLength[1]
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  +-------- [2]  XferLength[2]
    ;   |  |  |  |  |  |  |  |  |  |  |  |  +----------- [3]  XferLength[3]
    ;   |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  +-------------- [4]  XferLength[4]
    ;   |  |  |  |  |  |  |  |  |  |  +----------------- [5]  XferLength[5]
    ;   |  |  |  |  |  |  |  |  |  +-------------------- [6]  XferLength[6]
    ;   |  |  |  |  |  |  |  |  +----------------------- [7]  XferLength[7]
    ;   |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  +-------------------------- [8]  XferLength[8]
    ;   |  |  |  |  |  |  +----------------------------- [9]  XferLength[9]
    ;   |  |  |  |  |  +-------------------------------- [10] XferLength[10]
    ;   |  |  |  |  +----------------------------------- [11] XferLength[11]
    ;   |  |  |  |
    ;   |  |  |  +-------------------------------------- [12] XferLength[12]
    ;   |  |  +----------------------------------------- [13] XferLength[13]
    ;   |  +-------------------------------------------- [14] XferLength[14]
    ;   +----------------------------------------------- [15] XferLength[15]
DMA2_CH3_TC_MSW         .set     0x0E65    ; DMA2 Channel 0 Transfer Control MSW Register
    ; DMA2_CH3_TC_MSW   Address:  0x0E65 (IO space)      DMA2 Channel 3 Transfer Control MSW Register
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ; |15:14:13:12|11:10: 9: 8| 7: 6: 5: 4| 3: 2: 1: 0|  <<== Bit Position
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; |rw:rw:rw:rw|r :r :rw:rw|rw:rw:rw:rw|rw:r :rw:rw|  <<== Read / Write Access
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; | 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0|  <<== Reset Values
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-- [0]  SourceSize[0]      Source Data Size:
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  +----- [1]  SourceSize[1]      (00: 32-bit, 01: 16-bit, 10: 8-bit,  11: Reserved)
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  +-------- [2]  Sync               (1: DMA transfers one burst-mode length of 32-bit words per one peripheral event, 0: DMA transfers not controlled by peripheral events)
    ;   |  |  |  |  |  |  |  |  |  |  |  |  +----------- [3]  BurstMode[0]       (000:1 32bit word burst, 001:2 32bit word burst,
    ;   |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  +-------------- [4]  BurstMode[1]        010:4 32bit word burst, 011:8 32bit word burst,
    ;   |  |  |  |  |  |  |  |  |  |  +----------------- [5]  BurstMode[2]        100:16 32bit word burst, others:reserved)
    ;   |  |  |  |  |  |  |  |  |  +-------------------- [6]  SrcAddrMode[0]     (00:autoincr, 10:src addr is fixed, others:reserved)
    ;   |  |  |  |  |  |  |  |  +----------------------- [7]  SrcAddrMode[1]
    ;   |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  +-------------------------- [8]  DestAddrMode[0]    (00:autoincr, 10:dest addr is fixed, others:reserved)
    ;   |  |  |  |  |  |  +----------------------------- [9]  DestAddrMode[1]
    ;   |  |  |  |  |  +-------------------------------- [10] DestSize[0]        Destination data size:
    ;   |  |  |  |  +----------------------------------- [11] DestSize[1]        (00: 32-bit, 01: 16-bit, 10: 8-bit,  11: Reserved)
    ;   |  |  |  |
    ;   |  |  |  +-------------------------------------- [12] AutoReload        (0:disabled, to restart DMA set start bit = 1; 1:enabled, to stop DMA from reloading set start bit = 0 )
    ;   |  |  +----------------------------------------- [13] InterruptEn       (0:no interrupts generated, 1:interrupt generated when xfer complete)
    ;   |  +-------------------------------------------- [14] Status            (0:channel inactive, 1:channel active)
    ;   +----------------------------------------------- [15] Start/Stop        (0:stops after burst is complete, 1:starts block xfer)
;****************************************************************************************

;****************************************************************************************
;         DMA 3
;**************************************************************************
;        DMA3 Ch0 Register Addresses
;**************************************************************************
DMA3_CH0_SRC_LSW        .set     0x0F00    ; DMA3 Channel 0 Source LSW Address
    ; DMA3_CH0_SRC_LSW   Address:  0x0F00 (IO space)      DMA3 Channel 0 Source LSW Address
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ; |15:14:13:12|11:10: 9: 8| 7: 6: 5: 4| 3: 2: 1: 0|  <<== Bit Position
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; |rw:rw:rw:rw|rw:rw:rw:rw|rw:rw:rw:rw|rw:rw:rw:rw|  <<== Read / Write Access
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; | 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0|  <<== Reset Values
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-- [0]  DMASrcByteAddr[0]     ( Psuedo Code for setting DMA SRC/DEST Addresses:
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  +----- [1]  DMASrcByteAddr[1]      if( io_space ) {
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  +-------- [2]  DMASrcByteAddr[2]          DMASrcByteAddr[17:0] = DSP_IOPORT_ADDR;
    ;   |  |  |  |  |  |  |  |  |  |  |  |  +----------- [3]  DMASrcByteAddr[3]      } elsif( daram ) {
    ;   |  |  |  |  |  |  |  |  |  |  |  |                                               DMASrcByteAddr[17:0] = 0x10000 + DSP_BYTE_ADDR;
    ;   |  |  |  |  |  |  |  |  |  |  |  +-------------- [4]  DMASrcByteAddr[4]      } elsif( saram ) {
    ;   |  |  |  |  |  |  |  |  |  |  +----------------- [5]  DMASrcByteAddr[5]          DMASrcByteAddr[17:0] = 0x20000 + DSP_BYTE_ADDR;
    ;   |  |  |  |  |  |  |  |  |  +-------------------- [6]  DMASrcByteAddr[6]      }
    ;   |  |  |  |  |  |  |  |  +----------------------- [7]  DMASrcByteAddr[7] 
    ;   |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  +-------------------------- [8]  DMASrcByteAddr[8]      DMA0 can see: 
    ;   |  |  |  |  |  |  +----------------------------- [9]  DMASrcByteAddr[9]      DMA1 can see: 
    ;   |  |  |  |  |  +-------------------------------- [10] DMASrcByteAddr[10]     DMA2 can see: 
    ;   |  |  |  |  +----------------------------------- [11] DMASrcByteAddr[11]     DMA3 can see: )
    ;   |  |  |  |
    ;   |  |  |  +-------------------------------------- [12] DMASrcByteAddr[12]
    ;   |  |  +----------------------------------------- [13] DMASrcByteAddr[13]
    ;   |  +-------------------------------------------- [14] DMASrcByteAddr[14]
    ;   +----------------------------------------------- [15] DMASrcByteAddr[15]
DMA3_CH0_SRC_MSW        .set     0x0F01    ; DMA3 Channel 0 Source MSW Address
    ; DMA3_CH0_SRC_MSW   Address:  0x0F01 (IO space)      DMA3 Channel 0 Source MSW Address
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ; |15:14:13:12|11:10: 9: 8| 7: 6: 5: 4| 3: 2: 1: 0|  <<== Bit Position
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; |r :r :r :r |r :r :r :r |r :r :r :r |r :r :rw:rw|  <<== Read / Write Access
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; | 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0|  <<== Reset Values
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-- [0]  DMASrcByteAddr[16]
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  +----- [1]  DMASrcByteAddr[17]
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  +-------- [2]  reserved
    ;   |  |  |  |  |  |  |  |  |  |  |  |  +----------- [3]  reserved
    ;   |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  +-------------- [4]  reserved
    ;   |  |  |  |  |  |  |  |  |  |  +----------------- [5]  reserved
    ;   |  |  |  |  |  |  |  |  |  +-------------------- [6]  reserved
    ;   |  |  |  |  |  |  |  |  +----------------------- [7]  reserved
    ;   |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  +-------------------------- [8]  reserved
    ;   |  |  |  |  |  |  +----------------------------- [9]  reserved
    ;   |  |  |  |  |  +-------------------------------- [10] reserved
    ;   |  |  |  |  +----------------------------------- [11] reserved
    ;   |  |  |  |
    ;   |  |  |  +-------------------------------------- [12] reserved
    ;   |  |  +----------------------------------------- [13] reserved
    ;   |  +-------------------------------------------- [14] reserved
    ;   +----------------------------------------------- [15] reserved
DMA3_CH0_DST_LSW        .set     0x0F02    ; DMA3 Channel 0 Destination LSW Address
    ; DMA3_CH0_DST_LSW   Address:  0x0F02 (IO space)      DMA3 Channel 0 Destination LSW Address
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ; |15:14:13:12|11:10: 9: 8| 7: 6: 5: 4| 3: 2: 1: 0|  <<== Bit Position
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; |rw:rw:rw:rw|rw:rw:rw:rw|rw:rw:rw:rw|rw:rw:rw:rw|  <<== Read / Write Access
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; | 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0|  <<== Reset Values
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-- [0]  DMADestByteAddr[0]    ( Psuedo Code for setting DMA SRC/DEST Addresses:
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  +----- [1]  DMADestByteAddr[1]     if( io_space ) {
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  +-------- [2]  DMADestByteAddr[2]         DMADestByteAddr[17:0] = DSP_IOPORT_ADDR;
    ;   |  |  |  |  |  |  |  |  |  |  |  |  +----------- [3]  DMADestByteAddr[3]     } elsif( daram ) {
    ;   |  |  |  |  |  |  |  |  |  |  |  |                                              DMADestByteAddr[17:0] = 0x10000 + DSP_BYTE_ADDR;
    ;   |  |  |  |  |  |  |  |  |  |  |  +-------------- [4]  DMADestByteAddr[4]     } elsif( saram ) {
    ;   |  |  |  |  |  |  |  |  |  |  +----------------- [5]  DMADestByteAddr[5]         DMADestByteAddr[17:0] = 0x20000 + DSP_BYTE_ADDR;
    ;   |  |  |  |  |  |  |  |  |  +-------------------- [6]  DMADestByteAddr[6]     }
    ;   |  |  |  |  |  |  |  |  +----------------------- [7]  DMADestByteAddr[7] 
    ;   |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  +-------------------------- [8]  DMADestByteAddr[8]      DMA0 can see: 
    ;   |  |  |  |  |  |  +----------------------------- [9]  DMADestByteAddr[9]      DMA1 can see: 
    ;   |  |  |  |  |  +-------------------------------- [10] DMADestByteAddr[10]     DMA2 can see: 
    ;   |  |  |  |  +----------------------------------- [11] DMADestByteAddr[11]     DMA3 can see: )
    ;   |  |  |  |
    ;   |  |  |  +-------------------------------------- [12] DMADestByteAddr[12]
    ;   |  |  +----------------------------------------- [13] DMADestByteAddr[13]
    ;   |  +-------------------------------------------- [14] DMADestByteAddr[14]
    ;   +----------------------------------------------- [15] DMADestByteAddr[15]
DMA3_CH0_DST_MSW        .set     0x0F03    ; DMA3 Channel 0 Destination MSW Address
    ; DMA3_CH0_DST_MSW   Address:  0x0F03 (IO space)      DMA3 Channel 0 Destination MSW Address
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ; |15:14:13:12|11:10: 9: 8| 7: 6: 5: 4| 3: 2: 1: 0|  <<== Bit Position
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; |r :r :r :r |r :r :r :r |r :r :r :r |r :r :rw:rw|  <<== Read / Write Access
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; | 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0|  <<== Reset Values
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-- [0]  DMADestByteAddr[16]
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  +----- [1]  DMADestByteAddr[17]
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  +-------- [2]  reserved
    ;   |  |  |  |  |  |  |  |  |  |  |  |  +----------- [3]  reserved
    ;   |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  +-------------- [4]  reserved
    ;   |  |  |  |  |  |  |  |  |  |  +----------------- [5]  reserved
    ;   |  |  |  |  |  |  |  |  |  +-------------------- [6]  reserved
    ;   |  |  |  |  |  |  |  |  +----------------------- [7]  reserved
    ;   |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  +-------------------------- [8]  reserved
    ;   |  |  |  |  |  |  +----------------------------- [9]  reserved
    ;   |  |  |  |  |  +-------------------------------- [10] reserved
    ;   |  |  |  |  +----------------------------------- [11] reserved
    ;   |  |  |  |
    ;   |  |  |  +-------------------------------------- [12] reserved
    ;   |  |  +----------------------------------------- [13] reserved
    ;   |  +-------------------------------------------- [14] reserved
    ;   +----------------------------------------------- [15] reserved
DMA3_CH0_TC_LEN         .set     0x0F04    ; DMA3 Channel 0 Length / Transfer Control LSW Register
    ; DMA3_CH0_TC_LEN   Address:  0x0F04 (IO space)      DMA3 Channel 0 Length / Transfer Control LSW Register
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ; |15:14:13:12|11:10: 9: 8| 7: 6: 5: 4| 3: 2: 1: 0|  <<== Bit Position
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; |rw:rw:rw:rw|rw:rw:rw:rw|rw:rw:rw:rw|rw:rw:r :r |  <<== Read / Write Access
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; | 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0|  <<== Reset Values
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |   ( XferLength[15:0] = number of bytes to be transfered)
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-- [0]  XferLength[0]
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  +----- [1]  XferLength[1]
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  +-------- [2]  XferLength[2]
    ;   |  |  |  |  |  |  |  |  |  |  |  |  +----------- [3]  XferLength[3]
    ;   |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  +-------------- [4]  XferLength[4]
    ;   |  |  |  |  |  |  |  |  |  |  +----------------- [5]  XferLength[5]
    ;   |  |  |  |  |  |  |  |  |  +-------------------- [6]  XferLength[6]
    ;   |  |  |  |  |  |  |  |  +----------------------- [7]  XferLength[7]
    ;   |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  +-------------------------- [8]  XferLength[8]
    ;   |  |  |  |  |  |  +----------------------------- [9]  XferLength[9]
    ;   |  |  |  |  |  +-------------------------------- [10] XferLength[10]
    ;   |  |  |  |  +----------------------------------- [11] XferLength[11]
    ;   |  |  |  |
    ;   |  |  |  +-------------------------------------- [12] XferLength[12]
    ;   |  |  +----------------------------------------- [13] XferLength[13]
    ;   |  +-------------------------------------------- [14] XferLength[14]
    ;   +----------------------------------------------- [15] XferLength[15]
DMA3_CH0_TC_MSW         .set     0x0F05    ; DMA3 Channel 0 Transfer Control MSW Register
    ; DMA3_CH0_TC_MSW   Address:  0x0F05 (IO space)      DMA3 Channel 0 Transfer Control MSW Register
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ; |15:14:13:12|11:10: 9: 8| 7: 6: 5: 4| 3: 2: 1: 0|  <<== Bit Position
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; |rw:rw:rw:rw|r :r :rw:rw|rw:rw:rw:rw|rw:r :rw:rw|  <<== Read / Write Access
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; | 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0|  <<== Reset Values
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-- [0]  SourceSize[0]      Source Data Size:
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  +----- [1]  SourceSize[1]      (00: 32-bit, 01: 16-bit, 10: 8-bit,  11: Reserved)
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  +-------- [2]  Sync               (1: DMA transfers one burst-mode length of 32-bit words per one peripheral event, 0: DMA transfers not controlled by peripheral events)
    ;   |  |  |  |  |  |  |  |  |  |  |  |  +----------- [3]  BurstMode[0]       (000:1 32bit word burst, 001:2 32bit word burst,
    ;   |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  +-------------- [4]  BurstMode[1]        010:4 32bit word burst, 011:8 32bit word burst,
    ;   |  |  |  |  |  |  |  |  |  |  +----------------- [5]  BurstMode[2]        100:16 32bit word burst, others:reserved)
    ;   |  |  |  |  |  |  |  |  |  +-------------------- [6]  SrcAddrMode[0]     (00:autoincr, 10:src addr is fixed, others:reserved)
    ;   |  |  |  |  |  |  |  |  +----------------------- [7]  SrcAddrMode[1]
    ;   |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  +-------------------------- [8]  DestAddrMode[0]    (00:autoincr, 10:dest addr is fixed, others:reserved)
    ;   |  |  |  |  |  |  +----------------------------- [9]  DestAddrMode[1]
    ;   |  |  |  |  |  +-------------------------------- [10] DestSize[0]        Destination data size:
    ;   |  |  |  |  +----------------------------------- [11] DestSize[1]        (00: 32-bit, 01: 16-bit, 10: 8-bit,  11: Reserved)
    ;   |  |  |  |
    ;   |  |  |  +-------------------------------------- [12] AutoReload        (0:disabled, to restart DMA set start bit = 1; 1:enabled, to stop DMA from reloading set start bit = 0 )
    ;   |  |  +----------------------------------------- [13] InterruptEn       (0:no interrupts generated, 1:interrupt generated when xfer complete)
    ;   |  +-------------------------------------------- [14] Status            (0:channel inactive, 1:channel active)
    ;   +----------------------------------------------- [15] Start/Stop        (0:stops after burst is complete, 1:starts block xfer)


;**************************************************************************
;        DMA3 Ch1 Register Addresses
;**************************************************************************
DMA3_CH1_SRC_LSW        .set     0x0F20    ; DMA3 Channel 1 Source LSW Address
    ; DMA3_CH1_SRC_LSW   Address:  0x0F20 (IO space)      DMA3 Channel 1 Source LSW Address
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ; |15:14:13:12|11:10: 9: 8| 7: 6: 5: 4| 3: 2: 1: 0|  <<== Bit Position
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; |rw:rw:rw:rw|rw:rw:rw:rw|rw:rw:rw:rw|rw:rw:rw:rw|  <<== Read / Write Access
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; | 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0|  <<== Reset Values
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-- [0]  DMASrcByteAddr[0]     ( Psuedo Code for setting DMA SRC/DEST Addresses:
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  +----- [1]  DMASrcByteAddr[1]      if( io_space ) {
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  +-------- [2]  DMASrcByteAddr[2]          DMASrcByteAddr[17:0] = DSP_IOPORT_ADDR;
    ;   |  |  |  |  |  |  |  |  |  |  |  |  +----------- [3]  DMASrcByteAddr[3]      } elsif( daram ) {
    ;   |  |  |  |  |  |  |  |  |  |  |  |                                               DMASrcByteAddr[17:0] = 0x10000 + DSP_BYTE_ADDR;
    ;   |  |  |  |  |  |  |  |  |  |  |  +-------------- [4]  DMASrcByteAddr[4]      } elsif( saram ) {
    ;   |  |  |  |  |  |  |  |  |  |  +----------------- [5]  DMASrcByteAddr[5]          DMASrcByteAddr[17:0] = 0x20000 + DSP_BYTE_ADDR;
    ;   |  |  |  |  |  |  |  |  |  +-------------------- [6]  DMASrcByteAddr[6]      }
    ;   |  |  |  |  |  |  |  |  +----------------------- [7]  DMASrcByteAddr[7]
    ;   |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  +-------------------------- [8]  DMASrcByteAddr[8]      DMA0 can see: 
    ;   |  |  |  |  |  |  +----------------------------- [9]  DMASrcByteAddr[9]      DMA1 can see: 
    ;   |  |  |  |  |  +-------------------------------- [10] DMASrcByteAddr[10]     DMA2 can see: 
    ;   |  |  |  |  +----------------------------------- [11] DMASrcByteAddr[11]     DMA3 can see: )
    ;   |  |  |  |
    ;   |  |  |  +-------------------------------------- [12] DMASrcByteAddr[12]
    ;   |  |  +----------------------------------------- [13] DMASrcByteAddr[13]
    ;   |  +-------------------------------------------- [14] DMASrcByteAddr[14]
    ;   +----------------------------------------------- [15] DMASrcByteAddr[15]
DMA3_CH1_SRC_MSW        .set     0x0F21    ; DMA3 Channel 1 Source MSW Address
    ; DMA3_CH1_SRC_MSW   Address:  0x0F21 (IO space)      DMA3 Channel 1 Source MSW Address
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ; |15:14:13:12|11:10: 9: 8| 7: 6: 5: 4| 3: 2: 1: 0|  <<== Bit Position
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; |r :r :r :r |r :r :r :r |r :r :r :r |r :r :rw:rw|  <<== Read / Write Access
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; | 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0|  <<== Reset Values
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-- [0]  DMASrcByteAddr[16]
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  +----- [1]  DMASrcByteAddr[17]
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  +-------- [2]  reserved
    ;   |  |  |  |  |  |  |  |  |  |  |  |  +----------- [3]  reserved
    ;   |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  +-------------- [4]  reserved
    ;   |  |  |  |  |  |  |  |  |  |  +----------------- [5]  reserved
    ;   |  |  |  |  |  |  |  |  |  +-------------------- [6]  reserved
    ;   |  |  |  |  |  |  |  |  +----------------------- [7]  reserved
    ;   |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  +-------------------------- [8]  reserved
    ;   |  |  |  |  |  |  +----------------------------- [9]  reserved
    ;   |  |  |  |  |  +-------------------------------- [10] reserved
    ;   |  |  |  |  +----------------------------------- [11] reserved
    ;   |  |  |  |
    ;   |  |  |  +-------------------------------------- [12] reserved
    ;   |  |  +----------------------------------------- [13] reserved
    ;   |  +-------------------------------------------- [14] reserved
    ;   +----------------------------------------------- [15] reserved
DMA3_CH1_DST_LSW        .set     0x0F22    ; DMA3 Channel 1 Destination LSW Address
    ; DMA3_CH1_DST_LSW   Address:  0x0F02 (IO space)      DMA3 Channel 1 Destination LSW Address
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ; |15:14:13:12|11:10: 9: 8| 7: 6: 5: 4| 3: 2: 1: 0|  <<== Bit Position
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; |rw:rw:rw:rw|rw:rw:rw:rw|rw:rw:rw:rw|rw:rw:rw:rw|  <<== Read / Write Access
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; | 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0|  <<== Reset Values
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-- [0]  DMADestByteAddr[0]    ( Psuedo Code for setting DMA SRC/DEST Addresses:
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  +----- [1]  DMADestByteAddr[1]     if( io_space ) {
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  +-------- [2]  DMADestByteAddr[2]         DMADestByteAddr[17:0] = DSP_IOPORT_ADDR;
    ;   |  |  |  |  |  |  |  |  |  |  |  |  +----------- [3]  DMADestByteAddr[3]     } elsif( daram ) {
    ;   |  |  |  |  |  |  |  |  |  |  |  |                                              DMADestByteAddr[17:0] = 0x10000 + DSP_BYTE_ADDR;
    ;   |  |  |  |  |  |  |  |  |  |  |  +-------------- [4]  DMADestByteAddr[4]     } elsif( saram ) {
    ;   |  |  |  |  |  |  |  |  |  |  +----------------- [5]  DMADestByteAddr[5]         DMADestByteAddr[17:0] = 0x20000 + DSP_BYTE_ADDR;
    ;   |  |  |  |  |  |  |  |  |  +-------------------- [6]  DMADestByteAddr[6]     }
    ;   |  |  |  |  |  |  |  |  +----------------------- [7]  DMADestByteAddr[7] 
    ;   |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  +-------------------------- [8]  DMADestByteAddr[8]      DMA0 can see: 
    ;   |  |  |  |  |  |  +----------------------------- [9]  DMADestByteAddr[9]      DMA1 can see: 
    ;   |  |  |  |  |  +-------------------------------- [10] DMADestByteAddr[10]     DMA2 can see: 
    ;   |  |  |  |  +----------------------------------- [11] DMADestByteAddr[11]     DMA3 can see: )
    ;   |  |  |  |
    ;   |  |  |  +-------------------------------------- [12] DMADestByteAddr[12]
    ;   |  |  +----------------------------------------- [13] DMADestByteAddr[13]
    ;   |  +-------------------------------------------- [14] DMADestByteAddr[14]
    ;   +----------------------------------------------- [15] DMADestByteAddr[15]
DMA3_CH1_DST_MSW        .set     0x0F23    ; DMA3 Channel 1 Destination MSW Address
    ; DMA3_CH1_DST_MSW   Address:  0x0F23 (IO space)      DMA3 Channel 1 Destination MSW Address
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ; |15:14:13:12|11:10: 9: 8| 7: 6: 5: 4| 3: 2: 1: 0|  <<== Bit Position
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; |r :r :r :r |r :r :r :r |r :r :r :r |r :r :rw:rw|  <<== Read / Write Access
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; | 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0|  <<== Reset Values
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-- [0]  DMADestByteAddr[16]
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  +----- [1]  DMADestByteAddr[17]
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  +-------- [2]  reserved
    ;   |  |  |  |  |  |  |  |  |  |  |  |  +----------- [3]  reserved
    ;   |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  +-------------- [4]  reserved
    ;   |  |  |  |  |  |  |  |  |  |  +----------------- [5]  reserved
    ;   |  |  |  |  |  |  |  |  |  +-------------------- [6]  reserved
    ;   |  |  |  |  |  |  |  |  +----------------------- [7]  reserved
    ;   |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  +-------------------------- [8]  reserved
    ;   |  |  |  |  |  |  +----------------------------- [9]  reserved
    ;   |  |  |  |  |  +-------------------------------- [10] reserved
    ;   |  |  |  |  +----------------------------------- [11] reserved
    ;   |  |  |  |
    ;   |  |  |  +-------------------------------------- [12] reserved
    ;   |  |  +----------------------------------------- [13] reserved
    ;   |  +-------------------------------------------- [14] reserved
    ;   +----------------------------------------------- [15] reserved
DMA3_CH1_TC_LEN         .set     0x0F24    ; DMA3 Channel 1 Length / Transfer Control LSW Register
    ; DMA3_CH1_TC_LEN   Address:  0x0F04 (IO space)      DMA3 Channel 1 Length / Transfer Control LSW Register
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ; |15:14:13:12|11:10: 9: 8| 7: 6: 5: 4| 3: 2: 1: 0|  <<== Bit Position
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; |rw:rw:rw:rw|rw:rw:rw:rw|rw:rw:rw:rw|rw:rw:r :r |  <<== Read / Write Access
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; | 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0|  <<== Reset Values
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |   ( XferLength[15:0] = number of bytes to be transfered)
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-- [0]  XferLength[0]
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  +----- [1]  XferLength[1]
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  +-------- [2]  XferLength[2]
    ;   |  |  |  |  |  |  |  |  |  |  |  |  +----------- [3]  XferLength[3]
    ;   |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  +-------------- [4]  XferLength[4]
    ;   |  |  |  |  |  |  |  |  |  |  +----------------- [5]  XferLength[5]
    ;   |  |  |  |  |  |  |  |  |  +-------------------- [6]  XferLength[6]
    ;   |  |  |  |  |  |  |  |  +----------------------- [7]  XferLength[7]
    ;   |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  +-------------------------- [8]  XferLength[8]
    ;   |  |  |  |  |  |  +----------------------------- [9]  XferLength[9]
    ;   |  |  |  |  |  +-------------------------------- [10] XferLength[10]
    ;   |  |  |  |  +----------------------------------- [11] XferLength[11]
    ;   |  |  |  |
    ;   |  |  |  +-------------------------------------- [12] XferLength[12]
    ;   |  |  +----------------------------------------- [13] XferLength[13]
    ;   |  +-------------------------------------------- [14] XferLength[14]
    ;   +----------------------------------------------- [15] XferLength[15]
DMA3_CH1_TC_MSW         .set     0x0F25    ; DMA3 Channel 1 Transfer Control MSW Register
    ; DMA3_CH1_TC_MSW   Address:  0x0F25 (IO space)      DMA3 Channel 1 Transfer Control MSW Register
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ; |15:14:13:12|11:10: 9: 8| 7: 6: 5: 4| 3: 2: 1: 0|  <<== Bit Position
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; |rw:rw:rw:rw|r :r :rw:rw|rw:rw:rw:rw|rw:r :rw:rw|  <<== Read / Write Access
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; | 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0|  <<== Reset Values
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-- [0]  SourceSize[0]      Source Data Size:
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  +----- [1]  SourceSize[1]      (00: 32-bit, 01: 16-bit, 10: 8-bit,  11: Reserved)
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  +-------- [2]  Sync               (1: DMA transfers one burst-mode length of 32-bit words per one peripheral event, 0: DMA transfers not controlled by peripheral events)
    ;   |  |  |  |  |  |  |  |  |  |  |  |  +----------- [3]  BurstMode[0]       (000:1 32bit word burst, 001:2 32bit word burst,
    ;   |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  +-------------- [4]  BurstMode[1]        010:4 32bit word burst, 011:8 32bit word burst,
    ;   |  |  |  |  |  |  |  |  |  |  +----------------- [5]  BurstMode[2]        100:16 32bit word burst, others:reserved)
    ;   |  |  |  |  |  |  |  |  |  +-------------------- [6]  SrcAddrMode[0]     (00:autoincr, 10:src addr is fixed, others:reserved)
    ;   |  |  |  |  |  |  |  |  +----------------------- [7]  SrcAddrMode[1]
    ;   |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  +-------------------------- [8]  DestAddrMode[0]    (00:autoincr, 10:dest addr is fixed, others:reserved)
    ;   |  |  |  |  |  |  +----------------------------- [9]  DestAddrMode[1]
    ;   |  |  |  |  |  +-------------------------------- [10] DestSize[0]        Destination data size:
    ;   |  |  |  |  +----------------------------------- [11] DestSize[1]        (00: 32-bit, 01: 16-bit, 10: 8-bit,  11: Reserved)
    ;   |  |  |  |
    ;   |  |  |  +-------------------------------------- [12] AutoReload        (0:disabled, to restart DMA set start bit = 1; 1:enabled, to stop DMA from reloading set start bit = 0 )
    ;   |  |  +----------------------------------------- [13] InterruptEn       (0:no interrupts generated, 1:interrupt generated when xfer complete)
    ;   |  +-------------------------------------------- [14] Status            (0:channel inactive, 1:channel active)
    ;   +----------------------------------------------- [15] Start/Stop        (0:stops after burst is complete, 1:starts block xfer)

;**************************************************************************
;        DMA3 Ch2 Register Addresses
;**************************************************************************
DMA3_CH2_SRC_LSW        .set     0x0F40    ; DMA3 Channel 2 Source LSW Address
    ; DMA3_CH2_SRC_LSW   Address:  0x0F40 (IO space)      DMA3 Channel 2 Source LSW Address
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ; |15:14:13:12|11:10: 9: 8| 7: 6: 5: 4| 3: 2: 1: 0|  <<== Bit Position
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; |rw:rw:rw:rw|rw:rw:rw:rw|rw:rw:rw:rw|rw:rw:rw:rw|  <<== Read / Write Access
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; | 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0|  <<== Reset Values
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-- [0]  DMASrcByteAddr[0]     ( Psuedo Code for setting DMA SRC/DEST Addresses:
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  +----- [1]  DMASrcByteAddr[1]      if( io_space ) {
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  +-------- [2]  DMASrcByteAddr[2]          DMASrcByteAddr[17:0] = DSP_IOPORT_ADDR;
    ;   |  |  |  |  |  |  |  |  |  |  |  |  +----------- [3]  DMASrcByteAddr[3]      } elsif( daram ) {
    ;   |  |  |  |  |  |  |  |  |  |  |  |                                               DMASrcByteAddr[17:0] = 0x10000 + DSP_BYTE_ADDR;
    ;   |  |  |  |  |  |  |  |  |  |  |  +-------------- [4]  DMASrcByteAddr[4]      } elsif( saram ) {
    ;   |  |  |  |  |  |  |  |  |  |  +----------------- [5]  DMASrcByteAddr[5]          DMASrcByteAddr[17:0] = 0x20000 + DSP_BYTE_ADDR;
    ;   |  |  |  |  |  |  |  |  |  +-------------------- [6]  DMASrcByteAddr[6]      }
    ;   |  |  |  |  |  |  |  |  +----------------------- [7]  DMASrcByteAddr[7] 
    ;   |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  +-------------------------- [8]  DMASrcByteAddr[8]      DMA0 can see: 
    ;   |  |  |  |  |  |  +----------------------------- [9]  DMASrcByteAddr[9]      DMA1 can see: 
    ;   |  |  |  |  |  +-------------------------------- [10] DMASrcByteAddr[10]     DMA2 can see: 
    ;   |  |  |  |  +----------------------------------- [11] DMASrcByteAddr[11]     DMA3 can see: )
    ;   |  |  |  |
    ;   |  |  |  +-------------------------------------- [12] DMASrcByteAddr[12]
    ;   |  |  +----------------------------------------- [13] DMASrcByteAddr[13]
    ;   |  +-------------------------------------------- [14] DMASrcByteAddr[14]
    ;   +----------------------------------------------- [15] DMASrcByteAddr[15]
DMA3_CH2_SRC_MSW        .set     0x0F41    ; DMA3 Channel 2 Source MSW Address
    ; DMA3_CH2_SRC_MSW   Address:  0x0F41 (IO space)      DMA3 Channel 2 Source MSW Address
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ; |15:14:13:12|11:10: 9: 8| 7: 6: 5: 4| 3: 2: 1: 0|  <<== Bit Position
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; |r :r :r :r |r :r :r :r |r :r :r :r |r :r :rw:rw|  <<== Read / Write Access
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; | 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0|  <<== Reset Values
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-- [0]  DMASrcByteAddr[16]
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  +----- [1]  DMASrcByteAddr[17]
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  +-------- [2]  reserved
    ;   |  |  |  |  |  |  |  |  |  |  |  |  +----------- [3]  reserved
    ;   |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  +-------------- [4]  reserved
    ;   |  |  |  |  |  |  |  |  |  |  +----------------- [5]  reserved
    ;   |  |  |  |  |  |  |  |  |  +-------------------- [6]  reserved
    ;   |  |  |  |  |  |  |  |  +----------------------- [7]  reserved
    ;   |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  +-------------------------- [8]  reserved
    ;   |  |  |  |  |  |  +----------------------------- [9]  reserved
    ;   |  |  |  |  |  +-------------------------------- [10] reserved
    ;   |  |  |  |  +----------------------------------- [11] reserved
    ;   |  |  |  |
    ;   |  |  |  +-------------------------------------- [12] reserved
    ;   |  |  +----------------------------------------- [13] reserved
    ;   |  +-------------------------------------------- [14] reserved
    ;   +----------------------------------------------- [15] reserved
DMA3_CH2_DST_LSW        .set     0x0F42    ; DMA3 Channel 2 Destination LSW Address
    ; DMA3_CH2_DST_LSW   Address:  0x0F42 (IO space)      DMA3 Channel 2 Destination LSW Address
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ; |15:14:13:12|11:10: 9: 8| 7: 6: 5: 4| 3: 2: 1: 0|  <<== Bit Position
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; |rw:rw:rw:rw|rw:rw:rw:rw|rw:rw:rw:rw|rw:rw:rw:rw|  <<== Read / Write Access
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; | 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0|  <<== Reset Values
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-- [0]  DMADestByteAddr[0]    ( Psuedo Code for setting DMA SRC/DEST Addresses:
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  +----- [1]  DMADestByteAddr[1]     if( io_space ) {
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  +-------- [2]  DMADestByteAddr[2]         DMADestByteAddr[17:0] = DSP_IOPORT_ADDR;
    ;   |  |  |  |  |  |  |  |  |  |  |  |  +----------- [3]  DMADestByteAddr[3]     } elsif( daram ) {
    ;   |  |  |  |  |  |  |  |  |  |  |  |                                              DMADestByteAddr[17:0] = 0x10000 + DSP_BYTE_ADDR;
    ;   |  |  |  |  |  |  |  |  |  |  |  +-------------- [4]  DMADestByteAddr[4]     } elsif( saram ) {
    ;   |  |  |  |  |  |  |  |  |  |  +----------------- [5]  DMADestByteAddr[5]         DMADestByteAddr[17:0] = 0x20000 + DSP_BYTE_ADDR;
    ;   |  |  |  |  |  |  |  |  |  +-------------------- [6]  DMADestByteAddr[6]     }
    ;   |  |  |  |  |  |  |  |  +----------------------- [7]  DMADestByteAddr[7] 
    ;   |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  +-------------------------- [8]  DMADestByteAddr[8]      DMA0 can see: 
    ;   |  |  |  |  |  |  +----------------------------- [9]  DMADestByteAddr[9]      DMA1 can see: 
    ;   |  |  |  |  |  +-------------------------------- [10] DMADestByteAddr[10]     DMA2 can see: 
    ;   |  |  |  |  +----------------------------------- [11] DMADestByteAddr[11]     DMA3 can see: )
    ;   |  |  |  |
    ;   |  |  |  +-------------------------------------- [12] DMADestByteAddr[12]
    ;   |  |  +----------------------------------------- [13] DMADestByteAddr[13]
    ;   |  +-------------------------------------------- [14] DMADestByteAddr[14]
    ;   +----------------------------------------------- [15] DMADestByteAddr[15]
DMA3_CH2_DST_MSW        .set     0x0F43    ; DMA3 Channel 2 Destination MSW Address
    ; DMA3_CH2_DST_MSW   Address:  0x0F43 (IO space)      DMA3 Channel 2 Destination MSW Address
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ; |15:14:13:12|11:10: 9: 8| 7: 6: 5: 4| 3: 2: 1: 0|  <<== Bit Position
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; |r :r :r :r |r :r :r :r |r :r :r :r |r :r :rw:rw|  <<== Read / Write Access
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; | 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0|  <<== Reset Values
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-- [0]  DMADestByteAddr[16]
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  +----- [1]  DMADestByteAddr[17]
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  +-------- [2]  reserved
    ;   |  |  |  |  |  |  |  |  |  |  |  |  +----------- [3]  reserved
    ;   |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  +-------------- [4]  reserved
    ;   |  |  |  |  |  |  |  |  |  |  +----------------- [5]  reserved
    ;   |  |  |  |  |  |  |  |  |  +-------------------- [6]  reserved
    ;   |  |  |  |  |  |  |  |  +----------------------- [7]  reserved
    ;   |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  +-------------------------- [8]  reserved
    ;   |  |  |  |  |  |  +----------------------------- [9]  reserved
    ;   |  |  |  |  |  +-------------------------------- [10] reserved
    ;   |  |  |  |  +----------------------------------- [11] reserved
    ;   |  |  |  |
    ;   |  |  |  +-------------------------------------- [12] reserved
    ;   |  |  +----------------------------------------- [13] reserved
    ;   |  +-------------------------------------------- [14] reserved
    ;   +----------------------------------------------- [15] reserved
DMA3_CH2_TC_LEN         .set     0x0F44    ; DMA3 Destination Address
    ; DMA3_CH2_TC_LEN   Address:  0x0F44 (IO space)      DMA3 Channel 2 Length / Transfer Control LSW Register
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ; |15:14:13:12|11:10: 9: 8| 7: 6: 5: 4| 3: 2: 1: 0|  <<== Bit Position
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; |rw:rw:rw:rw|rw:rw:rw:rw|rw:rw:rw:rw|rw:rw:r :r |  <<== Read / Write Access
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; | 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0|  <<== Reset Values
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |   ( XferLength[15:0] = number of bytes to be transfered)
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-- [0]  XferLength[0]
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  +----- [1]  XferLength[1]
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  +-------- [2]  XferLength[2]
    ;   |  |  |  |  |  |  |  |  |  |  |  |  +----------- [3]  XferLength[3]
    ;   |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  +-------------- [4]  XferLength[4]
    ;   |  |  |  |  |  |  |  |  |  |  +----------------- [5]  XferLength[5]
    ;   |  |  |  |  |  |  |  |  |  +-------------------- [6]  XferLength[6]
    ;   |  |  |  |  |  |  |  |  +----------------------- [7]  XferLength[7]
    ;   |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  +-------------------------- [8]  XferLength[8]
    ;   |  |  |  |  |  |  +----------------------------- [9]  XferLength[9]
    ;   |  |  |  |  |  +-------------------------------- [10] XferLength[10]
    ;   |  |  |  |  +----------------------------------- [11] XferLength[11]
    ;   |  |  |  |
    ;   |  |  |  +-------------------------------------- [12] XferLength[12]
    ;   |  |  +----------------------------------------- [13] XferLength[13]
    ;   |  +-------------------------------------------- [14] XferLength[14]
    ;   +----------------------------------------------- [15] XferLength[15]
DMA3_CH2_TC_MSW         .set     0x0F45    ; DMA3 Channel 2 Transfer Control MSW Register
    ; DMA3_CH2_TC_MSW   Address:  0x0F45 (IO space)      DMA3 Channel 2 Transfer Control MSW Register
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ; |15:14:13:12|11:10: 9: 8| 7: 6: 5: 4| 3: 2: 1: 0|  <<== Bit Position
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; |rw:rw:rw:rw|r :r :rw:rw|rw:rw:rw:rw|rw:r :rw:rw|  <<== Read / Write Access
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; | 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0|  <<== Reset Values
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +--  [0]  SourceSize[0]      Source Data Size:
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-----  [1]  SourceSize[1]      (00: 32-bit, 01: 16-bit, 10: 8-bit,  11: Reserved)
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  +--------  [2]  Sync               (1: DMA transfers one burst-mode length of 32-bit words per one peripheral event, 0: DMA transfers not controlled by peripheral events)
    ;   |  |  |  |  |  |  |  |  |  |  |  |  +-----------  [3]  BurstMode[0]       (000:1 32bit word burst, 001:2 32bit word burst,
    ;   |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  +--------------  [4]  BurstMode[1]        010:4 32bit word burst, 011:8 32bit word burst,
    ;   |  |  |  |  |  |  |  |  |  |  +-----------------  [5]  BurstMode[2]        100:16 32bit word burst, others:reserved)
    ;   |  |  |  |  |  |  |  |  |  +--------------------  [6]  SrcAddrMode[0]     (00:autoincr, 10:src addr is fixed, others:reserved)
    ;   |  |  |  |  |  |  |  |  +-----------------------  [7]  SrcAddrMode[1]
    ;   |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  +--------------------------  [8]  DestAddrMode[0]    (00:autoincr, 10:dest addr is fixed, others:reserved)
    ;   |  |  |  |  |  |  +-----------------------------  [9]  DestAddrMode[1]
    ;   |  |  |  |  |  +--------------------------------  [10] DestSize[0]        Destination data size:
    ;   |  |  |  |  +-----------------------------------  [11] DestSize[1]        (00: 32-bit, 01: 16-bit, 10: 8-bit,  11: Reserved)
    ;   |  |  |  |
    ;   |  |  |  +--------------------------------------  [12] AutoReload        (0:disabled, to restart DMA set start bit = 1; 1:enabled, to stop DMA from reloading set start bit = 0 )
    ;   |  |  +-----------------------------------------  [13] InterruptEn       (0:no interrupts generated, 1:interrupt generated when xfer complete)
    ;   |  +--------------------------------------------  [14] Status            (0:channel inactive, 1:channel active)
    ;   +-----------------------------------------------  [15] Start/Stop        (0:stops after burst is complete, 1:starts block xfer)

;**************************************************************************
;        DMA3 Ch3 Register Addresses
;**************************************************************************
DMA3_CH3_SRC_LSW        .set     0x0F60    ; DMA3 Channel 3 Source LSW Address
    ; DMA3_CH3_SRC_LSW   Address:  0x0F60 (IO space)      DMA3 Channel 3 Source LSW Address
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ; |15:14:13:12|11:10: 9: 8| 7: 6: 5: 4| 3: 2: 1: 0|  <<== Bit Position
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; |rw:rw:rw:rw|rw:rw:rw:rw|rw:rw:rw:rw|rw:rw:rw:rw|  <<== Read / Write Access
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; | 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0|  <<== Reset Values
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-- [0]  DMASrcByteAddr[0]     ( Psuedo Code for setting DMA SRC/DEST Addresses:
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  +----- [1]  DMASrcByteAddr[1]      if( io_space ) {
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  +-------- [2]  DMASrcByteAddr[2]          DMASrcByteAddr[17:0] = DSP_IOPORT_ADDR;
    ;   |  |  |  |  |  |  |  |  |  |  |  |  +----------- [3]  DMASrcByteAddr[3]      } elsif( daram ) {
    ;   |  |  |  |  |  |  |  |  |  |  |  |                                               DMASrcByteAddr[17:0] = 0x10000 + DSP_BYTE_ADDR;
    ;   |  |  |  |  |  |  |  |  |  |  |  +-------------- [4]  DMASrcByteAddr[4]      } elsif( saram ) {
    ;   |  |  |  |  |  |  |  |  |  |  +----------------- [5]  DMASrcByteAddr[5]          DMASrcByteAddr[17:0] = 0x20000 + DSP_BYTE_ADDR;
    ;   |  |  |  |  |  |  |  |  |  +-------------------- [6]  DMASrcByteAddr[6]      }
    ;   |  |  |  |  |  |  |  |  +----------------------- [7]  DMASrcByteAddr[7] 
    ;   |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  +-------------------------- [8]  DMASrcByteAddr[8]      DMA0 can see: 
    ;   |  |  |  |  |  |  +----------------------------- [9]  DMASrcByteAddr[9]      DMA1 can see: 
    ;   |  |  |  |  |  +-------------------------------- [10] DMASrcByteAddr[10]     DMA2 can see: 
    ;   |  |  |  |  +----------------------------------- [11] DMASrcByteAddr[11]     DMA3 can see: )
    ;   |  |  |  |
    ;   |  |  |  +-------------------------------------- [12] DMASrcByteAddr[12]
    ;   |  |  +----------------------------------------- [13] DMASrcByteAddr[13]
    ;   |  +-------------------------------------------- [14] DMASrcByteAddr[14]
    ;   +----------------------------------------------- [15] DMASrcByteAddr[15]
DMA3_CH3_SRC_MSW        .set     0x0F61    ; DMA3 Channel 3 Source MSW Address
    ; DMA3_CH3_SRC_MSW   Address:  0x0F61 (IO space)      DMA3 Channel 3 Source MSW Address
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ; |15:14:13:12|11:10: 9: 8| 7: 6: 5: 4| 3: 2: 1: 0|  <<== Bit Position
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; |r :r :r :r |r :r :r :r |r :r :r :r |r :r :rw:rw|  <<== Read / Write Access
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; | 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0|  <<== Reset Values
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-- [0]  DMASrcByteAddr[16]
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  +----- [1]  DMASrcByteAddr[17]
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  +-------- [2]  reserved
    ;   |  |  |  |  |  |  |  |  |  |  |  |  +----------- [3]  reserved
    ;   |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  +-------------- [4]  reserved
    ;   |  |  |  |  |  |  |  |  |  |  +----------------- [5]  reserved
    ;   |  |  |  |  |  |  |  |  |  +-------------------- [6]  reserved
    ;   |  |  |  |  |  |  |  |  +----------------------- [7]  reserved
    ;   |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  +-------------------------- [8]  reserved
    ;   |  |  |  |  |  |  +----------------------------- [9]  reserved
    ;   |  |  |  |  |  +-------------------------------- [10] reserved
    ;   |  |  |  |  +----------------------------------- [11] reserved
    ;   |  |  |  |
    ;   |  |  |  +-------------------------------------- [12] reserved
    ;   |  |  +----------------------------------------- [13] reserved
    ;   |  +-------------------------------------------- [14] reserved
    ;   +----------------------------------------------- [15] reserved
DMA3_CH3_DST_LSW        .set     0x0F62    ; DMA3 Channel 3 Destination LSW Address
    ; DMA3_CH3_DST_LSW   Address:  0x0F62 (IO space)      DMA3 Channel 3 Destination LSW Address
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ; |15:14:13:12|11:10: 9: 8| 7: 6: 5: 4| 3: 2: 1: 0|  <<== Bit Position
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; |rw:rw:rw:rw|rw:rw:rw:rw|rw:rw:rw:rw|rw:rw:rw:rw|  <<== Read / Write Access
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; | 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0|  <<== Reset Values
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-- [0]  DMADestByteAddr[0]    ( Psuedo Code for setting DMA SRC/DEST Addresses:
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  +----- [1]  DMADestByteAddr[1]     if( io_space ) {
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  +-------- [2]  DMADestByteAddr[2]         DMADestByteAddr[17:0] = DSP_IOPORT_ADDR;
    ;   |  |  |  |  |  |  |  |  |  |  |  |  +----------- [3]  DMADestByteAddr[3]     } elsif( daram ) {
    ;   |  |  |  |  |  |  |  |  |  |  |  |                                              DMADestByteAddr[17:0] = 0x10000 + DSP_BYTE_ADDR;
    ;   |  |  |  |  |  |  |  |  |  |  |  +-------------- [4]  DMADestByteAddr[4]     } elsif( saram ) {
    ;   |  |  |  |  |  |  |  |  |  |  +----------------- [5]  DMADestByteAddr[5]         DMADestByteAddr[17:0] = 0x20000 + DSP_BYTE_ADDR;
    ;   |  |  |  |  |  |  |  |  |  +-------------------- [6]  DMADestByteAddr[6]     }
    ;   |  |  |  |  |  |  |  |  +----------------------- [7]  DMADestByteAddr[7] 
    ;   |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  +-------------------------- [8]  DMADestByteAddr[8]      DMA0 can see: 
    ;   |  |  |  |  |  |  +----------------------------- [9]  DMADestByteAddr[9]      DMA1 can see: 
    ;   |  |  |  |  |  +-------------------------------- [10] DMADestByteAddr[10]     DMA2 can see: 
    ;   |  |  |  |  +----------------------------------- [11] DMADestByteAddr[11]     DMA3 can see: )
    ;   |  |  |  |
    ;   |  |  |  +-------------------------------------- [12] DMADestByteAddr[12]
    ;   |  |  +----------------------------------------- [13] DMADestByteAddr[13]
    ;   |  +-------------------------------------------- [14] DMADestByteAddr[14]
    ;   +----------------------------------------------- [15] DMADestByteAddr[15]
DMA3_CH3_DST_MSW        .set     0x0F63    ; DMA3 Channel 3 Destination MSW Address
    ; DMA3_CH3_DST_MSW   Address:  0x0F63 (IO space)      DMA3 Channel 3 Destination MSW Address
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ; |15:14:13:12|11:10: 9: 8| 7: 6: 5: 4| 3: 2: 1: 0|  <<== Bit Position
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; |r :r :r :r |r :r :r :r |r :r :r :r |r :r :rw:rw|  <<== Read / Write Access
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; | 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0|  <<== Reset Values
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-- [0]  DMADestByteAddr[16]
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  +----- [1]  DMADestByteAddr[17]
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  +-------- [2]  reserved
    ;   |  |  |  |  |  |  |  |  |  |  |  |  +----------- [3]  reserved
    ;   |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  +-------------- [4]  reserved
    ;   |  |  |  |  |  |  |  |  |  |  +----------------- [5]  reserved
    ;   |  |  |  |  |  |  |  |  |  +-------------------- [6]  reserved
    ;   |  |  |  |  |  |  |  |  +----------------------- [7]  reserved
    ;   |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  +-------------------------- [8]  reserved
    ;   |  |  |  |  |  |  +----------------------------- [9]  reserved
    ;   |  |  |  |  |  +-------------------------------- [10] reserved
    ;   |  |  |  |  +----------------------------------- [11] reserved
    ;   |  |  |  |
    ;   |  |  |  +-------------------------------------- [12] reserved
    ;   |  |  +----------------------------------------- [13] reserved
    ;   |  +-------------------------------------------- [14] reserved
    ;   +----------------------------------------------- [15] reserved
DMA3_CH3_TC_LEN         .set     0x0F64    ; DMA3 Destination Address
    ; DMA3_CH3_TC_LEN   Address:  0x0F64 (IO space)      DMA3 Channel 3 Length / Transfer Control LSW Register
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ; |15:14:13:12|11:10: 9: 8| 7: 6: 5: 4| 3: 2: 1: 0|  <<== Bit Position
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; |rw:rw:rw:rw|rw:rw:rw:rw|rw:rw:rw:rw|rw:rw:r :r |  <<== Read / Write Access
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; | 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0|  <<== Reset Values
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |   ( XferLength[15:0] = number of bytes to be transfered)
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-- [0]  XferLength[0]
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  +----- [1]  XferLength[1]
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  +-------- [2]  XferLength[2]
    ;   |  |  |  |  |  |  |  |  |  |  |  |  +----------- [3]  XferLength[3]
    ;   |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  +-------------- [4]  XferLength[4]
    ;   |  |  |  |  |  |  |  |  |  |  +----------------- [5]  XferLength[5]
    ;   |  |  |  |  |  |  |  |  |  +-------------------- [6]  XferLength[6]
    ;   |  |  |  |  |  |  |  |  +----------------------- [7]  XferLength[7]
    ;   |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  +-------------------------- [8]  XferLength[8]
    ;   |  |  |  |  |  |  +----------------------------- [9]  XferLength[9]
    ;   |  |  |  |  |  +-------------------------------- [10] XferLength[10]
    ;   |  |  |  |  +----------------------------------- [11] XferLength[11]
    ;   |  |  |  |
    ;   |  |  |  +-------------------------------------- [12] XferLength[12]
    ;   |  |  +----------------------------------------- [13] XferLength[13]
    ;   |  +-------------------------------------------- [14] XferLength[14]
    ;   +----------------------------------------------- [15] XferLength[15]
DMA3_CH3_TC_MSW         .set     0x0F65    ; DMA3 Channel 0 Transfer Control MSW Register
    ; DMA3_CH3_TC_MSW   Address:  0x0F65 (IO space)      DMA3 Channel 3 Transfer Control MSW Register
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ; |15:14:13:12|11:10: 9: 8| 7: 6: 5: 4| 3: 2: 1: 0|  <<== Bit Position
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; |rw:rw:rw:rw|r :r :rw:rw|rw:rw:rw:rw|rw:r :rw:rw|  <<== Read / Write Access
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; | 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0|  <<== Reset Values
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +--  [0]  SourceSize[0]      Source Data Size:
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-----  [1]  SourceSize[1]      (00: 32-bit, 01: 16-bit, 10: 8-bit,  11: Reserved)
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  +--------  [2]  Sync               (1: DMA transfers one burst-mode length of 32-bit words per one peripheral event, 0: DMA transfers not controlled by peripheral events)
    ;   |  |  |  |  |  |  |  |  |  |  |  |  +-----------  [3]  BurstMode[0]       (000:1 32bit word burst, 001:2 32bit word burst,
    ;   |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  +--------------  [4]  BurstMode[1]        010:4 32bit word burst, 011:8 32bit word burst,
    ;   |  |  |  |  |  |  |  |  |  |  +-----------------  [5]  BurstMode[2]        100:16 32bit word burst, others:reserved)
    ;   |  |  |  |  |  |  |  |  |  +--------------------  [6]  SrcAddrMode[0]     (00:autoincr, 10:src addr is fixed, others:reserved)
    ;   |  |  |  |  |  |  |  |  +-----------------------  [7]  SrcAddrMode[1]
    ;   |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  +--------------------------  [8]  DestAddrMode[0]    (00:autoincr, 10:dest addr is fixed, others:reserved)
    ;   |  |  |  |  |  |  +-----------------------------  [9]  DestAddrMode[1]
    ;   |  |  |  |  |  +--------------------------------  [10] DestSize[0]        Destination data size:
    ;   |  |  |  |  +-----------------------------------  [11] DestSize[1]        (00: 32-bit, 01: 16-bit, 10: 8-bit,  11: Reserved)
    ;   |  |  |  |
    ;   |  |  |  +--------------------------------------  [12] AutoReload        (0:disabled, to restart DMA set start bit = 1; 1:enabled, to stop DMA from reloading set start bit = 0 )
    ;   |  |  +-----------------------------------------  [13] InterruptEn       (0:no interrupts generated, 1:interrupt generated when xfer complete)
    ;   |  +--------------------------------------------  [14] Status            (0:channel inactive, 1:channel active)
    ;   +-----------------------------------------------  [15] Start/Stop        (0:stops after burst is complete, 1:starts block xfer)
;****************************************************************************************

;----------------------------------------------------------------------------------------
;        DMA Interrupt Flag and Mask Register Bit Fields
;----------------------------------------------------------------------------------------
DMA0_0_INT            .set    0x0001     
DMA0_1_INT            .set    0x0002     
DMA0_2_INT            .set    0x0004     
DMA0_3_INT            .set    0x0008     
DMA1_0_INT            .set    0x0010     
DMA1_1_INT            .set    0x0020    
DMA1_2_INT            .set    0x0040     
DMA1_3_INT            .set    0x0080     
DMA2_0_INT            .set    0x0100     
DMA2_1_INT            .set    0x0200     
DMA2_2_INT            .set    0x0400     
DMA2_3_INT            .set    0x0800     
DMA3_0_INT            .set    0x1000     
DMA3_1_INT            .set    0x2000    
DMA3_2_INT            .set    0x4000     
DMA3_3_INT            .set    0x8000     

;----------------------------------------------------------------------------------------
;        DMA Channel Source Register Bit Fields (DA224 - OBSOLETE)
;----------------------------------------------------------------------------------------
I2S0                .set    0x01      ; I2S0 Event
I2S1                .set    0x02      ; I2S1 Event
I2S2                .set    0x03      ; I2S2 Event
I2S3                .set    0x04      ; I2S3 Event
COPROC              .set    0x05      ; Coprocessor Event
ADC_LEFT            .set    0x06      ; ADC Left Channel Event
ADC_RIGHT           .set    0x07      ; ADC Right Channel Event
DAC_LEFT            .set    0x08      ; DAC Left Channel Event
DAC_RIGHT           .set    0x09      ; DAC Right Channel Event
UART_RX             .set    0x0A      ; UART RX Event
UART_TX             .set    0x0B      ; UART TX Event
TIMER0              .set    0x0C      ; Timer 0 Event
SAR                 .set    0x0D      ; 10-Bit SAR Event
TIMER1              .set    0x0E      ; Timer 1 Event
TIMER2              .set    0x0F      ; Timer 2 Event

;****************************************************************************************
;        Watchdog Timer Register Addresses
;****************************************************************************************
WT_KICKLOCK         .set    0x1800        ; Watchdog Timer Kick Lock Register
                                        ;  Write 0x5555 to unlock, then
                                        ;  Write 0xAAAA to unlock
WT_KICK             .set    0x1802        ; Watchdog Timer Kick Register
WT_COUNTERLOCK      .set    0x1804        ; Watchdog Timer Counter Lock Register
                                        ;  Write 0x6666 to unlock, then
                                        ;  Write 0xBBBB to unlock
WT_COUNTER          .set    0x1806        ; Watchdog Timer Change Register
WT_DISABLELOCK      .set    0x1808        ; Watchdog Timer Disable Lock Register
                                        ;  Write 0x7777 to unlock, then
                                        ;  Write 0xCCCC to unlock, then
                                        ;  Write 0xDDDD to unlock
WT_DISABLE          .set    0x180A        ; Watchdog Timer Disable Register
                                        ;  Write 1 to enable
WT_PRESCALELOCK     .set    0x180C        ; Watchdog Timer Prescale Lock Register
                                        ;  Write 0x5A5A to unlock, then
                                        ;  Write 0xA5A5 to unlock
WT_PRESCALE         .set    0x180E        ; Watchdog Timer Prescale Register


;****************************************************************************************
;        Timer 0 Register Addresses
;****************************************************************************************
TIM0_CNTL            .set    0x1810        ; Timer Control Register
    ; TIM0_CNTL   Address:  0x1810                      Timer0 Control Register
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ; |15:14:13:12|11:10: 9: 8| 7: 6: 5: 4| 3: 2: 1: 0|  <<== Bit Position
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; |rw:r :r :r |r :r :r :r |r :r :rw:rw|rw:rw:rw:rw|  <<== Read / Write Access
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; | 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0|  <<== Reset Values
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-- [0]  Start                 (0:timer disabled; 1:timer enabled.  Period register copied to counter & starts counting down)
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  +----- [1]  Auto-Reload           (0:auto-reload disabled.  Timer stops when reaching zero and clears START; 1:auto-reload enabled)
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  +-------- [2]  PrescaleDivider[0]    (divide_by_factor = 
    ;   |  |  |  |  |  |  |  |  |  |  |  |  +----------- [3]  PrescaleDivider[1]        2 ^ (PrescaleDivider[3:0] + 1)
    ;   |  |  |  |  |  |  |  |  |  |  |  |                                          )
    ;   |  |  |  |  |  |  |  |  |  |  |  +-------------- [4]  PrescaleDivider[2]
    ;   |  |  |  |  |  |  |  |  |  |  +----------------- [5]  PrescaleDivider[3]
    ;   |  |  |  |  |  |  |  |  |  +-------------------- [6]  reserved
    ;   |  |  |  |  |  |  |  |  +----------------------- [7]  reserved
    ;   |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  +-------------------------- [8]  reserved
    ;   |  |  |  |  |  |  +----------------------------- [9]  reserved
    ;   |  |  |  |  |  +-------------------------------- [10] reserved
    ;   |  |  |  |  +----------------------------------- [11] reserved
    ;   |  |  |  |
    ;   |  |  |  +-------------------------------------- [12] reserved
    ;   |  |  +----------------------------------------- [13] reserved
    ;   |  +-------------------------------------------- [14] reserved
    ;   +----------------------------------------------- [15] TimerEn               (0:disabled, 1:enabled)

TIM0_PERL            .set    0x1812        ; Timer Period Least Significant Word Register
TIM0_PERH            .set    0x1813        ; Timer Period Most Significant Word Register
TIM0_COUNTL          .set    0x1814        ; TImer Counter Least Significant Word Register
TIM0_COUNTH          .set    0x1815        ; TImer Counter Most Significant Word Register
TIM0_INTF            .set    0x1816        ; Timer Interrupt Flag Register
    ; TIM0_INTF   Address:  0x1816                      Timer0 Interrupt Flag Register
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ; |15:14:13:12|11:10: 9: 8| 7: 6: 5: 4| 3: 2: 1: 0|  <<== Bit Position
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; |r :r :r :r |r :r :r :r |r :r :r :r |r :r :r :rw|  <<== Read / Write Access
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; | 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0|  <<== Reset Values
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |                      Must write a 1 to clear the interrupt flag
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-- [0]  Interrupt     (0:no interrupt has occurred; 1:interrupt occurred)
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  +----- [1]  reserved
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  +-------- [2]  reserved
    ;   |  |  |  |  |  |  |  |  |  |  |  |  +----------- [3]  reserved
    ;   |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  +-------------- [4]  reserved
    ;   |  |  |  |  |  |  |  |  |  |  +----------------- [5]  reserved
    ;   |  |  |  |  |  |  |  |  |  +-------------------- [6]  reserved
    ;   |  |  |  |  |  |  |  |  +----------------------- [7]  reserved
    ;   |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  +-------------------------- [8]  reserved
    ;   |  |  |  |  |  |  +----------------------------- [9]  reserved
    ;   |  |  |  |  |  +-------------------------------- [10] reserved
    ;   |  |  |  |  +----------------------------------- [11] reserved
    ;   |  |  |  |
    ;   |  |  |  +-------------------------------------- [12] reserved
    ;   |  |  +----------------------------------------- [13] reserved
    ;   |  +-------------------------------------------- [14] reserved
    ;   +----------------------------------------------- [15] reserved

;****************************************************************************************
;        Timer 1 Register Addresses
;****************************************************************************************
TIM1_CNTL            .set    0x1850        ; Timer Control Register
    ; TIM1_CNTL   Address:  0x1850                      Timer1 Control Register
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ; |15:14:13:12|11:10: 9: 8| 7: 6: 5: 4| 3: 2: 1: 0|  <<== Bit Position
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; |rw:r :r :r |r :r :r :r |r :r :rw:rw|rw:rw:rw:rw|  <<== Read / Write Access
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; | 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0|  <<== Reset Values
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-- [0]  Start                 (0:timer disabled; 1:timer enabled.  Period register copied to counter & starts counting down)
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  +----- [1]  Auto-Reload           (0:auto-reload disabled.  Timer stops when reaching zero and clears START; 1:auto-reload enabled)
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  +-------- [2]  PrescaleDivider[0]    (divide_by_factor = 
    ;   |  |  |  |  |  |  |  |  |  |  |  |  +----------- [3]  PrescaleDivider[1]        2 ^ (PrescaleDivider[3:0] + 1)
    ;   |  |  |  |  |  |  |  |  |  |  |  |                                          )
    ;   |  |  |  |  |  |  |  |  |  |  |  +-------------- [4]  PrescaleDivider[2]
    ;   |  |  |  |  |  |  |  |  |  |  +----------------- [5]  PrescaleDivider[3]
    ;   |  |  |  |  |  |  |  |  |  +-------------------- [6]  reserved
    ;   |  |  |  |  |  |  |  |  +----------------------- [7]  reserved
    ;   |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  +-------------------------- [8]  reserved
    ;   |  |  |  |  |  |  +----------------------------- [9]  reserved
    ;   |  |  |  |  |  +-------------------------------- [10] reserved
    ;   |  |  |  |  +----------------------------------- [11] reserved
    ;   |  |  |  |
    ;   |  |  |  +-------------------------------------- [12] reserved
    ;   |  |  +----------------------------------------- [13] reserved
    ;   |  +-------------------------------------------- [14] reserved
    ;   +----------------------------------------------- [15] TimerEn               (0:disabled, 1:enabled)
TIM1_PERL            .set    0x1852        ; Timer Period Least Significant Word Register
TIM1_PERH            .set    0x1853        ; Timer Period Most Significant Word Register
TIM1_COUNTL          .set    0x1854        ; TImer Counter Least Significant Word Register
TIM1_COUNTH          .set    0x1855        ; TImer Counter Most Significant Word Register
TIM1_INTF            .set    0x1856        ; Timer Interrupt Flag Register
    ; TIM1_INTF   Address:  0x1856                      Timer1 Interrupt Flag Register
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ; |15:14:13:12|11:10: 9: 8| 7: 6: 5: 4| 3: 2: 1: 0|  <<== Bit Position
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; |r :r :r :r |r :r :r :r |r :r :r :r |r :r :r :rw|  <<== Read / Write Access
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; | 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0|  <<== Reset Values
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |                      Must write a 1 to clear the interrupt flag
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-- [0]  Interrupt     (0:no interrupt has occurred; 1:interrupt occurred)
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  +----- [1]  reserved
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  +-------- [2]  reserved
    ;   |  |  |  |  |  |  |  |  |  |  |  |  +----------- [3]  reserved
    ;   |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  +-------------- [4]  reserved
    ;   |  |  |  |  |  |  |  |  |  |  +----------------- [5]  reserved
    ;   |  |  |  |  |  |  |  |  |  +-------------------- [6]  reserved
    ;   |  |  |  |  |  |  |  |  +----------------------- [7]  reserved
    ;   |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  +-------------------------- [8]  reserved
    ;   |  |  |  |  |  |  +----------------------------- [9]  reserved
    ;   |  |  |  |  |  +-------------------------------- [10] reserved
    ;   |  |  |  |  +----------------------------------- [11] reserved
    ;   |  |  |  |
    ;   |  |  |  +-------------------------------------- [12] reserved
    ;   |  |  +----------------------------------------- [13] reserved
    ;   |  +-------------------------------------------- [14] reserved
    ;   +----------------------------------------------- [15] reserved

;****************************************************************************************
;        Timer 2 Register Addresses
;****************************************************************************************
TIM2_CNTL            .set    0x1890        ; Timer Control Register
    ; TIM2_CNTL   Address:  0x1890                      Timer2 Control Register
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ; |15:14:13:12|11:10: 9: 8| 7: 6: 5: 4| 3: 2: 1: 0|  <<== Bit Position
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; |rw:r :r :r |r :r :r :r |r :r :rw:rw|rw:rw:rw:rw|  <<== Read / Write Access
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; | 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0|  <<== Reset Values
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-- [0]  Start                 (0:timer disabled; 1:timer enabled.  Period register copied to counter & starts counting down)
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  +----- [1]  Auto-Reload           (0:auto-reload disabled.  Timer stops when reaching zero and clears START; 1:auto-reload enabled)
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  +-------- [2]  PrescaleDivider[0]    (divide_by_factor = 
    ;   |  |  |  |  |  |  |  |  |  |  |  |  +----------- [3]  PrescaleDivider[1]        2 ^ (PrescaleDivider[3:0] + 1)
    ;   |  |  |  |  |  |  |  |  |  |  |  |                                          )
    ;   |  |  |  |  |  |  |  |  |  |  |  +-------------- [4]  PrescaleDivider[2]
    ;   |  |  |  |  |  |  |  |  |  |  +----------------- [5]  PrescaleDivider[3]
    ;   |  |  |  |  |  |  |  |  |  +-------------------- [6]  reserved
    ;   |  |  |  |  |  |  |  |  +----------------------- [7]  reserved
    ;   |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  +-------------------------- [8]  reserved
    ;   |  |  |  |  |  |  +----------------------------- [9]  reserved
    ;   |  |  |  |  |  +-------------------------------- [10] reserved
    ;   |  |  |  |  +----------------------------------- [11] reserved
    ;   |  |  |  |
    ;   |  |  |  +-------------------------------------- [12] reserved
    ;   |  |  +----------------------------------------- [13] reserved
    ;   |  +-------------------------------------------- [14] reserved
    ;   +----------------------------------------------- [15] TimerEn               (0:disabled, 1:enabled)
TIM2_PERL            .set    0x1892        ; Timer Period Least Significant Word Register
TIM2_PERH            .set    0x1893        ; Timer Period Most Significant Word Register
TIM2_COUNTL          .set    0x1894        ; TImer Counter Least Significant Word Register
TIM2_COUNTH          .set    0x1895        ; TImer Counter Most Significant Word Register
TIM2_INTF            .set    0x1896        ; Timer Interrupt Flag Register
    ; TIM2_INTF   Address:  0x1896                      Timer2 Interrupt Flag Register
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ; |15:14:13:12|11:10: 9: 8| 7: 6: 5: 4| 3: 2: 1: 0|  <<== Bit Position
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; |r :r :r :r |r :r :r :r |r :r :r :r |r :r :r :rw|  <<== Read / Write Access
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; | 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0|  <<== Reset Values
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |                      Must write a 1 to clear the interrupt flag
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-- [0]  Interrupt     (0:no interrupt has occurred; 1:interrupt occurred)
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  +----- [1]  reserved
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  +-------- [2]  reserved
    ;   |  |  |  |  |  |  |  |  |  |  |  |  +----------- [3]  reserved
    ;   |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  +-------------- [4]  reserved
    ;   |  |  |  |  |  |  |  |  |  |  +----------------- [5]  reserved
    ;   |  |  |  |  |  |  |  |  |  +-------------------- [6]  reserved
    ;   |  |  |  |  |  |  |  |  +----------------------- [7]  reserved
    ;   |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  +-------------------------- [8]  reserved
    ;   |  |  |  |  |  |  +----------------------------- [9]  reserved
    ;   |  |  |  |  |  +-------------------------------- [10] reserved
    ;   |  |  |  |  +----------------------------------- [11] reserved
    ;   |  |  |  |
    ;   |  |  |  +-------------------------------------- [12] reserved
    ;   |  |  +----------------------------------------- [13] reserved
    ;   |  +-------------------------------------------- [14] reserved
    ;   +----------------------------------------------- [15] reserved

;****************************************************************************************
;        RTC Register Addresses
;****************************************************************************************
RTC_MSEC             .set    0x1904        ; RTC MilliSeconds Register
RTC_SEC              .set    0x1908        ; RTC Seconds Register
RTC_MIN              .set    0x190C        ; RTC Minutes Register
RTC_HOUR             .set    0x1910        ; RTC Hours Register
RTC_DAY              .set    0x1914        ; RTC Days Register
RTC_MONTH            .set    0x1918        ; RTC Months Register
RTC_YEAR             .set    0x191C        ; RTC Years Register

RTC_MSECAL           .set    0x1905        ; RTC MilliSeconds Alarm Register
RTC_SECAL            .set    0x1909        ; RTC Seconds Alarm Register
RTC_MINAL            .set    0x190D        ; RTC Minutes Alarm Register
RTC_HOURAL           .set    0x1911        ; RTC Hours Alarm Register
RTC_DAYAL            .set    0x1915        ; RTC Days Alarm Register
RTC_MONTHAL          .set    0x1919        ; RTC Months Alarm Register
RTC_YEARAL           .set    0x191D        ; RTC Years Alarm Register

RTC_CTR             .set    0x1900        ; RTC Control Register
    ; RTC_CTR   Address:  0x1900 (IO space)              RTC Control Register
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ; |15:14:13:12|11:10: 9: 8| 7: 6: 5: 4| 3: 2: 1: 0|  <<== Bit Position
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; |r :r :r :r |r :r :r :r |r :r :r :r |r :r :r :rw|  <<== Read / Write Access
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; | 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0|  <<== Reset Values
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-- [0]  VBUS_int_enable       (0: Interrupts disabled @ VBUS i/f; 1: enabled)
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  +----- [1]  reserved
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  +-------- [2]  reserved
    ;   |  |  |  |  |  |  |  |  |  |  |  |  +----------- [3]  reserved
    ;   |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  +-------------- [4]  reserved
    ;   |  |  |  |  |  |  |  |  |  |  +----------------- [5]  reserved
    ;   |  |  |  |  |  |  |  |  |  +-------------------- [6]  reserved
    ;   |  |  |  |  |  |  |  |  +----------------------- [7]  reserved
    ;   |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  +-------------------------- [8]  reserved
    ;   |  |  |  |  |  |  +----------------------------- [9]  reserved
    ;   |  |  |  |  |  +-------------------------------- [10] reserved
    ;   |  |  |  |  +----------------------------------- [11] reserved
    ;   |  |  |  |
    ;   |  |  |  +-------------------------------------- [12] reserved
    ;   |  |  +----------------------------------------- [13] reserved
    ;   |  +-------------------------------------------- [14] reserved
    ;   +----------------------------------------------- [15] reserved
RTC_UPDT          .set    0x1901        ; RTC Update Register
    ; RTC_CTR   Address:  0x1901 (IO space)              RTC Update Register
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ; |15:14:13:12|11:10: 9: 8| 7: 6: 5: 4| 3: 2: 1: 0|  <<== Bit Position
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; |rw:rw:r :r |r :r :r :r |r :r :r :r |r :r :r :r |  <<== Read / Write Access
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; | 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0|  <<== Reset Values
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-- [0]  reserved
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  +----- [1]  reserved
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  +-------- [2]  reserved
    ;   |  |  |  |  |  |  |  |  |  |  |  |  +----------- [3]  reserved
    ;   |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  +-------------- [4]  reserved
    ;   |  |  |  |  |  |  |  |  |  |  +----------------- [5]  reserved
    ;   |  |  |  |  |  |  |  |  |  +-------------------- [6]  reserved
    ;   |  |  |  |  |  |  |  |  +----------------------- [7]  reserved
    ;   |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  +-------------------------- [8]  reserved
    ;   |  |  |  |  |  |  +----------------------------- [9]  reserved
    ;   |  |  |  |  |  +-------------------------------- [10] reserved
    ;   |  |  |  |  +----------------------------------- [11] reserved
    ;   |  |  |  |
    ;   |  |  |  +-------------------------------------- [12] reserved
    ;   |  |  +----------------------------------------- [13] reserved
    ;   |  +-------------------------------------------- [14] UPDT_AL            (1: Initiates update of the contents of the alarm comparison registers and resets upon successful update).
    ;   +----------------------------------------------- [15] UPDT               (1: Initiates update of the contents of the time registers and resets upon successful update).
;----------------------------------------------------------------------------------------
;    RTC Update Register Bit Field Settings
;----------------------------------------------------------------------------------------
RTC_AL_UPDT        .set    1b<<14           ; Initiates update of the contents of the alarm comparison registers and resets upon successful update).
RTC_TIME_UPDT      .set    1b<<15           ; Initiates update of the contents of the time registers and resets upon successful update)

RTC_STAT            .set    0x1920        ; RTC Status Register
    ; RTC_STAT   Address:  0x1920 (IO space)              RTC Status Register
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ; |15:14:13:12|11:10: 9: 8| 7: 6: 5: 4| 3: 2: 1: 0|  <<== Bit Position
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; |r :r :r :r |r :r :r :r |r :r :r :r |r :r :r :r |  <<== Read / Write Access
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; | 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0|  <<== Reset Values
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-- [0]  MS_EVT              (1: Millisecond Event Occured, self clearing upon read)
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  +----- [1]  SEC_EVT             (1: Second Event Occured, self clearing upon read)
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  +-------- [2]  MIN_EVT             (1: Minute Event Occured, self clearing upon read)
    ;   |  |  |  |  |  |  |  |  |  |  |  |  +----------- [3]  HR_EVT              (1: Hour Event Occured, self clearing upon read)
    ;   |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  +-------------- [4]  DAY_EVT             (1: Day Event Occured, self clearing upon read)
    ;   |  |  |  |  |  |  |  |  |  |  +----------------- [5]  EXT_EVT             (1: External Event Occured, self clearing upon read)
    ;   |  |  |  |  |  |  |  |  |  +-------------------- [6]  reserved
    ;   |  |  |  |  |  |  |  |  +----------------------- [7]  reserved
    ;   |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  +-------------------------- [8]  reserved
    ;   |  |  |  |  |  |  +----------------------------- [9]  reserved
    ;   |  |  |  |  |  +-------------------------------- [10] reserved
    ;   |  |  |  |  +----------------------------------- [11] reserved
    ;   |  |  |  |
    ;   |  |  |  +-------------------------------------- [12] reserved
    ;   |  |  +----------------------------------------- [13] reserved
    ;   |  +-------------------------------------------- [14] reserved
    ;   +----------------------------------------------- [15] ALARM               (1: Alarm Event Occured, self clearing upon read)
;----------------------------------------------------------------------------------------
;    RTC Status Register Bit Field Settings
;----------------------------------------------------------------------------------------
RTC_INT_MSEC        .set    1b<<0           ; RTC periodic interrupt millisecond enable
RTC_INT_SEC         .set    1b<<1           ; RTC periodic interrupt seconds enable
RTC_INT_MIN         .set    1b<<2           ; RTC periodic interrupt minutes enable
RTC_INT_HOUR        .set    1b<<3           ; RTC periodic interrupt hours enable
RTC_INT_DAY         .set    1b<<4           ; RTC periodic interrupt days enable
RTC_EXT_INT         .set    1b<<5           ; RTC external event interrupt enable
RTC_ALARM_INT       .set    1b<<15          ; enable RTC alarm interrupt

RTC_STAT_PWRUP          .set    0x1921        ; RTC Status Powerup Register
    ; RTC_STAT_PWRUP   Address:  0x1921 (IO space)              RTC Status Powerup Register
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ; |15:14:13:12|11:10: 9: 8| 7: 6: 5: 4| 3: 2: 1: 0|  <<== Bit Position
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; |r :r :r :r |r :r :r :r |r :r :r :r |r :r :r :r |  <<== Read / Write Access
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; | 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0|  <<== Reset Values
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-- [0]  Powerup             (1: POR, Powerup 'coldstart' Event Occured; 0: warmstart)
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  +----- [1]  reserved
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  +-------- [2]  reserved
    ;   |  |  |  |  |  |  |  |  |  |  |  |  +----------- [3]  reserved
    ;   |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  +-------------- [4]  reserved
    ;   |  |  |  |  |  |  |  |  |  |  +----------------- [5]  reserved
    ;   |  |  |  |  |  |  |  |  |  +-------------------- [6]  reserved
    ;   |  |  |  |  |  |  |  |  +----------------------- [7]  reserved
    ;   |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  +-------------------------- [8]  reserved
    ;   |  |  |  |  |  |  +----------------------------- [9]  reserved
    ;   |  |  |  |  |  +-------------------------------- [10] reserved
    ;   |  |  |  |  +----------------------------------- [11] reserved
    ;   |  |  |  |
    ;   |  |  |  +-------------------------------------- [12] reserved
    ;   |  |  +----------------------------------------- [13] reserved
    ;   |  +-------------------------------------------- [14] reserved
    ;   +----------------------------------------------- [15] reserved
    
RTC_INT          .set    0x1924        ; RTC Interrupt Control Register
    ; RTC_INT   Address:  0x1924 (IO space)              RTC Interrupt Control Register
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ; |15:14:13:12|11:10: 9: 8| 7: 6: 5: 4| 3: 2: 1: 0|  <<== Bit Position
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; |rw:r :r :r |r :r :r :r |r :r :rw:rw|rw:rw:rw:rw|  <<== Read / Write Access
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; | 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0|  <<== Reset Values
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-- [0]  MS_EVT     (1: Millisecond Event Interrupt Enabled; 0: Disabled)
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  +----- [1]  SEC_EVT    (1: Second Event Interrupt Enabled; 0: Disabled)
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  +-------- [2]  MIN_EVT    (1: Minute Event Interrupt Enabled; 0: Disabled)
    ;   |  |  |  |  |  |  |  |  |  |  |  |  +----------- [3]  HR_EVT     (1: Hour Event Interrupt Enabled; 0: Disabled)
    ;   |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  +-------------- [4]  DAY_EVT    (1: Day Event Interrupt Enabled; 0: Disabled)
    ;   |  |  |  |  |  |  |  |  |  |  +----------------- [5]  EXT_EVT    (1: External Event Interrupt Enabled; 0: Disabled)
    ;   |  |  |  |  |  |  |  |  |  +-------------------- [6]  reserved
    ;   |  |  |  |  |  |  |  |  +----------------------- [7]  reserved
    ;   |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  +-------------------------- [8]  reserved
    ;   |  |  |  |  |  |  +----------------------------- [9]  reserved
    ;   |  |  |  |  |  +-------------------------------- [10] reserved
    ;   |  |  |  |  +----------------------------------- [11] reserved
    ;   |  |  |  |
    ;   |  |  |  +-------------------------------------- [12] reserved
    ;   |  |  +----------------------------------------- [13] reserved
    ;   |  +-------------------------------------------- [14] reserved
    ;   +----------------------------------------------- [15] ALARM      (1: Alarm Event Interrupt Enabled; 0: Disabled)
    
RTC_COMP          .set    0x1928        ; RTC Oscillator Drift Compensation Register
    ; RTC_COMP   Address:  0x1928 (IO space)              RTC Oscillator Drift Compensation Register
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ; |15:14:13:12|11:10: 9: 8| 7: 6: 5: 4| 3: 2: 1: 0|  <<== Bit Position
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; |rw:r :r :rw|rw:rw:rw:rw|rw:rw:rw:rw|rw:rw:rw:rw|  <<== Read / Write Access
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; | 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0|  <<== Reset Values
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-- [0]  MS Compensation BCD 0, Compensation Hourly
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  +----- [1]  MS Compensation BCD 1, Compensation Hourly
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  +-------- [2]  MS Compensation BCD 2, Compensation Hourly
    ;   |  |  |  |  |  |  |  |  |  |  |  |  +----------- [3]  MS Compensation BCD 3, Compensation Hourly
    ;   |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  +-------------- [4]  MS Compensation BCD 4, Compensation Hourly
    ;   |  |  |  |  |  |  |  |  |  |  +----------------- [5]  MS Compensation BCD 5, Compensation Hourly
    ;   |  |  |  |  |  |  |  |  |  +-------------------- [6]  MS Compensation BCD 6, Compensation Hourly
    ;   |  |  |  |  |  |  |  |  +----------------------- [7]  MS Compensation BCD 7, Compensation Hourly
    ;   |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  +-------------------------- [8]  MS Compensation BCD 8, Compensation Hourly
    ;   |  |  |  |  |  |  +----------------------------- [9]  MS Compensation BCD 9, Compensation Hourly
    ;   |  |  |  |  |  +-------------------------------- [10] MS Compensation BCD 10, Compensation Hourly
    ;   |  |  |  |  +----------------------------------- [11] MS Compensation BCD 11, Compensation Hourly
    ;   |  |  |  |
    ;   |  |  |  +-------------------------------------- [12] MS Compensation BCD 12, Compensation Hourly
    ;   |  |  +----------------------------------------- [13] reserved
    ;   |  +-------------------------------------------- [14] reserved
    ;   +----------------------------------------------- [15] +/-  (1: Positive Compensation; 0: Negative Compensation)
RTC_OSC             .set    0x192c        ; RTC Oscillator Register
    ; RTC_OSC   Address:  0x192c (IO space)              RTC Oscillator Register
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ; |15:14:13:12|11:10: 9: 8| 7: 6: 5: 4| 3: 2: 1: 0|  <<== Bit Position
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; |rw:r :r :r |r :r :r :r |rw:rw:rw:rw|rw:rw:rw:rw|  <<== Read / Write Access
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; | 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0| 1: 0: 0: 0|  <<== Reset Values
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-- [0]  OscResistance[0]  (Oscillator Performance Control -
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  +----- [1]  OscResistance[1]   1000:Least Current Mode,
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  +-------- [2]  OscResistance[2]   1011:Fast Startup Mode,
    ;   |  |  |  |  |  |  |  |  |  |  |  |  +----------- [3]  OscResistance[3]   others:reserved)
    ;   |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  +-------------- [4]  OscPowerDown      (0:osc enabled, 1:osc disabled & bypass testmode (RTCXI->Y : tester can drive a high speed clock into RTCXI))
    ;   |  |  |  |  |  |  |  |  |  |  +----------------- [5]  reserved
    ;   |  |  |  |  |  |  |  |  |  +-------------------- [6]  reserved
    ;   |  |  |  |  |  |  |  |  +----------------------- [7]  reserved
    ;   |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  +-------------------------- [8]  reserved
    ;   |  |  |  |  |  |  +----------------------------- [9]  reserved
    ;   |  |  |  |  |  +-------------------------------- [10] reserved
    ;   |  |  |  |  +----------------------------------- [11] reserved
    ;   |  |  |  |
    ;   |  |  |  +-------------------------------------- [12] reserved
    ;   |  |  +----------------------------------------- [13] reserved
    ;   |  +-------------------------------------------- [14] reserved
    ;   +----------------------------------------------- [15] SWReset           (0:RTC not in reset, 1:RTC in reset)

RTC_LDORTCWAKE   .set    0x1930        ; RTC Power Management Control Register
RTC_PMGT         .set    0x1930        ; RTC Power Management Control Register
    ; RTC_PMGT   Address:  0x1930 (IO space)              RTC Power Management Control Register
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ; |15:14:13:12|11:10: 9: 8| 7: 6: 5: 4| 3: 2: 1: 0|  <<== Bit Position
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; | w:r :r :r |r :r :r :r |r :r :r :rw|rw:rw:rw:rw|  <<== Read / Write Access
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; | 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 1| 0: 0: 0: 0|  <<== Reset Values
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-- [0]  CLKOUTEN (1: rtc clock output is enabled; 0 disabled)
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  +----- [1]  LDO_PD   (1: LDO Powerdown)
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  +-------- [2]  BG_PD    (1: Bandgap Powerdown)
    ;   |  |  |  |  |  |  |  |  |  |  |  |  +----------- [3]  WU_DIR   (0: Wakeup pin is active high INPUT; 1: wakeup is an active low open-drain OUTPUT)
    ;   |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  +-------------- [4]  WU_DOUT  (0: Wakeup output pin is driven low; 1: wakeup pin is open drain output 'z')
    ;   |  |  |  |  |  |  |  |  |  |  +----------------- [5]  reserved
    ;   |  |  |  |  |  |  |  |  |  +-------------------- [6]  reserved
    ;   |  |  |  |  |  |  |  |  +----------------------- [7]  reserved
    ;   |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  +-------------------------- [8]  reserved
    ;   |  |  |  |  |  |  +----------------------------- [9]  reserved
    ;   |  |  |  |  |  +-------------------------------- [10] reserved
    ;   |  |  |  |  +----------------------------------- [11] reserved
    ;   |  |  |  |
    ;   |  |  |  +-------------------------------------- [12] reserved
    ;   |  |  +----------------------------------------- [13] reserved
    ;   |  +-------------------------------------------- [14] reserved
    ;   +----------------------------------------------- [15] reserved

RTC_SCRATCH0_LSW    .set    0x1960        ; RTC Scratch 0 Register
RTC_SCRATCH0_MSW    .set    0x1961        ; RTC Scratch 0 Register
RTC_SCRATCH1_LSW    .set    0x1964        ; RTC Scratch 1 Register
RTC_SCRATCH1_MSW    .set    0x1965        ; RTC Scratch 0 Register

;****************************************************************************************
;   RTC Control Macros
;   Pedro Gelabert
;   Sept 12, 2007
;****************************************************************************************
;----------------------------------------------------------------------------------------
;    RTC INT Register Bit Field Settings
;----------------------------------------------------------------------------------------
RTC_PER_INT_MSEC_EN     .set    1b<<0           ; RTC periodic interrupt millisecond enable
RTC_PER_INT_MSEC_DIS    .set    0b<<0           ; RTC periodic interrupt millisecond disable
RTC_PER_INT_SEC_EN      .set    1b<<1           ; RTC periodic interrupt seconds enable
RTC_PER_INT_SEC_DIS     .set    0b<<1           ; RTC periodic interrupt seconds disable
RTC_PER_INT_MIN_EN      .set    1b<<2           ; RTC periodic interrupt minutes enable
RTC_PER_INT_MIN_DIS     .set    0b<<2           ; RTC periodic interrupt minutes disable
RTC_PER_INT_HOUR_EN     .set    1b<<3           ; RTC periodic interrupt hours enable
RTC_PER_INT_HOUR_DIS    .set    0b<<3           ; RTC periodic interrupt hours disable
RTC_PER_INT_DAY_EN      .set    1b<<4           ; RTC periodic interrupt days enable
RTC_PER_INT_DAY_DIS     .set    0b<<4           ; RTC periodic interrupt days disable
RTC_EXT_INT_EN          .set    1b<<5           ; RTC external event interrupt enable
RTC_EXT_INT_DIS         .set    0b<<5           ; RTC external event interrupt disable
RTC_ALARM_INT_EN        .set    1b<<15          ; enable RTC alarm interrupt
RTC_ALARM_INT_DIS       .set    0b<<15          ; disable RTC alarm interrupt


;----------------------------------------------------------------------------------------
;    RTC LDORTCWAKE Register Bit Field Settings
;----------------------------------------------------------------------------------------
RTC_CLKOUT_DIS      .set    0b              ; RTC ClockOut is disabled
RTC_CLKOUT_EN       .set    1b              ; RTC ClockOut is enabled
PM_SHUTDOWN         .set    1b<<1           ; Shuts down Power Management
BG_SHUTDOWN         .set    1b<<2           ; Shuts down Bandgap
WAKEUP_DIR_OUT      .set    1b<<3           ; WAKEUP pin set as output
WAKEUP_DIR_IN       .set    0b<<3           ; WAKEUP pin set as output
WAKEUP_DATAOUT      .set    1b<<4           ; Wakeup Dataout is open drain

;****************************************************************************************
;        I2S Register Addresses
;****************************************************************************************
I2S_S0CR_LSW        .set    0x2800    ; I2S Serializer 0 Control Register
I2S_S0CR_MSW        .set    0x2801    ; I2S Serializer 0 Control Register
I2S_SRGR0           .set    0x2804    ; I2S Sample Rate Generator 0 Register

I2S_TXW0_LSW        .set    0x2808    ; I2S Transmit Word 0 Register
I2S_TXW0_MSW        .set    0x2809    ; I2S Transmit Word 0 Register
I2S_TXW1_LSW        .set    0x280C    ; I2S Transmit Word 1 Register
I2S_TXW1_MSW        .set    0x280D    ; I2S Transmit Word 1 Register

I2S_RXW0_LSW        .set    0x2828    ; I2S Receive Word 0 Register
I2S_RXW0_MSW        .set    0x2829    ; I2S Receive Word 0 Register
I2S_RXW1_LSW        .set    0x282C    ; I2S Receive Word 1 Register
I2S_RXW1_MSW        .set    0x282D    ; I2S Receive Word 1 Register

I2S_IR              .set    0x2810    ; I2S Interrupt Register
I2S_IMCR            .set    0x2814    ; I2S Interrupt CPU Mask Register
; Definitions above should be removed





    ; I2S0_SRGR   Address:  0x2804                           I2S_0 Interrupt Mask Register
    ; I2S1_SRGR   Address:  0x2904                           I2S_1 Interrupt Mask Register
    ; I2S2_SRGR   Address:  0x2A04                           I2S_2 Interrupt Mask Register
    ; I2S3_SRGR   Address:  0x2B04                           I2S_3 Interrupt Mask Register
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ; |15:14:13:12|11:10: 9: 8| 7: 6: 5: 4| 3: 2: 1: 0|  <<== Bit Position
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; |r :r :r :r |r :r :r :r |r :r :rw:rw|rw:rw:rw:rw|  <<== Read / Write Access
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; | 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0|  <<== Reset Values
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-- [0]  ClockDiv[0]   (F_bclk = F_sysclk / div_factor ;
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  +----- [1]  ClockDiv[1]    000:divby8,   001:divby16, 010:divby32, 011:divby64,
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  +-------- [2]  ClockDiv[2]    100:divby128, 101:divby256, others:reserved)
    ;   |  |  |  |  |  |  |  |  |  |  |  |  +----------- [3]  FSDiv[0]      (F_fs = F_bclk / div_factor ;
    ;   |  |  |  |  |  |  |  |  |  |  |  |                                   000: divby2,  001: divby4,  010: divby8,   011: divby16,
    ;   |  |  |  |  |  |  |  |  |  |  |  +-------------- [4]  FSDiv[1]       100: divby32, 101: divby64, 110: divby128, 111: divby256)
    ;   |  |  |  |  |  |  |  |  |  |  +----------------- [5]  FSDiv[2]
    ;   |  |  |  |  |  |  |  |  |  +-------------------- [6]  reserved
    ;   |  |  |  |  |  |  |  |  +----------------------- [7]  reserved
    ;   |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  +-------------------------- [8]  reserved
    ;   |  |  |  |  |  |  +----------------------------- [9]  reserved
    ;   |  |  |  |  |  +-------------------------------- [10] reserved
    ;   |  |  |  |  +----------------------------------- [11] reserved
    ;   |  |  |  |
    ;   |  |  |  +-------------------------------------- [12] reserved
    ;   |  |  +----------------------------------------- [13] reserved
    ;   |  +-------------------------------------------- [14] reserved
    ;   +----------------------------------------------- [15] reserved

    ; I2S0_IMCR   Address:  0x2814                           I2S_0 Interrupt Mask Register
    ; I2S1_IMCR   Address:  0x2914                           I2S_1 Interrupt Mask Register
    ; I2S2_IMCR   Address:  0x2A14                           I2S_2 Interrupt Mask Register
    ; I2S3_IMCR   Address:  0x2B14                           I2S_3 Interrupt Mask Register
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ; |15:14:13:12|11:10: 9: 8| 7: 6: 5: 4| 3: 2: 1: 0|  <<== Bit Position
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; |r :r :r :r |r :r :r :r |r :r :rw:rw|rw:rw:rw:rw|  <<== Read / Write Access
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; | 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0|  <<== Reset Values
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |        (1:enables the interrupt, 0:disables the interrupt)
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-- [0]  OUErr
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  +----- [1]  FErr
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  +-------- [2]  Rcv Mono
    ;   |  |  |  |  |  |  |  |  |  |  |  |  +----------- [3]  Rcv Stereo
    ;   |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  +-------------- [4]  Xmit Mono
    ;   |  |  |  |  |  |  |  |  |  |  +----------------- [5]  Xmit Stereo
    ;   |  |  |  |  |  |  |  |  |  +-------------------- [6]  reserved
    ;   |  |  |  |  |  |  |  |  +----------------------- [7]  reserved
    ;   |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  +-------------------------- [8]  reserved
    ;   |  |  |  |  |  |  +----------------------------- [9]  reserved
    ;   |  |  |  |  |  +-------------------------------- [10] reserved
    ;   |  |  |  |  +----------------------------------- [11] reserved
    ;   |  |  |  |
    ;   |  |  |  +-------------------------------------- [12] reserved
    ;   |  |  +----------------------------------------- [13] reserved
    ;   |  +-------------------------------------------- [14] reserved
    ;   +----------------------------------------------- [15] reserved

    ; I2S0_CR_LSW   Address:  0x2800                          I2S_0 Control Register
    ; I2S1_CR_LSW   Address:  0x2900                          I2S_1 Control Register
    ; I2S2_CR_LSW   Address:  0x2A00                          I2S_2 Control Register
    ; I2S3_CR_LSW   Address:  0x2B00                          I2S_3 Control Register
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ; |15:14:13:12|11:10: 9: 8| 7: 6: 5: 4| 3: 2: 1: 0|  <<== Bit Position
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; |r :r :r :r |r :r :r :r |r :r :rw:rw|rw:rw:rw:rw|  <<== Read / Write Access
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; | 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0|  <<== Reset Values
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-- [0]  Format        (0:I2S/left-just mode, 1:DSP Format)
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  +----- [1]  Mode          (0:slave mode, 1:master mode)
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  +-------- [2]  WordLen[0]    (0000:8bit,  0001:10bit, 0010:12bit, 0011:14bit,
    ;   |  |  |  |  |  |  |  |  |  |  |  |  +----------- [3]  WordLen[1]     0100:16bit, 0101:18bit, 0110:20bit, 0111:24bit,
    ;   |  |  |  |  |  |  |  |  |  |  |  |                                   1000:32bit, others:reserved)
    ;   |  |  |  |  |  |  |  |  |  |  |  +-------------- [4]  WordLen[2]
    ;   |  |  |  |  |  |  |  |  |  |  +----------------- [5]  WordLen[3]
    ;   |  |  |  |  |  |  |  |  |  +-------------------- [6]  SignExtend    (0:disabled, 1:enabled)
    ;   |  |  |  |  |  |  |  |  +----------------------- [7]  Pack          (0:disabled, 1:enabled)
    ;   |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  +-------------------------- [8]  DataDelay     (0:1bit delay, 1:2bit delay)
    ;   |  |  |  |  |  |  +----------------------------- [9]  ClkPol        (0:rcv on rising edge, xmit on falling edge, 1:opposite)
    ;   |  |  |  |  |  +-------------------------------- [10] FSPol         (0:Normal FS_low==>left_ch, 1:inverted)
    ;   |  |  |  |  +----------------------------------- [11] Loopback      (0:Normal mode, 1:Loopback mode)
    ;   |  |  |  |
    ;   |  |  |  +-------------------------------------- [12] Mono          (0:Stereo Operation, 1:Mono)
    ;   |  |  +----------------------------------------- [13] reserved
    ;   |  +-------------------------------------------- [14] reserved
    ;   +----------------------------------------------- [15] Enable        (0:disabled, 1:enabled)

;****************************************************************************************
;        I2S0
;****************************************************************************************
I2S0_CR_LSW         .set    0x2800    ; I2S0 Control Register
I2S0_CR_MSW         .set    0x2801    ; I2S0 Control Register
I2S0_SRGR           .set    0x2804    ; I2S0 Sample Rate Generator Register

I2S0_TXW0_LSW       .set    0x2808    ; I2S0 Transmit Word 0 Register
I2S0_TXW0_MSW       .set    0x2809    ; I2S0 Transmit Word 0 Register
I2S0_TXW1_LSW       .set    0x280C    ; I2S0 Transmit Word 1 Register
I2S0_TXW1_MSW       .set    0x280D    ; I2S0 Transmit Word 1 Register

I2S0_RXW0_LSW       .set    0x2828    ; I2S0 Receive Word 0 Register
I2S0_RXW0_MSW       .set    0x2829    ; I2S0 Receive Word 0 Register
I2S0_RXW1_LSW       .set    0x282C    ; I2S0 Receive Word 1 Register
I2S0_RXW1_MSW       .set    0x282D    ; I2S0 Receive Word 1 Register

I2S0_IR             .set    0x2810    ; I2S0 Interrupt Register
I2S0_IMCR           .set    0x2814    ; I2S0 Interrupt CPU Mask Register
;****************************************************************************************
;        I2S1
;****************************************************************************************
I2S1_CR_LSW         .set    0x2900    ; I2S1 Control Register
I2S1_CR_MSW         .set    0x2901    ; I2S1 Control Register
I2S1_SRGR           .set    0x2904    ; I2S1 Sample Rate Generator Register

I2S1_TXW0_LSW       .set    0x2908    ; I2S1 Transmit Word 0 Register
I2S1_TXW0_MSW       .set    0x2909    ; I2S1 Transmit Word 0 Register
I2S1_TXW1_LSW       .set    0x290C    ; I2S1 Transmit Word 1 Register
I2S1_TXW1_MSW       .set    0x290D    ; I2S1 Transmit Word 1 Register

I2S1_RXW0_LSW       .set    0x2928    ; I2S1 Receive Word 0 Register
I2S1_RXW0_MSW       .set    0x2929    ; I2S1 Receive Word 0 Register
I2S1_RXW1_LSW       .set    0x292C    ; I2S1 Receive Word 1 Register
I2S1_RXW1_MSW       .set    0x292D    ; I2S1 Receive Word 1 Register

I2S1_IR             .set    0x2910    ; I2S1 Interrupt Register
I2S1_IMCR           .set    0x2914    ; I2S1 Interrupt CPU Mask Register
;****************************************************************************************
;        I2S2
;****************************************************************************************
I2S2_CR_LSW         .set    0x2A00    ; I2S2 Control Register
I2S2_CR_MSW         .set    0x2A01    ; I2S2 Control Register
I2S2_SRGR           .set    0x2A04    ; I2S2 Sample Rate Generator Register

I2S2_TXW0_LSW       .set    0x2A08    ; I2S2 Transmit Word 0 Register
I2S2_TXW0_MSW       .set    0x2A09    ; I2S2 Transmit Word 0 Register
I2S2_TXW1_LSW       .set    0x2A0C    ; I2S2 Transmit Word 1 Register
I2S2_TXW1_MSW       .set    0x2A0D    ; I2S2 Transmit Word 1 Register

I2S2_RXW0_LSW       .set    0x2A28    ; I2S2 Receive Word 0 Register
I2S2_RXW0_MSW       .set    0x2A29    ; I2S2 Receive Word 0 Register
I2S2_RXW1_LSW       .set    0x2A2C    ; I2S2 Receive Word 1 Register
I2S2_RXW1_MSW       .set    0x2A2D    ; I2S2 Receive Word 1 Register

I2S2_IR             .set    0x2A10    ; I2S2 Interrupt Register
I2S2_IMCR           .set    0x2A14    ; I2S2 Interrupt CPU Mask Register
;****************************************************************************************
;        I2S3
;****************************************************************************************
I2S3_CR_LSW         .set    0x2B00    ; I2S3 Control Register
I2S3_CR_MSW         .set    0x2B01    ; I2S3 Control Register
I2S3_SRGR           .set    0x2B04    ; I2S3 Sample Rate Generator Register

I2S3_TXW0_LSW       .set    0x2B08    ; I2S3 Transmit Word 0 Register
I2S3_TXW0_MSW       .set    0x2B09    ; I2S3 Transmit Word 0 Register
I2S3_TXW1_LSW       .set    0x2B0C    ; I2S3 Transmit Word 1 Register
I2S3_TXW1_MSW       .set    0x2B0D    ; I2S3 Transmit Word 1 Register

I2S3_RXW0_LSW       .set    0x2B28    ; I2S3 Receive Word 0 Register
I2S3_RXW0_MSW       .set    0x2B29    ; I2S3 Receive Word 0 Register
I2S3_RXW1_LSW       .set    0x2B2C    ; I2S3 Receive Word 1 Register
I2S3_RXW1_MSW       .set    0x2B2D    ; I2S3 Receive Word 1 Register

I2S3_IR             .set    0x2B10    ; I2S3 Interrupt Register
I2S3_IMCR           .set    0x2B14    ; I2S3 Interrupt CPU Mask Register

;        I2S Register Addresses for Test Chip

I2S_S0W0_LSW        .set    0x2808    ; I2S Serializer 0 Word 0 Register
I2S_S0W0_MSW        .set    0x2809    ; I2S Serializer 0 Word 0 Register
I2S_S0W1_LSW        .set    0x280C    ; I2S Serializer 0 Word 1 Register
I2S_S0W1_MSW        .set    0x280D    ; I2S Serializer 0 Word 1 Register

I2S_S1W0_LSW        .set    0x2828    ; I2S Serializer 1 Word 0 Register
I2S_S1W0_MSW        .set    0x2829    ; I2S Serializer 1 Word 0 Register
I2S_S1W1_LSW        .set    0x282C    ; I2S Serializer 1 Word 1 Register
I2S_S1W1_MSW        .set    0x282D    ; I2S Serializer 1 Word 1 Register

I2S_S1CR_LSW        .set    0x2820    ; I2S Serializer 1 Control Register
I2S_S1CR_MSW        .set    0x2821    ; I2S Serializer 1 Control Register
I2S_SRGR1           .set    0x2824    ; I2S Sample Rate Generator 1 Register

I2S_S2CR_LSW        .set    0x2840    ; I2S Serializer 2 Control Register
I2S_S2CR_MSW        .set    0x2841    ; I2S Serializer 2 Control Register
I2S_SRGR2           .set    0x2844    ; I2S Sample Rate Generator 2 Register
I2S_S2W0_LSW        .set    0x2848    ; I2S Serializer 2 Word 0 Register
I2S_S2W0_MSW        .set    0x2849    ; I2S Serializer 2 Word 0 Register
I2S_S2W1_LSW        .set    0x284C    ; I2S Serializer 2 Word 1 Register
I2S_S2W1_MSW        .set    0x284D    ; I2S Serializer 2 Word 1 Register

I2S_S3CR_LSW        .set    0x2860    ; I2S Serializer 3 Control Register
I2S_S3CR_MSW        .set    0x2861    ; I2S Serializer 3 Control Register
I2S_SRGR3           .set    0x2864    ; I2S Sample Rate Generator 3 Register
I2S_S3W0_LSW        .set    0x2868    ; I2S Serializer 3 Word 0 Register
I2S_S3W0_MSW        .set    0x2869    ; I2S Serializer 3 Word 0 Register
I2S_S3W1_LSW        .set    0x286C    ; I2S Serializer 3 Word 1 Register
I2S_S3W1_MSW        .set    0x286D    ; I2S Serializer 3 Word 1 Register

;****************************************************************************************
;    I2S Control Macros added by Manel Ranmuthu
;    Date        : 28 April 2005
;    Updates        : Updated to match changes to I2S spec. (default CR settings
;            and changes to the clock dividers
;              13 May 2005    Manel R.
;****************************************************************************************
;----------------------------------------------------------------------------------------
;    Serializer Control Register Bit Field Settings
;----------------------------------------------------------------------------------------
ENABLE          .set    1b<<15         ; Enable Serializer
ENABLE_NOT      .set    0b<<15         ; Disable Serializer
MONO            .set    1b<<12         ; Mono
STEREO          .set    0b<<12         ; Stereo
LOOPBACK        .set    1b<<11         ; Enable loopback
REV_FS_POL      .set    1b<<10         ; FS pulse is active high (DSP), Low for left and high for right (LJ) 
DEF_FS_POL      .set    0b<<10         ; FS pulse is active low (DSP), High for left and low for right (LJ)
REV_CLK_POL     .set    1b<<9          ; TX on rising edge & RX on Falling 
DEF_CLK_POL     .set    0b<<9          ; TX on falling edge & RX on Rising (Default - typical I2S)
DELAY_2B        .set    1b<<8          ; 2 bit delay (default is 1 bit)
DELAY_1B        .set    0b<<8          ; 1 bit delay (default)
PACK            .set    1b<<7          ; Enable Pack Mode
NOPACK          .set    0b<<7          ; Disable Pack Mode
SIGNEXTEND      .set    1b<<6          ; Sign Extend
NOSIGNEXTEND    .set    0b<<6          ; Disable Sign Extend
BITS8           .set    0000b<<2       ; Wordlength = 8 bits (default is 8 bits)
BITS10          .set    0001b<<2       ; Wordlength = 10 bits
BITS12          .set    0010b<<2       ; Wordlength = 12 bits
BITS14          .set    0011b<<2       ; Wordlength = 14 bits
BITS16          .set    0100b<<2       ; Wordlength = 16 bits
BITS18          .set    0101b<<2       ; Wordlength = 18 bits
BITS20          .set    0110b<<2       ; Wordlength = 20 bits
BITS24          .set    0111b<<2       ; Wordlength = 24 bits
BITS32          .set    1000b<<2       ; Wordlength = 32 bits
MASTER_MODE     .set    1b<<1          ; Serializer outputs Clock & FS (default is Slave mode)
SLAVE_MODE      .set    0b<<1          ; Serializer outputs Clock & FS (default)
DSP_FORMAT      .set    1b<<0          ; DSP Format (default is LJ mode)
LJ_FORMAT       .set    0b<<0          ; Left-justified Format (default)
;----------------------------------------------------------------------------------------
;    Sample Rate Generator Register Bit Field Settings
;    Bit-clock rate (SCLK or BCLK) = System_Clock/CLKDIVx Hz
;    Frame_Sync-clock (FSync) = SCLK/FSDIVx Hz
;    FSDIVx should be chosen such that :
;            SCLK/FSYNC >= I2S_Data_Wordlength for mono in DSP format or
;            SCLK/FSYNC >= 2*I2S_Data_Wordlength for mono in LJ format or
;            SCLK/FSYNC >= 2*I2S_Data_Wordlength for Stereo in LJ or DSP format
;----------------------------------------------------------------------------------------
FSDIV4          .set    000b<<3        ; Gives frame-sync signal; divides bit-clock by 8    (8+DataDelay    bit-clocks per frame)
FSDIV8          .set    001b<<3        ; Gives frame-sync signal; divides bit-clock by 16   (16+DataDelay   bit-clocks per frame)
FSDIV16         .set    010b<<3        ; Gives frame-sync signal; divides bit-clock by 32   (32+DataDelay   bit-clocks per frame)
FSDIV32         .set    011b<<3        ; Gives frame-sync signal; divides bit-clock by 64   (64+DataDelay   bit-clocks per frame)
FSDIV64         .set    100b<<3        ; Gives frame-sync signal; divides bit-clock by 128  (128+DataDelay  bit-clocks per frame)
FSDIV128        .set    101b<<3        ; Gives frame-sync signal; divides bit-clock by 256  (256+DataDelay  bit-clocks per frame)
FSDIV256        .set    110b<<3        ; Gives frame-sync signal; divides bit-clock by 512  (512+DataDelay  bit-clocks per frame)
FSDIV512        .set    111b<<3        ; Gives frame-sync signal; divides bit-clock by 1024 (1024+DataDelay bit-clocks per frame)

CLKDIV2         .set    000b<<0        ; BCLK - Divides system clock by 2
CLKDIV4         .set    001b<<0        ; BCLK Divides system clock by 4
CLKDIV8         .set    010b<<0        ; BCLK Divides system clock by 8
CLKDIV16        .set    011b<<0        ; BCLK Divides system clock by 16
CLKDIV32        .set    100b<<0        ; BCLK Divides system clock by 32
CLKDIV64        .set    101b<<0        ; BCLK Divides system clock by 64
CLKDIV128       .set    110b<<0        ; BCLK Divides system clock by 128
CLKDIV256       .set    111b<<0        ; BCLK Divides system clock by 256
;----------------------------------------------------------------------------------------
;    Interrupt Control Mask Bit Field Settings
;----------------------------------------------------------------------------------------
XMT_R_INT       .set    1b<<5        ; Enable Right transmit data interrupt
XMT_L_INT       .set    1b<<4        ; Enable Left transmit data interrupt
RCV_R_INT       .set    1b<<3        ; Enable Right receive data interrupt
RCV_L_INT       .set    1b<<2        ; Enable Left receive data interrupt
ERR_INT         .set    1b<<1        ; Enable Frame error condition interrupt
OU_INT          .set    1b<<0        ; Enable underrun/overrun error interrupt


;****************************************************************************************
;        SPI Register Addresses
;****************************************************************************************
SPI_CLKDIV          .set    0x3000    ; SPI Clock Divider Register
SPI_CLKCTR          .set    0x3001    ; SPI Clock Control Register
SPI_DEVCS10         .set    0x3002    ; SPI External Device Setup Register for Chip Select 0 and 1
SPI_DEVCS32         .set    0x3003    ; SPI External Device Setup Register for Chip Select 2 and 3
SPI_CMD1            .set    0x3004    ; SPI Command 1 Register
SPI_CMD2            .set    0x3005    ; SPI Command 2 Register
SPI_STAT1           .set    0x3006    ; SPI Status 1 Register
SPI_STAT2           .set    0x3007    ; SPI Status 2 Register
SPI_DAT1            .set    0x3008    ; SPI Data 1 Register
SPI_DAT2            .set    0x3009    ; SPI Data 2 Register

;----------------------------------------------------------------------------------------
;    SPI Bit Field Settings
;----------------------------------------------------------------------------------------

SPIWRITE            .set    10b         ; Write command
SPIREAD             .set    01b         ; Read command
SPILOOP             .set    1b<<15      ; loopback enabled
SPICS0              .set    00b<<12     ; CS0 transfer
SPICS1              .set    01b<<12     ; CS1 transfer
SPICS2              .set    10b<<12     ; CS2 transfer
SPICS3              .set    11b<<12     ; CS3 transfer


;****************************************************************************************
;        I2C Register Addresses DA202
;****************************************************************************************
I2C_SLAVE           .set    0x3c00    ; I2C Slave Address Register
I2C_WRITED          .set    0x3c02    ; I2C Write Data Register
I2C_CONF            .set    0x3c04    ; I2C Configuration Register
I2C_READD           .set    0x3c06    ; I2C Read Data Register
I2C_CLKDIV          .set    0x3c08    ; I2C Clock Divider Register


;****************************************************************************************
;        I2C Register Addresses DA224
;****************************************************************************************
I2C_OAR             .set    0x1A00        ; I2C Own Address Register [9:0]
I2C_IMR             .set    0x1A04        ; I2C Interrupt Mask/Status Register [6:0]
I2C_STR             .set    0x1A08        ; I2C Interrupt Status Register [14:0]
I2C_CLKL            .set    0x1A0C        ; I2C Clock Divider Low Register [15:0]
                                          ;   SCL LOW = (I2C CLK) * (ICLKL + 5)
I2C_CLKH            .set    0x1A10        ; I2C Clock Divider High Register [15:0]
                                          ;   SCL HIGH = (I2C CLK) * (ICLKH + 5)
I2C_CNT             .set    0x1A14        ; I2C Data Count Register [15:0]
I2C_DRR             .set    0x1A18        ; READ-ONLY   I2C Data Recieve Register [7:0]
I2C_SAR             .set    0x1A1C        ; I2C Slave Address Register [9:0]

I2C_DXR             .set    0x1A20        ; I2C Data Transmit Register [7:0]
I2C_MDR             .set    0x1A24        ; I2C Mode Register [15:0]
I2C_IVR             .set    0x1A28        ; I2C Interrupt Vector Register [11:0]
I2C_EMDR            .set    0x1A2C        ; I2C Extended Mode Register [1:0]
I2C_PSC             .set    0x1A30        ; I2C Prescaler Register [7:0]
                                          ;   I2C CLK = (VBUS CLK) / (PSC + 1)
I2C_PID1            .set    0x1A34        ; READ-ONLY   I2C Pheripheral ID 1 Register [15:0]
I2C_PID2            .set    0x1A38        ; READ-ONLY   I2C Pheripheral ID 2 Register [7:0]
I2C_DMAC            .set    0x1A3C        ; I2C DMA Control Register [1:0]

I2C_PFUNC           .set    0x1A48        ; I2C Pin Function Register [0:0]
I2C_PDIR            .set    0x1A4C        ; I2C Pin Direction Register [1:0]
I2C_PDIN            .set    0x1A50        ; READ-ONLY   I2C Pin Data In Register [1:0]
I2C_PDOUT           .set    0x1A54        ; I2C Pin Data Out Register [1:0]
I2C_PDSET           .set    0x1A58        ; I2C Pin Data Set Register [1:0]
I2C_PDCLR           .set    0x1A5C        ; I2C Pin Data Clear Register [1:0]
I2C_PDRV            .set    0x1A60        ; I2C Pin Driver Mode Register [1:0]
I2C_PPDIS           .set    0x1A64        ; I2C Pin Pull Disable Register [1:0]
I2C_PPSEL           .set    0x1A68        ; I2C Pin Pull Select Register [1:0]
I2C_PSRS            .set    0x1A6C        ; I2C Pin Slew Rate Register [1:0]

ICNACK_FLAG     .set 0002h
ICRRDY_FLAG     .set 0008h
ICXRDY_FLAG     .set 0010h
ICSCD_FLAG      .set 0020h
ICBB_FLAG       .set 1000h

;****************************************************************************************
;        UART Register Addresses
;****************************************************************************************
UART_RBR            .set    0x1B00        ; Read - UART Receive Buffer Register
UART_THR            .set    0x1B00        ; Write - UART Transmit Holding Register
UART_IER            .set    0x1B02        ; UART Interrupt Enable Register
UART_IIR            .set    0x1B04        ; UART Interrupt Identification Register (when reading)
UART_FCR            .set    0x1B04        ; UART FIFO Control Register (when writing)
UART_LCR            .set    0x1B06        ; UART Line Control Register
UART_MCR            .set    0x1B08        ; UART Modem Control Register
UART_LSR            .set    0x1B0A        ; UART Line Status Register
UART_MSR            .set    0x1B0C        ; UART Mode Status Register
UART_SCR            .set    0x1B0E        ; UART Scratch Register
UART_DLL            .set    0x1B10        ; UART Divisor Latch LSB Register
UART_DLH            .set    0x1B12        ; UART Divisor Latch MSB Register
UART_PID1           .set    0x1B14        ; UART Peripheral ID 1 Register
UART_PID2           .set    0x1B16        ; UART Peripheral ID 1 Register
UART_PWREMU         .set    0x1B18        ; UART Power Mangement and Emulation Register

;****************************************************************************************
;   UART Control Macros
;   Frank Livingston
;   11 November 2006
;****************************************************************************************
;----------------------------------------------------------------------------------------
;    UART_IER Bit Field Settings
;----------------------------------------------------------------------------------------
UART_RXDATA_INT_DSBL    .set    0b<<0       ; disable receive data available interrupt
UART_RXDATA_INT_ENBL    .set    1b<<0       ; enable receive data available interrupt
UART_TXDATA_INT_DSBL    .set    0b<<1       ; disable transmit holding register empty interrupt
UART_TXDATA_INT_ENBL    .set    1b<<1       ; enable transmit holding register empty interrupt
UART_RXLS_INT_DSBL      .set    0b<<2       ; disable receiver line status interrupt
UART_RXLS_INT_ENBL      .set    1b<<2       ; enable receiver line status interrupt
UART_MS_INT_DSBL        .set    0b<<3       ; disable modem status interrupt
UART_MS_INT_ENBL        .set    1b<<3       ; enable modem status interrupt

;----------------------------------------------------------------------------------------
;    UART_IIR Bit Field Settings
;----------------------------------------------------------------------------------------
UART_IID_NONE           .set    0001b<<0    ; interrupt Id for no interrupt
UART_IID_RXLS           .set    0110b<<0    ; interrupt Id for receiver line status
UART_IID_RXDATA         .set    0100b<<0    ; interrupt Id for receiver data available
UART_IID_TIMEOUT        .set    1100b<<0    ; interrupt Id for character time-out indication
UART_IID_TXDATA         .set    0010b<<0    ; interrupt Id for transmitter holding register empty
UART_IID_MS             .set    0000b<<0    ; interrupt Id for modem status

;----------------------------------------------------------------------------------------
;    UART_FCR Bit Field Settings
;----------------------------------------------------------------------------------------
UART_FIFO_DSBL          .set    0b<<0       ; disable FIFO
UART_FIFO_ENBL          .set    1b<<0       ; enable FIFO
UART_RXFIFO_RST         .set    1b<<1       ; reset receiver FIFO
UART_TXFIFO_RST         .set    1b<<2       ; reset transmitter FIFO
UART_DMA_MODE_DSBL      .set    0b<<3       ; disable DMA mode
UART_DMA_MODE_ENBL      .set    1b<<3       ; enable DMA mode
UART_RXFIFO_TRIG_1B     .set    00b<<6      ; set receive FIFO trigger level to 1 byte
UART_RXFIFO_TRIG_4B     .set    01b<<6      ; set receive FIFO trigger level to 4 bytes
UART_RXFIFO_TRIG_8B     .set    10b<<6      ; set receive FIFO trigger level to 8 bytes
UART_RXFIFO_TRIG_14B    .set    11b<<6      ; set receive FIFO trigger level to 14 bytes

;----------------------------------------------------------------------------------------
;    UART_LCR Bit Field Settings
;----------------------------------------------------------------------------------------
UART_WORDLEN_5          .set    00b<<0  ; 5 bits per word
UART_WORDLEN_6          .set    01b<<0  ; 6 bits per word
UART_WORDLEN_7          .set    10b<<0  ; 7 bits per word
UART_WORDLEN_8          .set    11b<<0  ; 8 bits per word
UART_NUM_STOP_BITS_EQ1  .set    0b<<2   ; one stop bit per word
UART_NUM_STOP_BITS_GT1  .set    1b<<2   ; word length determines number of stop bits: (5 => 1.5; 6, 7 & 8 => 2)
UART_PARITY_DSBL        .set    0b<<3   ; disable parity bit
UART_PARITY_ENBL        .set    1b<<3   ; enable parity bit
UART_EVEN_PARITY_DSBL   .set    0b<<4   ; even parity disable
UART_EVEN_PARITY_ENBL   .set    1b<<4   ; even parity enable
UART_STICK_PARITY_DSBL  .set    0b<<5   ; stick parity disable
UART_STICK_PARITY_ENBL  .set    1b<<5   ; stick parity disable
UART_TX_BREAK_CTRL      .set    1b<<6   ; transmit break control
UART_DL_ACCESS_DSBL     .set    0b<<7   ; disable access to divisor latch
UART_DL_ACCESS_ENBL     .set    1b<<7   ; enable acesss to divisor latch

;----------------------------------------------------------------------------------------
;    UART_MCR Bit Field Settings
;----------------------------------------------------------------------------------------
UART_RTS_ASSERT         .set    1b<<1   ; assert RTS
UART_LOOP_DSBL          .set    0b<<4   ; disable loopback
UART_LOOP_ENBL          .set    1b<<4   ; enable loopback
UART_AF_DSBL            .set    0b<<5   ; autoflow disable
UART_AF_ENBL            .set    1b<<5   ; autoflow enable

;----------------------------------------------------------------------------------------
;    UART_MCR Bit Field Settings
;----------------------------------------------------------------------------------------
UART_PE_ERR             .set    1b<<2   ; parity error
UART_FE_ERR             .set    1b<<3   ; framing error
UART_BI_ERR             .set    1b<<4   ; break error

;----------------------------------------------------------------------------------------
;    UART_PWREMU Bit Field Settings
;----------------------------------------------------------------------------------------
UART_FREE_DSBL          .set    0b<<0   ; disable free mode
UART_FREE_ENBL          .set    1b<<0   ; enable free mode
UART_SOFT_DSBL          .set    0b<<1   ; disable soft mode
UART_SOFT_ENBL          .set    1b<<1   ; enable soft mode
UART_RST                .set    0b<<15  ; reset UART
UART_ENBL               .set    1b<<15  ; enable UART






;****************************************************************************************
;        ANA_REG Registers          (0x7002 - 0x70FF)
;****************************************************************************************
TRIM_FROM_EFUSE         .set    0x7002
    ; TRIM_FROM_EFUSE   Address:  0x7002 (IO space)       Read-Only Trim Value from Efuse
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ; |15:14:13:12|11:10: 9: 8| 7: 6: 5: 4| 3: 2: 1: 0|  <<== Bit Position
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; |r :r :r :r |r :r :r :r |r :r :r :r |r :r :r :r |  <<== Read / Write Access
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; | ?: ?: ?: ?| ?: ?: ?: ?| ?: ?: ?: ?| ?: ?: ?: ?|  <<== Reset Values
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-- [0]  Efuse_Bandgap_Trim[0]       (read-only value from the efuse bits.  Will always read 0000 prior
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  +----- [1]  Efuse_Bandgap_Trim[1]        to the fuses being blown.)
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  +-------- [2]  Efuse_Bandgap_Trim[2]
    ;   |  |  |  |  |  |  |  |  |  |  |  |  +----------- [3]  Efuse_Bandgap_Trim[3]
    ;   |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  +-------------- [4]  Efuse_CurrentRef_Trim[0]
    ;   |  |  |  |  |  |  |  |  |  |  +----------------- [5]  Efuse_CurrentRef_Trim[1]
    ;   |  |  |  |  |  |  |  |  |  +-------------------- [6]  Efuse_CurrentRef_Trim[2]
    ;   |  |  |  |  |  |  |  |  +----------------------- [7]  Efuse_CurrentRef_Trim[3]
    ;   |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  +-------------------------- [8]  reserved
    ;   |  |  |  |  |  |  +----------------------------- [9]  reserved
    ;   |  |  |  |  |  +-------------------------------- [10] reserved
    ;   |  |  |  |  +----------------------------------- [11] reserved
    ;   |  |  |  |
    ;   |  |  |  +-------------------------------------- [12] reserved
    ;   |  |  +----------------------------------------- [13] reserved
    ;   |  +-------------------------------------------- [14] reserved
    ;   +----------------------------------------------- [15] reserved

SET_REF_TRIM        .set    0x7003
    ; SET_REF_TRIM   Address:  0x7003 (IO space)             Analog Reference Trim Register
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ; |15:14:13:12|11:10: 9: 8| 7: 6: 5: 4| 3: 2: 1: 0|  <<== Bit Position
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; |rw:rw:r :r |r :rw:rw:rw|rw:rw:rw:rw|rw:rw:rw:rw|  <<== Read / Write Access
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; | 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0|  <<== Reset Values
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+       **** This register must be unlocked via the TEST_LOCK register to enable writes. ****
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |        In production test, the Bandgap voltage reference should be trimmed 
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |        to 0.7v +- 44mV.  Current Reference should be trimmed to 4uA +- 70nA.
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-- [0]  Bandgap_Trim[0]         [0000, 0001, 0010, ... 0111 = (0, 1, 2, ... 7) * BG_StepSize,
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  +----- [1]  Bandgap_Trim[1]          1000, 1001, 1010, ... 1111 = (-8, -7, -6, ... -1) * BG_StepSize]
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  +-------- [2]  Bandgap_Trim[2]
    ;   |  |  |  |  |  |  |  |  |  |  |  |  +----------- [3]  Bandgap_Trim[3]         (BG_StepSize =~ 40mV)
    ;   |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  +-------------- [4]  CurrentRef_Trim[0]      [0000, 0001, 0010, ... 0111 = (0, 1, 2, ... 7) * CR_StepSize,
    ;   |  |  |  |  |  |  |  |  |  |  +----------------- [5]  CurrentRef_Trim[1]       1000, 1001, 1010, ... 1111 = (-8, -7, -6, ... -1) * CR_StepSize]
    ;   |  |  |  |  |  |  |  |  |  +-------------------- [6]  CurrentRef_Trim[2]
    ;   |  |  |  |  |  |  |  |  +----------------------- [7]  CurrentRef_Trim[3]      (CR_StepSize =~ 70nA)
    ;   |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  +-------------------------- [8]  analog_testmode_sel[0]  [Enables transmission gates from various analog testpoints to the GPAIN3 pin.  In many cases it is also necessary to enable the testpoint in another register.
    ;   |  |  |  |  |  |  +----------------------------- [9]  analog_testmode_sel[1]   000:reserved, 001:reserved, 010:reserved, 011:pll_opamp_out_test,
    ;   |  |  |  |  |  +-------------------------------- [10] analog_testmode_sel[2]   100:sar ibias test, 101:Current Reference test, 110:reserved, 111:reserved]
    ;   |  |  |  |  +----------------------------------- [11] reserved
    ;   |  |  |  |
    ;   |  |  |  +-------------------------------------- [12] reserved
    ;   |  |  +----------------------------------------- [13] reserved
    ;   |  +-------------------------------------------- [14] currentref_testmode     [0:normal, 1:Enables the current reference to be measured on the GPAIN3 pin.  Must also set analog_testmode_sel[2:0] == 101]
    ;   +----------------------------------------------- [15] por_lv_det_dis          [POR low voltage detection - 0:enabled, 1:disabled.  Should be disabled (set high) before the trim bits are adjusted, else the POR might think a low-voltage condition exists & reset the DSP.]

USB_ANA_CNTL            .set    0x7004
    ; USB_ANA_CNTL   Address:  0x7004 (IO space)              USB Control
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ; |15:14:13:12|11:10: 9: 8| 7: 6: 5: 4| 3: 2: 1: 0|  <<== Bit Position
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; |r :r :r :r |r :r :r :r |r :r :r :r |r :r :r :rw|  <<== Read / Write Access
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; | 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0|  <<== Reset Values
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-- [0]  usb_ldo_en      [0:disabled (w/output tristated), 1:enabled]
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  +----- [1]  reserved
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  +-------- [2]  reserved
    ;   |  |  |  |  |  |  |  |  |  |  |  |  +----------- [3]  reserved
    ;   |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  +-------------- [4]  reserved
    ;   |  |  |  |  |  |  |  |  |  |  +----------------- [5]  reserved
    ;   |  |  |  |  |  |  |  |  |  +-------------------- [6]  reserved
    ;   |  |  |  |  |  |  |  |  +----------------------- [7]  reserved
    ;   |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  +-------------------------- [8]  reserved
    ;   |  |  |  |  |  |  +----------------------------- [9]  reserved
    ;   |  |  |  |  |  +-------------------------------- [10] reserved
    ;   |  |  |  |  +----------------------------------- [11] reserved
    ;   |  |  |  |
    ;   |  |  |  +-------------------------------------- [12] reserved
    ;   |  |  +----------------------------------------- [13] reserved
    ;   |  +-------------------------------------------- [14] reserved
    ;   +----------------------------------------------- [15] reserved

    ;******************************************************************
    ;   SAR Registers          
    ;******************************************************************
SAR_CNTL            .set    0x7012      ; SAR A/D Control Register
    ; SAR_CNTL   Address:  0x7012 (IO space)             SAR A/D Control Register
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ; |15:14:13:12|11:10: 9: 8| 7: 6: 5: 4| 3: 2: 1: 0|  <<== Bit Position
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; |rw:rw:rw:rw|rw:rw:rw:rw|rw:rw:rw:rw|rw:rw:rw:rw|  <<== Read / Write Access
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; | 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0|  <<== Reset Values
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-- [0]  servotestdata[0]  (Sets analog comparator threshold
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  +----- [1]  servotestdata[1]   for test purposes.)
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  +-------- [2]  servotestdata[2]
    ;   |  |  |  |  |  |  |  |  |  |  |  |  +----------- [3]  servotestdata[3]
    ;   |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  +-------------- [4]  servotestdata[4]
    ;   |  |  |  |  |  |  |  |  |  |  +----------------- [5]  servotestdata[5]
    ;   |  |  |  |  |  |  |  |  |  +-------------------- [6]  servotestdata[6]
    ;   |  |  |  |  |  |  |  |  +----------------------- [7]  servotestdata[7]
    ;   |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  +-------------------------- [8]  servotestdata[8]
    ;   |  |  |  |  |  |  +----------------------------- [9]  servotestdata[9]
    ;   |  |  |  |  |  +-------------------------------- [10] SingleConversion  (0:continuous conversions while ADCStart==1, 1:one conversion & then clear ADCStart)
    ;   |  |  |  |  +----------------------------------- [11] MultiCh           (Multichannel Operation - 0:no discharge of array, 1:discharge when switching channels)
    ;   |  |  |  |
    ;   |  |  |  +-------------------------------------- [12] ChSelect[0]       (000:Ch0/GPAIN0, 001:Ch1/GPAIN0, 010:Ch2/GPAIN0,
    ;   |  |  +----------------------------------------- [13] ChSelect[1]        011:Ch3/GPAIN1, 100:Ch4/GPAIN2, 101:Ch5/GPAIN3,
    ;   |  +-------------------------------------------- [14] ChSelect[2]        110-111:all analog switches OFF)
    ;   +----------------------------------------------- [15] ADCStart          (0:no conversion, 1:start conversion
    ;                                                                            Note: ADCStart is self clearing if SingleCyc==1)

SAR_DATA            .set    0x7014      ; SAR A/D Read Only Data Register
    ; SAR_DATA   Address:  0x7014 (IO space)              SAR A/D Read Only Data Register
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ; |15:14:13:12|11:10: 9: 8| 7: 6: 5: 4| 3: 2: 1: 0|  <<== Bit Position
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; | r: r: r: r| r: r: r: r| r: r: r: r| r: r: r: r|  <<== Read / Write Access
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; | 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0|  <<== Reset Values
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-- [0]  ADCData[0]    Converter data
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  +----- [1]  ADCData[1]
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  +-------- [2]  ADCData[2]
    ;   |  |  |  |  |  |  |  |  |  |  |  |  +----------- [3]  ADCData[3]
    ;   |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  +-------------- [4]  ADCData[4]
    ;   |  |  |  |  |  |  |  |  |  |  +----------------- [5]  ADCData[5]
    ;   |  |  |  |  |  |  |  |  |  +-------------------- [6]  ADCData[6]
    ;   |  |  |  |  |  |  |  |  +----------------------- [7]  ADCData[7]
    ;   |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  +-------------------------- [8]  ADCData[8]
    ;   |  |  |  |  |  |  +----------------------------- [9]  ADCData[9]
    ;   |  |  |  |  |  +-------------------------------- [10] reserved
    ;   |  |  |  |  +----------------------------------- [11] reserved
    ;   |  |  |  |
    ;   |  |  |  +-------------------------------------- [12] ChSelect-readonly[0]   (000:Ch0/GPAIN0, 001:Ch1/GPAIN0, 010:Ch2/GPAIN0,
    ;   |  |  +----------------------------------------- [13] ChSelect-readonly[1]    011:Ch3/GPAIN1, 100:Ch4/GPAIN2, 101:Ch5/GPAIN3,
    ;   |  +-------------------------------------------- [14] ChSelect-readonly[2]    110-111:all analog switches OFF)
    ;   +----------------------------------------------- [15] ADCBusy       (0:ADC data available, 1:ADC busy)

SAR_CLOCK_CNTL      .set    0x7016      ; SAR A/D Clock Control Register
    ; SAR_CLOCK_CNTL   Address:  0x7016 (IO space)            SAR A/D Clock Control Register
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ; |15:14:13:12|11:10: 9: 8| 7: 6: 5: 4| 3: 2: 1: 0|  <<== Bit Position
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; |r :rw:rw:rw|rw:rw:rw:rw|rw:rw:rw:rw|rw:rw:rw:rw|  <<== Read / Write Access
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; | 0: 1: 1: 1| 1: 1: 1: 1| 1: 1: 1: 1| 1: 1: 1: 1|  <<== Reset Values
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-- [0]  SarClkDiv[0]   (SAR_clk = sys_clock / (SarClkDiv[14:0] + 1))
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  +----- [1]  SarClkDiv[1]   (note: SAR_clk max is 2 mhz)
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  +-------- [2]  SarClkDiv[2]
    ;   |  |  |  |  |  |  |  |  |  |  |  |  +----------- [3]  SarClkDiv[3]   (ie: 0:divby1, 1:divby2, 2:divby3, ..., 32767:divby32768)
    ;   |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  +-------------- [4]  SarClkDiv[4]
    ;   |  |  |  |  |  |  |  |  |  |  +----------------- [5]  SarClkDiv[5]
    ;   |  |  |  |  |  |  |  |  |  +-------------------- [6]  SarClkDiv[6]
    ;   |  |  |  |  |  |  |  |  +----------------------- [7]  SarClkDiv[7]
    ;   |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  +-------------------------- [8]  SarClkDiv[8]
    ;   |  |  |  |  |  |  +----------------------------- [9]  SarClkDiv[9]
    ;   |  |  |  |  |  +-------------------------------- [10] SarClkDiv[10]
    ;   |  |  |  |  +----------------------------------- [11] SarClkDiv[11]
    ;   |  |  |  |
    ;   |  |  |  +-------------------------------------- [12] SarClkDiv[12]
    ;   |  |  +----------------------------------------- [13] SarClkDiv[13]
    ;   |  +-------------------------------------------- [14] SarClkDiv[14]
    ;   +----------------------------------------------- [15] reserved

SAR_PIN_CNTL        .set    0x7018      ; SAR A/D Pin Control Register
    ; SAR_PIN_CNTL   Address:  0x7018 (IO space)              SAR A/D Pin Control Register
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ; |15:14:13:12|11:10: 9: 8| 7: 6: 5: 4| 3: 2: 1: 0|  <<== Bit Position
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; |r :rw:rw:rw|r :rw:rw:rw|r :r :rw:rw|rw:rw:rw:rw|  <<== Read / Write Access
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; | 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0|  <<== Reset Values
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |        (note: Either NoHV or GndSwOn must be '1' to measure channels 0 or 1.  NoHV must be '1' to measure channel 2.
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |               If these conditions are not met then the channel will measure GND.)
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-- [0]  Half            [0:GPAIN[3:0] fed directly to SAR, GPAIN[3:0] divided by 2 before going to SAR]
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  +----- [1]  GndSwOn         [0:normal ch0, 1:channel 0 is grounded]
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  +-------- [2]  NoHV            [see spec for description of NoHV]
    ;   |  |  |  |  |  |  |  |  |  |  |  |  +----------- [3]  AVddMeas        [0:normal ch3, 1:measure VDDA_SAR voltage on chan 3]
    ;   |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  +-------------- [4]  TouchScreenMode [0:normal mode, 1:TouchScreen mode enabled]
    ;   |  |  |  |  |  |  |  |  |  |  +----------------- [5]  ServoTestMode   [0:normal mode, 1:Servo testmode enabled]
    ;   |  |  |  |  |  |  |  |  |  +-------------------- [6]  reserved
    ;   |  |  |  |  |  |  |  |  +----------------------- [7]  reserved
    ;   |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  +-------------------------- [8]  RefAVddSel      [0:Ref voltage based on bandgap, 1:reference voltage is VDDA_SAR]
    ;   |  |  |  |  |  |  +----------------------------- [9]  Ref1VSel        [0:Bandgap Ref Voltage 0.8v, 1:Bandgap Ref Voltage 1.0v]
    ;   |  |  |  |  |  +-------------------------------- [10] VrefPwrDnz      [0:Sar Vref powered down, 1:Sar Vref Powered)
    ;   |  |  |  |  +----------------------------------- [11] reserved
    ;   |  |  |  |
    ;   |  |  |  +-------------------------------------- [12] SARPwrUp        [0:SAR_analog powered down, 1:SAR_analog powered up]
    ;   |  |  +----------------------------------------- [13] PWRUP_IBIAS     [0:Sar's ibias is powered down, 1:Sar's ibias is powered up]
    ;   |  +-------------------------------------------- [14] SAR_DATA_StatusMask [0:CHSelect & ADCBusy status bits are visible in the SAR_DATA register, 1:SAR_DATA[15:10] always read zero (useful for DMA xfrs where only the data value is desired)]
    ;   +----------------------------------------------- [15] ServoTestCmpOut [0:compare result is low, 1:compare result is high]

SAR_GPO_CNTL        .set    0x701A      ; SAR A/D GPO Control Register
    ; SAR_GPO_CNTL   Address:  0x701A (IO space)              SAR A/D Pin Control Register
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ; |15:14:13:12|11:10: 9: 8| 7: 6: 5: 4| 3: 2: 1: 0|  <<== Bit Position
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; |r :r :r :r |r :r :r :rw|rw:rw:rw:rw|rw:rw:rw:rw|  <<== Read / Write Access
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; | 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0|  <<== Reset Values
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-- [0]  gpain_data[0]         (Data to drive when the GPAIN pin is configured as a digital output)
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  +----- [1]  gpain_data[1]
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  +-------- [2]  gpain_data[2]
    ;   |  |  |  |  |  |  |  |  |  |  |  |  +----------- [3]  gpain_data[3]
    ;   |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  +-------------- [4]  gpain_oen[0]          (0:analog sar input mode/output disabled, 1:digital output enabled)
    ;   |  |  |  |  |  |  |  |  |  |  +----------------- [5]  gpain_oen[1]
    ;   |  |  |  |  |  |  |  |  |  +-------------------- [6]  gpain_oen[2]
    ;   |  |  |  |  |  |  |  |  +----------------------- [7]  gpain_oen[3]
    ;   |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  +-------------------------- [8]  penirqen              (0:pen interrupt disabled, 1:pen interrupt enabled)
    ;   |  |  |  |  |  |  +----------------------------- [9]  penirq                (Pen Interrupt Flag.  *Not Latched*  1:indicates a pen interrupt occured. 0:indicates no interrupt occured)
    ;   |  |  |  |  |  +-------------------------------- [10] reserved
    ;   |  |  |  |  +----------------------------------- [11] reserved
    ;   |  |  |  |
    ;   |  |  |  +-------------------------------------- [12] reserved
    ;   |  |  +----------------------------------------- [13] reserved
    ;   |  +-------------------------------------------- [14] reserved
    ;   +----------------------------------------------- [15] reserved

;----------------------------------------------------------------------------------------
;        SAR Bit Fields
;----------------------------------------------------------------------------------------
GPO0High            .set    1b          ; GPO 0 Data High
GPO1High            .set    1b<<1       ; GPO 1 Data High
GPO2High            .set    1b<<2       ; GPO 2 Data High
GPO3High            .set    1b<<3       ; GPO 3 Data High

GPO0Low             .set    0b          ; GPO 0 Data Low
GPO1Low             .set    0b<<1       ; GPO 1 Data Low
GPO2Low             .set    0b<<2       ; GPO 2 Data Low
GPO3Low             .set    0b<<3       ; GPO 3 Data Low

GPO0En              .set    1b<<4       ; GPO 0 Enable
GPO1En              .set    1b<<5       ; GPO 1 Enable
GPO2En              .set    1b<<6       ; GPO 2 Enable
GPO3En              .set    1b<<7       ; GPO 3 Enable

PenIrqEn            .set    1b<<8       ; Pen Interrupt Enable
PenIrqSt            .set    1b<<9       ; Pen Interrupt Status

; For SAR_CNTL 
SingleCycle         .set    1b<<10      ; Perform one conversion and stop
ContCycle           .set    0b<<10      ; Continuous conversions while ADCStart=1 
MultiCh             .set    1b<<11      ; Discharge Array after switching to new channel
NoMultiCh           .set    0b<<11      ; No Array Discharge on switching to new channel
Ch0                 .set    000b<<12    ; Channel 0(GPAIN0)
Ch1                 .set    001b<<12    ; Channel 1(GPAIN0)
Ch2                 .set    010b<<12    ; Channel 2(GPAIN0)
Ch3                 .set    011b<<12    ; Channel 3(GPAIN1)
Ch4                 .set    100b<<12    ; Channel 4(GPAIN2)
Ch5                 .set    101b<<12    ; Channel 5(GPAIN3)
NoCh                .set    111b<<12    ; All analog switched OFF 
ADCStart            .set    1b<<15      ; Start Conversion - self clearing if SingleCycle
ADCStop             .set    0b<<15      ; Stop Conversion

;****************************************************************************************
;        Coprocessor Register Addresses
;****************************************************************************************
COPRO_FFT_COMM_REG_LSW          .set    0x6000    ; FFT Control LSW Register
COPRO_FFT_COMM_REG_MSW          .set    0x6001    ; FFT Control MSW Register
COPRO_FFT_STAT_REG_LSW          .set    0x6004    ; FFT Status LSW Register
COPRO_FFT_STAT_REG_MSW          .set    0x6005    ; FFT Status MSW Register
COPRO_FILTBANK_COMM_REG_LSW     .set    0x6008    ; Filterbank Control LSW Register
COPRO_FILTBANK_COMM_REG_MSW     .set    0x6009    ; Filterbank Control MSW Register
COPRO_FILTBANK_STAT_REG_LSW     .set    0x600C    ; Filterbank Status LSW Register
COPRO_FILTBANK_STAT_REG_MSW     .set    0x600D    ; Filterbank Status MSW Register
COPRO_MEM_PAGE0123_LSW          .set    0x6010    ; Memory Page Allocation LSW Register
COPRO_MEM_PAGE0123_MSW          .set    0x6011    ; Memory Page Allocation MSW Register
COPRO_TEST_MODE_REG_LSW         .set    0x6024    ; Test Mode register LSW ; customer need not be aware of this register
COPRO_TEST_MODE_REG_MSW         .set    0x6025    ; Test Mode register MSW
;COPRO_D0_ADDR                   .set    0x6014    ; D0 Bus Address Register
;COPRO_D1_ADDR                   .set    0x6015    ; D1 Bus Address Register
;COPRO_R_ADDR_LSW                .set    0x6018    ; R0 LSW Bus Address Regsiter
;COPRO_R_ADDR_MSW                .set    0x6019    ; R0 MSW Bus Address Regsiter
;COPRO_W0_ADDR                   .set    0x601C    ; W0 Bus Address
;COPRO_W1_ADDR                   .set    0x601D    ; W1 Bus Address
;COPRO_FB_COEF_ADDR_LSW          .set    0x6020    ; Analysis Filter Coeff Buffer Address + Analysis Filter Delay Buffer
;COPRO_FB_COEF_ADDR_MSW          .set    0x6021    ; Synthesis Filter Coeff Buffer Address + Synthesis Filter Delay Buffer
COPRO_PAGE0_ADDR                .set    0x4000     ; coproc. memory switch page 0 base address
COPRO_PAGE1_ADDR                .set    0x4400     ; coproc. memory switch page 1 base address
COPRO_PAGE2_ADDR                .set    0x4800     ; coproc. memory switch page 2 base address
COPRO_PAGE3_ADDR                .set    0x4C00     ; coproc. memory switch page 3 base address
COPRO_ROML_ADDR                 .set    0x5000     ; coproc. ROM low (0-255) base address
COPRO_ROMU_ADDR                 .set    0x5400     ; coproc. ROM high (256-511) base address
COPRO_AFB_COEF_ADDR             .set    0x5800     ; coproc. AF coefs base address
COPRO_SFB_COEF_ADDR             .set    0x5A00     ; coproc. SF coefs base address
COPRO_AFB_DLY_ADDR              .set    0x5C00     ; coproc. AF delay line base address
COPRO_SFB_DLY_ADDR              .set    0x5E00     ; coproc. SF delay line base address

;----------------------------------------------------------------------------------------
;        Coprocessor Bit Fields
;----------------------------------------------------------------------------------------
; COPRO_MEM_PAGE0123_LSW bit fields
PAGE0_FFT           .set    001b        ; Page 0 assigned to FFT engine
PAGE0_FLTBNK        .set    010b        ; Page 0 assigned to Filterbank engine
PAGE0_FB_FFT        .set    011b        ; Page 0 assigned to Filterbank then FFT engine
PAGE0_FFT_FB        .set    100b        ; Page 0 assigned to FFT then Filterbank engine
PAGE0_VBUS          .set    101b        ; Page 0 assigned to VBUS
PAGE0_VBUS_OL       .set    110b        ; Page 0 assigned to VBUS Overlapp
PAGE1_FFT           .set    001b<<3     ; Page 0 assigned to FFT engine
PAGE1_FLTBNK        .set    010b<<3     ; Page 0 assigned to Filterbank engine
PAGE1_FB_FFT        .set    011b<<3     ; Page 0 assigned to Filterbank then FFT engine
PAGE1_FFT_FB        .set    100b<<3     ; Page 0 assigned to FFT then Filterbank engine
PAGE1_VBUS          .set    101b<<3     ; Page 0 assigned to VBUS
PAGE1_VBUS_OL       .set    110b<<3     ; Page 0 assigned to VBUS Overlapp
PAGE2_FFT           .set    001b<<8     ; Page 0 assigned to FFT engine
PAGE2_FLTBNK        .set    010b<<8     ; Page 0 assigned to Filterbank engine
PAGE2_FB_FFT        .set    011b<<8     ; Page 0 assigned to Filterbank then FFT engine
PAGE2_FFT_FB        .set    100b<<8     ; Page 0 assigned to FFT then Filterbank engine
PAGE2_VBUS          .set    101b<<8     ; Page 0 assigned to VBUS
PAGE2_VBUS_OL       .set    110b<<8     ; Page 0 assigned to VBUS Overlapp
PAGE3_FFT           .set    001b<<11    ; Page 0 assigned to FFT engine
PAGE3_FLTBNK        .set    010b<<11    ; Page 0 assigned to Filterbank engine
PAGE3_FB_FFT        .set    011b<<11    ; Page 0 assigned to Filterbank then FFT engine
PAGE3_FFT_FB        .set    100b<<11    ; Page 0 assigned to FFT then Filterbank engine
PAGE3_VBUS          .set    101b<<11    ; Page 0 assigned to VBUS
PAGE3_VBUS_OL       .set    110b<<11    ; Page 0 assigned to VBUS Overlapp
; COPRO_MEM_PAGE0123_MSW bit fields
MEM_PACK            .set    1b          ; DMA pack mode
BITREV              .set    1b<<1       ; Bit reversed addressing
FB_BR               .set    1b<<2       ; Filterbank uses bit reversed addressing
; FFT_COM_REG_LSW bit fields
FFT_RESET           .set    (1b<<8)
; FFT_COMM_REG_MSW bit fields
FFT_16              .set    (00b<<0)    ; FFT/IFFT size is 16 points
FFT_32              .set    (01b<<0)    ; FFT/IFFT size is 32 points
FFT_64              .set    (10b<<0)    ; FFT/IFFT size is 64 points
FFT_128             .set    (11b<<0)    ; FFT/IFFT size is 128 points
FFT_DATA_FFT        .set    (0b<<2)     ; FFT engine performs FFT
FFT_DATA_IFFT       .set    (1b<<2)     ; IFFT engine performs IFFT
; FILTERBANK_COMM_REG_LSW bit fields
FB_DIR_ANALYSIS     .set    (0b<<12)    ; Filterbank engine performs analysis filtering
FB_DIR_SYNTHESIS    .set    (1b<<12)    ; Filterbank engine performs synthesis filtering
FILT_COEF_LOC_RAM   .set    (0b<<13)    ; Filterbank coefs in RAM
FILT_COEF_LOC_ROM   .set    (1b<<13)    ; Filterbank coefs in ROM
FB_RESET            .set    (1b<<8)
; FILTERBANK_COMM_REG_MSW bit fields
WIN_SELECT_HAMMING  .set    (000b<<10)  ; Window filter coefs in ROM -- Hamming window
WIN_SELECT_BLACKMAN .set    (001b<<10)  ; Window filter coefs in ROM -- Blackman window
WIN_SELECT_TAYLOR   .set    (010b<<10)  ; Window filter coefs in ROM -- Taylor window

;----------------------------------------------------------------------------------------
;        CPU Registers - Useful Comment Fields
;----------------------------------------------------------------------------------------
    ; IFR0   Address:  0x01 (MMAP)  (@#IFR0_, @IFR0_L)            Interrupt Flag Register 0
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ; |15:14:13:12|11:10: 9: 8| 7: 6: 5: 4| 3: 2: 1: 0|  <<== Bit Position
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; |rw:rw:rw:rw|rw:rw:rw:rw|rw:rw:rw:rw|rw:rw:rw:rw|  <<== Read / Write Access
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; | 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0|  <<== Reset Values
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |        (1:indicates an interrupt, 0:no interrupt) (writing a 1 clears the bit)
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-- [0]  reserved
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  +----- [1]  reserved
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  +-------- [2]  INT0                                  vector_offset=0x10
    ;   |  |  |  |  |  |  |  |  |  |  |  |  +----------- [3]  INT1                                  vector_offset=0x18
    ;   |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  +-------------- [4]  Aggregated Timers                     vector_offset=0x20
    ;   |  |  |  |  |  |  |  |  |  |  +----------------- [5]  PROG0 (I2S0_XMT or MMCSD0)            vector_offset=0x28
    ;   |  |  |  |  |  |  |  |  |  +-------------------- [6]  UART                                  vector_offset=0x30
    ;   |  |  |  |  |  |  |  |  +----------------------- [7]  PROG1 (I2S0_RCV or MMCSD0 SDIO)       vector_offset=0x38
    ;   |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  +-------------------------- [8]  Aggregated DMAs                       vector_offset=0x40
    ;   |  |  |  |  |  |  +----------------------------- [9]  PROG2 (I2S1_XMT or MMCSD1)            vector_offset=0x48
    ;   |  |  |  |  |  +-------------------------------- [10] FFTCOP                                vector_offset=0x50
    ;   |  |  |  |  +----------------------------------- [11] PROG3 (I2S1_RCV or MMCSD1 SDIO)       vector_offset=0x58
    ;   |  |  |  |
    ;   |  |  |  +-------------------------------------- [12] LCD                                   vector_offset=0x60
    ;   |  |  +----------------------------------------- [13] SAR                                   vector_offset=0x68
    ;   |  +-------------------------------------------- [14] I2S2 Transmit                         vector_offset=0x70
    ;   +----------------------------------------------- [15] I2S2 Receive                          vector_offset=0x78

    ; IFR1   Address:  0x46 (MMAP)  (@#IFR1_, @IFR1_L)            Interrupt Flag Register 1
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ; |15:14:13:12|11:10: 9: 8| 7: 6: 5: 4| 3: 2: 1: 0|  <<== Bit Position
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; |rw:rw:rw:rw|rw:rw:rw:rw|rw:rw:rw:rw|rw:rw:rw:rw|  <<== Read / Write Access
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; | 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0|  <<== Reset Values
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |        (1:indicates an interrupt, 0:no interrupt) (writing a 1 clears the bit)
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-- [0]  I2S3 Transmit                         vector_offset=0x80
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  +----- [1]  I2S3 Receive                          vector_offset=0x88
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  +-------- [2]  RTC / Wakeup                          vector_offset=0x90
    ;   |  |  |  |  |  |  |  |  |  |  |  |  +----------- [3]  SPI                                   vector_offset=0x98
    ;   |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  +-------------- [4]  USB                                   vector_offset=0xA0
    ;   |  |  |  |  |  |  |  |  |  |  +----------------- [5]  Aggregated GPIOs                      vector_offset=0xA8
    ;   |  |  |  |  |  |  |  |  |  +-------------------- [6]  EMIF                                  vector_offset=0xB0
    ;   |  |  |  |  |  |  |  |  +----------------------- [7]  I2C                                   vector_offset=0xB8
    ;   |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  +-------------------------- [8]  BERR                                  vector_offset=0xC0
    ;   |  |  |  |  |  |  +----------------------------- [9]  DLOG (emulation)                      vector_offset=0xC8
    ;   |  |  |  |  |  +-------------------------------- [10] RTOS (emulation)                      vector_offset=0xD0
    ;   |  |  |  |  +----------------------------------- [11] reserved (RTDX receive)               vector_offset=0xD8
    ;   |  |  |  |
    ;   |  |  |  +-------------------------------------- [12] reserved (RTDX transmit)              vector_offset=0xE0
    ;   |  |  +----------------------------------------- [13] reserved (EMUINT)                     vector_offset=0xE8
    ;   |  +-------------------------------------------- [14] reserved (SINT30 software interrupt)  vector_offset=0xF0
    ;   +----------------------------------------------- [15] reserved (SINT31 software interrupt)  vector_offset=0xF8

    ; IMR0/IER0   Address:  0x00 (MMAP)  (@#IMR0_, @IMR0_L)       Interrupt Mask Register 0
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ; |15:14:13:12|11:10: 9: 8| 7: 6: 5: 4| 3: 2: 1: 0|  <<== Bit Position
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; |rw:rw:rw:rw|rw:rw:rw:rw|rw:rw:rw:rw|rw:rw:rw:rw|  <<== Read / Write Access
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; | 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0|  <<== Reset Values
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |        (1:enables the interrupt, 0:disables the interrupt)
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-- [0]  reserved
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  +----- [1]  reserved
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  +-------- [2]  INT0                                  vector_offset=0x10
    ;   |  |  |  |  |  |  |  |  |  |  |  |  +----------- [3]  INT1                                  vector_offset=0x18
    ;   |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  +-------------- [4]  Aggregated Timers                     vector_offset=0x20
    ;   |  |  |  |  |  |  |  |  |  |  +----------------- [5]  PROG0 (I2S0_XMT or MMCSD0)            vector_offset=0x28
    ;   |  |  |  |  |  |  |  |  |  +-------------------- [6]  UART                                  vector_offset=0x30
    ;   |  |  |  |  |  |  |  |  +----------------------- [7]  PROG1 (I2S0_RCV or MMCSD0 SDIO)       vector_offset=0x38
    ;   |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  +-------------------------- [8]  Aggregated DMAs                       vector_offset=0x40
    ;   |  |  |  |  |  |  +----------------------------- [9]  PROG2 (I2S1_XMT or MMCSD1)            vector_offset=0x48
    ;   |  |  |  |  |  +-------------------------------- [10] FFTCOP                                vector_offset=0x50
    ;   |  |  |  |  +----------------------------------- [11] PROG3 (I2S1_RCV or MMCSD1 SDIO)       vector_offset=0x58
    ;   |  |  |  |
    ;   |  |  |  +-------------------------------------- [12] LCD                                   vector_offset=0x60
    ;   |  |  +----------------------------------------- [13] SAR                                   vector_offset=0x68
    ;   |  +-------------------------------------------- [14] I2S2 Transmit                         vector_offset=0x70
    ;   +----------------------------------------------- [15] I2S2 Receive                          vector_offset=0x78

    ; IMR1/IER1   Address:  0x45 (MMAP)  (@#IMR1_, @IMR1_L)       Interrupt Mask Register 1
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ; |15:14:13:12|11:10: 9: 8| 7: 6: 5: 4| 3: 2: 1: 0|  <<== Bit Position
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; |rw:rw:rw:rw|rw:rw:rw:rw|rw:rw:rw:rw|rw:rw:rw:rw|  <<== Read / Write Access
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; | 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0|  <<== Reset Values
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |        (1:enables the interrupt, 0:disables the interrupt)
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-- [0]  I2S3 Transmit                         vector_offset=0x80
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  +----- [1]  I2S3 Receive                          vector_offset=0x88
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  +-------- [2]  RTC / Wakeup                          vector_offset=0x90
    ;   |  |  |  |  |  |  |  |  |  |  |  |  +----------- [3]  SPI                                   vector_offset=0x98
    ;   |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  +-------------- [4]  USB                                   vector_offset=0xA0
    ;   |  |  |  |  |  |  |  |  |  |  +----------------- [5]  Aggregated GPIOs                      vector_offset=0xA8
    ;   |  |  |  |  |  |  |  |  |  +-------------------- [6]  EMIF                                  vector_offset=0xB0
    ;   |  |  |  |  |  |  |  |  +----------------------- [7]  I2C                                   vector_offset=0xB8
    ;   |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  +-------------------------- [8]  BERR                                  vector_offset=0xC0
    ;   |  |  |  |  |  |  +----------------------------- [9]  DLOG (emulation)                      vector_offset=0xC8
    ;   |  |  |  |  |  +-------------------------------- [10] RTOS (emulation)                      vector_offset=0xD0
    ;   |  |  |  |  +----------------------------------- [11] reserved (RTDX receive)               vector_offset=0xD8
    ;   |  |  |  |
    ;   |  |  |  +-------------------------------------- [12] reserved (RTDX transmit)              vector_offset=0xE0
    ;   |  |  +----------------------------------------- [13] reserved (EMUINT)                     vector_offset=0xE8
    ;   |  +-------------------------------------------- [14] reserved (SINT30 software interrupt)  vector_offset=0xF0
    ;   +----------------------------------------------- [15] reserved (SINT31 software interrupt)  vector_offset=0xF8


    ; ST0   Address:  0x02 (MMAP)  (@#ST0_)       Status Register 0
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ; |15:14:13:12|11:10: 9: 8| 7: 6: 5: 4| 3: 2: 1: 0|  <<== Bit Position
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; |rw:rw:rw:rw|rw:rw:rw:rw|rw:rw:rw:rw|rw:rw:rw:rw|  <<== Read / Write Access
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; | 0: 0: 1: 1| 1: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0|  <<== Reset Values
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-- [0]  DP[7]     (c54x legacy support - use the C55x DP register instead)
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  +----- [1]  DP[8]     (c54x legacy support - use the C55x DP register instead)
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  +-------- [2]  DP[9]     (c54x legacy support - use the C55x DP register instead)
    ;   |  |  |  |  |  |  |  |  |  |  |  |  +----------- [3]  DP[10]    (c54x legacy support - use the C55x DP register instead)
    ;   |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  +-------------- [4]  DP[11]    (c54x legacy support - use the C55x DP register instead)
    ;   |  |  |  |  |  |  |  |  |  |  +----------------- [5]  DP[12]    (c54x legacy support - use the C55x DP register instead)
    ;   |  |  |  |  |  |  |  |  |  +-------------------- [6]  DP[13]    (c54x legacy support - use the C55x DP register instead)
    ;   |  |  |  |  |  |  |  |  +----------------------- [7]  DP[14]    (c54x legacy support - use the C55x DP register instead)
    ;   |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  +-------------------------- [8]  DP[15]    (c54x legacy support - use the C55x DP register instead)
    ;   |  |  |  |  |  |  +----------------------------- [9]  ACOV1     (AC1 overflow flag - 1=overflow)
    ;   |  |  |  |  |  +-------------------------------- [10] ACOV0     (AC0 overflow flag - 1=overflow)
    ;   |  |  |  |  +----------------------------------- [11] CARRY     (0:no carry/borrow detected, 1:carry/borrow detected)
    ;   |  |  |  |
    ;   |  |  |  +-------------------------------------- [12] TC2       (Test/Control Flag 2)
    ;   |  |  +----------------------------------------- [13] TC1       (Test/Control Flag 1)
    ;   |  +-------------------------------------------- [14] ACOV3     (AC3 overflow flag - 1=overflow)
    ;   +----------------------------------------------- [15] ACOV2     (AC2 overflow flag - 1=overflow)

    ; ST1   Address:  0x03 (MMAP)  (@#ST1_)       Status Register 1
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ; |15:14:13:12|11:10: 9: 8| 7: 6: 5: 4| 3: 2: 1: 0|  <<== Bit Position
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; |rw:rw:rw:rw|rw:rw:rw:rw|rw:rw:rw:rw|rw:rw:rw:rw|  <<== Read / Write Access
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; | 0: 0: 1: 0| 1: 0: 0: 1| 0: 0: 1: 0| 0: 0: 0: 0|  <<== Reset Values
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-- [0]  ASM[0]    (Acc Shift Mode - c54x legacy support)
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  +----- [1]  ASM[1]    (Acc Shift Mode - c54x legacy support)
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  +-------- [2]  ASM[2]    (Acc Shift Mode - c54x legacy support)
    ;   |  |  |  |  |  |  |  |  |  |  |  |  +----------- [3]  ASM[3]    (Acc Shift Mode - c54x legacy support)
    ;   |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  +-------------- [4]  ASM[4]    (Acc Shift Mode - c54x legacy support)
    ;   |  |  |  |  |  |  |  |  |  |  +----------------- [5]  C54CM     (1:c54x compatible mode enabled)
    ;   |  |  |  |  |  |  |  |  |  +-------------------- [6]  FRCT      (Fractional Mode - 0:off, 1:on:results of multiply ops are shifted left by 1)
    ;   |  |  |  |  |  |  |  |  +----------------------- [7]  C16       (Dual 16bit Arith Mode - c54x legacy support)
    ;   |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  +-------------------------- [8]  SXMD      (Sign Extension Mode - 0:off, 1:on)
    ;   |  |  |  |  |  |  +----------------------------- [9]  SATD      (D_Unit Saturation Mode - 0:off, 1:D unit overflows will saturate)
    ;   |  |  |  |  |  +-------------------------------- [10] M40       (Computational Mode - 0:32bit mode, 1:40bit mode)
    ;   |  |  |  |  +----------------------------------- [11] INTM      (Interrupt Mode - 0:all unmasked interrupts enabled, 1:all maskable interrupts disabled)
    ;   |  |  |  |
    ;   |  |  |  +-------------------------------------- [12] HM        (Hold Mode - 0:dsp continues executing from internal mem, 1:dsp stops when the EMIF receives HOLD request)
    ;   |  |  +----------------------------------------- [13] XF
    ;   |  +-------------------------------------------- [14] CPL       (Compiler Mode Bit - 0:DP direct addressing mode, 1:SP direct addressing mode)
    ;   +----------------------------------------------- [15] BRAF      (Block Repeat Active Flag - c54x legacy support)

    ; ST2   Address:  0x4b (MMAP)  (@#ST2_)       Status Register 2
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ; |15:14:13:12|11:10: 9: 8| 7: 6: 5: 4| 3: 2: 1: 0|  <<== Bit Position
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; |rw:r :r :rw|rw:rw:r :rw|rw:rw:rw:rw|rw:rw:rw:rw|  <<== Read / Write Access
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; | 0: 1: 1: 1| 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0|  <<== Reset Values
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-- [0]  AR0LC     (0:linear addressing, 1:circular addressing)
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  +----- [1]  AR1LC     (0:linear addressing, 1:circular addressing)
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  +-------- [2]  AR2LC     (0:linear addressing, 1:circular addressing)
    ;   |  |  |  |  |  |  |  |  |  |  |  |  +----------- [3]  AR3LC     (0:linear addressing, 1:circular addressing)
    ;   |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  +-------------- [4]  AR4LC     (0:linear addressing, 1:circular addressing)
    ;   |  |  |  |  |  |  |  |  |  |  +----------------- [5]  AR5LC     (0:linear addressing, 1:circular addressing)
    ;   |  |  |  |  |  |  |  |  |  +-------------------- [6]  AR6LC     (0:linear addressing, 1:circular addressing)
    ;   |  |  |  |  |  |  |  |  +----------------------- [7]  AR7LC     (0:linear addressing, 1:circular addressing)
    ;   |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  +-------------------------- [8]  CDPLC     (0:linear addressing, 1:circular addressing)
    ;   |  |  |  |  |  |  +----------------------------- [9]  reserved
    ;   |  |  |  |  |  +-------------------------------- [10] RDM       (Rounding Mode - 0:round to infinite, 1:round to nearest)
    ;   |  |  |  |  +----------------------------------- [11] EALLOW    (Emulation Access Enable - 0:disabled, 1:enabled)
    ;   |  |  |  |
    ;   |  |  |  +-------------------------------------- [12] DBGM      (Debug Mode - 0:emulation enabled, 1:emulation disabled - used for critical sections of code)
    ;   |  |  +----------------------------------------- [13] reserved
    ;   |  +-------------------------------------------- [14] reserved
    ;   +----------------------------------------------- [15] ARMS      (AR Mode Switch - 0:dsp mode operands, 1:control mode operands)

    ; ST3   Address:  0x04 (MMAP)  (@#ST3_)       Status Register 3
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ; |15:14:13:12|11:10: 9: 8| 7: 6: 5: 4| 3: 2: 1: 0|  <<== Bit Position
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; |rw:rw:rw:rw|rw:rw:rw:rw|rw:rw:rw:rw|r :rw:rw:rw|  <<== Read / Write Access
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; | 0: 0: 0: 1| 1: 1: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0|  <<== Reset Values
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-- [0]  SST       (Saturate-On-Store Mode - 0:off, 1:on)
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  +----- [1]  SMUL      (Saturation-On-Multiplication Mode - 0:off, 1:on)
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  +-------- [2]  CLKOFF    (0:clkout pin is enabled, 1:clkout is disabled)
    ;   |  |  |  |  |  |  |  |  |  |  |  |  +----------- [3]  reserved
    ;   |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  +-------------- [4]  reserved  (always write as 0)
    ;   |  |  |  |  |  |  |  |  |  |  +----------------- [5]  SATA      (A_Unit Saturation Mode - 0:off, 1:A unit overflows will saturate)
    ;   |  |  |  |  |  |  |  |  |  +-------------------- [6]  MPNMC     (0:microcomputer mode (rom enabled), 1:microprocessor mode (rom disabled))
    ;   |  |  |  |  |  |  |  |  +----------------------- [7]  CBERR     (CPU Bus Error Flag - 0:no error, 1:error occurred) (write 0 to clear)
    ;   |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  +-------------------------- [8]  reserved  (always write as 0)
    ;   |  |  |  |  |  |  +----------------------------- [9]  reserved  (always write as 0)
    ;   |  |  |  |  |  +-------------------------------- [10] reserved  (always write as 1)
    ;   |  |  |  |  +----------------------------------- [11] reserved  (always write as 1)
    ;   |  |  |  |
    ;   |  |  |  +-------------------------------------- [12] reserved  (HINT)
    ;   |  |  +----------------------------------------- [13] reserved  (CACLR)
    ;   |  +-------------------------------------------- [14] reserved  (CAEN)
    ;   +----------------------------------------------- [15] reserved  (CAFRZ)

    ; TMCR0 / TMCR0_:    Address:  0x07FE (IO space)              Test Mode Control Register 0
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ; |15:14:13:12|11:10: 9: 8| 7: 6: 5: 4| 3: 2: 1: 0|  <<== Bit Position
    ; +--:--:--:--+--:--:--:--+--:--:--:--+--:--:--:--+
    ; |rw:rw:rw:rw|rw:rw:rw:rw|rw:rw:rw:rw|rw:rw:rw:rw|  <<== Read / Write Access
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--:--:--+
    ; | 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0| 0: 0: 0: 0|  <<== Reset Values
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-- [0]  FDBK          (0:globabl feedback mode disabled, 1:globabl feedback mode enabled)
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  +----- [1]  FDBKXD        (0:feedback for xport & dport disabled, 0:feedback for xport & dport enabled)
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  +-------- [2]  MMAP1         (0:normal memory map, 1:only daram0 is visible)
    ;   |  |  |  |  |  |  |  |  |  |  |  |  +----------- [3]  MMAP2         (0:normal memory map, 1:only daram0 & daram1 are visible & daram1 is mapped at 0xFFE000-0xFFFFFF)
    ;   |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  +-------------- [4]  reserved
    ;   |  |  |  |  |  |  |  |  |  |  +----------------- [5]  PSAEN         (0:Parallel Signature Analyzers disabled, 1:Parallel Signature Analyzers enabled)
    ;   |  |  |  |  |  |  |  |  |  +-------------------- [6]  TESTBOOTINT
    ;   |  |  |  |  |  |  |  |  +----------------------- [7]  TESTFAIL      (Test Status Reporting to chip pins - 0:failed test, 1:passed test)
    ;   |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  +-------------------------- [8]  TESTDONE      (Test Status Reporting to chip pins - 0:test not done, 1:test is done)
    ;   |  |  |  |  |  |  +----------------------------- [9]  LDBYPASS      (Tport interface type - 1:synchronous,  0:asynchronous for VLCT)
    ;   |  |  |  |  |  +-------------------------------- [10] TESTBOOT      (Tport Boot Mode Enable - 0:disabled, 1:enables shared chip pins to be used for LED testcases)
    ;   |  |  |  |  +----------------------------------- [11] TPORTOEN      (Tport Output Pin Driver Enable - 0:bidi test pins are in input mode (LED load), 1:bidi test pins are in output mode (LED Dump))
    ;   |  |  |  |
    ;   |  |  |  +-------------------------------------- [12] reserved
    ;   |  |  +----------------------------------------- [13] reserved
    ;   |  +-------------------------------------------- [14] reserved
    ;   +----------------------------------------------- [15] reserved

    ; TMCR1 / TMCR1_:    Address:  0x07FF (IO space)              Test Mode Control Register 1
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ; |15:14:13:12|11:10: 9: 8| 7: 6: 5: 4| 3: 2: 1: 0|  <<== Bit Position
    ; +--:--:--:--+--:--:--:--+--:--:--:--+--:--:--:--+
    ; |rw:rw:rw:rw|rw:rw:rw:rw|rw:rw:rw:rw|rw:rw:rw:rw|  <<== Read / Write Access
    ; +--:--:--:--+--:--:--:--+--:--:--:--+--:--:--:--+
    ; | 0: 0: 0: 0| 1: 0: 0: 0| 0: 1: 1: 0| 0: 0: 0: 0|  <<== Reset Values
    ; +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  +-- [0]  BOOTMOD[0]
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  |  +----- [1]  BOOTMOD[1]
    ;   |  |  |  |  |  |  |  |  |  |  |  |  |  +-------- [2]  BOOTMOD[2]
    ;   |  |  |  |  |  |  |  |  |  |  |  |  +----------- [3]  BOOTMOD[3]
    ;   |  |  |  |  |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  |  |  |  |  +-------------- [4]  ICTEST
    ;   |  |  |  |  |  |  |  |  |  |  +----------------- [5]  PWAKEUP
    ;   |  |  |  |  |  |  |  |  |  +-------------------- [6]  HMREQ
    ;   |  |  |  |  |  |  |  |  +----------------------- [7]  OCP
    ;   |  |  |  |  |  |  |  |
    ;   |  |  |  |  |  |  |  +-------------------------- [8]  CLKRATIO[0]
    ;   |  |  |  |  |  |  +----------------------------- [9]  CLKRATIO[1]
    ;   |  |  |  |  |  +-------------------------------- [10] WRESP
    ;   |  |  |  |  +----------------------------------- [11] PDISMISS
    ;   |  |  |  |
    ;   |  |  |  +-------------------------------------- [12] DDISMISS
    ;   |  |  +----------------------------------------- [13] APISIZE
    ;   |  +-------------------------------------------- [14] HOMINT
    ;   +----------------------------------------------- [15] reserved
