/*
 * Date  : 25 Jul 2020
 * Author: Amjad Yousef Majid
 * Email : amjad.y.majid@gmail.com
 */

#include <stdint.h>

#include "msp.h"

void disableInterrupts(void)
{
    __asm ("    CPSID  I\n"
            "    BX     LR\n");
}

void enableInterrupts(void)
{
    __asm ("    CPSIE  I\n"
            "    BX     LR\n");
}

// this function returns a value, PRIMASK register, through R0
void startCritical(void)
{
    __asm ("    MRS    R0, PRIMASK   ; save old status \n"
            "    CPSID  I             ; mask all (except faults)\n"
            "    BX     LR\n");
}

// this function takes an argument through R0 to restore the state of the PRIMASK register
void endCritical(long intreg)
{
    __asm ("    MSR    PRIMASK, R0\n"
            "    BX     LR\n");
}

void waitForInterrupt(void)
{
    __asm ("    WFI\n"
            "    BX     LR\n");
}

