/* 
 */
#define _SUPPRESS_PLIB_WARNING 1
#include <p32xxxx.h>
#include <plib.h>
#include "HMain.h"
//config
#pragma config FPLLMUL = MUL_20, FPLLIDIV = DIV_2, FPLLODIV = DIV_2
#pragma config POSCMOD = HS, FNOSC = PRIPLL, FPBDIV = DIV_1
#pragma config FWDTEN = OFF
#pragma config FSOSCEN = OFF
#pragma config WDTPS = PS4
#pragma config CP=OFF, BWP=OFF
#pragma config FCKSM = CSDCMD
#pragma config ICESEL   = ICS_PGx1      // ICE/ICD Comm Channel Select
#pragma config JTAGEN = OFF
//USB
#pragma config FUSBIDIO = OFF
#pragma config FVBUSONIO = OFF

unsigned char OS_Str_1[64];

//#=================================================================================================
//#=================================================================================================
void __ISR( _EXTERNAL_0_VECTOR, ipl2) INT0Interrupt( void)
{ // input capture interrupt service routine
   Delayms(10);
   SoftReset();
   mINT0ClearIntFlag();
}

//#=================================================================================================
//#=================================================================================================
int main( void ) {
    Tweeq_Init();

    COMM1_Tx_Str("EXAMPLE : INT0 external intrrupt \n");

    ConfigINT0(EXT_INT_PRI_2 | FALLING_EDGE_INT | EXT_INT_ENABLE);

    // enable multi-vector interrupts
    INTEnableSystemMultiVectoredInt();

    while(1)
    {
        LED_HIGH;
        Delayms(250);
        LED_LOW;
        Delayms(250);

        COMM1_Tx_Str("Endless \n");;
    }

    return (EXIT_SUCCESS);
}
//#=================================================================================================
//#=================================================================================================

