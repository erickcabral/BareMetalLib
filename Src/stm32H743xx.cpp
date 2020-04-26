/*
 * stm32H743xx.cpp
 *
 *  Created on: 26 Mar 2020
 *      Author: Erick Cabral
 */

#include "stm32H743xx.h"

RCC::RCC(uint32_t rcc_baseAddress) {
	/* AHB4 SETUP */
	this->pAHB4RSTR = ((__int32U*) (rcc_baseAddress + 0x088));
	this->pAHB4ENR = ((__int32U*) (rcc_baseAddress + 0x0E0));
	this->pC1_AHB4ENR = ((__int32U*) (rcc_baseAddress + 0x140)); //= (RCC_BASEADDRES + 0x140);	//OFFSET -> 0x140
	this->pC1_AHB4LPENR = ((__int32U*) (rcc_baseAddress + 0x168)); // = (RCC_BASEADDRES + 0x168);	//OFFSET -> 0x168

	/* APB4 SETUP */
	this->pAPB4RSTR = ((__int32U*) (rcc_baseAddress + 0x09C)); //OFFSET -> 0x09C
	this->pAPB4ENR = ((__int32U*) (rcc_baseAddress + 0x0F4)); //OFFSET -> 0x0F4
	this->pC1_APB4ENR = ((__int32U*) (rcc_baseAddress + 0x154)); //OFFSET -> 0x154
}
void RCC::setAHB4ENR(__int32U value) {
	*(this->pAHB4ENR) = value;
}

/*
 void RCC::setAPB4ENR(int configToEnable) {
 unsigned long int current = *(this->pAPB4ENR);
 *(this->pAPB4ENR) = (current |= (1<<configToEnable));
 }
 */
void RCC::enableSYSCFG(bool enable) {
	if (enable) {
		*(this->pAPB4ENR) |= (1 << SYSCFG_ENABLE);
	} else {
		*(this->pAPB4ENR) &= ~(1 << SYSCFG_ENABLE);
	}
}

void RCC::setGPIOxEnable(int gpioBit, bool enable) {
	if (enable) {
		switch (gpioBit) {
		case GPIOA:
		case GPIOB:
		case GPIOC:
		case GPIOD:
		case GPIOE:
		case GPIOF:
		case GPIOG:
		case GPIOH:
		case GPIOI:
		case GPIOJ:
		case GPIOK:
			setOneBitRegister(this->pAHB4ENR, gpioBit, enable);
		}
	}
}
/*
 void RCC::setSYSCONFIG() {
 *(this->pAPB4ENR) = APB4_SYSCFG_ENABLE;
 }
 */
/* GPIO SETUP */
GPIOx::GPIOx(uint32_t gpio_baseAddr) {
	this->pMODER = (__int32U*) (gpio_baseAddr + 0x00U);
	this->pOTYPER = (__int32U*) (gpio_baseAddr + 0x04U);
	this->pOSPEEDR = (__int32U*) (gpio_baseAddr + 0x08U);
	this->pPUPDR = (__int32U*) (gpio_baseAddr + 0x0CU);
	this->pIDR = (__int32U*) (gpio_baseAddr + 0x10U);
	this->pODR = (__int32U*) (gpio_baseAddr + 0x14U);
	this->pBSRR = (__int32U*) (gpio_baseAddr + 0x18U);
	this->pLCKR = (__int32U*) (gpio_baseAddr + 0x1CU);
	this->pAFRL = (__int32U*) (gpio_baseAddr + 0x20U);
	this->pAFRH = (__int32U*) (gpio_baseAddr + 0x24U);
}

void GPIOx::setPinMode(int pinNum, int pinMode) {
	int leastBit = 2 * pinNum;
	setTwoBitsRegister(this->pMODER, leastBit, pinMode);
}
void GPIOx::setPinType(int pinNum, int pinType) {
	// 1 Bits Register
	setOneBitRegister(this->pOTYPER, pinNum, pinType);
}
void GPIOx::setPinSpeed(int pinNum, int pinSpeed) {
	// 2 Bits Register
	int leastBit = 2 * pinNum;
	setTwoBitsRegister(this->pOSPEEDR, leastBit, pinSpeed);
}
void GPIOx::setPinPUPD(uint8_t pinNum, uint8_t pinPUPD) {
	// 2 Bits Register
	int leastBit = 2 * pinNum;
	setTwoBitsRegister(this->pPUPDR, leastBit, pinPUPD);
}

int GPIOx::getPinIDR(int pinNum) {
	// 1 Bit Register
	int pinState = (*(this->pIDR) >> pinNum);
	//TODO....
	return pinState;
}

void GPIOx::setPinODR(int pinNum, int pinODR) {
	// 1 Bit Register
	setOneBitRegister(this->pODR, pinNum, pinODR);
}

