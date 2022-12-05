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
#include "main.h"

// Test 1,SCIA  DLB, 8-bit word, baud rate 0x000F, default, 1 STOP bit, no parity
void scia_echoback_init()
{
    // Note: Clocks were turned on to the SCIA peripheral
    // in the InitSysCtrl() function

    SciaRegs.SCICCR.all = 0x0007;  // 1 stop bit,  No loopback
                                   // No parity,8 char bits,
                                   // async mode, idle-line protocol
    SciaRegs.SCICTL1.all = 0x0003; // enable TX, RX, internal SCICLK,
                                   // Disable RX ERR, SLEEP, TXWAKE
    // ScicRegs.SCICTL2.all =0x0003;
    SciaRegs.SCICTL2.bit.TXINTENA = 1;
    SciaRegs.SCICTL2.bit.RXBKINTENA = 1;
    // ScicRegs.SCICCR.bit.LOOPBKENA =1;
    // SciaRegs.SCIHBAUD.all    =0x0002;  // 9600 baud @LSPCLK = 50MHz (200 MHz SYSCLK).
    // SciaRegs.SCILBAUD.all    =0x008B;

    SciaRegs.SCIHBAUD.all = 0x0000; // 38400 baud @LSPCLK = 50MHz (200 MHz SYSCLK).
    SciaRegs.SCILBAUD.all = 0x00A1;

    SciaRegs.SCICTL1.all = 0x0023; // Relinquish SCI from Reset
    SciaRegs.SCIFFTX.bit.TXFIFOXRESET = 1;
    SciaRegs.SCIFFRX.bit.RXFIFORESET = 1;
}

// Transmit a character from the SCI
void scia_xmit(int a)
{
    while (SciaRegs.SCIFFTX.bit.TXFFST != 0)
    {
    }
    SciaRegs.SCITXBUF.all = a;
}

void scia_msg(char *msg)
{
    int i;
    i = 0;
    while (msg[i] != '\0')
    {
        scia_xmit(msg[i]);
        i++;
    }
}

// Initialize the SCI FIFO
void scia_fifo_init()
{
    // ScicRegs.SCIFFTX.all=0xC022;
    // ScicRegs.SCIFFRX.all=0x0022;
    SciaRegs.SCIFFTX.all = 0xE040;
    SciaRegs.SCIFFRX.all = 0x204f;
    SciaRegs.SCIFFCT.all = 0x0;
}
