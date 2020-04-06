/*p
 * stm32H743xx.h
 *
 *  Created on: 26 Mar 2020
 *      Author: Erick Cabral
 */

#ifndef STM32H743XX_H_
#define STM32H743XX_H_

using namespace std;

/* CUSTOIM STM32H743 DRIVER */

/*!< DEFAULT VARIABLES >*/
#define SET				1
#define RESET			0
#define ENABLE			SET
#define DISABLE			DISABLE
#define HIGH			SET
#define LOW				DISABLE

#define RESET_ALL 	0x00000000U

#define __vol32U 	volatile unsigned long int
#define __int32U 	unsigned long int



/*<! NVIC IRQ BASE ADRESSES >*/
#define NVIC_ISER0						((__vol32U*)0xE000E100U)
#define NVIC_ISER1						((__vol32U*)0xE000E104U)
#define NVIC_ISER2						((__vol32U*)0xE000E108U)
#define NVIC_ISER3						((__vol32U*)0xE000E10CU)
#define NVIC_ISER4						((__vol32U*)0xE000E110U)
#define NVIC_ISER5						((__vol32U*)0xE000E114U)
#define NVIC_ISER6						((__vol32U*)0xE000E118U)
#define NVIC_ISER7						((__vol32U*)0xE000E11CU)

#define NVIC_ICER0						((__vol32U*)0XE000E180U)
#define NVIC_ICER1						((__vol32U*)0XE000E184U)
#define NVIC_ICER2						((__vol32U*)0XE000E188U)
#define NVIC_ICER3						((__vol32U*)0XE000E18CU)
#define NVIC_ICER4						((__vol32U*)0XE000E190U)
#define NVIC_ICER5						((__vol32U*)0XE000E194U)
#define NVIC_ICER6						((__vol32U*)0XE000E198U)
#define NVIC_ICER7						((__vol32U*)0XE000E19CU)

/*!< BASE ADDRESSES DEFAULT >*/
#define RCC_BASEADDRESS					0x58024400U

#define APB1_BASEADDRESS				0x40000000U
#define APB2_BASEADDRESS				0x40010000U
#define APB3_BASEADDRESS				0x50000000U
#define APB4_BASEADDRESS				0x58000000U

#define AHB1_BASEADDRESS				0x40017400U
#define AHB2_BASEADDRESS				0x48022800U
#define AHB3_BASEADDRESS				0x51000000U
#define AHB4_BASEADDRESS				0x58020000U

#define GPIOK_BASEADDRESS 				0x58022800U
#define GPIOJ_BASEADDRESS				0x58022400U
#define GPIOI_BASEADDRESS 				0x58022000U
#define GPIOH_BASEADDRESS 				0x58021C00U
#define GPIOG_BASEADDRESS 				0x58021800U
#define GPIOF_BASEADDRESS 				0x58021400U
#define GPIOE_BASEADDRESS 				0x58021000U
#define GPIOD_BASEADDRESS 				0x58020C00U
#define GPIOC_BASEADDRESS 				0x58020800U
#define GPIOB_BASEADDRESS				0x58020400U
#define GPIOA_BASEADDRESS 				0x58020000U

/*
 *  GPIO SETUP STRUCTURE
 */
#define GPIOA 						0
#define GPIOB 						1
#define GPIOC 						2
#define GPIOD 						3
#define GPIOE 						4
#define GPIOF 						5
#define GPIOG 						6
#define GPIOH 						7
#define GPIOI 						8
#define GPIOJ						9
#define GPIOK						10

/**
 *  RCC SETUP API
 */
#define DEFAULT_AHB4_VALUE			RESET_ALL
#define DEFAULT_APB4_VALUE			0x00010000
#define APB4_SYSCFG_ENABLE  		0x00010002

class RCC {

public:
	RCC(__int32U rcc_baseAddress);
	/*setting full registers*/
	void setAHB4ENR(__int32U value);
	void setAPB4ENR(__int32U value);

	/*set Single Register*/
	void setGPIOxEnable(int gpioBit, bool enable);
	//void setSYSCONFIG();
private:
	__vol32U *pAHB4RSTR; // = ((__vol32U*)(RCC_BASEADDRES + 0x088));		//OFFSET -> 0x088
	__vol32U *pAHB4ENR;			//OFFSET -> 0x0E0
	__vol32U *pC1_AHB4ENR; 	//= (RCC_BASEADDRES + 0x140);	//OFFSET -> 0x140
	__vol32U *pC1_AHB4LPENR; // = (RCC_BASEADDRES + 0x168);	//OFFSET -> 0x168