/**
 *  SYSCFG API
 */
SYSCFG::SYSCFG() {
	/*
	 this->pPMCR = ((__int32U*) (SYSCFG_BASEADDRESS + 0x04));	//OFFSET -> 0x04
	 this->pEXTI_CR1 = ((__int32U*) (SYSCFG_BASEADDRESS + 0x08));//OFFSET -> 0x08
	 this->pEXTI_CR2 = ((__int32U*) (SYSCFG_BASEADDRESS + 0x0C));//OFFSET -> 0x0C
	 this->pEXTI_CR3 = ((__int32U*) (SYSCFG_BASEADDRESS + 0x10));//OFFSET -> 0x10
	 this->pEXTI_CR4 = ((__int32U*) (SYSCFG_BASEADDRESS + 0x14));//OFFSET -> 0x14
	 this->pCFGR = ((__int32U*) (SYSCFG_BASEADDRESS + 0x18));	//OFFSET -> 0x18
	 //..
	 this->pCCSR = ((__int32U*) (SYSCFG_BASEADDRESS + 0x20));	//OFFSET -> 0x20
	 this->pCCVR = ((__int32U*) (SYSCFG_BASEADDRESS + 0x24));	//OFFSET -> 0x24
	 this->pCCCR = ((__int32U*) (SYSCFG_BASEADDRESS + 0x28));	//OFFSET -> 0x28
	 //..
	 this->pPKGR = ((__int32U*) (SYSCFG_BASEADDRESS + 0x124));//OFFSET -> 0x124
	 //..
	 this->pUR0 = ((__int32U*) (SYSCFG_BASEADDRESS + 0x300));//OFFSET -> 0x300
	 //..
	 */
	/*
	 if (enable) {
	 *(this->pPMCR) = SYSCFG_RESET_VALUE;
	 *(this->pEXTI_CR1) = SYSCFG_RESET_VALUE;
	 *(this->pEXTI_CR2) = SYSCFG_RESET_VALUE;
	 *(this->pEXTI_CR3) = SYSCFG_RESET_VALUE;
	 *(this->pEXTI_CR4) = SYSCFG_RESET_VALUE;
	 *(this->pCFGR) = SYSCFG_RESET_VALUE;
	 //..
	 *(this->pCCSR) = SYSCFG_RESET_VALUE;
	 *(this->pCCVR) = SYSCFG_RESET_VALUE;
	 *(this->pCCCR) = SYSCFG_RESET_VALUE;
	 //..
	 *(this->pPKGR) = SYSCFG_RESET_VALUE;
	 //..
	 *(this->pUR0) = SYSCFG_RESET_VALUE;
	 }
	 */
}
void SYSCFG::setPMCR() {

}

/**
 *  CONFIG API FOR EXTI_CRx REGISTERS
 *  pinNum = GPIOx Pin Number -> select the less significant Bit to set the portX value
 *  portX = Port_x value to set on EXTI_CRx Register (4bits) -> PORT_A = 0000 ... PORT_K = 1010
 */
void SYSCFG::setEXTI_CR(int pinNum, int portX) {
	/*SELECTING EXTI_CR[x] FOR SETUP */
	int leastBit = 0;
	if (pinNum <= 3) {
		leastBit = pinNum * 4;
		setFourBitsRegister(this->pEXTI_CR1, leastBit, portX);
	} else if (pinNum > 3 && pinNum <= 7) {
		leastBit = (pinNum % 4) * 4;
		setFourBitsRegister(this->pEXTI_CR2, leastBit, portX);
	} else if (pinNum > 7 && pinNum <= 11) {
		leastBit = (pinNum % 4) * 4;
		setFourBitsRegister(this->pEXTI_CR3, leastBit, portX);
	} else if (pinNum > 11 && pinNum <= 15) {
		leastBit = (pinNum % 4) * 4;
		setFourBitsRegister(this->pEXTI_CR4, leastBit, portX);
	}
}

int SYSCFG::getBitShift(int pinNum) {
	int bitPos = (int) (pinNum * 4);
	if (bitPos == 0) {
		return 0;
	} else if (bitPos == 1) {
		return 4;
	} else if (bitPos == 2) {
		return 8;
	} else {
		return 12;
	}
}

/**
 *  EXTI REGISTERS SETUP
 */

