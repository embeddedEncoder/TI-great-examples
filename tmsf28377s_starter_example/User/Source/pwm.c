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
#include "device.h"
#include "pwm.h"
#include "main.h"

#define DEADBANDS_ACTIVE 1
#define ACTIVATE_INTERRUPTS 1

void InitPWM(void)
{

    EPwm7Regs.TBPRD = 1249;
    // Period = 500 TBCLK counts
    EPwm7Regs.TBPHS.bit.TBPHS = 0;

    // EPwm1Regs.TBCTL.bit.PHSDIR = 0; //count down after sync
    //  Set Phase register to zero
    EPwm7Regs.TBCTL.bit.CTRMODE = TB_FREEZE; // stop timer

    // Symmetrical mode
    EPwm7Regs.TBCTL.bit.PHSEN = 0; // enable phase loading

    EPwm7Regs.TBCTL.bit.PHSDIR = 0; // count down after sync
    // Master module
    EPwm7Regs.TBCTL.bit.PRDLD = 0;     // load on CTR = 0
    EPwm7Regs.TBCTL.bit.SYNCOSEL = 1;  // CTR = 0
    EPwm7Regs.TBCTL.bit.HSPCLKDIV = 0; // using 100MHz clock

    // Sync down-stream module
    EPwm7Regs.CMPCTL.bit.SHDWAMODE = 0x0000; // shadow updates
    EPwm7Regs.CMPCTL.bit.SHDWBMODE = 0;      // shadow updates
    EPwm7Regs.CMPCTL.bit.LOADAMODE = 2;      // load on CTR = PRD or CTR = 0
    // load on CTR=Zero
    EPwm7Regs.CMPCTL.bit.LOADBMODE = 2; // load on CTR = PRD or CTR = 0
    // load on CTR=Zero
    EPwm7Regs.AQCTLA.bit.CAU = 2; // set on compare while count up
    // set actions for EPWM1A
    EPwm7Regs.AQCTLA.bit.CAD = 1; // clear on compare while count down

    EPwm7Regs.AQCTLB.bit.CAU = 1; // clear on compare while count up
                                  //  set actions for EPWM1A
    EPwm7Regs.AQCTLB.bit.CAD = 2; // set on compare while count down

#if DEADBANDS_ACTIVE
    EPwm7Regs.DBCTL.all = 0x000B;
    EPwm7Regs.DBRED = 10;
    //  DBRED       Rising Edge DB in Clock Counts
    EPwm7Regs.DBFED = 10;
    //  DBFED       Falling Edge DB in Clock Counts
#endif

    // EPWM8 Configurations
    EPwm8Regs.TBPRD = 1249;
    // Period = 900 TBCLK counts
    EPwm8Regs.TBPHS.bit.TBPHS = 100;
    // Set Phase register to zero
    EPwm8Regs.TBCTL.bit.CTRMODE = TB_FREEZE; // stop timer
    // Symmetrical mode
    EPwm8Regs.TBCTL.bit.PHSEN = 1; // enable phase loading

    EPwm8Regs.TBCTL.bit.PHSDIR = 0; // count down after sync
    // Master module
    EPwm8Regs.TBCTL.bit.PRDLD = 0;     // load on CTR = 0
    EPwm8Regs.TBCTL.bit.SYNCOSEL = 1;  // CTR = 0
    EPwm8Regs.TBCTL.bit.HSPCLKDIV = 0; // using 100MHz clock

    // Sync down-stream module
    EPwm8Regs.CMPCTL.bit.SHDWAMODE = 0; // shadow updates
    EPwm8Regs.CMPCTL.bit.SHDWBMODE = 0; // shadow updates
    EPwm8Regs.CMPCTL.bit.LOADAMODE = 2; // load on CTR = PRD or CTR = 0
    // load on CTR=Zero
    EPwm8Regs.CMPCTL.bit.LOADBMODE = 2; // load on CTR = PRD or CTR = 0

    EPwm8Regs.AQCTLA.bit.CAU = 2; // set on compare while count up
    // set actions for EPWM1A
    EPwm8Regs.AQCTLA.bit.CAD = 1; // clear on compare while count down

    EPwm8Regs.AQCTLB.bit.CAU = 1; // clear on compare while count up
                                  //  set actions for EPWM1A
    EPwm8Regs.AQCTLB.bit.CAD = 2; // set on compare while count down
#if DEADBANDS_ACTIVE
    EPwm8Regs.DBCTL.all = 0x000B;
    EPwm8Regs.DBRED = 10;
    //  DBRED       Rising Edge DB in Clock Counts
    EPwm8Regs.DBFED = 10;
    //  DBFED       Falling Edge DB in Clock Counts
#endif

    EPwm7Regs.CMPA.bit.CMPA = 624;
    EPwm7Regs.CMPB.bit.CMPB = 624;
    // adjust duty for output EPWM1A
    EPwm8Regs.CMPA.bit.CMPA = 624;
    EPwm8Regs.CMPB.bit.CMPB = 624;

    // configuring ePWM11 for creating sync events for the sdfm; epwm11 config is the same as
    EPwm11Regs.TBCTL.bit.FREE_SOFT = 0;
    EPwm11Regs.TBCTL.bit.CTRMODE = TB_FREEZE; // stop the timer
    EPwm11Regs.TBPRD = 2497;

    EPwm11Regs.TBCTR = 0x0000;
    EPwm11Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;
    EPwm11Regs.TBCTL.bit.CLKDIV = TB_DIV1;

    EPwm11Regs.AQCTLA.bit.CAU = AQ_SET;
    EPwm11Regs.AQCTLA.bit.PRD = AQ_CLEAR;

    // Set Compare values
    EPwm11Regs.CMPC = 0;

    // experimental epwm10 setup
    EPwm10Regs.TBCTL.bit.FREE_SOFT = 0;
    EPwm10Regs.TBCTL.bit.CTRMODE = TB_FREEZE; // stop the timer
    EPwm10Regs.TBPRD = 2497;

    EPwm10Regs.TBCTR = 0x0000;
    EPwm10Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;
    EPwm10Regs.TBCTL.bit.CLKDIV = TB_DIV1;

    EPwm10Regs.AQCTLA.bit.CAU = AQ_SET;
    EPwm10Regs.AQCTLA.bit.PRD = AQ_CLEAR;

    // experimental for epwm7-epwm11 synchronization
    TrigRegs.SYNCSELECT.bit.EPWM10SYNCIN = 2; // select epwm7's syncout to be epwm10's syncin
    EPwm10Regs.TBCTL.bit.PHSEN = 1;           // enable phase loading on epwm10
    EPwm10Regs.TBCTL.bit.SYNCOSEL = 0;        // epwm10's syncin connected to syncout
    EPwm11Regs.TBCTL.bit.PHSEN = 1;           // enable phase loading on epwm11
    EPwm11Regs.TBPHS.bit.TBPHS = 0x0000;      // phase must be zero

    EPwm7Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN; // Count up/down timer
    EPwm8Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN; // Count up/down timer
    EPwm2Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN; // Count up/down timer
    EPwm10Regs.TBCTL.bit.CTRMODE = TB_COUNT_UP;    // Count up timer
    EPwm11Regs.TBCTL.bit.CTRMODE = TB_COUNT_UP;    // Count up timer

    // EPwm10Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN; //Count up timer
    // EPwm11Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN; //Count up timer

    // Interrupt settings
    // Interrupt from EPWM-1A
#if ACTIVATE_INTERRUPTS
    EPwm11Regs.ETSEL.bit.INTSELCMP = 1;
    EPwm11Regs.ETSEL.bit.INTSEL = 4; // Enable event time-base counter equal to zero or period
    EPwm11Regs.ETSEL.bit.INTEN = 1;  // Enable INT
    EPwm11Regs.ETPS.bit.INTPRD = 01; // Generate INT on 1st event

    EALLOW;
    // PieVectTable.EPWM7_INT = &epwm7_isr;
    // IER |= 0x0004; //Enable INT3
    // PieCtrlRegs.PIEIER3.bit.INTx7 = 1; //Enable PIE Group 3's Channel 1 (Which happens to be the ePWM1 )
    // PieCtrlRegs.PIEIFR3.bit.INTx1 = 0; //Interrupt flag is cleared. Ready to be set by the interrupt peripheral
#endif
}

