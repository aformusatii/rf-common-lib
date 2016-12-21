/********************************************************************************
Includes
********************************************************************************/
#include <avr/io.h>
#include <stdio.h>
#include "../common/util.h"

/********************************************************************************
	Macros and Defines
********************************************************************************/
#define TIMER1_PRESCALER 256
#define CYCLES_PER_SECOND F_CPU/TIMER1_PRESCALER

/********************************************************************************
Function Prototypes
********************************************************************************/
void initTimer1();
void incrementOvf();
uint64_t convertSecondsToCicles(uint16_t value);
uint64_t getCurrentTimeCicles();
uint32_t getElapsedMilliseconds(uint64_t startTime);
