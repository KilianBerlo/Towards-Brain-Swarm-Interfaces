#include <stdint.h>
#include <stdio.h>

#include "msp.h"
#include "initialization.h"
#include "differentialRobot.h"
#include "motor.h"
#include "timer_A1.h"
#include "interruptHandler.h"
#include "controller.h"
#include "UART1.h"
#include "us_distance.h"

#define CONTROL_PERIOD 5000
//#define PHATH_LEN 6
//float path[PHATH_LEN][2]= { {0.8,0}, {1.6,0}, {1.6, -0.8}, {1.6,-1.6},  {0,-1.6},  {0,0}  };
//uint8_t pauses[] =        {  1,      0,       1,            0,           0,         0     };

#define PHATH_LEN 2
char temp;
float path[PHATH_LEN][2] = { { 10, 10 }, { 2, 2 } };
uint8_t pauses[] = { 0, 0 };

uint8_t goal_reached = 0;
uint32_t pause_cntr = 0;

uint32_t location_cntr = 0;

void main(void)
{
    P1->OUT &= ~BIT5;
    P1->DIR |= BIT5;
    // initialize the clock, buttons to go, and UART for debugging
    initialize();
    differential_robot_t *robot = robot_init();
    controller_init(path[location_cntr][0], path[location_cntr][1], robot, CONTROL_PERIOD, &goal_reached);
    enableInterrupts();
    //ultrasound_init();

//    uint8_t control_code = '0';

    while (1)
    {
        waitForInterrupt();
    }

#if 0
//--------------avoid obstacles behavior-----------------------

    avoid_obstacle_init(robot, CONTROL_PERIOD);

    while(1) {
//        temp = UART1_InChar();
//        UART1_OutChar('g');
//        UART1_OutChar(temp);
        waitForInterrupt();
    }

//--------------Go to goal behavior-----------------------


    go_to_goal_init(path[location_cntr][0] ,path[location_cntr][1] , robot,CONTROL_PERIOD, goal_flag);
    enableInterrupts();

    while(1){
      if (goal_reached)
      {
        disableInterrupts();
        location_cntr++;  // increase to set the next goal
        goal_reached = 0;
        enableInterrupts();
        
        // check if the robot has reached the final location (or goal)
        if(location_cntr == PHATH_LEN )
        {
            motor_stop();
            timerA1_stop();
        }
        else
        {
            // check if the robot need to pause before going to the next location
            if (pauses[location_cntr-1])
            {
                while (pause_cntr < 0x3fffff)
                {
                    pause_cntr++;
                }
                pause_cntr=0;
            }
            // go to the next location (or goal)
            go_to_goal_init(path[location_cntr][0] ,path[location_cntr][1] , robot, CONTROL_PERIOD, goal_flag);
        }
      }
      waitForInterrupt();
    }
#endif 

}
