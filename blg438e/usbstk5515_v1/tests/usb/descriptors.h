/*
 *  Copyright 2010 by Spectrum Digital Incorporated.
 *  All rights reserved. Property of Spectrum Digital Incorporated.
 */
 /*
 *  EVMC5515 USB Definitions
 *
 */

int error=0; //Error count. Should be 0 at end of test.
int rev=0;
int set_address_cnt=0;
int address2=0;
int dev_des_req=0;
int cfg_des_req=0;
int str_des_req=0;
int inf_des_req=0;
int enp_des_req=0;
int no_rpk=0;
int i;

Uint16 *inPtr, *deviceDescPtr, *cfgDescPtr, *strDescPtr, *reportDescPtr;
Uint16 bRequest_bmRequestType;
Uint8 bmRequestType;
Uint8 bRequest;
Uint8 wValueL;
Uint8 wValueH;
Uint8 wIndexL;
Uint8 wIndexH;
Uint8 ep1_in_status;
Uint8 ep1_out_status;
Uint16 Addr = 0;
Uint16 curCfg = 0;
Uint16 Req = 0;  
Uint16 wValue = 0;
Uint16 wIndex = 0;
Uint16 wLength = 0;
Uint16 interface_setting = 0;



Uint16 intrReg1 = 0;
Uint16 intrReg2 = 0;
Uint16 txIntStat = 0;
Uint16 rxIntStat = 0;
Uint16 usbIntStat = 0;
Uint16 *pBuffer16_ep1;
Uint16 *pBuffer16_ep2;
Uint16 *pBuffer16_ep3;
Uint16 *pBuffer16_ep4;
Uint8 rxCount;

//Uint8 pBuffer[512]; // Buffer for in out endpoints 
Uint8 pBuffer8_ep1[512]; // Buffer for EP1 in/out
Uint8 pBuffer8_ep2[64]; // Buffer for EP2 in/out
Uint8 pBuffer8_ep3[64]; // Buffer for EP3 in/out
Uint8 pBuffer8_ep4[64]; // Buffer for EP4 in/out

unsigned char suspend = 0x00;
unsigned char reset_usb = 0x00;
unsigned char resume = 0x00; 
Uint16 ep0_rx_tx = 0x0000;
Uint16 ep1_rx = 0x0000;
Uint16 ep2_rx = 0x0000;
Uint16 ep3_rx = 0x0000;
Uint16 ep4_rx = 0x0000;

Uint16 ep1_tx = 0x0000;
Uint16 ep2_tx = 0x0000;
Uint16 ep3_tx = 0x0000;
Uint16 ep4_tx = 0x0000;
Uint16 resetCnt = 0;
unsigned char input[8];

int ep0_frame = 0;
int left_over = 0;
Uint16 *Desc_point;

Uint16 RXPKTRDY;
Uint16 TXPKTRDY;
Uint16 SENTSTALL;

Uint16 *testPktPtr;



//USB Device Descriptor: 18-bytes
const unsigned char deviceDesc[]=
  {0x12,       // bLength = 18d
   0x01,       // bDeviceDescriptorType=1(defined by USB spec)
   0x00, 0x02, // bcdUSB USB Version 2.0 (L-Byte/H-Byte)
   0x00,       // bDeviceClass
   0x00,       // bDeviceSubclass
   0x00,       // bDeviceProtocol
   0x40,       // bMaxPacketSize 64 Bytes
   0xB3, 0x04, // idVendor(L-Byte/H-Byte)
   0x0B, 0x31, // idProduct(L-Byte/H-Byte)
   0x10, 0x01, // bcdDevice(L-Byte/H-Byte): device's release number 
   0,          // iManufacturer String Index
   0,          // iProduct String Index
   0,          // iSerialNumber String Index
   1};         // bNumberConfigurations

