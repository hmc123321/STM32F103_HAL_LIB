/*
 * iic.h
 *
 *  Created on: Oct 23, 2019
 *      Author: 23950
 */

#ifndef IIC_H_
#define IIC_H_
#include "stm32f1xx_hal.h"

#define GPIO_PORT_I2C	SCL_GPIO_Port		     // GPIO端口
#define I2C_SCL_PIN		SCL_Pin			 // 连接到SCL时钟线的GPIO
#define I2C_SDA_PIN		SDA_Pin			 // 连接到SDA数据线的GPIO

/* 定义读写SCL和SDA的宏 */
#define I2C_SCL_1()  GPIO_PORT_I2C->BSRR = I2C_SCL_PIN											// SCL = 1
#define I2C_SCL_0()  GPIO_PORT_I2C->BSRR = (uint32_t)I2C_SCL_PIN << 16U  		// SCL = 0

#define I2C_SDA_1()  GPIO_PORT_I2C->BSRR = I2C_SDA_PIN   										// SDA = 1
#define I2C_SDA_0()  GPIO_PORT_I2C->BSRR = (uint32_t)I2C_SDA_PIN << 16U  		// SDA = 0

#define I2C_SDA_READ()  (GPIO_PORT_I2C->IDR & I2C_SDA_PIN)										// 读SDA口线状态
#define I2C_SCL_READ()  (GPIO_PORT_I2C->IDR & I2C_SCL_PIN)									// 读SCL口线状态

void i2c_Delay(void);
void start();
void endMod();
void ack();
uint8_t wait_ack();
void write_byte(uint8_t data_in);
uint8_t read_byte();
#endif /* IIC_H_ */
