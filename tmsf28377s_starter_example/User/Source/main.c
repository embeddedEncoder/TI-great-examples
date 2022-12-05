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

#include <stdlib.h>
#include "main.h"
#include "device.h"
#include "pwm.h"
#include "sci.h"


interrupt void cpu_timer0_isr(void);



Uint16 i;
Uint16 LoopCount;  // sci
Uint16 ErrorCount; // sci


void main(void)
{

    Uint16 ReceivedChar;
    char *msg;
    //   For flash only (1/2)
    //  memcpy(&RamfuncsRunStart, &RamfuncsLoadStart, (size_t)&RamfuncsLoadSize);

    // Initialize System Control: PLL, WatchDog, enable Peripheral Clocks
    InitSysCtrl();

    //  For flash only (2/2)
    //  InitFlash();

    // Initialize GPIO
    InitGpio();

    // Disable CPU interrupts
    DINT;

    // Initialize the PIE control registers to their default state
    InitPieCtrl();

    // Disable CPU interrupts and clear all CPU interrupt flags
    IER = 0x0000;
    IFR = 0x0000;

    // Initialize the PIE vector table with pointers to the shell Interrupt
    // Service Routines (ISR).
    // This will populate the entire table, even if the interrupt
    // is not used in this example.  This is useful for debug purposes.
    // The shell ISR routines are found in F2837xD_DefaultIsr.c.
    InitPieVectTable();

    //  Stop pwm clocks
    EALLOW;
    CpuSysRegs.PCLKCR0.bit.TBCLKSYNC = 0;
    EDIS;

    //  Set interrupt functions here
    EALLOW;
    //  PieVectTable.whatever = &some_ISR;
    PieVectTable.TIMER0_INT = &cpu_timer0_isr;
    PieVectTable.EPWM11_INT = &epwm11_isr;

    EDIS;

    InitPWM();

    //Setting up PWM pins on GPIO
    for (i = 0; i < 16; i++)
    {
        GPIO_SetupPinOptions(i, GPIO_OUTPUT, GPIO_ASYNC);

        GPIO_SetupPinMux(i, GPIO_MUX_CPU1, 1);
    }

    // experimental for SCI for launchpad tms320f28377s
    //  Receiver
    GPIO_SetupPinMux(85, GPIO_MUX_CPU1, 5);
    GPIO_SetupPinOptions(85, GPIO_INPUT, GPIO_PUSHPULL);
    // Transmitter
    GPIO_SetupPinMux(84, GPIO_MUX_CPU1, 5);
    GPIO_SetupPinOptions(84, GPIO_OUTPUT, GPIO_ASYNC);

    InitCpuTimers();
    ConfigCpuTimer(&CpuTimer0, 200, 2);

    //  Enable interrupt groups here
    //  IER |= some interrupt group, see p93 of tech ref manual
    IER |= M_INT1;
    IER |= M_INT3;
    IER |= M_INT5;

    //  Enable individual interrupts here
    // PieCtrlRegs.PIEIER1.bit.INTx1 = 1;   // ADC interrupt enabled
    PieCtrlRegs.PIEIER1.bit.INTx7 = 1;  // Timer interrupt enabled
    PieCtrlRegs.PIEIER3.bit.INTx11 = 1; // Epwm11 interrupt enabled


    kill_pwm();

    // OPEN LOOP TEST
    EPwm8Regs.TBPHS.bit.TBPHS = 0;

    //  Start all pwm clocks together
    EALLOW;
    CpuSysRegs.PCLKCR0.bit.TBCLKSYNC = 1;
    EDIS;

    // Enable global Interrupts and higher priority real-time debug events
    EINT;
    ERTM;

    LoopCount = 0;
    ErrorCount = 0;
    EALLOW;
    CpuSysRegs.PCLKCR7.bit.SCI_C = 1;
    scia_fifo_init();     // Initialize the SCI FIFO
    scia_echoback_init(); // Initialize SCI for echoback
    EDIS;
    // GpioDataRegs.GPBSET.bit.GPIO55=1;

    for (;;)
    {

        // Wait for inc character

        while (SciaRegs.SCIFFRX.bit.RXFFST == 0)
        {
        } // wait for XRDY =1 for empty state

        // Get character
        // ReceivedChar = ScicRegs.SCIRXBUF.all;
        msg = "  You sent: \0";
        scia_msg(msg);
        // scia_xmit(ReceivedChar);
        do
        {
            ReceivedChar = SciaRegs.SCIRXBUF.all;
            // Echo character back
            scia_xmit(ReceivedChar);
            i++;
        } while (SciaRegs.SCIFFRX.bit.RXFFST != 0);
        LoopCount++;
    }
}

interrupt void cpu_timer0_isr(void)
{
    //   CpuTimer0.InterruptCount++;
    StopCpuTimer0();
    ReloadCpuTimer0();
    // Acknowledge this interrupt to receive more interrupts from group 1
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
}
