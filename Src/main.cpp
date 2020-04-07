/*
 * main.cpp
 *
 *  Created on: 26 Mar 2020
 *      Author: Erick Cabral
 */

#include "stm32H743xx.h"

EXTI extiCFG;

int main(void) {

	RCC rcc = RCC(RCC_BASEADDRESS);
	rcc.enableSYSCFG(true);
	rcc.setGPIOxEnable(GPIOB, ENABLE);
	rcc.setGPIOxEnable(GPIOC, ENABLE);
/*
	extiCFG = EXTI();
	extiCFG.setFTSR1(PIN_13);
	extiCFG.setIMR(PIN_13, true);

	SYSCFG sysCFG = SYSCFG();
	sysCFG.setEXTI_CR(PIN_13, GPIOC); //USER BUTTON
*/
	GPIOx gpioB = GPIOx(GPIOB_BASEADDRESS);
	gpioB.setPinMode(PIN_7, MODE_OUTPUT);
	gpioB.setPinType(PIN_7, TYPE_PUSHPULL);
	gpioB.setPinSpeed(PIN_7, SPD_MID);
	gpioB.setPinPUPD(PIN_7, PUPD_PULL_UP);

	GPIOx gpioC = GPIOx(GPIOC_BASEADDRESS);
	gpioC.setPinMode(PIN_13, MODE_INPUT);
	gpioC.setPinType(PIN_13, TYPE_PUSHPULL);
	gpioC.setPinPUPD(PIN_13, PUPD_PULL_DOWN);

	setGPIO_IRQ(40, true);
	setIRQ_PRIORITY(40, 10);

	while (1) {
		if (gpioC.getPinIDR(PIN_13)) {
			gpioB.setPinODR(PIN_7, HIGH);
		} else {
			gpioB.setPinODR(PIN_7, LOW);
		}
	}
}

void EXTI15_10_IRQHandler(void) {

	resetPendingRegister(PIN_13, extiCFG);
	bool test = true;
	GPIOx gpioB = GPIOx(GPIOB_BASEADDRESS);
	gpioB.setPinMode(PIN_7, MODE_OUTPUT);
	gpioB.setPinType(PIN_7, TYPE_PUSHPULL);
	gpioB.setPinSpeed(PIN_7, SPD_MID);
	gpioB.setPinPUPD(PIN_7, PUPD_PULL_UP);

}

