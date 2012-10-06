#include "lpc17xx.h"

#define PCUART0_POWERON 	(1 << 3)
#define PCLK_UART0 				6
#define PCLK_UART0_MASK 	(3 << 6)
#define LSR_RDR						0x01
#define LSR_THRE					0x20

void UART0_Init (int baudrate) {
	// PCLK_UART0 is being set to 1/4 of SystemCoreClock
	int pclk = SystemCoreClock / 4;	
	
	// Turn on power to UART0
	LPC_SC->PCONP |=  PCUART0_POWERON;
		
	// Turn on UART0 peripheral clock
	LPC_SC->PCLKSEL0 &= ~(PCLK_UART0_MASK);
	LPC_SC->PCLKSEL0 |=  (0 << PCLK_UART0);		// PCLK_periph = CCLK/4
	
	// Set PINSEL0 so that P0.2 = TXD0, P0.3 = RXD0
	LPC_PINCON->PINSEL0 &= ~0xf0;
	LPC_PINCON->PINSEL0 |= ((1 << 4) | (1 << 6));
	
	LPC_UART0->LCR = 0x83;		// 8 bits, no Parity, 1 Stop bit, DLAB=1
	unsigned long Fdiv = (pclk / 16) / baudrate ;	// Set baud rate
	LPC_UART0->DLM = Fdiv >> 8;							
	LPC_UART0->DLL = Fdiv;
	LPC_UART0->LCR = 0x03;		// 8 bits, no Parity, 1 Stop bit DLAB = 0
	LPC_UART0->FCR = 0x07;		// Enable and reset TX and RX FIFO
}

void UART0_Sendchar (char c) {
	while ((LPC_UART0->LSR & LSR_THRE) == 0)
		;
	LPC_UART0->THR = c;
}

char UART0_Haschar () {
	return (LPC_UART0->LSR & LSR_RDR) != 0;
}

char UART0_Getchar () {
	while (!UART0_Haschar())
		;
	return LPC_UART0->RBR;
}

void UART0_PrintString (const char *s) {
	while (*s != 0)
		UART0_Sendchar(*s++);
}
