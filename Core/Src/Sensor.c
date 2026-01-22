
#include "Sensor.h"

const uint8_t channel_1 = 1, channel_2 = 2, channel_3 = 4, channel_4 = 8,
		channel_5 = 16, channel_6 = 32, channel_7 = 64, channel_8 = 128;
const uint16_t cmd_reg = (0x22 << 8),
		temp_reg = (0x2E << 8),
		pressure_reg = (0x36 << 8),
		status_reg_syn = (0x32 << 8),
		status_reg = (0x36 << 8);
#define sensor_addr (0x6C << 1)
const uint16_t reset_write = 0xB169;
const uint16_t reset = 0xFFFF;

void sensor_get_psi(sensor_info_t *i, uint8_t maddr, uint8_t buffer_sel){
	uint8_t buffer;
	int16_t sensor_buffer;
	//MUX Channel select
	HAL_I2C_Master_Transmit(&hi2c1, maddr, &channel_1, sizeof(uint8_t), 100);
	HAL_I2C_Master_Receive(&hi2c1, maddr, &buffer, sizeof(uint8_t), 100);

	//Reset sensor
//	HAL_I2C_Mem_Write(&hi2c1, sensor_addr, cmd_reg, I2C_MEMADD_SIZE_16BIT, &reset_write, 1, 100);
	//Get Status from sensor
	HAL_I2C_Mem_Write(&hi2c1, sensor_addr, status_reg, I2C_MEMADD_SIZE_16BIT, &reset, 2, 100);
	HAL_I2C_Mem_Read(&hi2c1, sensor_addr, status_reg_syn, I2C_MEMADD_SIZE_16BIT, &i->sensor_status[buffer_sel][0], 2, 100);
	//Get temp from sensor
	HAL_I2C_Mem_Read(&hi2c1, sensor_addr, temp_reg, I2C_MEMADD_SIZE_16BIT, &sensor_buffer, 2, 100);
	i->sensor_temp[buffer_sel][0] = sensor_buffer;
	HAL_I2C_Mem_Read(&hi2c1, sensor_addr, pressure_reg, I2C_MEMADD_SIZE_16BIT, &sensor_buffer, 2, 100);
	i->sensor_pressure[buffer_sel][0] = 1000 * (0.58 * (sensor_buffer + 26214) / 52428) - 0.29;

	//MUX Channel select
//	HAL_I2C_Master_Transmit(&hi2c1, maddr, &channel_2, sizeof(uint8_t), 100);
//	HAL_I2C_Master_Receive(&hi2c1, maddr, &buffer, sizeof(uint8_t), 100);
//	//Get psi from sensor
//	HAL_I2C_Mem_Read(&hi2c1, sensor_addr, &status_reg, sizeof(uint8_t), &i->sensor_status[buffer_sel][0], sizeof(uint16_t), 100);
//	HAL_I2C_Mem_Read(&hi2c1, sensor_addr, &status_reg, sizeof(uint8_t), &i->sensor_status[buffer_sel][0], sizeof(uint16_t), 100);
//
//	HAL_I2C_Master_Transmit(&hi2c1, maddr, &channel_3, sizeof(uint8_t), 100);
//	HAL_I2C_Master_Receive(&hi2c1, maddr, &buffer, sizeof(uint8_t), 100);
//	HAL_I2C_Master_Transmit(&hi2c1, maddr, &channel_4, sizeof(uint8_t), 100);
//	HAL_I2C_Master_Receive(&hi2c1, maddr, &buffer, sizeof(uint8_t), 100);
//	HAL_I2C_Master_Transmit(&hi2c1, maddr , &channel_5, sizeof(uint8_t), 100);
//	HAL_I2C_Master_Receive(&hi2c1, maddr, &buffer, sizeof(uint8_t), 100);
//	HAL_I2C_Master_Transmit(&hi2c1, maddr, &channel_6, sizeof(uint8_t), 100);
//	HAL_I2C_Master_Receive(&hi2c1, maddr, &buffer, sizeof(uint8_t), 100);
//	HAL_I2C_Master_Transmit(&hi2c1, maddr, &channel_7, sizeof(uint8_t), 100);
//	HAL_I2C_Master_Receive(&hi2c1, maddr, &buffer, sizeof(uint8_t), 100);
//	HAL_I2C_Master_Transmit(&hi2c1, maddr, &channel_8, sizeof(uint8_t), 100);
//	HAL_I2C_Master_Receive(&hi2c1, maddr, &buffer, sizeof(uint8_t), 100);
}
