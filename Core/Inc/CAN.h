#ifndef INC_CAN_H_
#define INC_CAN_H_

#include "main.h"
#include "Sensor.h"

extern CAN_HandleTypeDef hcan1;
extern sensor_info_t sensor_info;

//create a lookup table struct for CAN id
typedef struct can_id_lookup_t{
	uint16_t message_1_id; //ID for
	uint16_t message_2_id; //ID for
	uint16_t message_3_id; //ID for
	uint16_t message_4_id; //ID for
} can_id_lookup_t;

typedef struct can_message_t{
	CAN_TxHeaderTypeDef tx_header;
	uint8_t can_data[8];
	uint32_t tx_mailbox;
}can_message_t;

void can_send(sensor_info_t *s, can_id_lookup_t *id, can_message_t *m);
void can_real_send(can_message_t *m);

#endif /* INC_CAN_H_ */
