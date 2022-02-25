// UART0.c
// Runs on MSP432
// Busy-wait device driver for the UART UCA0.
// Daniel Valvano
// September 23, 2017
// Modified by EE345L students Charlie Gough && Matt Hawk
// Modified by EE345M students Agustinus Darmawan && Mingjie Qiu

/* This example accompanies the books
 "Embedded Systems: Introduction to the MSP432 Microcontroller",
 ISBN: 978-1512185676, Jonathan Valvano, copyright (c) 2017
 "Embedded Systems: Real-Time Interfacing to the MSP432 Microcontroller",
 ISBN: 978-1514676585, Jonathan Valvano, copyright (c) 2017
 "Embedded Systems: Real-Time Operating Systems for ARM Cortex-M Microcontrollers",
 ISBN: 978-1466468863, , Jonathan Valvano, copyright (c) 2017
 For more information about my classes, my research, and my books, see
 http://users.ece.utexas.edu/~valvano/

 Simplified BSD License (FreeBSD License)
 Copyright (c) 2017, Jonathan Valvano, All rights reserved.

 Redistribution and use in source and binary forms, with or without modification,
 are permitted provided that the following conditions are met:

 1. Redistributions of source code must retain the above copyright notice,
 this list of conditions and the following disclaimer.
 2. Redistributions in binary form must reproduce the above copyright notice,
 this list of conditions and the following disclaimer in the documentation
 and/or other materials provided with the distribution.

 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE
 USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

 The views and conclusions contained in the software and documentation are
 those of the authors and should not be interpreted as representing official
 policies, either expressed or implied, of the FreeBSD Project.
 */

// UCA0RXD (VCP receive) connected to P1.2
// UCA0TXD (VCP transmit) connected to P1.3
#include <stdint.h>
#include <stdio.h>
#include "msp.h"

//------------UART0_Init------------
// Initialize the UART for 115,200 baud rate (assuming 12 MHz SMCLK clock),
// 8 bit word length, no parity bits, one stop bit
// Input: none
// Output: none
void UART0_Init(void)
{
    EUSCI_A0->CTLW0 = 0x0001;                   // hold the USCI module in reset mode
    // bit15=0,      no parity bits
    // bit14=x,      not used when parity is disabled
    // bit13=0,      LSB first
    // bit12=0,      8-bit data length
    // bit11=0,      1 stop bit
    // bits10-8=000, asynchronous UART mode
    // bits7-6=11,   clock source to SMCLK
    // bit5=0,       reject erroneous characters and do not set flag
    // bit4=0,       do not set flag for break characters
    // bit3=0,       not dormant
    // bit2=0,       transmit data, not address (not used here)
    // bit1=0,       do not transmit break (not used here)
    // bit0=1,       hold logic in reset state while configuring
    EUSCI_A0->CTLW0 = 0x00C1;
    // set the baud rate
    // N = clock/baud rate = 12,000,000/115,200 = 104.1667
    EUSCI_A0->BRW = 104;           // UCBR = baud rate = int(N) = 104
    EUSCI_A0->MCTLW &= ~0xFFF1;    // clear first and second modulation stage bit fields
    P1->SEL0 |= 0x0C;
    P1->SEL1 &= ~0x0C;             // configure P1.3 and P1.2 as primary module function
    EUSCI_A0->CTLW0 &= ~0x0001;    // enable the USCI module
    EUSCI_A0->IE &= ~0x000F;       // disable interrupts (transmit ready, start received, transmit empty, receive full)
}


//------------UART0_OutChar------------
// Output 8-bit to serial port
// Input: letter is an 8-bit ASCII character to be transferred
// Output: none
void UART0_OutChar(char letter)
{
    while ((EUSCI_A0->IFG & 0x02) == 0)
        ;
    EUSCI_A0->TXBUF = letter;
}


//------------UART0_InChar------------
// Wait for new serial port input
// Input: none
// Output: ASCII code for key typed
char UART0_InChar(void){
  while((EUSCI_A0->IFG&0x01) == 0);
  return((char)(EUSCI_A0->RXBUF));
}

//------------UART0_OutString------------
// Output String (NULL termination)
// Input: pointer to a NULL-terminated string to be transferred
// Output: none
void UART0_OutString(char *pt)
{
    while (*pt)
    {
        UART0_OutChar(*pt);
        pt++;
    }
}

//-----------------------UART0_OutUDec-----------------------
// Output a 32-bit number in unsigned decimal format
// Input: 32-bit number to be transferred
// Output: none
// Variable format 1-10 digits with no space before or after
void UART0_OutUDec(uint32_t n)
{
// This function uses recursion to convert decimal number
//   of unspecified length as an ASCII string
    if (n >= 10)
    {
        UART0_OutUDec(n / 10);
        n = n % 10;
    }
    UART0_OutChar(n + '0'); /* n is between 0 and 9 */
}

