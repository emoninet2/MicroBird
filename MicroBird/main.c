/*
 * carrot.c
 *
 * Created: 6/3/2016 10:16:40 PM
 *  Author: user
 */ 
#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include "FreeRTOS.h"
#include "task.h"
#include "nrf24l01p/nrf24l01p.h"


int thread_1(void)
{
	
	_nrf24l01p_init();
	_nrf24l01p_enable_dynamic_payload();
	_nrf24l01p_enable_payload_with_ack();

	_nrf24l01p_enable_auto_ack(_NRF24L01P_PIPE_P0);
	_nrf24l01p_enable_auto_ack(_NRF24L01P_PIPE_P1);
	_nrf24l01p_enable_auto_ack(_NRF24L01P_PIPE_P2);
	_nrf24l01p_enable_auto_ack(_NRF24L01P_PIPE_P3);
	_nrf24l01p_enable_auto_ack(_NRF24L01P_PIPE_P4);
	_nrf24l01p_enable_auto_ack(_NRF24L01P_PIPE_P5);

	_nrf24l01p_enable_dynamic_payload_pipe(_NRF24L01P_PIPE_P0);
	_nrf24l01p_enable_dynamic_payload_pipe(_NRF24L01P_PIPE_P1);
	_nrf24l01p_enable_dynamic_payload_pipe(_NRF24L01P_PIPE_P2);
	_nrf24l01p_enable_dynamic_payload_pipe(_NRF24L01P_PIPE_P3);
	_nrf24l01p_enable_dynamic_payload_pipe(_NRF24L01P_PIPE_P4);
	_nrf24l01p_enable_dynamic_payload_pipe(_NRF24L01P_PIPE_P5);

	_nrf24l01p_enable_rx_on_pipe(_NRF24L01P_PIPE_P0);
	_nrf24l01p_enable_rx_on_pipe(_NRF24L01P_PIPE_P1);
	_nrf24l01p_enable_rx_on_pipe(_NRF24L01P_PIPE_P2);
	_nrf24l01p_enable_rx_on_pipe(_NRF24L01P_PIPE_P3);
	_nrf24l01p_enable_rx_on_pipe(_NRF24L01P_PIPE_P4);
	_nrf24l01p_enable_rx_on_pipe(_NRF24L01P_PIPE_P5);

	_nrf24l01p_set_auto_retransmission_delay(15);
	_nrf24l01p_set_DataRate(_NRF24L01P_RF_SETUP_RF_DR_250KBPS);
	_nrf24l01p_flush_rx();
	//LEFT
	_nrf24l01p_set_RX_pipe_address(_NRF24L01P_PIPE_P1, 0x4C4C4C4C31);
	_nrf24l01p_set_RX_pipe_address(_NRF24L01P_PIPE_P2, 0x4C4C4C4C32);
	_nrf24l01p_set_RX_pipe_address(_NRF24L01P_PIPE_P3, 0x4C4C4C4C33);
	_nrf24l01p_set_RX_pipe_address(_NRF24L01P_PIPE_P4, 0x4C4C4C4C34);
	_nrf24l01p_set_RX_pipe_address(_NRF24L01P_PIPE_P5, 0x4C4C4C4C35);
	//RIGHT
// 	_nrf24l01p_set_RX_pipe_address(_NRF24L01P_PIPE_P1, 0x5252525231);
// 	_nrf24l01p_set_RX_pipe_address(_NRF24L01P_PIPE_P2, 0x5252525232);
// 	_nrf24l01p_set_RX_pipe_address(_NRF24L01P_PIPE_P3, 0x5252525233);
// 	_nrf24l01p_set_RX_pipe_address(_NRF24L01P_PIPE_P4, 0x5252525234);
// 	_nrf24l01p_set_RX_pipe_address(_NRF24L01P_PIPE_P5, 0x5252525235);	

	int txerr = 0;
	int passcount = 0;
	int total_count =0;
	char txbuff[32];
    while(1)
    {
 		char txData[] = "\t\t\tL";
		 
		 /*sprintf(txbuff,"\t\t\tL\t\t\t\t%d\t%d\t%d\t%d,",total_count,passcount,txerr);*/
		 sprintf(txbuff,"this is a sample text %d",total_count);
 		int txerrflag = _nrf24l01p_write_to_address_ack(0x4541525448, (uint8_t*)txbuff,strlen(txbuff));
		 if(txerrflag == -1) {
			 txerr++;
		 }
		 else{
			passcount++;
		 }
		total_count++;
		 vTaskDelay(1000); //wait 2 seconds
    }
}



/** Main program entry point. This routine contains the overall program flow, including initial
 *  setup of all components and the main program loop.
 */
int main(void)
{

	xTaskCreate(thread_1,(const char *) "t3", 200, NULL, tskIDLE_PRIORITY, NULL );
	
	//starting the scheduler
	vTaskStartScheduler();
	
	
	while(1)
	{
		
	}
}








