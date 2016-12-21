/********************************************************************************
Includes
********************************************************************************/

#include "mtimer.h"
#include "mtimer.h"

volatile uint32_t timer1_ovf_count = 0;

/**
 * Initialize timer.
 */
void initTimer1() {
    /*
     * |-------------------------------------------------------------------------------|
       | ICNC1 ICES1 – WGM13 WGM12 CS12 CS11 CS10 [TCCR1B]                             |
       |-------------------------------------------------------------------------------|
       | CS12 | CS11 | CS10 | Description                                              |
       |-------------------------------------------------------------------------------|
       |    0 |    0 |    0 | No clock source (Timer/Counter stopped).                 |
       |    0 |    0 |    1 | clkI/O/1 (No prescaling)                                 |
       |    0 |    1 |    0 | clkI/O/8 (From prescaler)                                |
       |    0 |    1 |    1 | clkI/O/64 (From prescaler)                               |
       |    1 |    0 |    0 | clkI/O/256 (From prescaler)                              |
       |    1 |    0 |    1 | clkI/O/1024 (From prescaler)                             |
       |    1 |    1 |    0 | External clock source on T1 pin. Clock on falling edge.  |
       |    1 |    1 |    1 | External clock source on T1 pin. Clock on rising edge.   |
       |-------------------------------------------------------------------------------|
    */
    // clkI/O/1024 (From prescaler)
    TCCR1B = (1<<CS12)|(0<<CS11)|(0<<CS10);

    // Enable Timer/Counter1 Overflow interrupt
	_on(TOIE1, TIMSK1);
}

void incrementOvf() {
	timer1_ovf_count++;
}

/**
 * Returns elapsed time in milliseconds starting with given startTime (in cpu cicles).
 * Figure valid for clkI/O/1024 (From prescaler) and clk = 8 Mhz
 */
uint32_t getElapsedMilliseconds(uint64_t startTime) {
	uint64_t endTime = getCurrentTimeCicles();
	uint64_t diff = (endTime - startTime);

	return (uint32_t) ((diff * 10000) / CYCLES_PER_SECOND);
}

/**
 * Returns cpu cicles needed to reach given period of seconds.
 */
uint64_t convertSecondsToCicles(uint16_t value) {
	return (value == 0) ? 0: getCurrentTimeCicles() + (value * CYCLES_PER_SECOND);
}

/**
 * Returns current cpu cicles counted so far by Timer 1 (48 bits - 7812.5 per second, max value ~1142 years, should be enough).
 * Figure valid for clkI/O/1024 (From prescaler) and clk = 8 Mhz
 */
uint64_t getCurrentTimeCicles() {
	uint32_t highValue = timer1_ovf_count;
	uint16_t lowValue = TCNT1;

	if (lowValue < 4) {
		highValue = timer1_ovf_count;
	}

	return _to_uint64(highValue, lowValue);
}
