/*
 *  Copyright 2010 by Spectrum Digital Incorporated.
 *  All rights reserved. Property of Spectrum Digital Incorporated.
 */

#include "stdio.h"
#include "usb.h"
#include "descriptors.h"
#include "c5515.h"
#include "sar.h"

/* USB Settings */
#define FIFO_MAXP 64        // 64 bytes
Uint16 usbSize;
Uint8 double_buffer = 1;    // 0 = single buffer fifo, 1 = double buffer fifo
Uint8 fifosize = 8;         // 1024 bytes
Uint8 mouseOn = 0;
Uint8 usbOn = 1;
Uint16 keyStore;


/* ------------------------------------------------------------------------ *
 *                                                                          *
 *  Initialize USB                                                          *
 *                                                                          *
 * ------------------------------------------------------------------------ */
Uint16 EVMC5515_USB_INIT()
{
    Uint16 i;
    USBSCR  = 0x6040;     //USB data polarity set as normal, Turn on USB controller
    // init USB module to be able to access mentor USB registers
    CLKSTOP = 0x0;        // No clock will be sotpped
    PCGCR_H = 0x003b;     // Enable USB and DMA clocks
    PSRCR   = 0x0010;     // Reset counter
    PRCR    = 0x0008;     // Reset USB
    // Reset the USB controller
    USB_CTRLR = 0x0001;
	for(i=0;i<0xF000;i++){}      // Wait
    // Clear all pending interrupts
    USB_INTCLRR1 = USB_INTSRCR1;
    USB_INTCLRR2 = USB_INTSRCR2;
    USB_FADDR_POWER |= 0x4000;   // USB D+/D- lines are enabled 
    #if 0
    USB_FADDR_POWER |=  0x2000;   // Enable  high-speed mode
	printf("    High-speed mode enabled.\n");
	#else
    USB_FADDR_POWER &= ~0x2000;   // Enable  full/low-speed mode
	printf("    Low/Full-speed mode enabled.\n");
    #endif
    
    // Interrupts
    USB_EOIR    = 0x00; // enable CPU ack of interrupt completion

    USB_INTRUSB_INTRUSBE = 0xf700; // disable SOF interrupt
    USB_INTRTXE = 0x1f; // enable all TX interrupt
    USB_INTRRXE = 0x1f; // enable all RX interrupt
     
    return 0;
}
/* ------------------------------------------------------------------------ *
 *                                                                          *
 *  Write to FIFO from Array                                                *
 *                                                                          *
 * ------------------------------------------------------------------------ */
void fifo_write(Uint16 *buf, int size)
{
    int i;

    USBSCR |= 2; //enable byte access by CPU and LOW-byte is selected
    for (i=0; i<size; i++) 
    {
        USB_FIFO0R1 = *buf;
        buf++;
    }
    USBSCR &= ~0x03; //enable word access by CPU
}
/* ------------------------------------------------------------------------ *
 *                                                                          *
 *  Get commands from mouse                                                 *
 *                                                                          *
 * ------------------------------------------------------------------------ */
void get_mouse()
{
    Uint16 key, event1, event2;
	key = Get_Sar_Key_usb();   // Get the pressed key
    if(key == SW1)             // Mouse 1
	{
		 event1 = 0x0001;
         event2 = 0x0000;
	}
    else if(key == SW2)        // Mouse 2
	{
		 event1 = 0x0002;
         event2 = 0x0000;
	}
	else if(key == 0)          // Mouse release
	{
		event1 = 0x0000;
        event2 = 0x0000;
		keyStore = 0;
	}
	else if(key == SW12)       // Both buttons => End test
	{
		mouseOn = 0;
		usbOn = 0;
	}
	else
	    return;
    while(USB_PERI_TXCSR_EP1 & 2);  // wait for empty FIFO
    USB_FIFO1R1 = event1 ;  // Laod lower data into FIFO
	USB_FIFO1R1 = event2 ;  // Laod upper data into FIFO

    // Set TxPktRdy bit of EP1
    USB_PERI_TXCSR_EP1 |= 0x0001;
    USB_PERI_CSR0 |= 0x08; // Set DATAEND(B3 of PERI_CSR0)
    keyStore = key;        // Store previous key
	return;
}

