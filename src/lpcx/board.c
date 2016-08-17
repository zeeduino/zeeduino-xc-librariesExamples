/*
 * board.c
 *
 *  Created on: May 16, 2015
 *      Author: iceman
 */

#include "chip.h"
#include "board/variant.h"

#if !defined(NO_BOARD_LIB)

/* System oscillator rate and clock rate on the CLKIN pin */
// Needed by sysinit.c
const uint32_t OscRateIn = 12000000;
const uint32_t ExtRateIn = 0;

/*
 * Set up and initialize hardware prior to call to main() in main.cpp
 * This is where we initialize basic system resources that any
 * board with this chip should have initialized
 */
void Board_SystemInit(void)
{
	// Initialization done in Board_Init() in arduino-xc-lpc13xx
	initVariant();
}

#endif