/*EXTI::EXTI(__int32U exti_baseaddr){

 this->pEXTI_RTSR1 = ((__int32U*)(exti_baseaddr + 0x00U)); 		//OFFSET 0x00U
 this->pEXTI_FTSR1 = ((__int32U*)(exti_baseaddr + 0x04U));		//OFFSET 0x04U
 this->pEXTI_SWIER1 = ((__int32U*)(exti_baseaddr + 0x08U));		//OFFSET 0x08U
 this->pEXTI_D3PMR1 = ((__int32U*)(exti_baseaddr + 0x0CU));		//OFFSET 0x0CU
 this->pEXTI_D3PCR1L = ((__int32U*)(exti_baseaddr + 0x10U));		//OFFSET 0x10U
 this->pEXTI_D3PCR1H = ((__int32U*)(exti_baseaddr + 0x14U));		//OFFSET 0x14U

 this->pEXTI_RTSR2 = ((__int32U*)(exti_baseaddr + 0x20U));		//OFFSET 0x20U
 this->pEXTI_FTSR2 = ((__int32U*)(exti_baseaddr + 0x24U));		//OFFSET 0x24U
 this->pEXTI_SWIER2 = ((__int32U*)(exti_baseaddr + 0x28U));		//OFFSET 0x28U
 this->pEXTI_D3PMR2 = ((__int32U*)(exti_baseaddr + 0x2CU));		//OFFSET 0x2CU
 this->pEXTI_D3PCR2L = ((__int32U*)(exti_baseaddr + 0x30U));		//OFFSET 0x30U
 this->pEXTI_D3PCR2H = ((__int32U*)(exti_baseaddr + 0x34U));		//OFFSET 0x34U

 this->pEXTI_RTSR3 = ((__int32U*)(exti_baseaddr + 0x40U));		//OFFSET 0x40U
 this->pEXTI_FTSR3 = ((__int32U*)(exti_baseaddr + 0x44U));		//OFFSET 0x44U
 this->pEXTI_SWIER3 = ((__int32U*)(exti_baseaddr + 0x48U));		//OFFSET 0x48U
 this->pEXTI_D3PMR3 = ((__int32U*)(exti_baseaddr + 0x4CU));		//OFFSET 0x4CU
 this->pEXTI_D3PCR3L = ((__int32U*)(exti_baseaddr + 0x50U));		//OFFSET 0x50U
 this->pEXTI_D3PCR3H = ((__int32U*)(exti_baseaddr + 0x54U));		//OFFSET 0x54U

 this->pEXTI_CPUIMR1 = ((__int32U*)(exti_baseaddr + 0x80U));		//OFFSET 0x80U
 this->pEXTI_CPUEMR1 = ((__int32U*)(exti_baseaddr + 0x84U));		//OFFSET 0x84U
 this->pEXTI_CPUPR1 = ((__int32U*)(exti_baseaddr + 0x88U));		//OFFSET 0x88U

 this->pEXTI_CPUIMR2 = ((__int32U*)(exti_baseaddr + 0x90U));		//OFFSET 0x90U
 this->pEXTI_CPUEMR2 = ((__int32U*)(exti_baseaddr + 0x94U));		//OFFSET 0x94U
 this->pEXTI_CPUPR2 = ((__int32U*)(exti_baseaddr + 0x98U));		//OFFSET 0x98U

 this->pEXTI_CPUIMR3 = ((__int32U*)(exti_baseaddr + 0xA0U));		//OFFSET 0xA0U
 this->pEXTI_CPUEMR3 = ((__int32U*)(exti_baseaddr + 0xA4U));		//OFFSET 0xA4U
 this->pEXTI_CPUPR3 = ((__int32U*)(exti_baseaddr + 0xA8U));		//OFFSET 0xA8U
 }
 */
void EXTI::setRTSR1(int pinNum) {
	*(this->pEXTI_FTSR1) &= ~(1 << pinNum); //RESET FTSR1
	*(this->pEXTI_RTSR1) |= (1 << pinNum);
}
void EXTI::setFTSR1(int pinNum) {
	*(this->pEXTI_RTSR1) &= ~(1 << pinNum); //RESET RTSR1
	*(this->pEXTI_FTSR1) |= (1 << pinNum);
}
void EXTI::setFT_RT1(int pinNum) {
	*(this->pEXTI_FTSR1) |= (1 << pinNum);
	*(this->pEXTI_RTSR1) |= (1 << pinNum);
}

void EXTI::setIMR(int irqNumber, bool enable) {
	int irqBitPosition = irqNumber % 32;
	if (irqNumber >= 0 && irqNumber < 32) { // FIRST 32 BITS
		setOneBitRegister(this->pEXTI_CPUIMR1, irqBitPosition, enable);
		setOneBitRegister(this->pEXTI_CPUEMR1, irqBitPosition, enable);
	} else if (irqNumber >= 32 && irqNumber < (32 * 2) && (irqNumber != 45)) { // SECOND 32 BITS
		setOneBitRegister(this->pEXTI_CPUIMR2, irqBitPosition, enable);
	} else if (irqNumber >= 64 && irqNumber < (32 * 3)) { // THIRD 32 BITS
		setOneBitRegister(this->pEXTI_CPUIMR3, irqBitPosition, enable);
	}
}

