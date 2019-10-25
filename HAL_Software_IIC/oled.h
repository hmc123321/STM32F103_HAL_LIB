/*
 * oled.h
 *
 *  Created on: Oct 23, 2019
 *      Author: 23950
 */
#include "iic.h"
#include "string.h"
#ifndef OLED_H_
#define OLED_H_


void oled_init();
void oled_write_data(uint8_t);
void oled_write_cmd(uint8_t);
void oled_clear();
void oled_full();
void oled_print(uint8_t x,uint8_t y,char *str);
#endif /* OLED_H_ */