interrupt void epwm11_isr(void)
{

    EPwm11Regs.ETCLR.bit.INT = 1; // clear the epwm intr flag
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP5;
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP3;
}

void kill_pwm(void)
{
    EPwm2Regs.DBCTL.all = 0x0008;
    EPwm8Regs.DBCTL.all = 0x0008;
    EPwm2Regs.AQCSFRC.all = 0x0005;
    EPwm8Regs.AQCSFRC.all = 0x0005;

    EPwm7Regs.DBCTL.all = 0x0008;
    EPwm11Regs.DBCTL.all = 0x0008;
    EPwm7Regs.AQCSFRC.all = 0x0005;
    EPwm11Regs.AQCSFRC.all = 0x0005;
}

void enable_pwm(void)
{
    EPwm2Regs.DBCTL.all = 0x000B;
    EPwm8Regs.DBCTL.all = 0x000B;
    EPwm2Regs.AQCSFRC.all = 0x000F;
    EPwm8Regs.AQCSFRC.all = 0x000F;

    EPwm7Regs.DBCTL.all = 0x000B;
    EPwm11Regs.DBCTL.all = 0x000B;
    EPwm7Regs.AQCSFRC.all = 0x000F;
    EPwm11Regs.AQCSFRC.all = 0x000F;
}
