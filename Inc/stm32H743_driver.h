/*
 * ccc.h
 *
 *  Created on: Apr 8, 2020
 *      Author: Erick Cabral
 */

#ifndef STM32H743_DRIVER_H_
#define STM32H743_DRIVER_H_


#include <cstdint>
using namespace std;

#define __uint8					unsigned short int
#define __int32U				unsigned long int

#define __volU16				volatile unsigned short int
#define __volU32				volatile unsigned long int

/*<! NVIC IRQ BASE ADRESSES >*/
/*
#define NVIC_ISER0						((__volU32*)0xE000E100U)
 #define NVIC_ISER1						((__volU32*)0xE000E104U)
 #define NVIC_ISER2						((__volU32*)0xE000E108U)
 #define NVIC_ISER3						((__volU32*)0xE000E10CU)
 #define NVIC_ISER4						((__volU32*)0xE000E110U)
 #define NVIC_ISER5						((__volU32*)0xE000E114U)
 #define NVIC_ISER6						((__volU32*)0xE000E118U)
 #define NVIC_ISER7						((__volU32*)0xE000E11CU)
 #define NVIC_ICER0						((__volU32*)0XE000E180U)
 #define NVIC_ICER1						((__volU32*)0XE000E184U)
 #define NVIC_ICER2						((__volU32*)0XE000E188U)
 #define NVIC_ICER3						((__volU32*)0XE000E18CU)
 #define NVIC_ICER4						((__volU32*)0XE000E190U)
 #define NVIC_ICER5						((__volU32*)0XE000E194U)
 #define NVIC_ICER6						((__volU32*)0XE000E198U)
 #define NVIC_ICER7						((__volU32*)0XE000E19CU)
 #define NVIC_PRI0						((__volU32*)0xE000E400U)
 #define NVIC_ISPR0						((__volU32*)0XE000E200U)
 */

class x {

};


class NVIC {
public:
	void setIRQ(__uint8 irqNum, bool enable);
	void reserIRQ(__uint8 irqNum, bool enable);
	void setIRQPenReg(__uint8 irqNum, bool enable);
	void setIRQ_PRIORITY(__uint8 irqNum, bool enable);

private:
	__volU32* pISERx = ((__volU32*) 0xE000E100U);
	__volU32 *pICERx = ((__volU32*) 0XE000E180U);
	__volU32 *pPRIx = ((__volU32*) 0xE000E400U);
	__volU32 *pISPRx = ((__volU32*) 0XE000E200U);

};

class EXTI {
public:
	void setRisingEdge(__volU16 irqNum, bool enable);
	void setFallingEdge(__volU16 irqNum, bool enable);
	void setCPUIMR(__volU16 irqNum, bool enable);
	void setCPUEMR(__volU16 irqNum, bool enable);
	void setCPUPendingReg(__volU16 irqNum, bool enable);

private:
	__volU32 *pRTSR1 = ((__volU32*) 0x58000000);			// OFFSET	0x00
	__volU32 *pFTSR1 = ((__volU32*) 0x58000000 + 0x04U);	// OFFSET 	0x04
	__volU32 *pCPUIMRx = ((__volU32*) 0x58000000 + 0x80U);	// OFFSET	0x80
	__volU32 *pCPUEMRx = ((__volU32*) 0x58000000 + 0x84U);	// OFFSET 	0x84
	__volU32 *pCPUPRx = ((__volU32*) 0x58000000 + 0x88U);	// OFFSET 	0x88
};

#endif /* STM32H743_DRIVER_H_ */
