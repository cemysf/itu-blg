/*
 *  Copyright 2010 by Spectrum Digital Incorporated.
 *  All rights reserved. Property of Spectrum Digital Incorporated.
 */

/*
 *  USB header file
 *
 */


/* ------------------------------------------------------------------------ *
 *  USB Registers                                                           *
 * ------------------------------------------------------------------------ */
#define USB_BASE            0x8000
#define USB_REVID1           *( volatile ioport Uint16* )( 0x8000 )
#define USB_REVID2           *( volatile ioport Uint16* )( 0x8001 )
#define USB_CTRLR            *( volatile ioport Uint16* )( 0x8004 ) // Control Register
#define USB_INTSRCR1         *( volatile ioport Uint16* )( 0x8020 ) // USB Interrupt Source Register 1
#define USB_INTSRCR2         *( volatile ioport Uint16* )( 0x8021 ) // USB Interrupt Source Register 2
#define USB_INTCLRR1         *( volatile ioport Uint16* )( 0x8028 ) // USB Interrupt Source Clear Register 1
#define USB_INTCLRR2         *( volatile ioport Uint16* )( 0x8029 ) // USB Interrupt Source Clear Register 2
#define USB_INTMSKSETR1      *( volatile ioport Uint16* )( 0x8030 ) // USB Interrupt Mask Set Register 1
#define USB_INTMSKSETR2      *( volatile ioport Uint16* )( 0x8031 ) // USB Interrupt Mask Set Register 2 
#define USB_EOIR    	     *( volatile ioport Uint16* )( 0x803C ) // USB End of Interrupt Register
#define USB_INTRTX           *( volatile ioport Uint16* )( 0x8401 + 1 ) // Interrupt Register for Endpoint 0 plus Transmit Endpoints 1 to 4
#define USB_INTRRX           *( volatile ioport Uint16* )( 0x8404 + 1 ) // Interrupt Register for Receive Endpoints 1 to 4
#define USB_INTRTXE          *( volatile ioport Uint16* )( 0x8405 + 1 ) // Interrupt enable register for INTRTX
#define USB_INTRRXE          *( volatile ioport Uint16* )( 0x8408 + 1 ) // Interrupt enable register for INTRRX
#define USB_INTRUSB_INTRUSBE *( volatile ioport Uint16* )( 0x8409 + 1 ) // Common USB Interrupts, Interrupt Enable Register

#define USB_FADDR_POWER     *( volatile ioport Uint16* )( 0x8400+1 ) // Function Address Register, Power Management Register
#define USB_INDEX_TESTMODE  *( volatile ioport Uint16* )( 0x840D+1 ) // Index Register for Selecting the Endpoint, Enable USB 2.0 Test Modes
#define USB_PERI_CSR0       *( volatile ioport Uint16* )( 0x8501+1 ) // Indexed Control Status Register for Endpoint 0 in Peripheral Mode
#define USB_FIFO0R1         *( volatile ioport Uint16* )( 0x8420+1 ) // Transmit and Receive FIFO Register 1 for Endpoint 0
#define USB_FIFO0R2         *( volatile ioport Uint16* )( 0x8421+1 ) // Transmit and Receive FIFO Register 2 for Endpoint 0
#define USB_FIFO1R1         *( volatile ioport Uint16* )( 0x8424+1 ) // Transmit and Receive FIFO Register 1 for Endpoint 1
#define USB_FIFO1R2         *( volatile ioport Uint16* )( 0x8425+1 ) // Transmit and Receive FIFO Register 2 for Endpoint 1 
#define USB_FIFO2R1         *( volatile ioport Uint16* )( 0x8428+1 ) // Transmit and Receive FIFO Register 1 for Endpoint 1
#define USB_FIFO2R2         *( volatile ioport Uint16* )( 0x8429+1 ) // Transmit and Receive FIFO Register 2 for Endpoint 1  
#define USB_FIFO3R1         *( volatile ioport Uint16* )( 0x842C+1 ) // Transmit and Receive FIFO Register 1 for Endpoint 1
#define USB_FIFO3R2         *( volatile ioport Uint16* )( 0x842D+1 ) // Transmit and Receive FIFO Register 2 for Endpoint 1  
#define USB_FIFO4R1         *( volatile ioport Uint16* )( 0x8430+1 ) // Transmit and Receive FIFO Register 1 for Endpoint 1
#define USB_FIFO4R2         *( volatile ioport Uint16* )( 0x8431+1 ) // Transmit and Receive FIFO Register 2 for Endpoint 1  