	__vol32U *pAPB4RSTR; 		//OFFSET -> 0x09C
	__vol32U *pAPB4ENR;			//OFFSET -> 0x0F4
	__vol32U *pC1_APB4ENR; 		//OFFSET -> 0x154
};

/*
 *  GPIO SETUP AND PIN CONFIG
 */

/* PIN NUMBER */
#define PIN_0	 				0	// 	0b0000
#define PIN_1					1	// 	0b0001
#define PIN_2	 				2	// 	0b0010
#define PIN_3					3	// 	0b0011
#define PIN_4	 				4	// 	0b0100
#define PIN_5					5	// 	0b0101
#define PIN_6	 				6	// 	0b0110
#define PIN_7					7	// 	0b0111
#define PIN_8	 				8	// 	0b1000
#define PIN_9					9	// 	0b1001
#define PIN_10 					10	// 	0b1010
#define PIN_11					11	// 	0b1011
#define PIN_12 					12	// 	0b1100
#define PIN_13					13	// 	0b1101
#define PIN_14					14	// 	0b1110
#define PIN_15					15	// 	0b1111

/* PIN MODE */
#define MODE_INPUT		 	0	// 	0b00	: Input mode
#define MODE_OUTPUT			1	// 	0b01	: General purpose output mode
#define MODE_ALT			2	//	0b10	: Alternate function mode
#define MODE_ANALOG			3	//	0b11	: Analog mode (reset state)

/* OUTPUT MODE */
#define TYPE_PUSHPULL		0	// 	0b00	: Output push-pull (reset state)
#define TYPE_OPEN_DRAIN		1	// 	0b01	: Output open-drain

/* SPEED MODE */
#define SPD_LOW		 		0	// 	0b00	: Low speed
#define SPD_MID				1	// 	0b01	: Medium speed
#define SPD_HIGH			2	//	0b10	: High speed
#define SPD_VHIGH			3	//	0b11	: Very high speed

/* RESISTOR MODE */
#define PUPD_DISABLED		0	// 	0b00	: No pull-up, pull-down
#define PUPD_PULL_UP		1	// 	0b01	: Pull-up
#define PUPD_PULL_DOWN		2	//	0b10	: Pull-down
#define PUDP_RESERVED		3	//	0b11	: Reserved

/* OUTPUT STATE */
#define OUTPUT_LOW	 		0	// 	0b00	: LOW
#define OUTPUT_HIGH			1	// 	0b01	: HIGH

/* ALT FUNCTION */
#define AF0	 				0	// 	0b0000: AF0
#define AF1					1	// 	0b0001: AF1
#define AF2	 				2	// 	0b0010: AF2
#define AF3					3	// 	0b0011: AF3
#define AF4	 				4	// 	0b0100: AF4
#define AF5					5	// 	0b0101: AF5
#define AF6	 				6	// 	0b0110: AF6
#define AF7					7	// 	0b0111: AF7
#define AF8	 				8	// 	0b1000: AF8
#define AF9					9	// 	0b1001: AF9
#define AF10 				10	// 	0b1010: AF10
#define AF11				11	// 	0b1011: AF11
#define AF12 				12	// 	0b1100: AF12
#define AF13				13	// 	0b1101: AF13
#define AF14				14	// 	0b1110: AF14
#define AF15				15	// 	0b1111: AF15

// GPIO CLASS //
class GPIOx {
public:
	GPIOx(__vol32U gpio_baseAddr);
	void setGPIOxEnable(int gpioBit, bool enable);

	//PIN CONFIG//
	void setPinMode(int pinNum, int pinMode); 	// 2 Bits Register
	void setPinType(int pinNum, int pinType);	// 2 Bits Register
	void setPinSpeed(int pinNum, int pinSpeed);	// 2 Bits Register
	void setPinPUPD(int pinNum, int pinPUPD);	// 2 Bits Register
	int getPinIDR(int pinNum);	// 1 Bit Register
	void setPinODR(int pinNum, int pinODR);	// 1 Bit Register
	void setPinBSRR(int pinNum, int pinBSRR);	// 2 Bits Register
	void setPinLCKR(int pinNum, int pinLCKR);	// 2 Bits Register
	void setPinAFRL(int pinNum, int pinAFRL);	// 2 Bits Register
	void setPinAFRH(int pinNum, int pinAFRH);	// 2 Bits Register

private:
	__vol32U *pMODER;			//OFFSET -> 0x00
	__vol32U *pOTYPER;			//OFFSET -> 0x04
	__vol32U *pOSPEEDR;			//OFFSET -> 0x08
	__vol32U *pPUPDR;			//OFFSET -> 0x0C
	__vol32U *pIDR;				//OFFSET -> 0x10
	__vol32U *pODR;				//OFFSET -> 0x14
	__vol32U *pBSRR;				//OFFSET -> 0x18
	__vol32U *pLCKR;				//OFFSET -> 0x1C
	__vol32U *pAFRL;				//OFFSET -> 0x20
	__vol32U *pAFRH;				//OFFSET -> 0x24

};

