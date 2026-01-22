#ifndef INC_SENSOR_H_
#define INC_SENSOR_H_

#include "main.h"

extern I2C_HandleTypeDef hi2c1;

typedef struct sensor_info_t{
	int8_t sensor_pressure[4][8];
	uint8_t sensor_temp[4][8];
	uint16_t sensor_status[4][8];
}sensor_info_t;

typedef struct mux_addr_t{
    uint8_t A;
    uint8_t B;
    uint8_t C;
    uint8_t D;
}mux_addr_t;


void sensor_get_psi(sensor_info_t *i, uint8_t maddr, uint8_t buffer_sel);



#endif /* INC_SENSOR_H_ */
