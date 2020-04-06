/*
 * main.cpp
 *
 *  Created on: 26 Mar 2020
 *      Author: Erick Cabral
 */

#include "stm32H743xx.h"

int main(void) {

	RCC rcc = RCC(RCC_BASEADDRESS);

	EXTI extiCFG = EXTI();


	extiCFG.setFTSR1(PIN_13);
	//extiCFG.setIMR(PIN_13, true);

	SYSCFG sysCFG = SYSCFG();
	sysCFG.setEXTI_CR(13, SYSCFG_PORT_C); //USER BUTTON

	extiCFG.setGPIO_IRQ(40, true);

	rcc.setAPB4ENR(APB4_SYSCFG_ENABLE);


	rcc.setGPIOxEnable(GPIOB, ENABLE);
	GPIOx gpioB = GPIOx(GPIOB_BASEADDRESS);
	gpioB.setPinMode(PIN_7, MODE_OUTPUT);
	gpioB.setPinType(PIN_7, TYPE_PUSHPULL);
	gpioB.setPinSpeed(PIN_7, SPD_MID);
	gpioB.setPinPUPD(PIN_7, PUPD_PULL_UP);

	gpioB.setPinODR(PIN_7, HIGH);

	while (1) {

	}
}

