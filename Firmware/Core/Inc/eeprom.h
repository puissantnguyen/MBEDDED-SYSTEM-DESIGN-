/*
 * eeprom.h
 *
 */

#ifndef EEPROM_H_
#define EEPROM_H_

#include "i2c.h"

#define	EEPROM_I2C hi2c1
#define EEPROM_ADDRESS (0x50 << 1)
#define EEPROM_PAGESIZE	128
#define EEPROM_WRITE 10
#define I2C_TIMEOUT 100

extern I2C_HandleTypeDef EEPROM_I2C;

HAL_StatusTypeDef AT24Cxx_is_connected(void);
HAL_StatusTypeDef Read_From_24LCxx(uint16_t MemAddress, uint8_t *pData, uint16_t len);
HAL_StatusTypeDef Write_To_24LCxx(uint16_t MemAddress, uint8_t *pData, uint16_t len);

#endif /* EEPROM_H_ */
