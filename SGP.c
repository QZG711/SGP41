#include "stm32f10x.h"  
#include "OLED.h"
#include "IIC.h"  
#include "Delay.h"
#include "SGP.h"

#define SGP_W_ADDRESS		(0x59 << 1)
#define SGP_R_ADDRESS		((0x59 << 1) | 0x01)

void SGP_WriteReg(uint8_t cmd1, uint8_t cmd2)
{
	MyI2C_Start();
	MyI2C_SendByte(SGP_W_ADDRESS);
	MyI2C_ReceiveAck();
	MyI2C_SendByte(cmd1);
	MyI2C_ReceiveAck();
	MyI2C_SendByte(cmd2);
	MyI2C_ReceiveAck();
}

void SGP_WriteCrc(uint8_t cmd1, uint8_t cmd2, uint8_t cmd3, uint8_t cmd4, uint8_t cmd5, uint8_t cmd6)
{
	MyI2C_SendByte(cmd1);
	MyI2C_ReceiveAck();
	MyI2C_SendByte(cmd2);
	MyI2C_ReceiveAck();
	MyI2C_SendByte(cmd3);
	MyI2C_ReceiveAck();
	MyI2C_SendByte(cmd4);
	MyI2C_ReceiveAck();
	MyI2C_SendByte(cmd5);
	MyI2C_ReceiveAck();
	MyI2C_SendByte(cmd6);
	MyI2C_ReceiveAck();
	MyI2C_Stop();
}

uint8_t SGP_ReadReg(void)
{
	uint8_t Data;

	MyI2C_Start();
	MyI2C_SendByte(SGP_R_ADDRESS);
	Data = MyI2C_ReceiveAck();
	
	return Data;
}

uint8_t SGP_ReadData(void)
{
	uint8_t Data;
	
	Data = MyI2C_ReceiveByte();
	MyI2C_SendAck(0);
	
	return Data;
}

uint8_t SGP_ReadCrc(void)
{
	uint8_t Data;
	
	Data = MyI2C_ReceiveByte();
	MyI2C_SendAck(0);
	
	return Data;
}

uint8_t SGP_ReadCrc_Off(void)
{
	uint8_t Data;
	
	Data = MyI2C_ReceiveByte();
	MyI2C_SendAck(1);
	
	return Data;
}

void SGP_GetData(uint16_t *Data1, uint16_t *Data2, uint16_t *Data3)		//接收2+1的数据段
{
	*Data1 = SGP_ReadData();
	*Data2 = SGP_ReadData();
	*Data3 = SGP_ReadCrc();
}

void SGP_GetData_Off(uint16_t *Data1, uint16_t *Data2, uint16_t *Data3)		//接收2+1的数据段
{
	*Data1 = SGP_ReadData();
	*Data2 = SGP_ReadData();
	*Data3 = SGP_ReadCrc_Off();
}

void SGP_Turn_Off(void)		//进入空闲模式
{
	SGP_WriteReg(0x36,0x15);
//	OLED_ShowString(4,1,"ready");
	MyI2C_Stop();
}

void SGP_Init(void)
{
	MyI2C_Init();
	SGP_Turn_Off();
}

void SGP_GetID(uint16_t *Data1, uint16_t *Data2, uint16_t *Data3,uint16_t *Data4, uint16_t *Data5, uint16_t *Data6)
{	
	uint8_t AckBit;
	uint16_t Crc[3];
	
	SGP_WriteReg(0x36,0x82);

	AckBit = SGP_ReadReg();
	if(AckBit)
	{	
	OLED_ShowString(4,1,"error");
	}
	else
	{
		SGP_GetData(Data1, Data2, &Crc[0]);
		SGP_GetData(Data3, Data4, &Crc[1]);
		SGP_GetData(Data5, Data6, &Crc[2]);
		MyI2C_Stop();
	}
}

void SGP_Execute_Conditoning(uint16_t *Data1, uint16_t *Data2)
{
	uint8_t AckBit;
	uint16_t Crc[1];
	
	SGP_WriteReg(0x26, 0x12);
	SGP_WriteCrc(0x80, 0x00, 0xA2, 0x66, 0x66, 0x93);
	Delay_ms(60);
	
	AckBit = SGP_ReadReg();
	if(AckBit)
	{	
	OLED_ShowString(4,1,"error");
	}
	else
	{
		SGP_GetData_Off(Data1, Data2, &Crc[0]);
		MyI2C_Stop();
	}
}

void SGP_Measure_Raw_Signals(uint16_t *Data1, uint16_t *Data2, uint16_t *Data3,uint16_t *Data4)
{
	uint8_t AckBit;
	uint16_t Crc[2];
	
	SGP_WriteReg(0x26, 0x19);
	SGP_WriteCrc(0x80, 0x00, 0xA2, 0x66, 0x66, 0x93);
	Delay_ms(60);
	
	AckBit = SGP_ReadReg();
	if(AckBit)
	{	
	OLED_ShowString(4,1,"error");
	}
	else
	{
		SGP_GetData(Data1, Data2, &Crc[0]);
		SGP_GetData_Off(Data3, Data4, &Crc[1]);
		MyI2C_Stop();
	}
}
