/* 
 */

#ifndef HMAIN_H
#define	HMAIN_H

#define SYS_FREQ 		(40000000L)
#define GetSystemClock()        (40000000L)
#define	GetPeripheralClock()	(GetSystemClock()/(1 << OSCCONbits.PBDIV))
#define	GetInstructionClock()	(GetSystemClock())

#define  NOP() asm("NOP");
#define  nop asm("NOP");

#define LED_TRIS            TRISBbits.TRISB12 = 0;
#define LED_HIGH            LATBbits.LATB12 = 1;
#define LED_LOW             LATBbits.LATB12 = 0;

#define BLE_RESET_TRIS      TRISBbits.TRISB2 = 0;
#define BLE_RESET_HIGH      LATBbits.LATB2 = 1;
#define BLE_RESET_LOW       LATBbits.LATB2 = 0;


#endif	/* HMAIN_H */

