/*
 * stm32H743xx.cpp
 *
 *  Created on: 26 Mar 2020
 *      Author: Erick Cabral
 */

#include "stm32H743xx.h"

RCC::RCC(uint32_t rcc_baseAddress) {
	this->pAHB4RSTR = ((uint32_t*) (rcc_baseAddress + 0x088));
	this->pAHB4ENR = ((uint32_t*) (rcc_baseAddress + 0x0E0));
}
void RCC::setAHB4ENR(uint32_t hexNumber) {
	*(this->pAHB4ENR) = hexNumber;
}
void RCC::setGPIOxEnable(uint8_t gpioBit, bool enable){
	if(enable){
		switch(gpioBit){
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

/* GPIO SETUP */
GPIOx::GPIOx(uint32_t gpio_baseAddr) {
	this->pMODER = ((uint32_t*) (gpio_baseAddr + 0x00U));
	this->pOTYPER = (uint32_t*) (gpio_baseAddr + 0x04U);
	this->pOSPEEDR = (uint32_t*) (gpio_baseAddr + 0x08U);
	this->pPUPDR = (uint32_t*) (gpio_baseAddr + 0x0CU);
	this->pIDR = (uint32_t*) (gpio_baseAddr + 0x10U);
	this->pODR = (uint32_t*) (gpio_baseAddr + 0x14U);
	this->pBSRR = (uint32_t*) (gpio_baseAddr + 0x18U);
	this->pLCKR = (uint32_t*) (gpio_baseAddr + 0x1CU);
	this->pAFRL = (uint32_t*) (gpio_baseAddr + 0x20U);
	this->pAFRH = (uint32_t*) (gpio_baseAddr + 0x24U);
}

void GPIOx::setPinMode(uint8_t pinNum, uint8_t pinMode) {
	setTwoBitsRegister(this->pMODER, pinNum, pinMode);
}
void GPIOx::setPinType(uint8_t pinNum, uint8_t pinType) {
	// 2 Bits Register
	setTwoBitsRegister(this->pOTYPER, pinNum, pinType);
}
void GPIOx::setPinSpeed(uint8_t pinNum, uint8_t pinSpeed) {
	// 2 Bits Register
	setTwoBitsRegister(this->pOSPEEDR, pinNum, pinSpeed);
}
void GPIOx::setPinPUPD(uint8_t pinNum, uint8_t pinPUPD) {
	// 2 Bits Register
	setTwoBitsRegister(this->pPUPDR, pinNum, pinPUPD);
}

uint8_t GPIOx::getPinIDR(uint8_t pinNum) {
	// 1 Bit Register
	//TODO:....
}

void GPIOx::setPinODR(uint8_t pinNum, uint8_t pinODR) {
	// 1 Bit Register
	setOneBitRegister(this->pODR, pinNum, pinODR);
}

// SUPPORT FUNCTION //

void setTwoBitsRegister(uint32_t *registerToSet, uint8_t bitToSet,
		uint8_t valueToSet) {
	uint32_t bit1 = 0;
	switch (valueToSet) {
	case 0:
		*registerToSet &= ~(1 << (2 * bitToSet + 1) | 1 << (2 * bitToSet));
		bit1 |= (0 << (2 * bitToSet + 1) | 0 << (2 * bitToSet));
		break;
	case 1:
		*registerToSet &= ~(1 << (2 * bitToSet + 1) | 1 << (2 * bitToSet));
		bit1 |= (0 << (2 * bitToSet + 1) | 1 << (2 * bitToSet));
		break;
	case 2:
		*registerToSet &= ~(1 << (2 * bitToSet + 1) | 1 << (2 * bitToSet));
		bit1 |= (1 << (2 * bitToSet + 1) | 0 << (2 * bitToSet));
		break;
	case 3:
		*registerToSet &= ~(1 << (2 * bitToSet + 1) | 1 << (2 * bitToSet));
		bit1 |= (1 << (2 * bitToSet + 1) | 1 << (2 * bitToSet));
		break;
	}
	*registerToSet |= bit1;
}

void setOneBitRegister(volatile uint32_t *registerToSet, uint8_t bitToSet,
		uint8_t valueToSet) {
	uint32_t bit1 = 0;
	*registerToSet &= ~(1 << (bitToSet));
	bit1 |= (valueToSet << (bitToSet));
	*registerToSet |= bit1;
}