#define USB_TX_RXFIFOSZ     *( volatile ioport Uint16* )( 0x8461+1 ) // Indexed Transmit Receive Endpoint FIFO Size 
#define USB_TXFIFOADDR      *( volatile ioport Uint16* )( 0x8464+1 ) // Indexed Transmit Endpoint FIFO Address 
#define USB_RXFIFOADDR      *( volatile ioport Uint16* )( 0x8465+1 ) // Indexed Receive Endpoint FIFO Address 


#define USB_TXMAXP_EP1	    *( volatile ioport Uint16* )( 0x8510+1 ) // Maximum Packet Size for Transmit Endpoint 1
#define USB_PERI_TXCSR_EP1  *( volatile ioport Uint16* )( 0x8511+1 ) // Control Status Register for Transmit Endpoint 1
#define USB_RXMAXP_EP1	    *( volatile ioport Uint16* )( 0x8514+1 ) // Maximum Packet Size for Receive Endpoint 1
#define USB_PERI_RXCSR_EP1  *( volatile ioport Uint16* )( 0x8515+1 ) // Control Status Register for Receive Endpoint 1
#define USB_RXCOUNT_EP1     *( volatile ioport Uint16* )( 0x8518+1 ) // Number of Received Bytes in Endpoint 1 FIFO

#define USB_TXMAXP_EP2	    *( volatile ioport Uint16* )( 0x8520+1 ) // Maximum Packet Size for Transmit Endpoint 2
#define USB_PERI_TXCSR_EP2  *( volatile ioport Uint16* )( 0x8521+1 ) // Control Status Register for Transmit Endpoint 2
#define USB_RXMAXP_EP2	    *( volatile ioport Uint16* )( 0x8524+1 ) // Maximum Packet Size for Receive Endpoint 2
#define USB_PERI_RXCSR_EP2  *( volatile ioport Uint16* )( 0x8525+1 ) // Control Status Register for Receive Endpoint 2 
#define USB_RXCOUNT_EP2     *( volatile ioport Uint16* )( 0x8528+1 ) // Number of Received Bytes in Endpoint 2 FIFO 

#define USB_TXMAXP_EP3	    *( volatile ioport Uint16* )( 0x8530+1 ) // Maximum Packet Size for Transmit Endpoint 3
#define USB_PERI_TXCSR_EP3  *( volatile ioport Uint16* )( 0x8531+1 ) // Control Status Register for Transmit Endpoint 3
#define USB_RXMAXP_EP3	    *( volatile ioport Uint16* )( 0x8534+1 ) // Maximum Packet Size for Receive Endpoint 3
#define USB_PERI_RXCSR_EP3  *( volatile ioport Uint16* )( 0x8535+1 ) // Control Status Register for Receive Endpoint 3  
#define USB_RXCOUNT_EP3     *( volatile ioport Uint16* )( 0x8538+1 ) // Number of Received Bytes in Endpoint 3 FIFO 

#define USB_TXMAXP_EP4	    *( volatile ioport Uint16* )( 0x8540+1 ) // Maximum Packet Size for Transmit Endpoint 4
#define USB_PERI_TXCSR_EP4  *( volatile ioport Uint16* )( 0x8541+1 ) // Control Status Register for Transmit Endpoint 4
#define USB_RXMAXP_EP4	    *( volatile ioport Uint16* )( 0x8544+1 ) // Maximum Packet Size for Receive Endpoint 4
#define USB_PERI_RXCSR_EP4  *( volatile ioport Uint16* )( 0x8545+1 ) // Control Status Register for Receive Endpoint 4
#define USB_RXCOUNT_EP4     *( volatile ioport Uint16* )( 0x8548+1 ) // Number of Received Bytes in Endpoint 4 FIFO







/* ------------------------------------------------------------------------ *
 *                                                                          *
 *  Variable types                                                          *
 *                                                                          *
 * ------------------------------------------------------------------------ */

#define Uint32  unsigned int
#define Uint16  unsigned short
#define Uint8   unsigned char
#define Int32   int
#define Int16   short
#define Int8    char

////////////////////////////////
//Function prototype
//////////////////////////////// 
void do_setup (void);

void std_request(void);
void get_status(void);
void clear_feature(void);   
void set_feature(void);     
void set_address(void);     
void set_address_2(void);     
void send_descriptor(void); 
void rcv_descriptor(void);  
void get_configuration(void);
void set_configuration(void);
void set_interface(void);   
void get_interface(void);   

void class_request(void); 
void vendor_request(void);
void stall_bus(void);
void fifo_write(Uint16 *buf, int size);
void usb_isr (void);
void get_mouse();
void fifo_write(Uint16 *buf, int size);
Uint16 EVMC5515_USB_INIT();
