/*p
 * stm32H743xx.h
 *
 *  Created on: 26 Mar 2020
 *      Author: Erick Cabral
 */

#ifndef STM32H743XX_H_
#define STM32H743XX_H_

#include <cstdint>

using namespace std;

/* CUSTOIM STM32H743 DRIVER */

/*!< DEFAULT VARIABLES >*/
#define SET				1
#define RESET			0
#define ENABLE			SET
#define DISABLE			DISABLE
#define HIGH			SET
#define LOW				DISABLE

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

class RCC {

public:
	RCC(uint32_t rcc_baseAddress);
	/*setting full registers*/
	void setAHB4ENR(uint32_t portValue);

	/*set Single Register*/
	void setGPIOxEnable(uint8_t gpioBit, bool enable);
private:
	uint32_t *pAHB4RSTR; // = ((uint32_t*)(RCC_BASEADDRES + 0x088));		//OFFSET -> 0x088
	uint32_t *pAHB4ENR;		//OFFSET -> 0x0E0
	uint32_t *pC1_AHB4ENR; //= (RCC_BASEADDRES + 0x140);	//OFFSET -> 0x140
	uint32_t *pC1_AHB4LPENR; // = (RCC_BASEADDRES + 0x168);	//OFFSET -> 0x168

};

// PIN CONFIG //

/*
 *  PIN DEFAULT VALUES
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

class GPIOx {
public:
	GPIOx(uint32_t gpio_baseAddr);
	void setGPIOxEnable(uint8_t gpioBit, bool enable);

	//PIN CONFIG//
	void setPinMode(uint8_t pinNum, uint8_t pinMode); 	// 2 Bits Register
	void setPinType(uint8_t pinNum, uint8_t pinType);	// 2 Bits Register
	void setPinSpeed(uint8_t pinNum, uint8_t pinSpeed);	// 2 Bits Register
	void setPinPUPD(uint8_t pinNum, uint8_t pinPUPD);	// 2 Bits Register
	uint8_t getPinIDR(uint8_t pinNum);	// 1 Bit Register
	void setPinODR(uint8_t pinNum, uint8_t pinODR);	// 1 Bit Register
	void setPinBSRR(uint8_t pinNum, uint8_t pinBSRR);	// 2 Bits Register
	void setPinLCKR(uint8_t pinNum, uint8_t pinLCKR);	// 2 Bits Register
	void setPinAFRL(uint8_t pinNum, uint8_t pinAFRL);	// 2 Bits Register
	void setPinAFRH(uint8_t pinNum, uint8_t pinAFRH);	// 2 Bits Register

private:
	uint32_t *pMODER;			//OFFSET -> 0x00
	uint32_t *pOTYPER;			//OFFSET -> 0x04
	uint32_t *pOSPEEDR;			//OFFSET -> 0x08
	uint32_t *pPUPDR;			//OFFSET -> 0x0C
	uint32_t *pIDR;				//OFFSET -> 0x10
	uint32_t *pODR;				//OFFSET -> 0x14
	uint32_t *pBSRR;				//OFFSET -> 0x18
	uint32_t *pLCKR;				//OFFSET -> 0x1C
	uint32_t *pAFRL;				//OFFSET -> 0x20
	uint32_t *pAFRH;				//OFFSET -> 0x24

};

void setTwoBitsRegister(uint32_t *registerToSet, uint8_t bitToSet,
		uint8_t valueToSet);
void setOneBitRegister(volatile uint32_t *registerToSet, uint8_t bitToSet,
		uint8_t valueToSet);
#endif /* STM32H743XX_H_ */