/* ------------------------------------------------------------------------ *
 *                                                                          *
 *  Main()  Testing Function                                                *
 *                                                                          *
 * ------------------------------------------------------------------------ */
Uint16 main( void )
{
    inPtr = (Uint16 *)input;
    USBLDOCTRL = 1;    // Turn on USB LDO
    
    printf("Testing USB\n");
    printf("Connect USB port J1 to a computer and the board is detected as a mouse.\n");

    /* Initialize 5515 and USB */
    EVMC5515_USB_INIT();
	Init_SAR();
    inPtr         = (Uint16 *)input;
    deviceDescPtr = (Uint16 *)deviceDesc;
    cfgDescPtr    = (Uint16 *)cfgDesc;
    strDescPtr    = (Uint16 *)strDesc;
    reportDescPtr = (Uint16 *)reportDesc;
    //pBuffer16     = (Uint16 *)pBuffer;
    pBuffer16_ep1 = (Uint16 *)pBuffer8_ep1;
    pBuffer16_ep2 = (Uint16 *)pBuffer8_ep2;
    pBuffer16_ep3 = (Uint16 *)pBuffer8_ep3;
    pBuffer16_ep4 = (Uint16 *)pBuffer8_ep4;
    printf("    The following functions are enabled.\n");
	printf("    MOUSE 1 = SW1 \t MOUSE 2 = SW2   \tEND = SW1&2\n");

    while(usbOn == 1)
    {
		if((USB_INTSRCR2 != 0) ||( USB_INTSRCR1 != 0))
		    usb_isr();
	    while(mouseOn == 1)
		{	    
            get_mouse();
        } 
    }
	printf("\n\n**ALL TESTS PASSED**\n\n");
	return 0;
}

/* ------------------------------------------------------------------------ *
 *                                                                          *
 *  USB interrupt service routine                                           *
 *                                                                          *
 * ------------------------------------------------------------------------ */
