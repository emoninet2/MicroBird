/*
 * nrf24l01p_arch_driver.h
 *
 * Created: 29-Mar-16 11:17:14 PM
 *  Author: emon1
 */ 


#ifndef NRF24L01P_ARCH_DRIVER_H_
#define NRF24L01P_ARCH_DRIVER_H_

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdbool.h>



#if defined (__cplusplus)
extern "C"{
#endif






#define _nrf24l01p_delay_us _delay_us
#define _nrf24l01p_delay_ms _delay_ms


#define set_bit(reg,bit) reg|= (1<<bit);
#define clr_bit(reg,bit) reg&= ~(1<<bit);
#define tgl_bit(reg,bit) reg^= (1<<bit);


#define CSN_DDR DDRD
#define CSN_PORT PORTD
#define CSN_PIN_BIT	7

#define CE_DDR	DDRB
#define CE_PORT	PORTB
#define CE_PIN_BIT	4


#define SPI_DDR		DDRB
#define SPI_PORT	PORTB

#define MOSI_DDR	DDRB
#define MOSI_PORT	PORTB
#define MOSI_BIT	2

#define MISO_DDR	DDRB
#define MISO_PORT	PORTB
#define MISO_BIT	3

#define SCK_DDR		DDRB
#define SCK_PORT	PORTB
#define SCK_BIT		1

#define SPI_SS_DDR		DDRB
#define SPI_SS_PORT	PORTB
#define SPI_SS_BIT		0


static void arch_nrf24l01p_ce_pin(bool state){
	if(state){set_bit(CE_PORT,CE_PIN_BIT);}
	else {clr_bit(CE_PORT,CE_PIN_BIT);}

	
}

static void arch_nrf24l01p_csn_pin(bool state){
	if(state){set_bit(CSN_PORT,CSN_PIN_BIT);}
	else {clr_bit(CSN_PORT,CSN_PIN_BIT);}

}

static void arch_nrf24l01p_initialize(){
		set_bit(CSN_DDR,CSN_PIN_BIT);
		set_bit(CE_DDR,CE_PIN_BIT);

		clr_bit(CE_PORT,CE_PIN_BIT);
		set_bit(CSN_PORT,CSN_PIN_BIT);
		SPI_DDR |= (1<<SPI_SS_BIT) | (1<<MOSI_BIT) | (1<<SCK_BIT);
		SPI_DDR &= ~(1<<MISO_BIT);
		SPCR |= (1<<SPE) | (1<<MSTR);
}


static uint8_t arch_spi_master_transmit_byte_val(uint8_t data)
{
	//fill SPDR with data to write
	SPDR = data;
	//wait for transmission to complete
	while(!(SPSR&(1<<SPIF)));
	return SPDR;
}

static uint8_t arch_spi_master_transmit_byte_ref(uint8_t *data)
{
	//fill SPDR with data to write
	SPDR = *data;
	//wait for transmission to complete
	while(!(SPSR&(1<<SPIF)));
	return SPDR;
}

static void arch_spi_master_receive_byte_ref(uint8_t *data){
	//fill SPDR with data to write
	SPDR = 0xFF;
	//wait for transmission to complete
	while(!(SPSR&(1<<SPIF)));
	*data = SPDR;
}


#if defined (__cplusplus)
}
#endif

#endif /* NRF24L01P_ARCH_DRIVER_H_ */