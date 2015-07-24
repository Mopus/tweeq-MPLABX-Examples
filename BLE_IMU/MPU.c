#define _SUPPRESS_PLIB_WARNING 1
#include <stdio.h>
#include <stdlib.h>
#include <p32xxxx.h>                // Processor defs
#include <plib.h>

#define MPU6050_ADDRESS 0b11010010 // Address with end write bit
#define MPU6050_RA_XG_OFFS_TC 0x00 //[7] PWR_MODE, [6:1] XG_OFFS_TC, [0] OTP_BNK_VLD
#define MPU6050_RA_YG_OFFS_TC 0x01 //[7] PWR_MODE, [6:1] YG_OFFS_TC, [0] OTP_BNK_VLD
#define MPU6050_RA_ZG_OFFS_TC 0x02 //[7] PWR_MODE, [6:1] ZG_OFFS_TC, [0] OTP_BNK_VLD
#define MPU6050_RA_X_FINE_GAIN 0x03 //[7:0] X_FINE_GAIN
#define MPU6050_RA_Y_FINE_GAIN 0x04 //[7:0] Y_FINE_GAIN
#define MPU6050_RA_Z_FINE_GAIN 0x05 //[7:0] Z_FINE_GAIN
#define MPU6050_RA_XA_OFFS_H 0x06 //[15:0] XA_OFFS
#define MPU6050_RA_XA_OFFS_L_TC 0x07
#define MPU6050_RA_YA_OFFS_H 0x08 //[15:0] YA_OFFS
#define MPU6050_RA_YA_OFFS_L_TC 0x09
#define MPU6050_RA_ZA_OFFS_H 0x0A //[15:0] ZA_OFFS
#define MPU6050_RA_ZA_OFFS_L_TC 0x0B
#define MPU6050_RA_XG_OFFS_USRH 0x13 //[15:0] XG_OFFS_USR
#define MPU6050_RA_XG_OFFS_USRL 0x14
#define MPU6050_RA_YG_OFFS_USRH 0x15 //[15:0] YG_OFFS_USR
#define MPU6050_RA_YG_OFFS_USRL 0x16
#define MPU6050_RA_ZG_OFFS_USRH 0x17 //[15:0] ZG_OFFS_USR
#define MPU6050_RA_ZG_OFFS_USRL 0x18
#define MPU6050_RA_SMPLRT_DIV 0x19
#define MPU6050_RA_CONFIG 0x1A
#define MPU6050_RA_GYRO_CONFIG 0x1B
#define MPU6050_RA_ACCEL_CONFIG 0x1C
#define MPU6050_RA_FF_THR 0x1D
#define MPU6050_RA_FF_DUR 0x1E
#define MPU6050_RA_MOT_THR 0x1F
#define MPU6050_RA_MOT_DUR 0x20
#define MPU6050_RA_ZRMOT_THR 0x21
#define MPU6050_RA_ZRMOT_DUR 0x22
#define MPU6050_RA_FIFO_EN 0x23
#define MPU6050_RA_I2C_MST_CTRL 0x24
#define MPU6050_RA_I2C_SLV0_ADDR 0x25
#define MPU6050_RA_I2C_SLV0_REG 0x26
#define MPU6050_RA_I2C_SLV0_CTRL 0x27
#define MPU6050_RA_I2C_SLV1_ADDR 0x28
#define MPU6050_RA_I2C_SLV1_REG 0x29
#define MPU6050_RA_I2C_SLV1_CTRL 0x2A
#define MPU6050_RA_I2C_SLV2_ADDR 0x2B
#define MPU6050_RA_I2C_SLV2_REG 0x2C
#define MPU6050_RA_I2C_SLV2_CTRL 0x2D
#define MPU6050_RA_I2C_SLV3_ADDR 0x2E
#define MPU6050_RA_I2C_SLV3_REG 0x2F
#define MPU6050_RA_I2C_SLV3_CTRL 0x30
#define MPU6050_RA_I2C_SLV4_ADDR 0x31
#define MPU6050_RA_I2C_SLV4_REG 0x32
#define MPU6050_RA_I2C_SLV4_DO 0x33
#define MPU6050_RA_I2C_SLV4_CTRL 0x34
#define MPU6050_RA_I2C_SLV4_DI 0x35
#define MPU6050_RA_I2C_MST_STATUS 0x36
#define MPU6050_RA_INT_PIN_CFG 0x37
#define MPU6050_RA_INT_ENABLE 0x38
#define MPU6050_RA_DMP_INT_STATUS 0x39
#define MPU6050_RA_INT_STATUS 0x3A
#define MPU6050_RA_ACCEL_XOUT_H 0x3B
#define MPU6050_RA_ACCEL_XOUT_L 0x3C
#define MPU6050_RA_ACCEL_YOUT_H 0x3D
#define MPU6050_RA_ACCEL_YOUT_L 0x3E
#define MPU6050_RA_ACCEL_ZOUT_H 0x3F
#define MPU6050_RA_ACCEL_ZOUT_L 0x40
#define MPU6050_RA_TEMP_OUT_H 0x41
#define MPU6050_RA_TEMP_OUT_L 0x42
#define MPU6050_RA_GYRO_XOUT_H 0x43
#define MPU6050_RA_GYRO_XOUT_L 0x44
#define MPU6050_RA_GYRO_YOUT_H 0x45
#define MPU6050_RA_GYRO_YOUT_L 0x46
#define MPU6050_RA_GYRO_ZOUT_H 0x47
#define MPU6050_RA_GYRO_ZOUT_L 0x48
#define MPU6050_RA_EXT_SENS_DATA_00 0x49
#define MPU6050_RA_EXT_SENS_DATA_01 0x4A
#define MPU6050_RA_EXT_SENS_DATA_02 0x4B
#define MPU6050_RA_EXT_SENS_DATA_03 0x4C
#define MPU6050_RA_EXT_SENS_DATA_04 0x4D
#define MPU6050_RA_EXT_SENS_DATA_05 0x4E
#define MPU6050_RA_EXT_SENS_DATA_06 0x4F
#define MPU6050_RA_EXT_SENS_DATA_07 0x50
#define MPU6050_RA_EXT_SENS_DATA_08 0x51
#define MPU6050_RA_EXT_SENS_DATA_09 0x52
#define MPU6050_RA_EXT_SENS_DATA_10 0x53
#define MPU6050_RA_EXT_SENS_DATA_11 0x54
#define MPU6050_RA_EXT_SENS_DATA_12 0x55
#define MPU6050_RA_EXT_SENS_DATA_13 0x56
#define MPU6050_RA_EXT_SENS_DATA_14 0x57
#define MPU6050_RA_EXT_SENS_DATA_15 0x58
#define MPU6050_RA_EXT_SENS_DATA_16 0x59
#define MPU6050_RA_EXT_SENS_DATA_17 0x5A
#define MPU6050_RA_EXT_SENS_DATA_18 0x5B
#define MPU6050_RA_EXT_SENS_DATA_19 0x5C
#define MPU6050_RA_EXT_SENS_DATA_20 0x5D
#define MPU6050_RA_EXT_SENS_DATA_21 0x5E
#define MPU6050_RA_EXT_SENS_DATA_22 0x5F
#define MPU6050_RA_EXT_SENS_DATA_23 0x60
#define MPU6050_RA_MOT_DETECT_STATUS 0x61
#define MPU6050_RA_I2C_SLV0_DO 0x63
#define MPU6050_RA_I2C_SLV1_DO 0x64
#define MPU6050_RA_I2C_SLV2_DO 0x65
#define MPU6050_RA_I2C_SLV3_DO 0x66
#define MPU6050_RA_I2C_MST_DELAY_CTRL 0x67
#define MPU6050_RA_SIGNAL_PATH_RESET 0x68
#define MPU6050_RA_MOT_DETECT_CTRL 0x69
#define MPU6050_RA_USER_CTRL 0x6A
#define MPU6050_RA_PWR_MGMT_1 0x6B
#define MPU6050_RA_PWR_MGMT_2 0x6C
#define MPU6050_RA_BANK_SEL 0x6D
#define MPU6050_RA_MEM_START_ADDR 0x6E
#define MPU6050_RA_MEM_R_W 0x6F
#define MPU6050_RA_DMP_CFG_1 0x70
#define MPU6050_RA_DMP_CFG_2 0x71
#define MPU6050_RA_FIFO_COUNTH 0x72
#define MPU6050_RA_FIFO_COUNTL 0x73
#define MPU6050_RA_FIFO_R_W 0x74
#define MPU6050_RA_WHO_AM_I 0x75