void usb_isr (void)
{
    int j;
    intrReg1 = USB_INTSRCR1; // Save USB TX/RX interrupts 
    intrReg2 = USB_INTSRCR2; // Save commom USB interrupts 
    // Clear interrupts
    if((intrReg1) != 0)
    {
        USB_INTCLRR1 = intrReg1;
    }

    if((intrReg2) != 0)
    {
      USB_INTCLRR2 = intrReg2;
    }

    // Get Tx interrupt status
    txIntStat = intrReg1 & 0x001F;

    // Get Rx interrupt status
    rxIntStat = intrReg1 & 0x1F00;

    // Get USB interrupt status
    usbIntStat = ((Uint8)(intrReg2) & 0x00FF);

    suspend   = (usbIntStat & 0x01);
    resume    = (usbIntStat & 0x02);
    reset_usb = (usbIntStat & 0x04);

    ep0_rx_tx = (txIntStat & 0x0001);
    ep1_tx    = (txIntStat & 0x0002);
    ep2_tx    = (txIntStat & 0x0004);
    ep3_tx    = (txIntStat & 0x0008);
    ep4_tx    = (txIntStat & 0x0010);

    ep1_rx    = (rxIntStat & 0x0200);
    ep2_rx    = (rxIntStat & 0x0400);
    ep3_rx    = (rxIntStat & 0x0800);
    ep4_rx    = (rxIntStat & 0x1000);

    ////////////////////////////////////////
    // When RESET occurs:
    // Clears FADDR register to 0. 
    // Clears INDEX register to 0. 
    // Flushes all endpoint FIFOs. 
    // Clears all control/status registers. 
    ////////////////////////////////////////

    // For reset interrupt
    if(reset_usb == 0x04) //(usbIntStat & 0x04)
    {
        USB_INDEX_TESTMODE = 0x0000;   // Clear INDEX and no test mode is set
        USB_PERI_CSR0 |= 0x100;         // Flush FIFO
        resetCnt++;

        // Dynamic FIFO sizing
        // Flush FIFO
        // Flush FIFO twice for double buffer
        // Dynamic FIFO sizing is not using

        // Initialize EP1
        USB_INDEX_TESTMODE = 1;   // Select Index 1
        USB_RXFIFOADDR = 8;       // Select offset 8
        USB_TX_RXFIFOSZ = ((fifosize | ((double_buffer & 1)<<4)) << 8) | (fifosize | ((double_buffer & 1)<<4)); // Buffer size
        USB_TXFIFOADDR = 8 + (1<<(fifosize+double_buffer)); 

        USB_RXMAXP_EP1 = 0x04;      // FIFO maximum packet size (value set in the begenning of this file)
        USB_TXMAXP_EP1 = 0x04;
        USB_PERI_RXCSR_EP1 = 0x10;  // Flush FIFO
        USB_PERI_RXCSR_EP1 = 0x10;  // Flush FIFO twice for double buffer

        // Initialize EP2
        USB_INDEX_TESTMODE = 2;     // Select Index 2
        USB_RXFIFOADDR = 8 + 0x10;
        USB_TX_RXFIFOSZ =  ((fifosize | ((double_buffer & 1)<<4)) << 8) | (fifosize | ((double_buffer & 1)<<4));
        USB_TXFIFOADDR = 8 + 0x10 + (1<<(fifosize+double_buffer)); 

        USB_RXMAXP_EP2 = FIFO_MAXP; // FIFO maximum packet size (value set in the begenning of this file)
        USB_TXMAXP_EP2 = FIFO_MAXP;
        USB_PERI_RXCSR_EP2 = 0x10;  // Flush FIFO
        USB_PERI_RXCSR_EP2 = 0x10;  // Flush FIFO twice for double buffer

        // Initialize EP3
        USB_INDEX_TESTMODE = 3;
        USB_RXFIFOADDR = 8 + 0x20;
        USB_TX_RXFIFOSZ = ((fifosize | ((double_buffer & 1)<<4)) << 8) | (fifosize | ((double_buffer & 1)<<4));
        USB_TXFIFOADDR = 8 + 0x20 + (1<<(fifosize+double_buffer));

        USB_RXMAXP_EP3 = FIFO_MAXP; // FIFO maximum packet size (value set in the begenning of this file)
        USB_TXMAXP_EP3 = FIFO_MAXP;
        USB_PERI_RXCSR_EP3 = 0x10;  // Flush FIFO
        USB_PERI_RXCSR_EP3 = 0x10;  // Flush FIFO twice for double buffer 

        // Initialize EP4
        USB_INDEX_TESTMODE = 4;
        USB_RXFIFOADDR = 8 + 0x30;
        USB_TX_RXFIFOSZ = ((fifosize | ((double_buffer & 1)<<4)) << 8) | (fifosize | ((double_buffer & 1)<<4));
        USB_TXFIFOADDR  = 8 + 0x30 + (1<<(fifosize+double_buffer));

        USB_RXMAXP_EP4 = FIFO_MAXP; // FIFO maximum packet size (value set in the begenning of this file)
        USB_TXMAXP_EP4 = FIFO_MAXP;
        USB_PERI_RXCSR_EP4 = 0x10;  // Flush FIFO
        USB_PERI_RXCSR_EP4 = 0x10;  // Flush FIFO twice for double buffer 
    }
    /////////////////////
    //Suspend interrupt//
    /////////////////////
    if(suspend == 0x01) // (usbIntStat & 0x01) //if suspend
    {
        USB_INDEX_TESTMODE = 0x0000;
    }
    ////////////////////
    //Resume interrupt//
    ////////////////////  
    if(resume == 0x02) // (usbIntStat & 0x02)
    {
        USB_INDEX_TESTMODE = 0x0000;
    }

    //////////////////////////////
    //EP0 interrupt service
    //////////////////////////////
    if (ep0_rx_tx == 0x0001)
    {
        RXPKTRDY = (USB_PERI_CSR0 & 0x0001);
        TXPKTRDY = (USB_PERI_CSR0 & 0x0002);
        SENTSTALL = (USB_PERI_CSR0 & 0x0004);

        // If a bus error occured: abort current transfer, clear SENTSTALL bit
        if (SENTSTALL == 0x0004)
        {
            USB_PERI_CSR0 &= ~0x0004; //clear SENTSTALL bit

        // If a packet has been received without bus-error
        } 
        else if (RXPKTRDY == 0x0001) 
        {
            for (j = 0; j < 4; j++) 
            {
                *inPtr = USB_FIFO0R1;
                inPtr++;
            }
            inPtr = (Uint16 *)input; // Reset the pointer back to the beginning of input-buffer
            USB_PERI_CSR0 |= 0x40;  // Set (B6) of PERI_CSR0: received package served			
            // Get the setup data 
            bRequest_bmRequestType = *(((Uint16 *)&input)+0);
            wValue                 = *(((Uint16 *)&input)+1);
            wIndex                 = *(((Uint16 *)&input)+2);
            wLength                = *(((Uint16 *)&input)+3);
      
            bmRequestType = (Uint8)(bRequest_bmRequestType) & 0x00FF;
            bRequest      = (Uint8)(bRequest_bmRequestType >> 8) & 0x00FF;
            wValueL       = (Uint8)(wValue) & 0x00FF;
            wValueH       = (Uint8)(wValue>>8) & 0x00FF;
            wIndexL       = (Uint8)(wIndex) & 0x00FF;
            wIndexH       = (Uint8)(wIndex>>8) & 0x00FF;
            do_setup();
        // Other interrupts without receiving a package
        }
        else
        {
            // If the sending-data is > 64 bytes, here will send whatever left after the first 64 bytes
            if (TXPKTRDY == 0x0000 && ep0_frame > 0) 
            {

                if (left_over > 64) 
                {   
                    // Still more than one frame   
                    fifo_write(Desc_point + 64*ep0_frame, 64);
                    ep0_frame++;
                    left_over = left_over - 64;
                    USB_PERI_CSR0 |= 0x02;  // Set TXPKTRDY (B1 of PERI_CSR0)
                } 
                else 
                {                     
                    // Current data sending will finish here
                    fifo_write(Desc_point + 64*ep0_frame, left_over);
                    ep0_frame = 0;
                    left_over = 0;
                    USB_PERI_CSR0 |= 0x02; // Set TXPKTRDY (B1 of PERI_CSR0)
                    USB_PERI_CSR0 |= 0x08; // Set DATAEND(B3 of PERI_CSR0)
                 }
     
            }
 
            if (bRequest == 0x05)
            {
                USB_FADDR_POWER &= 0xFF00;
                USB_FADDR_POWER |= Addr;
            }
        }

        USB_INDEX_TESTMODE = 0x0000;  // Set INDEX pointing to EP0 and no test mode

    }//end of "if (ep0_rx_tx == 0x0001)"



    //////////////////////////////
    //EP1 interrupt service
    //////////////////////////////

    //EP1 sending a data package to host
    if (ep1_tx)
    {
//        get_mouse();
    }	  

    //EP1 receiving a data package from host
    if (ep1_rx)
    {

    }	  


 ///////// end of all endpoints service //////////

    USB_EOIR = 0x00; //enable CPU ack of interrupt completion

} // End of usb_isr (interrupt service routine) 

