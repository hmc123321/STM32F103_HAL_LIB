/*
 * iic.c
 *
 *  Created on: Oct 23, 2019
 *      Author: 23950
 */
#include "iic.h"
#include "main.h"

void i2c_Delay(void)
{
//	uint8_t i;
//	for (i = 0; i <1; i++);
}

/*
void start (){
	I2C_SDA_1();
	//i2c_Delay();
	I2C_SCL_1();
	//i2c_Delay();
	I2C_SDA_1();
	//i2c_Delay();
	I2C_SCL_0();
}
void endMod (){
	I2C_SCL_0();
	//i2c_Delay();
	I2C_SDA_1();
	//i2c_Delay();
	I2C_SCL_1();
	//i2c_Delay();
	I2C_SDA_1();
	//i2c_Delay();
}
void yack(){
	 I2C_SCL_0();
	 //i2c_Delay();
	 I2C_SDA_1();
	// i2c_Delay();
	 I2C_SCL_1();
	 //i2c_Delay();
	 I2C_SCL_0();
}
void nack(){
	 I2C_SCL_0();
	 //i2c_Delay();
	 I2C_SDA_1();
	// i2c_Delay();
	 I2C_SCL_1();
	// i2c_Delay();
	 I2C_SCL_0();
}
uint8_t  wait_ack(){//0 is Acked,1 is not acked;
	int x;
	I2C_SCL_0();
	I2C_SDA_1();
	//i2c_Delay();
	I2C_SCL_1();
	i2c_Delay();
	while(I2C_SDA_READ())
	{
		x++;
		if(x>250)
		{
			endMod();
			return 1;
		}
	}
	I2C_SCL_0();
	return 0;
}
void write_byte(uint8_t data_in){
	uint8_t i;
	I2C_SCL_0();
	for (i=0;i<8;i++)
	{
		I2C_SCL_0();
		if(data_in&0x80)
		I2C_SDA_1();
		else I2C_SDA_1();
		data_in<<=1;
		I2C_SCL_1();
		i2c_Delay();
		I2C_SCL_0();
		//i2c_Delay();
	}
}
uint8_t READ_byte(uint8_t ack)//1 ack;0 not ack;
{
	uint8_t x=0,i;
	I2C_SCL_0();
	for (i=0;i<8;i++)
	{
		I2C_SCL_0();
		i2c_Delay();
		I2C_SCL_1();
		x<<=1;
		if(I2C_SDA_READ()) x++;
		//i2c_Delay();
	}
	if (!ack)
		nack();
	else
	    yack();
	I2C_SCL_0();
	return x;
}
*/

void start(void)
{
	// 当SCL高电平时，SDA出现一个下跳沿表示I2C总线启动信号
	I2C_SDA_1();
	I2C_SCL_1();
	//i2c_Delay();
	I2C_SDA_0();
	//i2c_Delay();
	I2C_SCL_0();
	//i2c_Delay();
}

//停止信号
void endMod(void)
{
	// 当SCL高电平时，SDA出现一个上跳沿表示I2C总线停止信号
	I2C_SDA_0();
	I2C_SCL_1();
	//i2c_Delay();
	I2C_SDA_1();
	//i2c_Delay();
}
//发送一个字节
void write_byte(uint8_t _ucByte)
{
	uint8_t i;

	// 先发送字节的高位bit7
	for (i = 0; i < 8; i++)
	{
		if (_ucByte & 0x80)
		{
			I2C_SDA_1();
		}
		else
		{
			I2C_SDA_0();
		}
		//i2c_Delay();
		I2C_SCL_1();
		//i2c_Delay();
		I2C_SCL_0();
		if (i == 7)
		{
			 I2C_SDA_1(); 	// 释放总线
		}
		_ucByte <<= 1;		// 左移一个bit
		//i2c_Delay();
	}
}
//读取一个字节
uint8_t read_byte(void)
{
	uint8_t i;
	uint8_t value;// 读到第1个bit为数据的bit7
	value = 0;
	for (i = 0; i < 8; i++)
	{
		value <<= 1;
		I2C_SCL_1();
		//i2c_Delay();
		if (I2C_SDA_READ())
		{
			value++;
		}
		I2C_SCL_0();
		//i2c_Delay();
	}
	return value;
}

//等待应答信号
uint8_t wait_ack(void)
{
	uint8_t re;

	I2C_SDA_1();	// CPU释放SDA总线
//	i2c_Delay();
	I2C_SCL_1();	//CPU驱动SCL = 1, 此时器件会返回ACK应答
	//i2c_Delay();

	if (I2C_SDA_READ())	// CPU读取SDA口线状态
	{
		re = 1;
	}
	else
	{
		re = 0;
	}

	I2C_SCL_0();
	//i2c_Delay();
	return re;
}
//应答信号
void ack(void)
{
	I2C_SDA_0();	//CPU驱动SDA = 0
	i2c_Delay();
	I2C_SCL_1();	// CPU产生1个时钟
	i2c_Delay();
	I2C_SCL_0();
	i2c_Delay();
	I2C_SDA_1();	// CPU释放SDA总线
}