#define GYROCLK_MAXVAL 0xFFFF
#define GYRO_SECS_PER_CLK 2.5005722/(10^10)

unsigned int curr_I2C_Addr;
unsigned int gyroScale = 500;
unsigned int accelScale= 2;

void MPU_SetAddr( unsigned int I2C_Addr)
{
    curr_I2C_Addr = I2C_Addr<<1;
}
unsigned char OS_Str_1[64];
unsigned int MPU_GetID( void )
{
unsigned int Rx1, Rx2;
    i2c_Start(0);
    i2c_Tx(curr_I2C_Addr);
    i2c_Tx(0x75);
    i2c_Start(1); //ReStart
    i2c_Tx(curr_I2C_Addr + 1);
    //Rx1 = i2c_Rx(0);
    Rx1 = i2c_Rx(1);
    i2c_Stop();
    return Rx1;
}

void MPU_WriteReg_1( unsigned int Addr, unsigned int xData )
{
    i2c_Start(0);
    i2c_Tx(curr_I2C_Addr);
    i2c_Tx(Addr);
    i2c_Tx(xData);
    i2c_Stop();
    Delayms(1);
}

void MPU_Init()
{
    //Sets sample rate to 8000/1+7 = 1000Hz
    MPU_WriteReg_1(MPU6050_RA_SMPLRT_DIV, 0x07);
    //Disable FSync, 256Hz DLPF
    MPU_WriteReg_1(MPU6050_RA_CONFIG, 0x00);
    //Disable gyro self tests, scale of 500 degrees/s
    //Disable accel self tests, scale of +-2g, no DHPF
    MPU_Config(2,500);
    //Freefall threshold of |0mg|
    MPU_WriteReg_1(MPU6050_RA_FF_THR, 0x00);
    //Freefall duration limit of 0
    MPU_WriteReg_1(MPU6050_RA_FF_DUR, 0x00);
    //Motion threshold of 0mg
    MPU_WriteReg_1(MPU6050_RA_MOT_THR, 0x00);
    //Motion duration of 0s
    MPU_WriteReg_1(MPU6050_RA_MOT_DUR, 0x00);
    //Zero motion threshold
    MPU_WriteReg_1(MPU6050_RA_ZRMOT_THR, 0x00);
    //Zero motion duration threshold
    MPU_WriteReg_1(MPU6050_RA_ZRMOT_DUR, 0x00);
    //Disable sensor output to FIFO buffer
    MPU_WriteReg_1(MPU6050_RA_FIFO_EN, 0x00);

    //AUX I2C setup
    //Sets AUX I2C to single master control, plus other config
    MPU_WriteReg_1(MPU6050_RA_I2C_MST_CTRL, 0x00);
    //Setup AUX I2C slaves
    MPU_WriteReg_1(MPU6050_RA_I2C_SLV0_ADDR, 0x00);
    MPU_WriteReg_1(MPU6050_RA_I2C_SLV0_REG, 0x00);
    MPU_WriteReg_1(MPU6050_RA_I2C_SLV0_CTRL, 0x00);
    MPU_WriteReg_1(MPU6050_RA_I2C_SLV1_ADDR, 0x00);
    MPU_WriteReg_1(MPU6050_RA_I2C_SLV1_REG, 0x00);
    MPU_WriteReg_1(MPU6050_RA_I2C_SLV1_CTRL, 0x00);
    MPU_WriteReg_1(MPU6050_RA_I2C_SLV2_ADDR, 0x00);
    MPU_WriteReg_1(MPU6050_RA_I2C_SLV2_REG, 0x00);
    MPU_WriteReg_1(MPU6050_RA_I2C_SLV2_CTRL, 0x00);
    MPU_WriteReg_1(MPU6050_RA_I2C_SLV3_ADDR, 0x00);
    MPU_WriteReg_1(MPU6050_RA_I2C_SLV3_REG, 0x00);
    MPU_WriteReg_1(MPU6050_RA_I2C_SLV3_CTRL, 0x00);
    MPU_WriteReg_1(MPU6050_RA_I2C_SLV4_ADDR, 0x00);
    MPU_WriteReg_1(MPU6050_RA_I2C_SLV4_REG, 0x00);
    MPU_WriteReg_1(MPU6050_RA_I2C_SLV4_DO, 0x00);
    MPU_WriteReg_1(MPU6050_RA_I2C_SLV4_CTRL, 0x00);
    MPU_WriteReg_1(MPU6050_RA_I2C_SLV4_DI, 0x00);

    //MPU6050_RA_I2C_MST_STATUS //Read-only
    //Setup INT pin and AUX I2C pass through
    MPU_WriteReg_1(MPU6050_RA_INT_PIN_CFG, 0x00);
    //Enable data ready interrupt
    MPU_WriteReg_1(MPU6050_RA_INT_ENABLE, 0x00);

    //Slave out, dont care
    MPU_WriteReg_1(MPU6050_RA_I2C_SLV0_DO, 0x00);
    MPU_WriteReg_1(MPU6050_RA_I2C_SLV1_DO, 0x00);
    MPU_WriteReg_1(MPU6050_RA_I2C_SLV2_DO, 0x00);
    MPU_WriteReg_1(MPU6050_RA_I2C_SLV3_DO, 0x00);
    //More slave config
    MPU_WriteReg_1(MPU6050_RA_I2C_MST_DELAY_CTRL, 0x00);
    //Reset sensor signal paths
    MPU_WriteReg_1(MPU6050_RA_SIGNAL_PATH_RESET, 0x00);
    //Motion detection control
    MPU_WriteReg_1(MPU6050_RA_MOT_DETECT_CTRL, 0x00);
    //Disables FIFO, AUX I2C, FIFO and I2C reset bits to 0
    MPU_WriteReg_1(MPU6050_RA_USER_CTRL, 0x00);
    //Sets clock source to gyro reference w/ PLL
    MPU_WriteReg_1(MPU6050_RA_PWR_MGMT_1, 0b00000010);
    //Controls frequency of wakeups in accel low power mode plus the sensor standby modes
    MPU_WriteReg_1(MPU6050_RA_PWR_MGMT_2, 0x00);
    //MPU6050_RA_BANK_SEL            //Not in datasheet
    //MPU6050_RA_MEM_START_ADDR        //Not in datasheet
    //MPU6050_RA_MEM_R_W            //Not in datasheet
    //MPU6050_RA_DMP_CFG_1            //Not in datasheet
    //MPU6050_RA_DMP_CFG_2            //Not in datasheet
    //MPU6050_RA_FIFO_COUNTH        //Read-only
    //MPU6050_RA_FIFO_COUNTL        //Read-only
    //Data transfer to and from the FIFO buffer
    MPU_WriteReg_1(MPU6050_RA_FIFO_R_W, 0x00);

}