/* ------------------------------------------------------------------------ *
 *                                                                          *
 *  USB request setup functions                                             *
 *                                                                          *
 * ------------------------------------------------------------------------ */
void do_setup(void)
{							
    // Got a SETUP packet. Read the 8 SETUP bytes
    switch(bmRequestType&0x60) // Parse the SETUP packet.
    {
        case 0x00:  std_request();    break;
        case 0x20:  class_request();  break; // A place holder, not implmented 
        case 0x40:  vendor_request(); break; // A place holder, not implmented
        default:    stall_bus();             // Unrecognized request type
    }
}

/* ------------------------------------------------------------------------ *
 *                                                                          *
 *  Starndard requests                                                        *
 *                                                                          *
 * ------------------------------------------------------------------------ */
void std_request(void)
{
    switch(bRequest)
    {
        case  SR_GET_STATUS:         get_status();        break;
        case  SR_CLEAR_FEATURE:      clear_feature();     break;
        case  SR_SET_FEATURE:        set_feature();       break;
        case  SR_SET_ADDRESS:        set_address();       break;
        case  SR_GET_DESCRIPTOR:     send_descriptor();   break;
        case  SR_SET_DESCRIPTOR:     rcv_descriptor();    break;//not implemented
        case  SR_GET_CONFIGURATION:  get_configuration(); break;
        case  SR_SET_CONFIGURATION:  set_configuration(); break;
        case  SR_SET_INTERFACE:      set_interface();     break;
        case  SR_GET_INTERFACE:      get_interface();     break;
        //case  SR_SYNCH_FRAME:        synch_frame();     break;
       default:  stall_bus();
    }
}

