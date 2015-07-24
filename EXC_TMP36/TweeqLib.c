/*
 */
#include <p32xxxx.h>
#define _SUPPRESS_PLIB_WARNING 1
#include <plib.h>

#include "HMain.h"
//#=============================================================================
//# Delays
//#=============================================================================
//#-----------------------------------------------------------------------------
void Tweeq_Init( void ) {
    ANSELA = 0x0;	//All pin digital
    ANSELB = 0x0;
    BLE_RESET_TRIS;     //BLE RESET PIN
    BLE_RESET_HIGH;
    LED_TRIS;
    COMM1_Init();
    COMM2_Init();
}
//#=============================================================================
//# Delays
//#=============================================================================
//#-----------------------------------------------------------------------------
void Delayus(unsigned int t) {
    unsigned int CalT;
    WriteCoreTimer(0);
    CalT = t * 20;

    while ( (unsigned int)(ReadCoreTimer()) < CalT ) {};
} //Delayus
//#=============================================================================
//# Delayms
//#-----------------------------------------------------------------------------
void Delayms(unsigned int t) {
    unsigned int T = 0;
    while ( (T++) < t )
    {
        Delayus(999);
    }
} //Delayms
//#=============================================================================

//#=================================================================================================
// COMM1
//#=================================================================================================
//#-------------------------------------------------------------------------------------------------
void COMM1_Init( void )
{
    _TRISB13 = 1;
    U1RXRbits.U1RXR = 3; //
    RPB15Rbits.RPB15R = 1; //
    U1BRG = (SYS_FREQ/17/(115200)); //
    UARTSetDataRate(UART1, SYS_FREQ, 115200);
    U1MODE = UART_EN;
    U1STA = (UART_RX_ENABLE | UART_TX_ENABLE);
}
//#-------------------------------------------------------------------------------------------------
void COMM1_Tx(unsigned int d)
{
    while( U1STAbits.UTXBF);
    putcUART1(d);
}
//#-------------------------------------------------------------------------------------------------
void COMM1_Tx_Str(unsigned char *str)
{
    while ((*str) != '\0')
    {
        COMM1_Tx(*str );
        *(str++);
    }
}
//-----------------------------------------------==================================================
// COMM2
//#-------------------------------------------------------------------------------------------------
void COMM2_Init( void )
{
    _TRISB5 = 1;
    U2RXRbits.U2RXR = 1; //
    RPB10Rbits.RPB10R = 2; //
    U2BRG = (SYS_FREQ/17/(115200));
    UARTSetDataRate(UART2, SYS_FREQ, 115200);
    U2MODE = UART_EN;
    U2STA = (UART_RX_ENABLE | UART_TX_ENABLE);
}
//#-------------------------------------------------------------------------------------------------
void COMM2_Tx(unsigned int d)
{
    while( U2STAbits.UTXBF);
    putcUART2(d);
}
//#-------------------------------------------------------------------------------------------------
void COMM2_Tx_Str(unsigned char *str)
{
    while ((*str) != '\0')
    {
        COMM2_Tx(*str );
        *(str++);
    }
}
//#-------------------------------------------------------------------------------------------------
int COMM2_Rx( void )
{
int rx;

    if (U1STAbits.URXDA)
    {
        rx = U1RXREG;
    }else
    {
        rx = -1;
    }
    return rx;
}

//#=================================================================================================
// SPI
//#=================================================================================================
int SPI1_Write_8( int i)
{
    SPI1BUF = i;                  // write to buffer for TX
    while( !SPI1STATbits.SPIRBF); // wait for transfer complete

    //INTClearFlag(INT_SPI1);
    SPI1STATCLR = 0x40;           // clear Overflow bit

    return SPI1BUF;               // read the received value
}//SPI1_Write_8
//#-------------------------------------------------------------------------------------------------
int SPI1_Init( void )
{
    _TRISB11 = 1; //SDI
    _TRISB6 = 0;  //SDO
    SDI1Rbits.SDI1R = 0b011; //
    RPB6Rbits.RPB6R = 0B011; //

    int rData = SPI1BUF;

    SPI1STATCLR = 0x40;
    //SpiChnOpen(1, SPI_CON_MODE8 |SPI_OPEN_MSTEN|SPI_OPEN_MODE8, 2);
    SPI1CON = 0x8120 ;
    SPI1BRG = 5; //0 - FAST : 256 - SLOW

    SPI1CONbits.SMP = 0;
    SPI1CONbits.CKE = 1;

    return SPI1BUF;               // read the received value
}//SPI1_Init
//#-------------------------------------------------------------------------------------------------



//#=================================================================================================
#define EEPROM_I2C_BUS              I2C1
//==============================================================================
void i2c_Init( void )
{
    I2C1BRG = 0X080; //
    I2C1CON = 0X9200; //I2C1CON.ON = 1
}
//==============================================================================
BOOL i2c_Start(UINT8 restart )
{
    I2C_STATUS  status;

    // Send the Start (or Restart) signal
    if(restart)
    {
        //I2CRepeatStart(EEPROM_I2C_BUS);
           I2C1CONbits.RSEN = 1;
    }
    else
    {
        // Wait for the bus to be idle, then start the transfer
        while( !I2CBusIsIdle(EEPROM_I2C_BUS) );

        if(I2CStart(EEPROM_I2C_BUS) != I2C_SUCCESS)
        {
            DBPRINTF("Error: Bus collision during transfer Start\n");
            return FALSE;
        }
    }

    // Wait for the signal to complete
    do
    {
        status = I2CGetStatus(EEPROM_I2C_BUS);
    } while ( !(status & I2C_START) );


    return TRUE;
}
//==============================================================================
void i2c_Stop( void )
{
    I2C_STATUS  status;

    // Send the Stop signal
    I2CStop(EEPROM_I2C_BUS);

    // Wait for the signal to complete
    do
    {
        status = I2CGetStatus(EEPROM_I2C_BUS);

    } while ( !(status & I2C_STOP) );
}
//==============================================================================
BOOL i2c_Tx( UINT8 data )
{
    // Wait for the transmitter to be ready
    while(!I2CTransmitterIsReady(EEPROM_I2C_BUS));
    //while ( !I2C1STATbits.TBF ) ;

    // Transmit the byte
    if(I2CSendByte(EEPROM_I2C_BUS, data) == I2C_MASTER_BUS_COLLISION)
    {
        putsUART1("Error: I2C Master Bus Collision\n");
        return FALSE;
    }
    //I2C1TRN = data;

    // Wait for the transmission to finish
    while(!I2CTransmissionHasCompleted(EEPROM_I2C_BUS));
    //while ( I2C1STATbits.TRSTAT );

    return TRUE;
}
//==============================================================================
int i2c_Rx( int Nack )
{
    I2C1CONbits.RCEN = 1;

    while( !I2C1STATbits.RBF );

    if (Nack == 1)
    {
        I2C1CONbits.ACKDT = 1;
        I2C1CONbits.ACKEN = 1;
    }else
    {
        I2C1CONbits.ACKDT = 0;
        I2C1CONbits.ACKEN = 1;
    }

    if(I2CReceiverEnable(EEPROM_I2C_BUS, TRUE) == I2C_RECEIVE_OVERFLOW)
    {
        putsUART1("Error: I2C Receive Overflow\n");
        return FALSE;
    }
    else
    {
        int x;
        while(!I2CReceivedDataIsAvailable(EEPROM_I2C_BUS));
        x = I2CGetByte(EEPROM_I2C_BUS);

        while ( I2C1CONbits.ACKEN );

        return x;
    }
}
//==============================================================================
//==============================================================================

