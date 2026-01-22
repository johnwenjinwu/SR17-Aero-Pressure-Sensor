
//CAN send function

#include "main.h"
#include "CAN.h"

extern char buffer[32];

/*This functions load the batt_info to the CAN message and load to send
 *Since each CAN frame is 8-bit and only LSB are consider
 *16-bit data must be separate into two 8-bit*/
void can_send(sensor_info_t *b, can_id_lookup_t *id, can_message_t *m){
	//Load cell voltages 0-3 to CAN data
	m->can_data[0] = (uint8_t) sensor_info.sensor_status[0][0];
	m->can_data[1] = (uint8_t) (sensor_info.sensor_status[0][0] >> 8);;
	m->can_data[2] = 2;
	m->can_data[3] = (uint8_t) 3;
	m->can_data[4] = (uint8_t) 4;
	m->can_data[5] = (uint8_t) 5;
	m->can_data[6] = (uint8_t) 6;
	m->can_data[7] = (uint8_t) 7;
	//Set CAN ID for message 1
	m->tx_header.StdId = id->message_1_id;
	can_real_send(m);

}

void can_real_send(can_message_t *m){
	//Check if mailbox is free
	if(HAL_CAN_GetTxMailboxesFreeLevel(&hcan1) == 0){
		uint32_t start_tick = HAL_GetTick();
		//No free mailbox, wait
		while(HAL_CAN_GetTxMailboxesFreeLevel(&hcan1) == 0){
		//Timeout after 10ms
			if((HAL_GetTick() - start_tick) > 10){
				return; //Exit function if timeout
			}
		}
	}
	HAL_CAN_AddTxMessage(&hcan1, &m->tx_header, &m->can_data[0], &m->tx_mailbox);
}