/* ------------------------------------------------------------------------ *
 *                                                                          *
 *  Get status function                                                       *
 *                                                                          *
 * ------------------------------------------------------------------------ */
void get_status(void)
{
    unsigned char status_array[2] = {0x12, 0x34};
    Uint16 *status_array_ptr;

    status_array_ptr = (Uint16 *)status_array;

    switch(bmRequestType)	
    {
        case 0x80:  // DEVICE status
            status_array[0] = 0x00;
            status_array[1] = 0x01;
            fifo_write(status_array_ptr, 2);
            break; 				
        case 0x81:  // INTERFACE status
            status_array[0] = 0x00;
            status_array[1] = 0x00;
            fifo_write(status_array_ptr, 2);
            break; 				
        case 0x82:  // ENDPOINT status
            status_array[0] = 0x00;
            status_array[1] = 0x00;
            fifo_write(status_array_ptr, 2);

            if(wIndexL==0x81) 
            {   // For EP1_IN
                status_array[0] = 0x00;
                status_array[1] = ep1_in_status;
                fifo_write(status_array_ptr, 2);
                break;
            } 
            else if (wIndexL==0x01) 
            {   //for EP1_OUT
                status_array[0] = 0x00;
                status_array[1] = ep1_out_status;
                fifo_write(status_array_ptr, 2);
                break;    
            } 
            else 
            {  
                stall_bus();// Host tried to stall an invalid endpoint (not 3)
            }
        default:  stall_bus(); // Don't recognize the request
    } // End of switch
}

/* ------------------------------------------------------------------------ *
 *                                                                          *
 *  CLEAR_FEATURE                                                       *
 *                                                                          *
 * ------------------------------------------------------------------------ */
void clear_feature(void)
{
    //recipient is an EP; wValueL is feature selector, 00 is EP Halt; wIndexL -> EP1_IN
  /*  if((bmRequestType==0x02) && (wValueL==0x00) && (wIndexL==0x81)) 
    {
        stall_bus(); //not implemented
    }*/	  
}

/* ------------------------------------------------------------------------ *
 *                                                                          *
 *  SET_FEATURE; the test mode is requested during default state            *
 *                                                                          *
 * ------------------------------------------------------------------------ */
void set_feature(void)
{
    //recipient is a device; wValueL=02 is device-test; wIndexH=01(test_J); wIndexL->device
    if((bmRequestType==0x00) && (wValueL==0x02) && (wIndexH==0x01) && (wIndexL==0x00))
    {
        USB_INDEX_TESTMODE = 0x0200;
        USB_PERI_CSR0 |= 0x08; //set DATAEND(B3 of PERI_CSR0)
    //recipient is a device; wValueL=02 is device-test; wIndexH=02(test_K); wIndexL->device
    } 
    else if((bmRequestType==0x00) && (wValueL==0x02) && (wIndexH==0x02) && (wIndexL==0x00))
    {
        USB_INDEX_TESTMODE = 0x0400;
        USB_PERI_CSR0 |= 0x08; //set DATAEND(B3 of PERI_CSR0)
        //recipient is a device; wValueL=02 is device-test; wIndexH=03(test_SE0_NAK); wIndexL->device
    } 
    else if((bmRequestType==0x00) && (wValueL==0x02) && (wIndexH==0x03) && (wIndexL==0x00))
    {
        USB_INDEX_TESTMODE = 0x0100;
        USB_PERI_CSR0 |= 0x08; //set DATAEND(B3 of PERI_CSR0)
  //recipient is a device; wValueL=02 is device-test; wIndexH=04(test_packet); wIndexL->device
    } 
    else if((bmRequestType==0x00) && (wValueL==0x02) && (wIndexH==0x04) && (wIndexL==0x00))
    {
        testPktPtr = (Uint16 *)test_packet;
        fifo_write(testPktPtr, 53); //bug, need to write 53 bytes not 54???
        USB_INDEX_TESTMODE = 0x0800;
        USB_PERI_CSR0 |= 0x02; //set TXPKTRDY of PERI_CSR0 = 1
        USB_PERI_CSR0 |= 0x08;//set DATAEND: 0-length data package
    //recipient is a device; wValueL=02 is device-test; wIndexH=05(test_force_enable); wIndexL->device
    }
    else if((bmRequestType==0x00) && (wValueL==0x02) && (wIndexH==0x05) && (wIndexL==0x00))
    {
        stall_bus();
    }
}  

