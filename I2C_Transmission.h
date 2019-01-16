#include "MKL46Z4.h"

#define I2C_READ 1 
#define I2C_WRITE 0

void I2C_Init(void);
void I2C_WriteByte(uint8_t data);
uint8_t I2C_ReadByte(void);
void I2C_Start(void);
void I2C_Stop(void);
void I2C_Wait(void);
void I2C_RepeatedStart(void);
void I2C_SendAck(void);
uint8_t I2C_GetAck(void);
void I2C_SetTXmode(void);
void I2C_SetRXmode(void);
void I2C_SendNack(void);
void I2C_WaitForAck(void);
void I2C_Write(uint8_t data);
void I2C_set_slave_mode(void);

void I2C_set_master_mode(void);
void i2c_give_nack(I2C_MemMapPtr p);
void i2c_give_ack(I2C_MemMapPtr p);
void i2c_repeated_start(I2C_MemMapPtr p);
void i2c_write_byte(I2C_MemMapPtr p, uint8_t data);
uint8_t i2c_read_byte(I2C_MemMapPtr p);
void i2c_start(I2C_MemMapPtr p);
void i2c_stop(I2C_MemMapPtr p);
void i2c_wait(I2C_MemMapPtr p);
_Bool i2c_get_ack(I2C_MemMapPtr p);
void hal_i2c0_init(I2C_MemMapPtr p);
void hal_i2c1_init(I2C_MemMapPtr p);
void hal_i2c0_deinit(I2C_MemMapPtr p);
void hal_i2c1_deinit(I2C_MemMapPtr p);