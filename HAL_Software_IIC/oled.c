/*
 * oled.c
 *
 *  Created on: Oct 23, 2019
 *      Author: 23950
 */
#include "oled.h"
#include "ASCII_8x16.h"
void oled_write_cmd(uint8_t cmd)
{
	start();
	write_byte(0x78);//write the device address
	wait_ack();
	write_byte(0x00);//write the command,co=0,c/d=0
	wait_ack();
	write_byte(cmd);
	wait_ack();
	endMod();
}
void oled_write_data(uint8_t data)
{
	start();
	write_byte(0x78);//write the device address
	wait_ack();
	write_byte(0x40);//write the data,co=0,c/d=1
	wait_ack();
	write_byte(data);
	wait_ack();
	endMod();
}
void oled_init(){
/* Init LCD */
oled_write_cmd(0xAE); //display off
oled_write_cmd(0x20); //Set Memory Addressing Mode
oled_write_cmd(0x10); //00,Horizontal Addressing Mode;01,Vertical Addressing Mode;10,Page Addressing Mode (RESET);11,Invalid
oled_write_cmd(0xB0); //Set Page Start Address for Page Addressing Mode,0-7
oled_write_cmd(0xC8); //Set COM Output Scan Direction
oled_write_cmd(0x00); //---set low column address
oled_write_cmd(0x10); //---set high column address
oled_write_cmd(0x40); //--set start line address
oled_write_cmd(0x81); //--set contrast control register
oled_write_cmd(0xFF);
oled_write_cmd(0xA1); //--set segment re-map 0 to 127
oled_write_cmd(0xA6); //--set normal display
oled_write_cmd(0xA8); //--set multiplex ratio(1 to 64)
oled_write_cmd(0x3F); //
oled_write_cmd(0xA4); //0xa4,Output follows RAM content;0xa5,Output ignores RAM content
oled_write_cmd(0xD3); //-set display offset
oled_write_cmd(0x00); //-not offset
oled_write_cmd(0xD5); //--set display clock divide ratio/oscillator frequency
oled_write_cmd(0xF0); //--set divide ratio
oled_write_cmd(0xD9); //--set pre-charge period
oled_write_cmd(0x22); //
oled_write_cmd(0xDA); //--set com pins hardware configuration
oled_write_cmd(0x12);
oled_write_cmd(0xDB); //--set vcomh
oled_write_cmd(0x20); //0x20,0.77xVcc
oled_write_cmd(0x8D); //--set DC-DC enable
oled_write_cmd(0x14); //
oled_write_cmd(0xAF);
}
void oled_clear(){
	int a,j;
	//oled_write_cmd(0x22);
	for(a=0;a<8;a++){
		oled_write_cmd (0xb0+a);
		oled_write_cmd (0x00);
		oled_write_cmd (0x10);
		for (j=0;j<128;j++){
		oled_write_data (0);
		}
	}
}
void oled_full(){
	int a,j;
	//oled_write_cmd(0x22);
	for(a=0;a<8;a++){
		oled_write_cmd (0xb0+a);
		oled_write_cmd (0x00);
		oled_write_cmd (0x10);
		for (j=0;j<128;j++){
		oled_write_data (0xff);
		}
	}
}

void  oled_print(uint8_t x,uint8_t y,char *str){
	int8_t i,j,k=strlen((const char *)str);
	oled_write_cmd (0x20);
	oled_write_cmd (0x10);

	oled_write_cmd (0xb0+y);
	oled_write_cmd (0x00+(x&0x0F));
	oled_write_cmd (0x10+(x>>4));

	for (i=0;i<k;i++){
		for (j=0;j<8;j++){
			oled_write_data (ascii_8x16[str[i]-0x20][j]);
		}
	}
	oled_write_cmd (0x00+(x&0x0F));
	oled_write_cmd (0x10+(x>>4));
	oled_write_cmd (0xb1+y);
	for (i=0;i<k;i++){
		for (j=8;j<16;j++){
			oled_write_data (ascii_8x16[str[i]-0x20][j]);
		}
	}
}