/**
 *  SYSCONFIG REGISTER DEFAULTS
 */
#define SYSCFG_BASEADDRESS		0x58000400U
#define SYSCFG_RESET_VALUE		RESET_ALL

#define SYSCFG_PORT_A			0b0000
#define	SYSCFG_PORT_B			0b0001
#define	SYSCFG_PORT_C			0b0010
#define	SYSCFG_PORT_D			0b0011
#define	SYSCFG_PORT_E			0b0100
#define	SYSCFG_PORT_F			0b0101
#define	SYSCFG_PORT_G			0b0110
#define	SYSCFG_PORT_H			0b0111
#define	SYSCFG_PORT_I			0b1000
#define	SYSCFG_PORT_J			0b1001
#define	SYSCFG_PORT_K			0b1010

#define EXTI_15_10_BASEADDRESS	0x000000E0
#define EXTI_15_10_POSITION		40

/**
 *  SYSCFG API.
 *  SYSCFG IS CONNECTED TO APB4 (BASE ADD -> 0x58000000U)
 */
class SYSCFG {
public:
	SYSCFG();
	void setPMCR();
	void setEXTI_CR(int pinNum, int portPx);

private:
	__vol32U *pPMCR = ((__vol32U*) (SYSCFG_BASEADDRESS + 0x04));//OFFSET -> 0x04
	__vol32U *pEXTI_CR1 = ((__vol32U*) (SYSCFG_BASEADDRESS + 0x08));//OFFSET -> 0x08
	__vol32U *pEXTI_CR2 = ((__vol32U*) (SYSCFG_BASEADDRESS + 0x0C));//OFFSET -> 0x0C
	__vol32U *pEXTI_CR3 = ((__vol32U*) (SYSCFG_BASEADDRESS + 0x10));//OFFSET -> 0x10
	__vol32U *pEXTI_CR4 = ((__vol32U*) (SYSCFG_BASEADDRESS + 0x14));//OFFSET -> 0x14
	__vol32U *pCFGR = ((__vol32U*) (SYSCFG_BASEADDRESS + 0x18));//OFFSET -> 0x18
	__vol32U *pCCSR = ((__vol32U*) (SYSCFG_BASEADDRESS + 0x20));//OFFSET -> 0x20
	__vol32U *pCCVR = ((__vol32U*) (SYSCFG_BASEADDRESS + 0x24));//OFFSET -> 0x24
	__vol32U *pCCCR = ((__vol32U*) (SYSCFG_BASEADDRESS + 0x28));//OFFSET -> 0x28
	//..
	__vol32U *pPKGR = ((__vol32U*) (SYSCFG_BASEADDRESS + 0x124));//OFFSET -> 0x124
	//..
	__vol32U *pUR0 = ((__vol32U*) (SYSCFG_BASEADDRESS + 0x300));//OFFSET -> 0x300

	//PRIVATE FUNCTIONS//
	int getBitShift(int pinNum);
};

/**
 *  EXTI REGISTERS CONFIG
 */

#define EXTI_BASE_ADDR		0x58000000U

class EXTI {
public:
	//EXTI(__vol32U EXTI_BASE_ADDR);
	void setRTSR1(int pinNum);
	void setFTSR1(int pinNum);
	void setFT_RT1(int pinNum);

	void setCPUIMR1(int value);
	void setIMR(int pinNum, bool enable);

