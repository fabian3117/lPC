#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "LPC845.h"
#include "./headers/cosas.h"
#include "fsl_debug_console.h"
/* TODO: insert other include files here. */

/* TODO: insert other definitions and declarations here. */

/*
 * @brief   Application entry point.
 */
int main(void) {

    /* Init board hardware. */
   // BOARD_InitBootPins();
   // BOARD_InitBootClocks();
    //BOARD_InitBootPeripherals();
#ifndef BOARD_INIT_DEBUG_CONSOLE_PERIPHERAL
    /* Init FSL debug console. */
    //BOARD_InitDebugConsole();
#endif

    PRINTF("Hello World\n");
    InicializarSPI();
    /* Force the counter to be placed into memory. */
    volatile static int i = 0 ;
    /* Enter an infinite loop, just incrementing a counter. */
    while(1) {
        i++ ;
        /* 'Dummy' NOP to allow source level single stepping of
            tight while() loop */
      //  __asm volatile ("nop");
    }
    return 0 ;
}

void InicializarSPI(void){
	//SYSAHBCLKCTRL0=SYSAHBCLKCTRL0|4095;
	SYSAHBCLKCTRL0[0]=0x0019CF;


	PRESETCTRL0[0]&0x43000000;

	//INTENCLR1&0x43000000;
	INTENCLR1[0]=0x00000002;
	//-->   MISO0 PIN0_1 (Entrada) - MOSI (Salida) PIN0_5  -   CLOCK(Salida)  PIN0_4   - SS(Salida) Pondre pin selecionador SEL0 PIN0_2
	PINASSIGN6[0]=0xFF030201;
	//-->   Solo me falta configurar la salida del maestro y el clock  <--
	PINASSIGN5[0]=0x0504FFFF;

	//-->   Ahora falta usar SPI0CLKSEL registro para configurar la fuente de clock del SPI <--
	//-->   Por lo que entiendo tengo que poner el SPIClOCKSELECT en 001 para usar el reloj principal   <--
	//SPI1CLKSEL
	SPI1CLKSEL[0]&0xFFFFFF01;

	CFG1[0]=      0x00000285;  //-->   Activo modo maestro MSB primero en enviar - Captura datos  en el primer cambio de reloj esta en modo LOOP en activo alto    ---

	//--> Ahora intentare enviar informacion usando registro TXDATCTL con control   -- Pag 313 <---
	//SPI1CLKSEL&0x01FFFFFF;
	//CFG1[0]=  0x00000285;
	//TXDATCTL1[0]=0x0F4D0110;
	//TxCon1[0]= 0x0F4D0110;  //-->   Enn teoria esto deberia enviar los datos por SPI que dato? creooo que un 3 no lo se rick    <--


}
