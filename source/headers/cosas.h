

#define __R     volatile const
#define __W     volatile
#define __RW    volatile

typedef unsigned int uint32_t;
typedef short unsigned int uint16_t;
typedef unsigned char uint8_t;
//typedef int int32_t;
//typedef short int int16_t;
//typedef char int8_t;

#define GPIOInterrupts  ((__RW uint32_t*)0xA000400)
//#define GPIO            ((__RW uint32_t*)0xA000000)
#define ActiveInterruptsVectors1 ((__RW uint32_t*)0x000000C0)
#define ActiveInterruptsVectors0 ((__RW uint32_t*)0x00000000)

#define SYSAHBCLKCTRL0  ((__RW uint32_t*)0x40048080)
#define PRESETCTRL0 ((__RW uint32_t*) 0x40048088)
#define INTENSET0 ((__RW uint32_t*)  0x4005800C)
#define INTENSET1 ((__RW uint32_t*)  0x4005C00C)

#define INTENCLR0 ((__RW uint32_t*)0x40058010)
#define INTENCLR1 ((__RW uint32_t*)0x4005C010)

#define PINASSIGN5 ((__RW uint32_t*)0x4000C014)
#define PINASSIGN6 ((__RW uint32_t*) 0x4000C018)

#define SPI0CLKSEL ((__RW uint32_t*) 0x400480B4)
#define SPI1CLKSEL ((__RW uint32_t*) 0x400480B8)

#define CFG0 ((__RW uint32_t*) 0x40058000)
#define CFG1 ((__RW uint32_t*) 0x4005C000)
#define TXDATCTL1 ((__RW uint32_t*) 0x4005C018)
#define TXDATCTL0 ((__RW uint32_t*) 0x40058018)

#define EXAMPLE_SPI_MASTER          SPI0
#define EXAMPLE_CLK_SRC             kCLOCK_MainClk
#define EXAMPLE_SPI_MASTER_CLK_FREQ CLOCK_GetFreq(EXAMPLE_CLK_SRC)
#define EXAMPLE_SPI_MASTER_BAUDRATE 500000U
#define EXAMPLE_SPI_MASTER_SSEL     kSPI_Ssel0Assert


typedef struct _spi_master_config
{
    bool enableLoopback;                /*!< Enable loopback for test purpose */
    bool enableMaster;                  /*!< Enable SPI at initialization time */
    uint32_t baudRate_Bps;              /*!< Baud Rate for SPI in Hz */
    spi_clock_polarity_t clockPolarity; /*!< Clock polarity */
    spi_clock_phase_t clockPhase;       /*!< Clock phase */
    spi_shift_direction_t direction;    /*!< MSB or LSB */
    uint8_t dataWidth;                  /*!< Width of the data */
    spi_ssel_t sselNumber;              /*!< Slave select number */
    spi_spol_t sselPolarity;            /*!< Configure active CS polarity */
    spi_delay_config_t delayConfig;     /*!< Configure for delay time. */
} spi_master_config_t;

typedef union{
	uint32_t Reg;
	struct{
	uint32_t Enable:1;
	uint32_t Res:1;	//-->	Reservado escribir 0	<---
	uint32_t Master:1;	//-->	Modo maestro	<--
	uint32_t LSBF:1;	//-->	LSB firs mode	<---
	uint32_t CPHA:1;	//-->	Fase de lectura - Lectura en primer transicion de reloj en subida o bajada	<--
	uint32_t CPOL:1;	//--> 	Polaridad del reloj 	<---
	uint32_t Reser:1;
	uint32_t LOOP:1;	//-->	Modo Lopback aplica en modo maestro	<--
	uint32_t SPOL0:1;	//-->	Polaridad de SSEL0	<--
	uint32_t SPOL1:1;	//-->	Polaridad de SSEL1	<--
	uint32_t SPEL2:1;	//-->	Polaridad de SSEL2	<---
	uint32_t SPEL3:1;	//-->	Polaridad de SSEL3	<---
	uint32_t Reserv:19;	//-->	Reservados	<---
}
	SPI_Config;
}SPI_Cam_Configura;

void InicializarSPI(void);