/* ------------------------------------------------------------------------ *
 *                                                                          *
 *  SET_ADDRESS                                                        *
 *                                                                          *
 * ------------------------------------------------------------------------ */
/*void set_address(void) 
{
    Addr = wValue; //address got here may not be useful
    USB_PERI_CSR0 |= 0x80; //set DATAEND: 0-length data package
}*/
/* ------------------------------------------------------------------------ *
 *                                                                          *
 *  SET_ADDRESS                                                        *
 *                                                                          *
 * ------------------------------------------------------------------------ */
void set_address(void) 
{
    Addr = wValue;
	USB_PERI_CSR0 |= 0x48; //set DATAEND(B3 of PERI_CSR0)
}

/* ------------------------------------------------------------------------ *
 *                                                                          *
 *  // GET_DESCRIPTOR request function
 * DESCRIPTOR type is based on USB2.0 spec Table9-5, p251                   *
 *                                                                          *
 * ------------------------------------------------------------------------ */
void send_descriptor(void)
{
int Desc_length;
Desc_length = 0;

    switch (wValueH) //the high-8bit of wValue is descriptor type
    {
        case  GD_DEVICE:        //send Device Descriptor
	        dev_des_req++;
            Desc_length = sizeof(deviceDesc);
            Desc_point = deviceDescPtr;
            break;	
        case  GD_CONFIGURATION: //send Configuration Descriptor; include interface and EP decriptors 
	        cfg_des_req++;
            Desc_length = sizeof(cfgDesc);
            Desc_point = cfgDescPtr;
            break;
        case  GD_STRING:
        	str_des_req++;
            Desc_length = strDesc[wValueL][0];
            Desc_point = (Uint16 *)strDesc[wValueL];
            break;
        case  GD_INTERFACE:
	        inf_des_req++;
            Desc_length = cfgDesc[9];
            Desc_point = cfgDescPtr + 9;
            break;
        case  GD_ENDPOINT:
	        enp_des_req++;
            Desc_length = cfgDesc[18];
            Desc_point = cfgDescPtr + 18;
            break;
        case  GD_REPORT:
	        enp_des_req++;
            Desc_length =  sizeof(reportDesc);
            Desc_point = reportDescPtr;
            break;
    }// end switch on descriptor type
  
  //In normal operation, a request will be decoded, and the Desc_length should
  //be set as a non-ZERO number
  //If Desc_length stays "0" (Desc_length=0) which indicates the request can
  //not be decoded

    if (Desc_length == 0) 
    { //error: the current request can NOT be decoded
        stall_bus();
    } 
    else if (wLength <= ((Uint16)(Desc_length)) && Desc_length <= 64) 
    {
        fifo_write(Desc_point, wLength);
        USB_PERI_CSR0 |= 0x02;//set TXPKTRDY (B1 of PERI_CSR0)
        USB_PERI_CSR0 |= 0x08; //set DATAEND(B3 of PERI_CSR0)
    } 
    else if (wLength > ((Uint16)(Desc_length)) && Desc_length <= 64) 
    {
        fifo_write(Desc_point, Desc_length);    
        USB_PERI_CSR0 |= 0x02;//set TXPKTRDY (B1 of PERI_CSR0)
        USB_PERI_CSR0 |= 0x08; //set DATAEND(B3 of PERI_CSR0)
    } 
    else if (wLength <= 64 && Desc_length > 64) 
    {
        fifo_write(Desc_point, wLength); //send out data no more than host asked
        USB_PERI_CSR0 |= 0x02;//set TXPKTRDY (B1 of PERI_CSR0)
        USB_PERI_CSR0 |= 0x08; //set DATAEND(B3 of PERI_CSR0) 
        //send out the first 64 byte package, but don't set the "DATAEND"
    } 
    else if (wLength > 64 && Desc_length > 64 && wLength > ((Uint16)(Desc_length))) 
    {
        fifo_write(Desc_point, 64);
        ep0_frame = 1;
        left_over = Desc_length - 64; //host asked more than we have
        USB_PERI_CSR0 |= 0x02;//set TXPKTRDY (B1 of PERI_CSR0)

    //send out the first 64 byte package, but don't set the "DATAEND"
    } 
    else if (wLength > 64 && Desc_length > 64 && wLength <= ((Uint16)(Desc_length))) 
    {
        fifo_write(Desc_point, 64);
        ep0_frame = 1;
        left_over = wLength - 64; //host asked less or equal we have
        USB_PERI_CSR0 |= 0x02;//set TXPKTRDY (B1 of PERI_CSR0)
    } 
    else 
    {
        error = 9;
    }
	if(wValueH == GD_REPORT)
	{
	    mouseOn = 1;
	    //get_mouse();
	}

} //end of "send_descriptor" function

