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
int main( void ) {
    Tweeq_Init();

    COMM1_Tx_Str("EXAMPLE : ADC TMP36 \n");

    Delayms(100);

    _TRISA0 = 1;

    // configure and enable the ADC
    CloseADC10();	// ensure the ADC is off before setting the configuration
    // define setup parameters for OpenADC10
    // Turn module on | output in integer | trigger mode auto | enable  autosample
    #define PARAM1  ADC_MODULE_ON | ADC_FORMAT_INTG | ADC_CLK_AUTO | ADC_AUTO_SAMPLING_ON
    // define setup parameters for OpenADC10
    // ADC ref external    | disable offset test    | enable scan mode | perform 2 samples | use one buffer | use MUXA mode
    // note: to read X number of pins you must set ADC_SAMPLES_PER_INT_X
    #define PARAM2  ADC_VREF_AVDD_AVSS | ADC_OFFSET_CAL_DISABLE | ADC_SCAN_ON | ADC_SAMPLES_PER_INT_2 | ADC_ALT_BUF_OFF | ADC_ALT_INPUT_OFF
    // define setup parameters for OpenADC10
    // use ADC internal clock | set sample time
    #define PARAM3  ADC_CONV_CLK_INTERNAL_RC | ADC_SAMPLE_TIME_15
    // define setup parameters for OpenADC10

    // set AN0 - RA0
    #define PARAM4 ENABLE_AN0_ANA

    // define setup parameters for OpenADC10
    // do not assign channels to scan
    #define PARAM5 SKIP_SCAN_AN1 | SKIP_SCAN_AN2 | SKIP_SCAN_AN3 | SKIP_SCAN_AN4 | SKIP_SCAN_AN5 | SKIP_SCAN_AN6 | SKIP_SCAN_AN7 | SKIP_SCAN_AN8 | SKIP_SCAN_AN9 | SKIP_SCAN_AN10 | SKIP_SCAN_AN11 | SKIP_SCAN_AN12 | SKIP_SCAN_AN13 | SKIP_SCAN_AN14 | SKIP_SCAN_AN15

    // use ground as neg ref for A
    SetChanADC10( ADC_CH0_NEG_SAMPLEA_NVREF); // use ground as the negative reference
    OpenADC10( PARAM1, PARAM2, PARAM3, PARAM4, PARAM5 ); // configure ADC using parameter define above

    EnableADC10(); // Enable the ADC
    //while ( ! mAD1GetIntFlag() ) { }

    
    while(1)
    {
        LED_HIGH;
        Delayms(500);
        LED_LOW;
        Delayms(500);

        COMM1_Tx_Str("ADC = ");  //read ADC
        int adcV = ReadADC10(0);

        //claculate in C
        float Temp = (adcV * 3.3) / 1024;
        Temp = (Temp - 0.5) * 100;
        
        sprintf(OS_Str_1, "%d : : %f C", adcV, Temp);

        //Display
        putsUART1(( unsigned char * )OS_Str_1);

        COMM1_Tx_Str(" \n");
    }

    return (EXIT_SUCCESS);
}
//#=================================================================================================
//#=================================================================================================
