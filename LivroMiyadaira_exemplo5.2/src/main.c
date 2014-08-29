/*
===============================================================================
 Name        : main.c
 Author      : $(author)
 Version     :
 Copyright   : $(copyright)
 Description : main definition
===============================================================================
*/

#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif

#include <cr_section_macros.h>

// TODO: insert other include files here

// TODO: insert other definitions and declarations here
void Config_CLK();
void Config_FLASH();
void Config_CLKOUT();
void PLL1_FEED();

int main(void) {

    // TODO: insert code here

    // Force the counter to be placed into memory
    volatile static int i = 0 ;
    // Enter an infinite loop, just incrementing a counter
    while(1) {
        i++ ;
    }
    return 0 ;
}

void config_CLK()
{
	LPC_SC->SCS=1<<5;	// clock entre 1 e 20mhz
	while( !(LPC_SC->SCS & (1<<6)) );

	LPC_SC->PLL1CON=0x00;	// desconecta a PLL
	PLL1_FEED();

	LPC_SC->PLL1CFG=2;	// configura 3 * osc (16 mhz) = 48 mhz
	PLL1FEED();

	LPC_SC->PLL1CON=1<<0;	// conecta a PLL
	PLL1_FEED();


	LPC_SC->CLKSRCSEL=0b01;	// usa o OSC principal a 12 mhz
	LPC_SC->PLL1CFG = 99<<0 | 7<<16;	// seta para 300 mhz
	PLL1_FEED();

	LPC_SC->PLL0CON=1<<0;
	PLL0_FEED();



	while(!(LPC_SC->PLL0STAT & (1<<26)));
}

void PLL1_FEED()
{
	__disable_irq();
	LPC_SC->PLL0FEED = 0xAA;
	LPC_SC->PLL0FEED = 0x55;
	__enable_irq();
}