unsigned int MPU_Read_X( void )
{
unsigned int Rx1, Rx2;
    //MPU6050

    i2c_Start(0);
    i2c_Tx(curr_I2C_Addr);
    i2c_Tx(MPU6050_RA_ACCEL_XOUT_H);
    i2c_Start(1); //ReStart
    i2c_Tx(curr_I2C_Addr + 1);
    Rx1 = i2c_Rx(0);
    Rx2 = i2c_Rx(1);
    i2c_Stop();

    return (Rx1<<8) + Rx2;;
}

unsigned int MPU_Read_Y( void )
{
unsigned int Rx1, Rx2;
    //MPU6050

    i2c_Start(0);
    i2c_Tx(curr_I2C_Addr);
    i2c_Tx(MPU6050_RA_ACCEL_YOUT_H);
    i2c_Start(1); //ReStart
    i2c_Tx(curr_I2C_Addr + 1);
    Rx1 = i2c_Rx(0);
    Rx2 = i2c_Rx(1);
    i2c_Stop();

    return (Rx1<<8) + Rx2;;
}

unsigned int MPU_Read_Z( void )
{
unsigned int Rx1, Rx2;
    //MPU6050

    i2c_Start(0);
    i2c_Tx(curr_I2C_Addr);
    i2c_Tx(MPU6050_RA_ACCEL_ZOUT_H);
    i2c_Start(1); //ReStart
    i2c_Tx(curr_I2C_Addr + 1);
    Rx1 = i2c_Rx(0);
    Rx2 = i2c_Rx(1);
    i2c_Stop();

    return (Rx1<<8) + Rx2;;
}