void EXTI::setPR(bool enable, uint8_t bitPos) {
	if (enable) {
		*(this->pEXTI_CPUPR1) |= (1 << bitPos);
	} else {
		*(this->pEXTI_CPUPR1) &= ~(1 << bitPos);
	}
}
uint32_t EXTI::getPR(uint8_t value) {
	return *(this->pEXTI_CPUPR1);
}

/**
 *  SYSTEM STATIC FUNCTIONS
 */

void setGPIO_IRQ(int irqNumber, bool enable) {
	int iserX = (int) (irqNumber / 32); //SELECT ISER[x] Register
	int bitShifter = iserX == 0 ? irqNumber : (irqNumber % (32 * iserX)); //SHIFT TO THE ISERx REGISTER IRQ BIT
	if (enable) {
		switch (iserX) {
		case 0:
			*NVIC_ISER0 |= (1 << bitShifter);
			break;
		case 1:
			*NVIC_ISER1 |= (1 << bitShifter);
			break;
		case 2:
			*NVIC_ISER2 |= (1 << bitShifter);
			break;
		case 3:
			*NVIC_ISER3 |= (1 << bitShifter);
			break;
		case 4:
			*NVIC_ISER4 |= (1 << bitShifter);
			break;
		case 5:
			*NVIC_ISER5 |= (1 << bitShifter);
			break;
		case 6:
			*NVIC_ISER6 |= (1 << bitShifter);
			break;
		case 7:
			*NVIC_ISER7 |= (1 << bitShifter);
			break;
		}
	} else {
		switch (iserX) {
		case 0:
			*NVIC_ICER0 |= (1 << bitShifter);
			break;
		case 1:
			*NVIC_ICER1 |= (1 << bitShifter);
			break;
		case 2:
			*NVIC_ICER2 |= (1 << bitShifter);
			break;
		case 3:
			*NVIC_ICER3 |= (1 << bitShifter);
			break;
		case 4:
			*NVIC_ICER4 |= (1 << bitShifter);
			break;
		case 5:
			*NVIC_ICER5 |= (1 << bitShifter);
			break;
		case 6:
			*NVIC_ICER6 |= (1 << bitShifter);
			break;
		case 7:
			*NVIC_ICER7 |= (1 << bitShifter);
			break;
		}
	}
}

void setIRQ_PRIORITY(uint8_t irqNumber, uint16_t priority) {
	uint8_t irqPlace = irqNumber / 4;
	uint8_t irqLeastBit = (irqNumber % 4) * 8;
	uint8_t validSettingBits = (irqLeastBit + 4);
	uint32_t *NVIC_PRIx = ((uint32_t*) (NVIC_PRI0 + irqPlace));

	uint32_t value = *NVIC_PRIx;
	value |= (priority << validSettingBits);
	*NVIC_PRIx |= (priority << validSettingBits);
}

void setNVIC_PendingBit(int irqNumber, bool enable) {
	uint8_t isprX = (irqNumber / 32);
	uint8_t bitShift = isprX == 0 ? irqNumber : (irqNumber % (32 * isprX));
	uint32_t *NVIC_ISPRx = ((uint32_t*) (NVIC_ISPR0 + isprX));
	*NVIC_ISPRx |= (1 << bitShift);
}

void resetEXTIPendingRegister(uint8_t pinNumber, EXTI extiCFG) {
	if (extiCFG.getPR(1) & (1 << pinNumber)) {
		extiCFG.setPR(DISABLE, pinNumber);
	}
}
void setEXTIPendingRegister(uint8_t pinNumber, EXTI extiCFG) {
	extiCFG.setPR(ENABLE, pinNumber);
}

/**
 * SUPPORT FUNCTION
 */

void setOneBitRegister(__vol32U *registerToSet, int leastBit, int valueToSet) {
	*registerToSet &= ~(1 << (leastBit));  //RESET BIT BEFORE SET
	*registerToSet |= (valueToSet << (leastBit));
}
void setTwoBitsRegister(__vol32U *registerToSet, int leastBit, int valueToSet) {
	*registerToSet &= ~(1 << (leastBit + 1) | 1 << leastBit); //RESET BIT BEFORE SET
	*registerToSet |= (valueToSet << leastBit);
}

void setFourBitsRegister(__vol32U *registerToSet, int leastBit,
		int valueToSet) {
	*registerToSet &= ~(1 << (leastBit + 3) | 1 << (leastBit + 2)
			| 1 << (leastBit + 1) | 1 << (leastBit));  //RESET BIT BEFORE SET
	*registerToSet |= (valueToSet << leastBit);
}
