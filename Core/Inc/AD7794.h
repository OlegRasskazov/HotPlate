#include <stdint.h>
#include <stdbool.h>

#ifndef __AD7794__
#define __AD7794__
/*--------Defines for Comm Reg--------*/
// Write enable bit
#define Comm_WEN 0x80
// Set 1 for read.And 0 for write
#define Comm_RW 0x40
// Continuous read of the Data register
#define Comm_CREAD 0x4

// Communication register during write operation. Set #Comm_RW to read status register
#define Comm_Reg 0x0
// Read/Write Mode register
#define Mode_Reg 0x1
// Read/Write Configuration register
#define Conf_Reg 0x2
// Read only Data register
#define Data_Reg 0x3
// Read only ID register. The identification number for the ADC
#define ID_Reg 0x4
// Read/write IO register
#define IO_Reg 0x5
// Read/write Offset register
#define Offset_Reg 0x6
// Read/write Full-Scale register
#define Full_Reg 0x7
/*------------------------------------*/

/*--------Defines for Stat Reg--------*/
// Ready bit for ADC
#define Stat_RDY 0x80
// ADC Error bit
#define Stat_ERR 0x40
// No External reference bit
#define Stat_NOXREF 0x20
/*------------------------------------*/

/*--------Defines for Mode Register--------*/
// Continous conversion mode
#define Mode_MD_CCM 0x0
// Single conversion mode
#define Mode_MD_SCM 0x2000
// Idle mode
#define Mode_MD_Idle 0x4000
// Power down mode
#define Mode_MD_PW_DOWN 0x6000
// Internal zero-scale calibration
#define Mode_MD_INZSCLB 0x8000
// Internal full-scale calibration
#define Mode_MD_INFSCLB 0xA000
// System zero-scale calibration
#define Mode_MD_SYSZSCLB 0xC000
// System full-scale calibration
#define Mode_MD_SYSFSCLB 0xE000
// Instrumentation Amplifier Common-mode bit
#define Mode_AMPCM 0x200
// Set to close PSW. Clear to open
#define Mode_PSW 0x1000
// Internal 64kHz clock. CLK pin disabled
#define Mode_CLK_INDIS 0x0
// Internal 64kHz clock. CLK pin enabled
#define Mode_CLK_INEN 0x40
// External 64kHz.
#define Mode_CLK_EXT 0x80
// External. Divided by 2 within ADC
#define Mode_CLK_EXT_DIV 0XC0
// Set to disable CHOP-DIS
#define Mode_Chop_DIS 0x10

// Rates
#define Mode_Rate 0xF
#define Mode_Rate_None 0x0
#define Mode_Rate_470Hz_4ms 0x1
#define Mode_Rate_242Hz_8ms 0x2
#define Mode_Rate_123Hz_16ms 0x3
#define Mode_Rate_62Hz_32ms 0x4
#define Mode_Rate_50Hz_40ms 0x5
#define Mode_Rate_39Hz_48ms 0x6
#define Mode_Rate_33_2Hz_60ms 0x7
#define Mode_Rate_19_6Hz_101ms 0x8
//#define Mode_Rate_16_7Hz_120ms 0x9
#define Mode_Rate_16_7Hz_120ms 0xA
#define Mode_Rate_12_5Hz_160ms 0xB
#define Mode_Rate_10Hz_200ms 0xC
#define Mode_Rate_8_33Hz_240ms 0xD
#define Mode_Rate_6_25Hz_320ms 0xE
#define Mode_Rate_4_17Hz_480ms 0xF
/*------------------------------------*/

/*--------Defines for Conf Reg--------*/
// Bisa voltage generator disabled
#define Conf_VB_DIS 0x0
// Bisa voltage generator disabled
#define Conf_VB_AIN1 0x4000
// Bisa voltage generator disabled
#define Conf_VB_AIN2 0x8000
// Bisa voltage generator disabled
#define Conf_VB_AIN3 0xC000
// Burnout current enable bit. Can be enabled only when the buffer or in-amp is active
#define Conf_BO 0x2000
// Unipolar/Bipolar bit
#define Conf_UB 0x1000
// Boost bit. When set, the current consumed be the bias voltage generator is increased
#define Conf_Boost 0x800
// Gain 1 (in-amp not used)
#define Conf_G1 0x0
// Gain 2 (in-amp not used)
#define Conf_G2 0x100
// Gain 4
#define Conf_G4 0x200
// Gain 8
#define Conf_G8 0x300
// Gain 16
#define Conf_G16 0x400
// Gain 32
#define Conf_G32 0x500
// Gain 64
#define Conf_G64 0x600
// Gain 128
#define Conf_G128 0x700
// External reference applied between REFIN1(+) and REFIN1(-) 
#define Conf_Ext_R1 0x0
// External reference applied between REFIN2(+) and REFIN2(-) 
#define Conf_Ext_R2 0x40
// Internal 1.17V reference
#define Conf_Int 0x80
// Set for enable the reference detect function. 
#define Conf_Ref_Det 0x20
// Buffered mode. For Gain 1 and Gain 2 can be enabled or disabled. For higher gains, the buffer is auto enabled
#define Conf_Buf 0x10

/*--------Channel Select--------*/
#define Conf_Ch_AIN1 0x0
#define Conf_Ch_AIN2 0x1
#define Conf_Ch_AIN3 0x2
#define Conf_Ch_AIN4 0x3
#define Conf_Ch_AIN5 0x4
#define Conf_Ch_AIN6 0x5
#define Conf_Ch_TempSensor 0x6
#define Conf_Ch_VDD 0x7
/*------------------------------------*/



/*--------Defines for IO Reg--------*/
// Zero bits
#define IO_Zero 0x80
// IO enable AIN6
#define IO_IOEN 0x40
// IODAT P2/P1
#define IO_IODAT_P2 0x20
#define IO_IODAT_P1 0x10
// Direction of Current sources
#define IO_IEXCDIR 0xC
#define IO_IEX1IOUT1_IEX2IOUT2 0x0
#define IO_IEX1IOUT2_IEX2IOUT1 0x4
#define IO_IOUT1 0x8
#define IO_IOUT2 0xC
//--------------------------
// Current sourse enable
#define IO_IEXCEN_Dis 0x0
#define IO_IEXCEN_10uA 0x1
#define IO_IEXCEN_200uA 0x2
#define IO_IEXCEN_1mA 0x3
//--------------------------
/*------------------------------------*/

#define reverse_bytes_16(num) (((num & 0x0000FF00) >> 8) | ((num & 0x000000FF) << 8))
#define reverse_bytes_32(num) (((num & 0x00FF0000) >> 16) | ((num & 0x0000FF00)) | ((num & 0x000000FF) << 16))
#define BIT_IS_SET(var,pos) (bool)((var) & (1<<(pos)))

#endif //__AD7794__