//Gyro Read Functions

unsigned int MPU_Read_XGy( void )
{
unsigned int Rx1, Rx2;
    //MPU6050

    i2c_Start(0);
    i2c_Tx(curr_I2C_Addr);
    i2c_Tx(MPU6050_RA_GYRO_ZOUT_H);
    i2c_Start(1); //ReStart
    i2c_Tx(curr_I2C_Addr + 1);
    Rx1 = i2c_Rx(0);
    Rx2 = i2c_Rx(1);
    i2c_Stop();

    return (Rx1<<8) + Rx2;;
}

unsigned int MPU_Read_YGy( void )
{
unsigned int Rx1, Rx2;
    //MPU6050

    i2c_Start(0);
    i2c_Tx(curr_I2C_Addr);
    i2c_Tx(MPU6050_RA_GYRO_ZOUT_H);
    i2c_Start(1); //ReStart
    i2c_Tx(curr_I2C_Addr + 1);
    Rx1 = i2c_Rx(0);
    Rx2 = i2c_Rx(1);
    i2c_Stop();

    return (Rx1<<8) + Rx2;;
}

unsigned int MPU_Read_ZGy( void )
{
unsigned int Rx1, Rx2;
    //MPU6050

    i2c_Start(0);
    i2c_Tx(curr_I2C_Addr);
    i2c_Tx(MPU6050_RA_GYRO_ZOUT_H);
    i2c_Start(1); //ReStart
    i2c_Tx(curr_I2C_Addr + 1);
    Rx1 = i2c_Rx(0);
    Rx2 = i2c_Rx(1);
    i2c_Stop();

    return (Rx1<<8) + Rx2;;
}

