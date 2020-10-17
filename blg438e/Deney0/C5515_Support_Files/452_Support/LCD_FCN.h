#ifndef LCD_FCN_H_
#define LCD_FCN_H_

Int16 OSD9616_send( Uint16 comdat, Uint16 data );
Int16 OSD9616_multiSend( Uint8* data, Uint16 len );
void LCD_init(void);
void LCD_Display(Int16 * array, Int16 power);

#endif /*LCD_FCN_H_*/