//Configuration Descriptors
const unsigned char cfgDesc[]=
  {
  // CONFIGURATION Descriptor
  0x09,      // bLength
  0x02,      // bDescriptorType = Config (constant)
  0x22,  0x00, // wTotalLength(L/H)
  0x01,      // bNumInterfaces
  0x01,      // bConfigValue
  0x00,      // iConfiguration
  0xA0,      // bmAttributes; 
  0x28,      // MaxPower is 80mA
  // INTERFACE Descriptor
  0x09,      // length = 9
  0x04,      // type = IF; constant 4 for INTERFACE
  0x00,      // IF #0; Interface Identification #
  0x00,      // bAlternate Setting
  0x01,      // bNumber of Endpoints = 1 for 5515 mouse
  0x03,      // bInterfaceClass = HID
  0x01,      // bInterfaceSubClass = Boot Interface
  0x02,      // bInterfaceProtocol = Mouse
  0x00,      // iInterface
  // HID Descriptor
  0x09,      // length = 9
  0x21,      // bDescriptorType = HID
  0x00,      // bcdHID = HID Class Spec version
  0x01,      // 
  0x00,      // 
  0x01,      // bNumDescriptors = Number of Decriptors
  0x22,      // bDescriptorType = 34 (REPORT)
  0x34,      // wDescriptorLength = 52
  0x00,      // 
  // EndPoint_1_IN Descriptor
  0x07,      // bLength
  0x05,      // bDescriptorType (Endpoint)
  0x81,      // bEndpointAddress and direction(IN)    
  0x03,      // bmAttributes: B1B0->transfer-type: control=00; Iso=01; bulk=10; interrupt=11   
  0x04,0x00, // wMaxPacketSize(L/H)=4
  0x0A,      // bInterval: Max latency

  };

Uint8 reportDesc[] = {0x05,0x01,0x09,0x02,0xa1,0x01,0x09,0x01,
                                   0xa1,0x00,0x05,0x09,0x19,0x01,0x29,0x03,
                                   0x15,0x00,0x25,0x01,0x95,0x03,0x75,0x01,
                                   0x81,0x02,0x95,0x01,0x75,0x05,0x81,0x01,
                                   0x05,0x01,0x09,0x30,0x09,0x31,0x09,0x38,
                                   0x15,0x81,0x25,0x7f,0x75,0x08,0x95,0x03,
                                   0x81,0x06,0xc0,0xc0};

const unsigned char strDesc[4][64] = {
//string 0
{	
           4,  //>> length-in-byte
        0x03,  //   bDescriptorType = string
  0x09, 0x04,  //   English-USA
},

//string 1
{	
    36, 0x03, //string-length-in-byte, Manufacture ID
   'T', 0x00, 
   'e', 0x00, 
   'x', 0x00, 
   'a', 0x00,
   's', 0x00, 
   ' ', 0x00, 
   'I', 0x00, 
   'n', 0x00,
   's', 0x00, 
   't', 0x00, 
   'r', 0x00, 
   'u', 0x00,
   'm', 0x00, 
   'e', 0x00, 
   'n', 0x00, 
   't', 0x00,
   's', 0x00,
},

//string 2
{	
    12, 0x03, //string-length-in-byte, Product ID
   'C', 0x00,
   '5', 0x00, 
   '5', 0x00, 
   '0', 0x00,
   '5', 0x00,
},

//string 3
{	
    12, 0x03, //string-length-in-byte, Serial# ID
   '0', 0x00, 
   '0', 0x00, 
   '0', 0x00, 
   '0', 0x00,  
   '1', 0x00
}
};

//USB2.0 test data package, constants from the spec
const unsigned char test_packet[53] = {
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
  0xAA,0xEE,0xEE,0xEE,0xEE,0xEE,0xEE,0xEE,
  0xEE,0xFE,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
  0xFF,0xFF,0xFF,0xFF,0xFF,0x7F,0xBF,0xDF,
  0xEF,0xF7,0xFB,0xFD,0xFC,0x7E,0xBF,0xDF,
  0xEF,0xF7,0xFB,0xFD,0x7E};

//////////////////////////
// Standard USB Requests
//////////////////////////
#define SR_GET_STATUS         0x00// Get Status
#define SR_CLEAR_FEATURE      0x01// Clear Feature
#define SR_SET_FEATURE        0x03// Set Feature
#define SR_SET_ADDRESS        0x05// Set Address
#define SR_GET_DESCRIPTOR     0x06// Get Descriptor
#define SR_SET_DESCRIPTOR     0x07// Set Descriptor
#define SR_GET_CONFIGURATION  0x08// Get Configuration
#define SR_SET_CONFIGURATION  0x09// Set Configuration
#define SR_GET_INTERFACE      0x0a// Get Interface
#define SR_SET_INTERFACE      0x0b// Set Interface
//#define SYNCH_FRAME         0x0c

// Get Descriptor type codes	
#define GD_DEVICE         0x01 //Get device descriptor: Device
#define GD_CONFIGURATION  0x02 //Get device descriptor: Configuration
#define GD_STRING         0x03 //Get device descriptor: String
#define GD_INTERFACE      0x04 //Get descriptor: HID
#define GD_ENDPOINT       0x05 //Get descriptor: EP
#define GD_REPORT         0x22 //Get descriptor: Report
