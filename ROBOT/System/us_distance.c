#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include "msp.h"
#include "clock.h"

#define TIMELIM 2333 //Max time it is allowed to take before the us measurement is cancelled, this way the maximum distance it can measure is 800 mm or 80 cm

uint32_t SetDistanceCenter(uint8_t trigP, uint8_t echoP){
    uint32_t time;
    uint8_t echo;

    //Turn us trigger off
    P6->OUT &= ~trigP;
    Clock_Delay1us(2);

    //Turn us trigger on
    P6->OUT |= trigP;
    Clock_Delay1us(10);

    //Turn us trigger off
    P6->OUT &= ~trigP;

    time = 0;
    echo = (P6->IN & echoP);

    //Echo sensor waits for trigger signal
    while( echo == 0x00 && time < TIMELIM){
        //Delay one microsecond to note the time taken to receive the desired signal
        Clock_Delay1us(1);
        time++;
        echo = (P6->IN & echoP);
    }

    time = 0;
    echo = (P6->IN & echoP);

    //Wait for echo signal to return to LOW
    while( echo != 0x00 && time < TIMELIM){
        //Delay one microsecond to note the time taken for echo signal to return to 0
        Clock_Delay1us(1);
        time++;
        echo = (P6->IN & 0x20);
    }

    //Pace of sound in air: 0.343 km/s or mm/μs, so time times this rate gives the distance
    return (0.343 * time);
}

uint32_t SetDistanceLeft(uint8_t trigP, uint8_t echoP){
    uint32_t time;
    uint8_t echo;

    //Turn us trigger off
    P6->OUT &= ~trigP;
    Clock_Delay1us(2);

    //Turn us trigger on
    P6->OUT |= trigP;
    Clock_Delay1us(10);

    //Turn us trigger off
    P6->OUT &= ~trigP;

    time = 0;
    echo = (P2->IN & echoP);

    //Echo sensor waits for trigger signal
    while( echo == 0x00 && time < TIMELIM){
        //Delay one microsecond to note the time taken to receive the desired signal
        Clock_Delay1us(1);
        time++;
        echo = (P2->IN & echoP);
    }

    time = 0;
    echo = (P2->IN & echoP);

    //Wait for echo signal to return to LOW
    while( echo != 0x00 && time < TIMELIM){
        //Delay one microsecond to note the time taken for echo signal to return to 0
        Clock_Delay1us(1);
        time++;
        echo = (P2->IN & echoP);
    }

    //Pace of sound in air: 0.343 km/s or mm/μs, so time times this rate gives the distance
    return (0.343 * time);
}

uint32_t SetDistanceRight(uint8_t trigP, uint8_t echoP){
    uint32_t time;
    uint8_t echo;

    //Turn us trigger off
    P4->OUT &= ~trigP;
    Clock_Delay1us(2);

    //Turn us trigger on
    P4->OUT |= trigP;
    Clock_Delay1us(10);

    //Turn us trigger off
    P4->OUT &= ~trigP;

    time = 0;
    echo = (P3->IN & echoP);

    //Echo sensor waits for trigger signal
    while( echo == 0x00 && time < TIMELIM){
        //Delay one microsecond to note the time taken to receive the desired signal
        Clock_Delay1us(1);
        time++;
        echo = (P3->IN & echoP);
    }

    time = 0;
    echo = (P3->IN & echoP);

    //Wait for echo signal to return to LOW
    while( echo != 0x00 && time < TIMELIM){
        //Delay one microsecond to note the time taken for echo signal to return to 0
        Clock_Delay1us(1);
        time++;
        echo = (P3->IN & echoP);
    }

    //Pace of sound in air: 0.343 km/s or mm/μs, so time times this rate gives the distance
    return (0.343 * time);
}


void ultrasound_init(void)
{
    //TriggerC as GPIO, P6.4
    P6->SEL0 &= ~0x10;
    P6->SEL1 &= ~0x10;
    //TriggerC as Output
    P6->DIR |= 0x10;

    //EchoC as GPIO P6.5
    P6->SEL0 &= ~0x20;
    P6->SEL1 &= ~0x20;
    //EchoC as input
    P6->DIR &= ~0x20;

    //TriggerL as GPIO P6.0
    P6->SEL0 &= ~0x01;
    P6->SEL1 &= ~0x01;
    //Trigger as Output
    P6->DIR |= 0x01;

    //EchoBitL as GPIO P2.5
    P2->SEL0 &= ~0x20;
    P2->SEL1 &= ~0x20;
    //Echo as input
    P2->DIR &= ~0x20;

    //TriggerR as GPIO P4.1
    P4->SEL0 &= ~0x02;
    P4->SEL1 &= ~0x02;
    //Trigger as Output
    P4->DIR |= 0x02;

    //EchoBitR as GPIO P3.0
    P3->SEL0 &= ~0x01;
    P3->SEL1 &= ~0x01;
    //Echo as input
    P3->DIR &= ~0x01;
}

void us_distances(uint32_t *left, uint32_t *center, uint32_t *right)
{
    *center = SetDistanceCenter(0x10, 0x20);
    *left = SetDistanceLeft(0x01, 0x20);
    *right = SetDistanceRight(0x02, 0x01);
}
