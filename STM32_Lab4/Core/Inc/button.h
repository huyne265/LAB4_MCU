/*
 * button.h
 *
 *  Created on: Oct 24, 2024
 *      Author: ADMIN
 */

#ifndef INC_BUTTON_H_
#define INC_BUTTON_H_

#include "main.h"

#define NORMAL_STATE GPIO_PIN_SET
#define PRESSED_STATE GPIO_PIN_RESET

void setButton();
int isButtonPressed();
int isButtonLongPressed();
void getKeyInput();
void subKeyProcess( );


#endif /* INC_BUTTON_H_ */
