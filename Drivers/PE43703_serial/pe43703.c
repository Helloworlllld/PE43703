/**
 * @file    pe43703.c
 * @author  HelloworldGu
 * @brief   encode UTF-8
 * @brief   pe43703程控衰减器驱动
 * @version 0.1
 * @date    2024-04-25
 *
 *
 */

#include "pe43703.h"

/**
 * @brief 延时函数
 * @param nus 延时时间
 * @note 测试主频为480MHz时可用，可自行调整
 */
void delay_n(uint32_t nus)
{
    uint32_t i;
    for (i = 0; i < nus; i++)
        __nop();    //空操作,避免编译器优化
}

/**
 * @brief 设置PE43703为串行控制
 * @param db 衰减值,范围0-127,实际衰减值=db/4
 * @return HAL_StatusTypeDef HAL_OK:成功 HAL_ERROR:失败(衰减值超出范围)
 */
HAL_StatusTypeDef PE43703_set_serial(uint8_t db)
{
    if(db > 127){
        return HAL_ERROR;
    }
    HAL_GPIO_WritePin(PE_PS_GPIO_Port, PE_PS_Pin, GPIO_PIN_SET);
    for (uint8_t i = 0; i < 8; i++)
    {
        delay_n(50);
        HAL_GPIO_WritePin(PE_DATA_GPIO_Port, PE_DATA_Pin, (GPIO_PinState)((db >> i) & 0x01));
        delay_n(50);
        HAL_GPIO_WritePin(PE_CLK_GPIO_Port, PE_CLK_Pin, GPIO_PIN_SET);
        delay_n(50);
        HAL_GPIO_WritePin(PE_CLK_GPIO_Port, PE_CLK_Pin, GPIO_PIN_RESET);
    }
    for(uint8_t i = 0; i < 8; i++){
        delay_n(50);
        HAL_GPIO_WritePin(PE_DATA_GPIO_Port, PE_DATA_Pin, (GPIO_PinState)((PE_ADDR >> i) & 0x01));
        delay_n(50);
        HAL_GPIO_WritePin(PE_CLK_GPIO_Port, PE_CLK_Pin, GPIO_PIN_SET);
        delay_n(50);
        HAL_GPIO_WritePin(PE_CLK_GPIO_Port, PE_CLK_Pin, GPIO_PIN_RESET);
    }
    delay_n(50);
    HAL_GPIO_WritePin(PE_LE_GPIO_Port, PE_LE_Pin, GPIO_PIN_SET);
    delay_n(50);
    HAL_GPIO_WritePin(PE_LE_GPIO_Port, PE_LE_Pin, GPIO_PIN_RESET);
    return HAL_OK;
}

/**
 * @brief 设置PE43703为并行控制
 * @param void
 */
void PE43703_set_parallel(void){
    HAL_GPIO_WritePin(PE_PS_GPIO_Port, PE_PS_Pin, GPIO_PIN_RESET);
    delay_n(100);
    HAL_GPIO_WritePin(PE_LE_GPIO_Port, PE_LE_Pin, GPIO_PIN_SET);
}
