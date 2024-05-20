#include "stm32f10x.h"
#ifndef __SGP_H
#define __SGP_H

void SGP_WriteReg(uint8_t cmd1, uint8_t cmd2);
void SGP_WriteCrc(uint8_t cmd1, uint8_t cmd2, uint8_t cmd3, uint8_t cmd4, uint8_t cmd5, uint8_t cmd6);
uint8_t SGP_ReadReg(void);
uint8_t SGP_ReadData(void);
void SGP_GetData_Off(uint16_t *Data1, uint16_t *Data2, uint16_t *Data3);
uint8_t SGP_ReadCrc(void);
uint8_t SGP_ReadCrc_Off(void);
void SGP_GetData(uint16_t *Data1, uint16_t *Data2, uint16_t *Data3);	//接收2+1的数据
void SGP_Turn_Off(void);		//进入空闲模式
void SGP_Init(void);
void SGP_GetID(uint16_t *Data1, uint16_t *Data2, uint16_t *Data3,uint16_t *Data4, uint16_t *Data5, uint16_t *Data6);
void SGP_Execute_Conditoning(uint16_t *Data1, uint16_t *Data2);
void SGP_Measure_Raw_Signals(uint16_t *Data1, uint16_t *Data2, uint16_t *Data3,uint16_t *Data4);

#endif
