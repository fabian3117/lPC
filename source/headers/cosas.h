

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


void InicializarSPI(void);