/* ------------------------------------------------------------------------ *
 *                                                                          *
 *  SET_DESCRIPTOR: optional, not implemented                                                       *
 *                                                                          *
 * ------------------------------------------------------------------------ */
void rcv_descriptor(void)
{
    stall_bus();
}

/* ------------------------------------------------------------------------ *
 *                                                                          *
 *  GET_CONFIGURATION                                                       *
 *                                                                          *
 * ------------------------------------------------------------------------ */
void get_configuration(void)
{
    fifo_write(&curCfg, 1);
    USB_PERI_CSR0 |= 0x02;//set TXPKTRDY of PERI_CSR0
    USB_PERI_CSR0 |= 0x08; //set DATAEND(B3 of PERI_CSR0)
}

/* ------------------------------------------------------------------------ *
 *                                                                          *
 *  SET_CONFIGURATION                                                        *
 *                                                                          *
 * ------------------------------------------------------------------------ */
void set_configuration(void)
{
    //Set Configuration value if this is a real configuration value 
    if(wValue != 0x0000) 
    {
        curCfg = wValue; 
        USB_PERI_CSR0 |= 0x08; //set DATAEND(B3 of PERI_CSR0)
    }
}  

/* ------------------------------------------------------------------------ *
 *                                                                          *
 *  SET_INTERFACE                                                        *
 *                                                                          *
 * ------------------------------------------------------------------------ */
//Only accept Interface=0 and AlternateSetting=0, otherwise send STALL
//wValueL=Alternate Setting index; wIndexL=Interface index
void set_interface(void)
{
    if(wValueL==0x00 && wIndexL==0x00 && wLength==0x0000)
    {
        interface_setting = wValue; //save the interterface setting
        USB_PERI_CSR0 |= 0x08; //set DATAEND(B3 of PERI_CSR0)
    } 
    else 
    {
        stall_bus();
    }
}

/* ------------------------------------------------------------------------ *
 *                                                                          *
 *  GET_INTERFACE                                                        *
 *                                                                          *
 * ------------------------------------------------------------------------ */
//Check for Interface=0, always report AlternateSetting=0
void get_interface(void)
{
    if(wIndexL==0 && wValue==0x0000 && wLength == 0x0000)// wIndexL=Interface index
    {
        fifo_write(&interface_setting, 1);
        USB_PERI_CSR0 |= 0x02;//set TXPKTRDY(B1 of PERI_CSR0)
        USB_PERI_CSR0 |= 0x08; //set DATAEND(B3 of PERI_CSR0)
    } 
    else 
    {
        stall_bus();
    }
}

/* ------------------------------------------------------------------------ *
 *                                                                          *
 *  CLASS REQUEST                                                           *
 *                                                                          *
 * ------------------------------------------------------------------------ */
void class_request(void) 
{
    //stall_bus();
}                         

/* ------------------------------------------------------------------------ *
 *                                                                          *
 *  VENDOR REQUEST                                                          *
 *                                                                          *
 * ------------------------------------------------------------------------ */
void vendor_request(void)
{
    stall_bus();
}
/* ------------------------------------------------------------------------ *
 *                                                                          *
 *  Send "stall bus" signal to host                                         *
 *                                                                          *
 * ------------------------------------------------------------------------ */
void stall_bus(void)
{
    //set SERV_RXPKTRDY bit of PERI_CSR0 to clear RXPKTRDY bit
    USB_PERI_CSR0 |= 0x40;
    //set SENDSTALL bit of PERI_CSR0 to transmit STALL and terminate the current transaction 
    USB_PERI_CSR0 |= 0x20;
}