	void setGPIO_IRQ(int irqNumber, bool enable);

private:
	__vol32U *pEXTI_RTSR1 = ((__vol32U*) (EXTI_BASE_ADDR + 0x00U)); //OFFSET 0x00U
	__vol32U *pEXTI_FTSR1 = ((__vol32U*) (EXTI_BASE_ADDR + 0x04U));	//OFFSET 0x04U
	__vol32U *pEXTI_SWIER1 = ((__vol32U*) (EXTI_BASE_ADDR + 0x08U));//OFFSET 0x08U
	__vol32U *pEXTI_D3PMR1 = ((__vol32U*) (EXTI_BASE_ADDR + 0x0CU));//OFFSET 0x0CU
	__vol32U *pEXTI_D3PCR1L = ((__vol32U*) (EXTI_BASE_ADDR + 0x10U));//OFFSET 0x10U
	__vol32U *pEXTI_D3PCR1H = ((__vol32U*) (EXTI_BASE_ADDR + 0x14U));//OFFSET 0x14U

	__vol32U *pEXTI_RTSR2 = ((__vol32U*) (EXTI_BASE_ADDR + 0x20U));	//OFFSET 0x20U
	__vol32U *pEXTI_FTSR2 = ((__vol32U*) (EXTI_BASE_ADDR + 0x24U));	//OFFSET 0x24U
	__vol32U *pEXTI_SWIER2 = ((__vol32U*) (EXTI_BASE_ADDR + 0x28U));//OFFSET 0x28U
	__vol32U *pEXTI_D3PMR2 = ((__vol32U*) (EXTI_BASE_ADDR + 0x2CU));//OFFSET 0x2CU
	__vol32U *pEXTI_D3PCR2L = ((__vol32U*) (EXTI_BASE_ADDR + 0x30U));//OFFSET 0x30U
	__vol32U *pEXTI_D3PCR2H = ((__vol32U*) (EXTI_BASE_ADDR + 0x34U));//OFFSET 0x34U

	__vol32U *pEXTI_RTSR3 = ((__vol32U*) (EXTI_BASE_ADDR + 0x40U));	//OFFSET 0x40U
	__vol32U *pEXTI_FTSR3 = ((__vol32U*) (EXTI_BASE_ADDR + 0x44U));	//OFFSET 0x44U
	__vol32U *pEXTI_SWIER3 = ((__vol32U*) (EXTI_BASE_ADDR + 0x48U));//OFFSET 0x48U
	__vol32U *pEXTI_D3PMR3 = ((__vol32U*) (EXTI_BASE_ADDR + 0x4CU));//OFFSET 0x4CU
	__vol32U *pEXTI_D3PCR3L = ((__vol32U*) (EXTI_BASE_ADDR + 0x50U));//OFFSET 0x50U
	__vol32U *pEXTI_D3PCR3H = ((__vol32U*) (EXTI_BASE_ADDR + 0x54U));//OFFSET 0x54U

	__vol32U *pEXTI_CPUIMR1 = ((__vol32U*) (EXTI_BASE_ADDR + 0x80U));//OFFSET 0x80U
	__vol32U *pEXTI_CPUEMR1 = ((__vol32U*) (EXTI_BASE_ADDR + 0x84U));//OFFSET 0x84U
	__vol32U *pEXTI_CPUPR1 = ((__vol32U*) (EXTI_BASE_ADDR + 0x88U));//OFFSET 0x88U

	__vol32U *pEXTI_CPUIMR2 = ((__vol32U*) (EXTI_BASE_ADDR + 0x90U));//OFFSET 0x90U
	__vol32U *pEXTI_CPUEMR2 = ((__vol32U*) (EXTI_BASE_ADDR + 0x94U));//OFFSET 0x94U
	__vol32U *pEXTI_CPUPR2 = ((__vol32U*) (EXTI_BASE_ADDR + 0x98U));//OFFSET 0x98U

	__vol32U *pEXTI_CPUIMR3 = ((__vol32U*) (EXTI_BASE_ADDR + 0xA0U));//OFFSET 0xA0U
	__vol32U *pEXTI_CPUEMR3 = ((__vol32U*) (EXTI_BASE_ADDR + 0xA4U));//OFFSET 0xA4U
	__vol32U *pEXTI_CPUPR3 = ((__vol32U*) (EXTI_BASE_ADDR + 0xA8U));//OFFSET 0xA8U
};

/**
 * SUPPORT FUNCTIONS FOR SETTING 1 and 2 BITS REGISTERS
 */

void setOneBitRegister(__vol32U *registerToSet, int bitToSet,
		int valueToSet);
void setTwoBitsRegister(__vol32U *registerToSet, int bitToSet,
		int valueToSet);
void setFourBitsRegister(__vol32U *registerToSet, int leastBit,
		int binaryValue);
#endif /* STM32H743XX_H_ */
