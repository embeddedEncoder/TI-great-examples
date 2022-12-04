/*
MIT License

Copyright (c) 2022 embeddedEncoder

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

// This file is basically a gutted version of the examples.h header file, and
// only contains the stuff we think I need.


#ifndef DEVICE_H_
#define DEVICE_H_

#include "F2837xS_Device.h"
#include "F2837xS_SysCtrl.h"
#include "F2837xS_GlobalPrototypes.h"
#include "F2837xS_struct.h"
#include "F2837xS_sdfm_drivers.h"


// This stuff is used by the SysCtrl code, and there are other options,
// but I don't plan on changing them any time soon.
#define   IMULT_40        40
#define   IMULT_20        20
#define   FMULT_1    	  0

#define   PLLCLK_BY_2      1
#define   PLLCLK_BY_126    63

#define   AUXPLLRAWCLK_BY_8    3

#define   INT_OSC2		 0
#define   XTAL_OSC		 1
#define   INT_OSC1		 2
#define   AUXCLKIN		 4

#define CPU_RATE   5.00L   // for a 200MHz CPU clock speed (SYSCLKOUT)

#define SYSCLK_HZ 200000000L
#define LSPCLK_HZ (SYSCLK_HZ / 4L)
#define SYSCLK_MHZ (SYSCLK_HZ / 1000000L)


// The following pointer to a function call calibrates the ADC reference,
// DAC offset, and internal oscillators
#define Device_cal (void   (*)(void))0x070282

// The following pointers to functions calibrate the ADC linearity.  Use this
// in the AdcSetMode(...) function only
#define CalAdcaINL (void   (*)(void))0x0703B4
#define CalAdcbINL (void   (*)(void))0x0703B2
#define CalAdccINL (void   (*)(void))0x0703B0
#define CalAdcdINL (void   (*)(void))0x0703AE

// The following pointer to a function call looks up the ADC offset trim for a
// given condition. Use this in the AdcSetMode(...) function only.
#define GetAdcOffsetTrimOTP (Uint16 (*)(Uint16 OTPoffset))0x0703AC


#include "F2837xS_cputimervars.h"
#include "F2837xS_Cla_defines.h"              // Macros used for CLA examples.
#include "F2837xS_EPwm_defines.h"             // Macros used for PWM examples.
#include "F2837xS_Adc_defines.h"              // Macros used for ADC examples.
#include "F2837xS_Emif_defines.h"			 // Macros used for EMIF examples.
#include "F2837xS_Gpio_defines.h"             // Macros used for GPIO support code
#include "F2837xS_I2c_defines.h"              // Macros used for I2C examples.
//#include "F2837xD_Ipc_defines.h"              // Macros used for IPC support code.
#include "F2837xS_Pie_defines.h"              // Macros used for PIE examples.
#include "F2837xS_Dma_defines.h"              // Macros used for DMA examples.
#include "F2837xS_SysCtrl_defines.h"          // Macros used for LPM support code
#include "F2837xS_Upp_defines.h"              // Macros used for UPP examples.

#define CPU_FRQ_200MHZ 1
#define CPU_FRQ_150MHZ 0
#define CPU_FRQ_120MHZ 0

extern void F28x_usDelay(long LoopCount);
// DO NOT MODIFY THIS LINE.
#define DELAY_US(A)  F28x_usDelay(((((long double) A * 1000.0L) / (long double)CPU_RATE) - 9.0L) / 5.0L)

//---------------------------------------------------------------------------
// Useful Timer Operations:
//
// Start Timer:
#define StartCpuTimer0()   CpuTimer0Regs.TCR.bit.TSS = 0

// Stop Timer:
#define StopCpuTimer0()   CpuTimer0Regs.TCR.bit.TSS = 1

// Reload Timer With period Value:
#define ReloadCpuTimer0() CpuTimer0Regs.TCR.bit.TRB = 1

// Read 32-Bit Timer Value:
#define ReadCpuTimer0Counter() CpuTimer0Regs.TIM.all

// Read 32-Bit Period Value:
#define ReadCpuTimer0Period() CpuTimer0Regs.PRD.all

// Start Timer:
#define StartCpuTimer1()   CpuTimer1Regs.TCR.bit.TSS = 0
#define StartCpuTimer2()   CpuTimer2Regs.TCR.bit.TSS = 0

// Stop Timer:
#define StopCpuTimer1()   CpuTimer1Regs.TCR.bit.TSS = 1
#define StopCpuTimer2()   CpuTimer2Regs.TCR.bit.TSS = 1

// Reload Timer With period Value:
#define ReloadCpuTimer1() CpuTimer1Regs.TCR.bit.TRB = 1
#define ReloadCpuTimer2() CpuTimer2Regs.TCR.bit.TRB = 1

// Read 32-Bit Timer Value:
#define ReadCpuTimer1Counter() CpuTimer1Regs.TIM.all
#define ReadCpuTimer2Counter() CpuTimer2Regs.TIM.all

// Read 32-Bit Period Value:
#define ReadCpuTimer1Period() CpuTimer1Regs.PRD.all
#define ReadCpuTimer2Period() CpuTimer2Regs.PRD.all

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif

