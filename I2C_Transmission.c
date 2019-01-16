#include "MKL46Z4.h"
#include "I2C_Transmission.h"

/**
@brief Function initializes I2C transmission.
@note  It's worth to say, that I2C-port must be defined as open-drain. 
@author Jakub Brzezowski
@version 1.0 2018-12-01
@param none
@retval none
*/
void I2C_Init(void)
{
   SIM->SCGC4 |= SIM_SCGC4_I2C0_MASK;
   SIM->SCGC5 |= SIM_SCGC5_PORTE_MASK;
	
	PORTC->PCR[4] |= PORT_PCR_MUX(2); // I2C0_SCL
	PORTC->PCR[5] |= PORT_PCR_MUX(2); // I2C0_SDA
	
	// I2C_Baudrate = bus_speed / ( mul * SCL_Divider )
	I2C0->F = 0x14; // SCL_Divider = 80
	// I2C_Baudrate = 24 * 10^6 / 80 = 3 * 10^5
	I2C0->C1 =  0x80;// I2C Enable
}

void I2C_RepeatedStart(void)
{
	I2C0->C1 |= I2C_C1_RSTA_MASK; // Repeat start
}
/**
@brief Function using in interrpt-type transmission.
@author Jakub Brzezowski
@version 1.0 2018-12-01
@param none
@retval none
*/
void I2C_Wait(void)
{    
  while( (I2C0->S & I2C_S_IICIF_MASK) == 0); // Wait for interrupt pending
  I2C0->S |= I2C_S_IICIF_MASK; // Clear interrupt flag
} 

void I2C_SetRXmode(void)
{
	I2C0->C1 &= ~I2C_C1_TX_MASK; // Set Transmit Mode to Receive
}

void I2C_SetTXmode(void)
{
	I2C0->C1 |= I2C_C1_TX_MASK; // Set Transmit Mode to Transmit
}
void I2C_set_slave_mode(void)
{
  I2C0->C1  &= ~I2C_C1_MST_MASK;
}
void I2C_set_master_mode(void)
{
  I2C0->C1  |=  I2C_C1_MST_MASK;
}
/**
@brief Start of transmission.
@author Jakub Brzezowski
@version 1.0 2018-12-01
@param none
@retval none
*/
void I2C_Start(void)
{
	I2C_set_master_mode(); // Set Master Mode, START signal generated
	I2C_SetTXmode(); // Transmiter mode
}
/**
@brief End of transmission.
@author Jakub Brzezowski
@version 1.0 2018-12-01
@param none
@retval none
*/
void I2C_Stop(void)
{
	I2C_set_slave_mode(); // Set Slave mode, STOP signal generated
	I2C_SetRXmode(); // Receiver mode
}
/**
@brief Function writes byte of data to extern register.
@author Jakub Brzezowski
@version 1.0 2018-12-01
@param none
@retval none
*/
void I2C_WriteByte(uint8_t data)
{
	I2C0->D = data;	
}
/**
@brief Function reads data form extern device.
@author Jakub Brzezowski
@version 1.0 2018-12-01
@param none
@retval none
*/
uint8_t I2C_ReadByte(void)
{
	return I2C0->D;
}

void I2C_SendAck(void)
{
	I2C0->C1 &= ~I2C_C1_TXAK_MASK; // ACK Enable
}

void I2C_SendNack(void)
{
	I2C0->C1 |= I2C_C1_TXAK_MASK; // ACK Disable
}

uint8_t I2C_GetAck(void)
{
	if((I2C0->S & I2C_S_RXAK_MASK) == 0) 
		return 1; // ACK signal received
	else
		return 0; // ACK signal didn't received
}

void I2C_WaitForAck(void)
{
    I2C_Wait();
    // Get acknowledge signal
    if ( ! I2C_GetAck() )
    {
        // Generate STOP signal
        I2C_Stop(); 
        // Error, receiving device not send ACK bit
        
    }       
}

void I2C_Write(uint8_t data)
{
	I2C_WriteByte(data);
	// Wait for transfer complete
	I2C_WaitForAck();
}
void I2C_deinit(void){
	
	  I2C0->C1 = 0x00;  
    SIM->SCGC4 &= ~SIM_SCGC4_I2C0_MASK;
}