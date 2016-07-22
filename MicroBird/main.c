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




#define switchPINPORT_0	PIND
#define switchPINPORT_1	PINB
#define switchPINPORT_2	PINB
#define switchPINPORT_3	PINB

#define switchPIN_0		6
#define switchPIN_1		7
#define switchPIN_2		6
#define switchPIN_3		5


#define relayPORT_0	PORTD
#define relayPORT_1 PORTD
#define relayPORT_2 PORTD
#define relayPORT_3 PORTC

#define relayPIN_0 0 
#define relayPIN_1 1
#define relayPIN_2 4
#define relayPIN_3 6


volatile bool relayState_0 = 0;
volatile bool relayState_1 = 0;
volatile bool relayState_2 = 0;
volatile bool relayState_3 = 0;

void test_relay(){
			relay_control(3,0);
			vTaskDelay(2000);
			relay_control(3,1);
			vTaskDelay(2000);
			
			relay_control(2,0);
			vTaskDelay(2000);
			relay_control(2,1);
			vTaskDelay(2000);

			relay_control(1,0);
			vTaskDelay(2000);
			relay_control(1,1);
			vTaskDelay(2000);
			
			relay_control(0,0);
			vTaskDelay(2000);
			relay_control(0,1);
			vTaskDelay(2000);
}



void relay_control(int relayID, bool state){
	
	
	
	switch(relayID){
		case 0: {
			relayPORT_0 &= ~(1<<relayPIN_0);
			relayPORT_0 |= (state<<relayPIN_0);
			relayState_0 = state;
			break;
		}
		
		case 1: {
			relayPORT_1 &= ~(1<<relayPIN_1);
			relayPORT_1 |= (state<<relayPIN_1);
			relayState_1 = state;
			break;
		}
		
		case 2: {
			relayPORT_2 &= ~(1<<relayPIN_2);
			relayPORT_2 |= (state<<relayPIN_2);
			relayState_2 = state;
			break;
		}
		
		case 3: {
			relayPORT_3 &= ~(1<<relayPIN_3);
			relayPORT_3 |= (state<<relayPIN_3);
			relayState_3 = state;
			break;
		}
		default:{
			break;
		}
		
	}
}




char *command_handler(char **args,int arg_count){

	if(!strcmp(args[0], "light") ) {
		if(!strcmp(args[1], "0")) {
			if(!strcmp(args[2], "0")) {
				relay_control(1,1);
			}
			else if(!strcmp(args[2], "1")) {
				relay_control(1,0);
			}
		}
		else if(!strcmp(args[1], "1")) {
			if(!strcmp(args[2], "0")) {
				relay_control(3,1);			
			}
			else if(!strcmp(args[2], "1")) {
				relay_control(3,0);			
			}
		}
	}
	else if(!strcmp(args[0], "fan") ) {
		if(!strcmp(args[1], "0")) {
			relay_control(0,1);
		}
		else if(!strcmp(args[1], "1")) {
			relay_control(0,0);
		}
	}
	else{
		//printf("unknown command\r\n");
		//char message[50] = "unknown command\r\n";
		//remotch_client->send_all("unknown command\r\n", sizeof("unknown command\r\n")-1);
	}

	return 0;
}

void command_parse_execute(char *command){

	int arg_index = 0;
	char *pch;
	char *remotch_args[ 10];
	pch = strtok(command, " ");
	while(pch != NULL) {
		remotch_args[arg_index] = pch;
		arg_index++;
		if(arg_index >=10) break;
		pch = strtok (NULL, " ");
	}
	command_handler(remotch_args,arg_index);
}







int thread_1(void)
{
	DDRC|= (1<<7);
	
	DDRD|=(1<<0);
	DDRD|=(1<<1);
	DDRD|=(1<<4);
	DDRC|=(1<<6);
	
	DDRD &= ~(1<<6);
	DDRB &= ~(1<<7);
	DDRB &= ~(1<<6);
	DDRB &= ~(1<<5);
	
	DDRD&= ~(1<<6);
	
	
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
	
	
	
	char rxData[35];
	
	
	relay_control(0,1);
	relay_control(1,1);
	relay_control(2,1);
	relay_control(3,1);
	
	bool cow = 0;
	while(1){

		
		if((_nrf24l01p_readable(_NRF24L01P_PIPE_P1))){
			int width = _nrf24l01p_read_dyn_pld(_NRF24L01P_PIPE_P1, (uint8_t*) rxData);
			rxData[width] = '\0';
			command_parse_execute(rxData);

		}
		
		
		
		if((switchPINPORT_0&(1<<switchPIN_0))){
			relayState_0 = !relayState_0;
			relay_control(0,relayState_0);
			//PORTC^=(1<<7);
			while((switchPINPORT_0&(1<<switchPIN_0)));
			vTaskDelay(50);
		}
		if((switchPINPORT_1&(1<<switchPIN_1))){
			relayState_1 = !relayState_1;
			relay_control(1,relayState_1);
			//PORTC^=(1<<7);
			while((switchPINPORT_1&(1<<switchPIN_1)));
			vTaskDelay(50);
		}

		if((switchPINPORT_2&(1<<switchPIN_2))){
			relayState_2 = !relayState_2;
			relay_control(2,relayState_2);
			//PORTC^=(1<<7);
			while((switchPINPORT_2&(1<<switchPIN_2)));
			vTaskDelay(50);
		}
		
		if((switchPINPORT_3&(1<<switchPIN_3))){
			relayState_3 = !relayState_3;
			relay_control(3,relayState_3);
			//PORTC^=(1<<7);
			while((switchPINPORT_3&(1<<switchPIN_3)));
			vTaskDelay(50);
		}
				
		
	}
}




/** Main program entry point. This routine contains the overall program flow, including initial
 *  setup of all components and the main program loop.
 */
int main(void)
{

	xTaskCreate(thread_1,(const char *) "t1", 500, NULL, tskIDLE_PRIORITY, NULL );
	
	//starting the scheduler
	vTaskStartScheduler();
	
	while(1){
		
	}
	

}








