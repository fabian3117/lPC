#include "mde_general.h"
#include "../mis_drivers/gpio.h"
#include "salidas_digitales.h"
#include "wifii.h"
#include "Sensor_de_distancia.h"
#include "entradas_digitales.h"
extern uint8_t Error;

void MDE_Principal (void){


}
void Funcion_titilante_ON (void){
	//-->	Esta funcion Me prende el Modo Titilante	<--
	//PRINT("");
		Amarillos_ON();
		TimerStop(2);
		TimerStart(2,TIEMPO_ENCENDIDO_TITILANTE,Funcion_titilante_OFF,SEG);

}
void Funcion_titilante_OFF (void){
	//-->	OFF	:	 apagar	<---

	Amarillos_OFF();
	TimerStop(EV_FUNC_TITILANTE);
	TimerStart(EV_FUNC_TITILANTE,TIEMPO_APAGADO_TITILANTE,Funcion_titilante_ON,SEG);

}
void Inicializacion (void){
	 SysTickInic (SystemCoreClock/DV_FRC_TMR); //Con esta configuracion, el stick interrumpe cada 4 ms

	//-->	Todo lo de I2C esta en pagina 331	<--
	//-->	Activar el clock de la interfaz (Activar el pin)	<--
	//-->	SYSAHBCLKCTRL	Poner un 1 en bit 5 <--
	//SYSCON->
	 SWM0->PINENABLE0&=~(0x3<<12);
	 IOCON->PIO[IOCON_INDEX_PIO0_11]|=(0x2<<8);
	 IOCON->PIO[IOCON_INDEX_PIO0_10]|=(0x2<<8);
	uint8_t mask_I2C_0=(0x3<<5);
	//SYSCON->SYSAHBCLKCTRL0
//	(0x40048080u)=(0x1<<5);
	SYSCON->SYSAHBCLKCTRL0|=mask_I2C_0;	//-->	Pongo un 1 en el bit de activacion clock de pines I2C0
	SYSCON->FCLKSEL[5]&=(0xFFFFFFF1);	//-->	Esto deberia enviar al I2C el clock principal	<--
	//-->	Ahora reinicio el peliferico	<--
	//-->	PRESETCTRL		Poner en 1 el bit 5 para I2C0	<--
	//SYSCON->PRESETCTRL0|=(0x1<<5);

	//-->	Ahora tengo que habilitar las interrupciones del I2C0	<--

	//I2C0_BASE=(0x151);
	//ISER0=(0x1<<8);	//-->	Puedo hacer esto por que escribir 0 no tiene efecto aca	<--
	I2C0->INTENCLR=1;
	I2C0->INTENSET=1;
	I2C0->STAT=1;
	I2C0->CFG=(0x2);	//-->	I2C_0	Registro de configuracion	<--
	//I2C0->SLVADR[0]=(0x7);
		//-->	Tengo que limpiar las demas interrupciones creoo	<--


	//-->	NVIC	No entendi	<--
	//-->	Uso la tabla ISER0  bit 8 con un 1	Para habilitar la interrupcion de I2C0 	<--

	//-->	La tabla INTENCLR Limpia y habilita pelifericos	<--


	//-->	Tengo que habilitar el SDA y SCL	<--
	SWM0->PINENABLE0&=~(0x3<<12);	//-->	Tengo que hacer con un and de tal manera de poner en 0 los bit 12-13	<-- ~(0x2<<12)

	//-->	Ahora voy a poner el I2C modo Esclavo	<--
	//CFG
}

void Setear_Movimiento1(uint32_t S1){
	switch(S1){
	case 'R':
			LED_ROJO_MOVIMIENTO_1();
				break;
	case 'A':
			LED_AMARILLO_MOVIMIENTO_1();
				break;
	case 'V':
			LED_VERDE_MOVIMIENTO_1();
				break;
	}
}
void Setear_Movimiento2(uint32_t S2){
	switch(S2){
	case 'R':
			LED_ROJO_MOVIMIENTO_2();
				break;
	case 'A':
			LED_AMARILLO_MOVIMIENTO_2();
				break;
	case 'V':
			LED_VERDE_MOVIMIENTO_2();
				break;
	}
}
void Contar_Autos_Movimiento1 (uint32_t	S1){
	if(S1=='V'){
		N_Autos_S1=Contar_Autos();
	}
}
void Contar_Autos_Movimiento2 (uint32_t	S2){
	if(S2=='V'){
		N_Autos_S2=Contar_Autos();
	}
}
void Programa_Semaforo (uint32_t S1 , uint32_t S2 , uint32_t T){

		flag_intervalo=0; // Apenas me pasen los estados del semaforo con sus tiempos, desactivo un flag para que no siga mandando nuevos estados.
		while((contador_segundos_de_programa_semaforo*DV_FRC_TMR)<=T){ //¿Esta bien esto? es decir, quise poner que avance unos segundos y se quede en el estado de abajo mientras que no sea mayor que mi tiempo.
			Setear_Movimiento1(S1);
			Contar_Autos_Movimiento1(S1);
			Setear_Movimiento2(S2);
			Contar_Autos_Movimiento2(S2);
		}
			N_INTERVALO++; //Aumento los intervalos aca apenas termino.
			flag_intervalo=1; //Aca activo de nuevo para que el while de Accion pueda circular con su nuevo indice y me pasen el siguiente intervalo
}
void Accion (void){
	while(N_INTERVALO<=INDICE_INTERVALO_FINAL){ //¿Esta bien hacer esto? Yo quiero decir que se quede constantemente entre las lineas 161, y 168.
		if(flag_intervalo){
			Programa_Semaforo(Buffer_S1[N_INTERVALO],Buffer_S2[N_INTERVALO],Buffer_T[N_INTERVALO]);
		}
		if(N_INTERVALO==INDICE_INTERVALO_FINAL) //Esto lo hago para que sea ciclico, porque INIDICE_INTERVALO_FINAL es la cantida de intervalos que tiene mi programa actual que esta dando vueltas en el micro.
		{
			N_INTERVALO=0;
		}
	}
}
