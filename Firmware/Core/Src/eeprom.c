/*
 * eeprom.c
 *
 */

#include <stdint.h>
#include <stdlib.h>
#include "eeprom.h"

static unsigned inpage_addr_mask = EEPROM_PAGESIZE - 1;

static unsigned size_to_page_end(unsigned addr);

HAL_StatusTypeDef AT24Cxx_is_connected(void)
{
	return HAL_I2C_IsDeviceReady(&EEPROM_I2C, EEPROM_ADDRESS, 1, I2C_TIMEOUT);
}

HAL_StatusTypeDef Read_From_24LCxx(uint16_t MemAddress, uint8_t *pData, uint16_t len)
{
	HAL_StatusTypeDef returnValue;
	uint8_t addr[2];

	/* We compute the MSB and LSB parts of the memory address */
	addr[0] = (uint8_t) ((MemAddress & 0xFF00) >> 8);
	addr[1] = (uint8_t) (MemAddress & 0xFF);

	/* First we send the memory location address where start reading data */
	returnValue = HAL_I2C_Master_Transmit(&EEPROM_I2C, EEPROM_ADDRESS, addr, 2, HAL_MAX_DELAY);
	if(returnValue != HAL_OK)
		return returnValue;

	/* Next we can retrieve the data from EEPROM */
	returnValue = HAL_I2C_Master_Receive(&EEPROM_I2C, EEPROM_ADDRESS, pData, len, HAL_MAX_DELAY);
	return returnValue;
}

HAL_StatusTypeDef Write_To_24LCxx(uint16_t MemAddress, uint8_t *pData, uint16_t len)
{
	HAL_StatusTypeDef returnValue;
	uint8_t *data;

	/* First we allocate a temporary buffer to store the destination memory
 	 * address and the data to store */
	data = (uint8_t*)malloc(sizeof(uint8_t)*(len+2));

	/* We compute the MSB and LSB parts of the memory address */
	data[0] = (uint8_t) ((MemAddress & 0xFF00) >> 8);
	data[1] = (uint8_t) (MemAddress & 0xFF);

	/* And copy the content of the pData array in the temporary buffer */
	memcpy(data+2, pData, len);

	/* We are now ready to transfer the buffer over the I2C bus */
	returnValue = HAL_I2C_Master_Transmit(&EEPROM_I2C, EEPROM_ADDRESS, data, len + 2, HAL_MAX_DELAY);
	if(returnValue != HAL_OK)
		return returnValue;

	free(data);

	/* We wait until the EEPROM effectively stores data in memory */
	while(HAL_I2C_Master_Transmit(&EEPROM_I2C, EEPROM_ADDRESS, 0, 0, HAL_MAX_DELAY) != HAL_OK);

	return HAL_OK;
}


static unsigned size_to_page_end(unsigned addr)
{
    return (~addr & inpage_addr_mask) + 1;
}
