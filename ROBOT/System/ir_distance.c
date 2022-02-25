/*
 * Date  : 29 Jul 2020
 * Author: Amjad Yousef Majid
 */


#include "ir_distance.h"
#include "msp.h"
#include "lpf.h"
#include "UART0.h"

uint32_t left_convert(uint32_t nl)
{        // returns left distance in mm
    uint32_t d = 1195172 / (nl - 880) + 70;
    if (d > IR_MAX_DISTANCE)
    {
        d = IR_MAX_DISTANCE;
    }
    return d;
}

uint32_t center_convert(uint32_t nc)
{   // returns center distance in mm

    uint32_t d = 1195172 / (nc - 880) + 70;
    if (d > IR_MAX_DISTANCE)
    {
        d = IR_MAX_DISTANCE;
    }
    return d;
}

uint32_t right_convert(uint32_t nr)
{      // returns right distance in mm
    uint32_t d = 1195172 / (nr - 880) + 70;
    if (d > IR_MAX_DISTANCE)
    {
        d = IR_MAX_DISTANCE;
    }
    return d;
}

// Initialize the channels 17, 14 and 16 for analog to digital conversion
// These channels represent the left, middle and right infrared sensors respectively
void adc_init_channel_14_16_17(void)
{
    ADC14->CTL0 &= ~ADC14_CTL0_ENC;        // to allow programming
    while (ADC14->CTL0 & 0x00010000)
    {
    };          // wait for BUSY to be zero
    ADC14->CTL0 = ADC14_CTL0_ON | ADC14_CTL0_MSC | ADC14_CTL0_SHT0__32 | ADC14_CTL0_SHT1__32 | ADC14_CTL0_CONSEQ_1 |
    ADC14_CTL0_SSEL__SMCLK | ADC14_CTL0_DIV__1 | ADC14_CTL0_SHP;          //  single, SMCLK, on, disabled, /1, 32 SHM
    ADC14->CTL1 = 0x00000030;                 // ADC14MEM0, 14-bit, ref on, regular power
    ADC14->MCTL[0] = ADC14_MCTLN_INCH_14;
    ADC14->MCTL[1] = ADC14_MCTLN_INCH_16;
    ADC14->MCTL[2] = ADC14_MCTLN_INCH_17 | ADC14_MCTLN_EOS;
    ;         // 0 to 3.3V, channel 17
    ADC14->IER0 = 0; // no interrupts
    ADC14->IER1 = 0; // no interrupts

    P4->SEL1 |= BIT1;
    P4->SEL0 |= BIT1;
    P9->SEL1 |= BIT0;
    P9->SEL0 |= BIT0;
    P9->SEL1 |= BIT1;
    P9->SEL0 |= BIT1;

    ADC14->CTL0 |= ADC14_CTL0_ENC;         // enable
}

volatile uint32_t debug_reg = 0;
volatile uint32_t adc14_mem_0 = 0;
volatile uint32_t adc14_mem_1 = 0;
volatile uint32_t adc14_mem_2 = 0;

void read_adc_14_16_17()
{
    while (ADC14->CTL0 & 0x00010000)
    {
    };    // wait for BUSY to be zero

    ADC14->CTL0 |= ADC14_CTL0_SC;
    while (debug_reg != 0x07)
    {
        debug_reg = ADC14->IFGR0;
    };
    adc14_mem_0 = ADC14->MEM[0];      // return result 0 to 16383
    adc14_mem_1 = ADC14->MEM[1];
    adc14_mem_2 = ADC14->MEM[2];
}

void ir_distances(uint32_t *left, uint32_t *center, uint32_t *right)
{
    read_adc_14_16_17();
    *left = left_convert(adc14_mem_0);         // left is channel 14, P6.1
    *center = center_convert(adc14_mem_1);     // center is channel 16, P9.1
    *right = right_convert(adc14_mem_2);       // right is channel 17, P9.0

}