/*
 * function:    Configure the MPU Accelerometer and Gyro Scale, 
 *                set global values for later access
 * 
 * parameters:  accel_scale - Accelerometer Scale. for the MPU6050, the following values are permitted (in g)
 *              2, 4, 8, 16 (Default 2)
 *              gyro_scale  - Gyroscope Scale. for the MPU6050, the following values are permitted (in deg/sec)
 *              250, 500, 1000, 2000 (Default 500)
 * 
 * returns:     void.
 */

void MPU_Config(int accel_scale, int gyro_scale)
{
    short i,j;
    
    for(i=0;i<5;i++)
        if(i>3) {
            MPU_WriteReg_1(MPU6050_RA_ACCEL_CONFIG,0);
            break;
        }
        else if(accel_scale=(2^(i+1))) {
            MPU_WriteReg_1(MPU6050_RA_ACCEL_CONFIG,i<<3);
            accelScale=accel_scale;
            break;
        }
    
    for(i=0;i<5;i++)
        if(i>3) {
            MPU_WriteReg_1(MPU6050_RA_GYRO_CONFIG,0b00001000);
            break;
        }
        else if(gyro_scale==((2^(i+1))*125)) {
            MPU_WriteReg_1(MPU6050_RA_ACCEL_CONFIG,i<<3);
            gyroScale=gyro_scale;
            break;
        }    
}

/*
 * function:    Convert raw accelerometer values to gs or m/s, using the current scale.
 * 
 * parameters:  accelval - Current raw accel value. 
 *              g - Output selection. 0 gives m/s, 1 gives output in Gs.
 * 
 * returns:     Standardised float value in selected format
 */

float MPU_AccelConv(unsigned int accelval, unsigned int g){
    
    if(g==1)
        return (accelval/(32768/accelScale));
    else
        return (accelval/(32768/accelScale))*(9.81);
}

/*
 * function:    Convert raw gyro values to degress per second, using the current scale.
 * 
 * parameters:  Current raw gyro value. Output from MPU_Read_xGy
 * 
 * returns:     Standardised float value in degrees per second
 */

float MPU_GyroConv(unsigned int gyroval) {
    return (gyroval/(32750/gyroScale));
}

/*
 *function:      Convert gyro values of angular momentum to fixed degrees of movement.
 *               To initialize, simply call with negative values of the respective axes and init values.
 *
 *parameters:    gyVal - Angular momentum in deg/sec, output of MPU_GyroConv
 *              axis - The axis of measurement. 1-X, 2-Y, 3-Z
 *              clk - A timer needs to be setup for continous runningand reset-on-overflow, to measure time for integration.
 *                      Set constants GYROCLK_MAXVAL and GYRO_SECS_PER_CLK to their respective values,
 *                          based on current frequency and bitsize of the timer. TIMEER REQUIRED.
 *                      Ideally, the timer maxval is a multiple of the refresh rate of the gyro. 
 *
 *returns:       single float value of the current degree of turn of the axis specified.
 */

float MPU_GyroVal(float gyVal, int axis, unsigned int clk) {
    static float XDeg=0, YDeg=0, ZDeg=0;
    static unsigned int last_clk=0;    
    
    unsigned int diff=clk-last_clk;

    if(axis<0)
    {
        if(0-axis==1)
            return (XDeg=gyVal);
        else if(0-axis==2)
            return (YDeg=gyVal);
        else if(0-axis==3)
            return (ZDeg=gyVal);
    }
    
    if(clk<last_clk)
        diff = GYROCLK_MAXVAL+clk;
    
    switch(axis) {
        case 1:
            XDeg+=gyVal*GYRO_SECS_PER_CLK*diff;
            return XDeg;
        case 2:
            YDeg+=gyVal*GYRO_SECS_PER_CLK*diff;
            return YDeg;
        case 3:
            ZDeg+=gyVal*GYRO_SECS_PER_CLK*diff;
            return ZDeg;
        default:
            return 0;
    }
}