//###########################################################################
//
// FILE:    F2837xS_trig_xbar.h
//
// TITLE:   F2837xS Device TRIG_XBAR Register Definitions.
//
//###########################################################################
// $TI Release: F2837xS Support Library v160 $
// $Release Date: Mon Jun 15 14:14:46 CDT 2015 $
// $Copyright: Copyright (C) 2014-2015 Texas Instruments Incorporated -
//             http://www.ti.com/ ALL RIGHTS RESERVED $
//###########################################################################

#ifndef __F2837xS_TRIG_XBAR_H__
#define __F2837xS_TRIG_XBAR_H__

#ifdef __cplusplus 
extern "C" {
#endif 


//---------------------------------------------------------------------------
// TRIG_XBAR Individual Register Bit Definitions:

struct SYNCSELECT_BITS {                // bits description
    Uint16 EPWM4SYNCIN:3;               // 2:0 Selects Sync Input Source for EPWM4
    Uint16 EPWM7SYNCIN:3;               // 5:3 Selects Sync Input Source for EPWM7
    Uint16 EPWM10SYNCIN:3;              // 8:6 Selects Sync Input Source for EPWM10
    Uint16 ECAP1SYNCIN:3;               // 11:9 Selects Sync Input Source for ECAP1
    Uint16 ECAP4SYNCIN:3;               // 14:12 Selects Sync Input Source for ECAP4
    Uint16 rsvd1:1;                     // 15 Reserved
    Uint16 rsvd2:11;                    // 26:16 Reserved
    Uint16 SYNCOUT:2;                   // 28:27 Select Syncout Source
    Uint16 rsvd3:3;                     // 31:29 Reserved
};

union SYNCSELECT_REG {
    Uint32  all;
    struct  SYNCSELECT_BITS  bit;
};

struct EXTADCSOCSELECT_BITS {           // bits description
    Uint16 PWM1SOCAEN:1;                // 0 PWM1SOCAEN Enable for ADCSOCAOn 
    Uint16 PWM2SOCAEN:1;                // 1 PWM2SOCAEN Enable for ADCSOCAOn 
    Uint16 PWM3SOCAEN:1;                // 2 PWM3SOCAEN Enable for ADCSOCAOn 
    Uint16 PWM4SOCAEN:1;                // 3 PWM4SOCAEN Enable for ADCSOCAOn 
    Uint16 PWM5SOCAEN:1;                // 4 PWM5SOCAEN Enable for ADCSOCAOn 
    Uint16 PWM6SOCAEN:1;                // 5 PWM6SOCAEN Enable for ADCSOCAOn 
    Uint16 PWM7SOCAEN:1;                // 6 PWM7SOCAEN Enable for ADCSOCAOn 
    Uint16 PWM8SOCAEN:1;                // 7 PWM8SOCAEN Enable for ADCSOCAOn 
    Uint16 PWM9SOCAEN:1;                // 8 PWM9SOCAEN Enable for ADCSOCAOn 
    Uint16 PWM10SOCAEN:1;               // 9 PWM10SOCAEN Enable for ADCSOCAOn 
    Uint16 PWM11SOCAEN:1;               // 10 PWM11SOCAEN Enable for ADCSOCAOn 
    Uint16 PWM12SOCAEN:1;               // 11 PWM12SOCAEN Enable for ADCSOCAOn 
    Uint16 rsvd1:4;                     // 15:12 Reserved
    Uint16 PWM1SOCBEN:1;                // 16 PWM1SOCBEN Enable for ADCSOCBOn 
    Uint16 PWM2SOCBEN:1;                // 17 PWM2SOCBEN Enable for ADCSOCBOn 
    Uint16 PWM3SOCBEN:1;                // 18 PWM3SOCBEN Enable for ADCSOCBOn 
    Uint16 PWM4SOCBEN:1;                // 19 PWM4SOCBEN Enable for ADCSOCBOn 
    Uint16 PWM5SOCBEN:1;                // 20 PWM5SOCBEN Enable for ADCSOCBOn 
    Uint16 PWM6SOCBEN:1;                // 21 PWM6SOCBEN Enable for ADCSOCBOn 
    Uint16 PWM7SOCBEN:1;                // 22 PWM7SOCBEN Enable for ADCSOCBOn 
    Uint16 PWM8SOCBEN:1;                // 23 PWM8SOCBEN Enable for ADCSOCBOn 
    Uint16 PWM9SOCBEN:1;                // 24 PWM9SOCBEN Enable for ADCSOCBOn 
    Uint16 PWM10SOCBEN:1;               // 25 PWM10SOCBEN Enable for ADCSOCBOn 
    Uint16 PWM11SOCBEN:1;               // 26 PWM11SOCBEN Enable for ADCSOCBOn 
    Uint16 PWM12SOCBEN:1;               // 27 PWM12SOCBEN Enable for ADCSOCBOn 
    Uint16 rsvd2:4;                     // 31:28 Reserved
};

union EXTADCSOCSELECT_REG {
    Uint32  all;
    struct  EXTADCSOCSELECT_BITS  bit;
};

struct SYNCSOCLOCK_BITS {               // bits description
    Uint16 SYNCSELECT:1;                // 0 SYNCSEL Register Lock bit
    Uint16 EXTADCSOCSELECT:1;           // 1 EXTADCSOCSEL Register Lock bit
    Uint16 rsvd1:14;                    // 15:2 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union SYNCSOCLOCK_REG {
    Uint32  all;
    struct  SYNCSOCLOCK_BITS  bit;
};

struct TRIG_REGS {
    union   SYNCSELECT_REG                   SYNCSELECT;                   // Sync Input and Output Select Register
    union   EXTADCSOCSELECT_REG              EXTADCSOCSELECT;              // External ADCSOC Select Register
    union   SYNCSOCLOCK_REG                  SYNCSOCLOCK;                  // SYNCSEL and EXTADCSOC Select Lock register
};

//---------------------------------------------------------------------------
// TRIG_XBAR External References & Function Declarations:
//
extern volatile struct TRIG_REGS TrigRegs;
#ifdef __cplusplus
}
#endif                                  /* extern "C" */

#endif

//===========================================================================
// End of file.
//===========================================================================
