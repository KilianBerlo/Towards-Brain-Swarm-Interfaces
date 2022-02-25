/**
 * @file      UART0.h
 * @brief     Provide receive/transmit functions for EUSCI A0
 * @details   EUSCI_A0 UART is connected to the PC via the USB cable
 * To be able to use printf<br>
 * 1) add UART0.c to project<br>
 * 2) "..\inc
 RT0.h"<br>
 * 3) Must be running at 48 MHz, Clock_Init48MHz();<br>
 * 4) Call UART0_Initprintf()
 * @remark    UCA0RXD (VCP receive) connected to P1.2
 * @remark    UCA0TXD (VCP transmit) connected to P1.3
 * @remark    Busy-wait device driver for the EUSCI A0 UART
 * @version   TI-RSLK MAX v1.1
 * @author    Daniel Valvano and Jonathan Valvano
 * @copyright Copyright 2019 by Jonathan W. Valvano, valvano@mail.utexas.edu,
 * @warning   AS-IS
 * @note      For more information see  http://users.ece.utexas.edu/~valvano/
 * @date      June 28, 2019
 <table>
 <caption id="UART0ports">UART connected via USB cable</caption>
 <tr><th>Pin  <th>signal
 <tr><th>P1.2 <td>UCA0RXD (VCP receive)
 <tr><th>P1.3 <td>UCA0TXD (VCP transmit)
 </table>
 ******************************************************************************/

/* This example accompanies the book
 "Embedded Systems: Introduction to Robotics,
 Jonathan W. Valvano, ISBN: 9781074544300, copyright (c) 2019
 For more information about my classes, my research, and my books, see
 http://users.ece.utexas.edu/~valvano/

 Simplified BSD License (FreeBSD License)
 Copyright (c) 2019, Jonathan Valvano, All rights reserved.

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
// Modified by EE345L students Charlie Gough && Matt Hawk
// Modified by EE345M students Agustinus Darmawan && Mingjie Qiu
// standard ASCII symbols
/**
 * \brief Carriage return character
 */
#define CR   0x0D
/**
 * \brief Line feed character
 */
#define LF   0x0A
/**
 * \brief Back space character
 */
#define BS   0x08
/**
 * \brief escape character
 */
#define ESC  0x1B
/**
 * \brief space character
 */
#define SP   0x20
/**
 * \brief delete character
 */
#define DEL  0x7F

/**
 * @details   Initialize EUSCI_A0 for UART operation
 * @details   115,200 baud rate (assuming 12 MHz SMCLK clock),
 * @details   8 bit word length, no parity bits, one stop bit
 * @param  none
 * @return none
 * @note   assumes 48 MHz bus and 12 MHz SMCLK
 * @brief  Initialize EUSCI A0
 */
void UART0_Init(void);

/**
 * @details   Receive a character from EUSCI_A0 UART
 * @details   Busy-wait synchronization,
 * @details   blocking, wait for new serial port input
 * @param  none
 * @return ASCII code for key typed
 * @note   UART0_Init must be called once prior
 * @brief  Receive byte into MSP432
 */
char UART0_InChar(void);

/**
 * @details   Transmit a character to EUSCI_A0 UART
 * @details   Busy-wait synchronization,
 * @details   blocking, wait for UART to be ready
 * @param  letter is the ASCII code for key to send
 * @return none
 * @note   UART0_Init must be called once prior
 * @brief  Transmit byte out of MSP432
 */
void UART0_OutChar(char letter);

/**
 * @details   Transmit a string to EUSCI_A0 UART
 * @param  pt is pointer to null-terminated ASCII string to be transferred
 * @return none
 * @note   UART0_Init must be called once prior
 * @brief  Transmit string out of MSP432
 */
void UART0_OutString(char *pt);

/**
 * @details   Transmit a number as ASCII characters in unsigned decimal format
 * @details   Variable format 1-10 digits with no space before or after
 * @param  n is a unsigned 32-bit number to be transferred
 * @return none
 * @note   UART0_Init must be called once prior
 * @brief  Transmit an unsigned number out of MSP432
 */
void UART0_OutUDec(uint32_t n);

