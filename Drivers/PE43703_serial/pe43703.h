#ifndef _PE43703_H
#define _PE43703_H

#define PE_ADDR ((uint8_t)0b001) // 地址A0=1,A1=0,A2=0

#include "main.h"

void delay_n(uint32_t nus);
HAL_StatusTypeDef PE43703_set_serial(uint8_t db);
void PE43703_set_parallel(void);

#endif // !_PE43703_H
