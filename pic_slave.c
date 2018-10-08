#include <stdio.h>
#include <stdint.h>
#include "pic24_all.h"

#define LED1 (_LATA0)
#define one_wire (_RB13) //PIN RB 13
#define byte unsigned char

typedef enum  {
  WAIT_FOR_RESET,
  ROM_CMD,
  FUNCTION_CMD,
} state_t; //Different states of command

volatile state_t current_state = WAIT_FOR_RESET; //DEFAULT TO WAIT FOR RESET
volatile byte can_read = 1;

//HARD CODED SERIAL NUMBER
byte serial_number[8] = {0x28, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02};

//HARD CODED SENSOR VALUES
const byte scratchpad[10] = {0x00, 0x79, 0x01, 0x4B, 0x46, 0x7F, 0xFF, 0x07, 0x10, 0x70};

//FUNCTION PROTOTYPE
byte detect_reset(void);
void send_presence_pulse(void);
byte read_bit (void);
byte read_byte (void);
void pull_bus_low(void);
void release_bus(void);
void write_byte (byte write_data);
void write_bit(byte write_bitt);
byte match_search(byte write_bit);
byte match_bits (byte read_bit);

//CONFIGURE INPUT
void config_pb()  {
  CONFIG_RB13_AS_DIG_INPUT();
  ENABLE_RB13_PULLUP();
  // Give the pullup some time to take effect.
  DELAY_US(1);
}


// Change notification interrupt configuration
// -------------------------------------------
// Enable change-notification interrupts on the one wire pins
void config_cn(void) {
  // Enable change notifications on RB13 specifically.
  ENABLE_RB13_CN_INTERRUPT();
  // Clear the interrupt flag.
  _CNIF = 0;
  // Choose a priority.
  _CNIP = 1;
  // Enable the Change Notification general interrupt.
  _CNIE = 1;
  
  CONFIG_RA0_AS_DIG_OUTPUT(); //configure LEDs
}

// Change notification
// -------------------
void _ISR _CNInterrupt(void) {
  _CNIF = 0;
  _CNIE = 0;
  byte buffer;
    switch (current_state) {
        case WAIT_FOR_RESET:
            //CHECK IF MASTEr sends a reset pulse
            if (detect_reset()) {
                //send a presence pulse and wait for ROM command
                send_presence_pulse();
                current_state = ROM_CMD;
            }
            break;
        case ROM_CMD:
            buffer = read_byte();
            if (0x31 <= buffer && buffer <= 0x35) { //read rom command
                ;
                LED1 = 1;
                int i = 0;
                while (i < 8){
                    write_byte(serial_number[i]);
                    i++;
                }
                //basically write the serial number onto the bus
            } else if (0xEC <= buffer && buffer <= 0xF4){ //search rom command
                ;
                //unfolded to increase speed
                int i_2 = 0;
                while (i_2 < 8){
                    byte current_byte = serial_number[i_2];

                    while(one_wire);
                    if(!match_search(current_byte & 0x01)){ 	// sending LS-bit first
                        break;
                    }
                    current_byte >>= 1;							// shift the data byte for the next bit to send

                    while(one_wire);
                    if(!match_search(current_byte & 0x01)){
                        break;
                    }
                    current_byte >>= 1;

                    while(one_wire);
                    if(!match_search(current_byte & 0x01)){
                        break;
                    }
                    current_byte >>= 1;

                    while(one_wire);
                    if(!match_search(current_byte & 0x01)){
                        break;
                    }
                    current_byte >>= 1;

                    while(one_wire);
                    if(!match_search(current_byte & 0x01)){
                        break;
                    }
                    current_byte >>= 1;

                    while(one_wire);
                    if(!match_search(current_byte & 0x01)){
                        break;
                    }
                    current_byte >>= 1;

                    while(one_wire);
                    if(!match_search(current_byte & 0x01)){
                        break;
                    }
                    current_byte >>= 1;

                    while(one_wire);
                    if(!match_search(current_byte & 0x01)){
                        break;
                    }

                    i_2++;
                }
                buffer = 0;
                current_state = WAIT_FOR_RESET;
                _CNIF = 0;
                return;
            } else if (0x53 <= buffer && buffer <= 0x57){ //match rom command
                ;
                int i_3 = 0;
                while (i_3 < 8) {
                    byte current_byte = serial_number[i_3];
                    int j = 0;
                    while (j < 8) {
                        while (one_wire);
                        if (!match_bits(current_byte & 0x01)) {
                            buffer = 0;
                            current_state = WAIT_FOR_RESET;
                            _CNIE = 1;
                            return;
                        }
                        current_byte >>=1 ;
                        j++;
                    }
                    i_3++;
                }
                buffer = 0;
                current_state = FUNCTION_CMD;
            } else if (0xCA <= buffer && buffer <= 0xCE){ //skip rom command
                buffer = 0;
                current_state = FUNCTION_CMD;
        }
        break;
    case FUNCTION_CMD:
        buffer = read_byte();
        if (0x42 <= buffer && buffer <= 0x46){
            //BASICALLY TELLS THE sensor to sense things and save to scratchpad
            can_read = 1;
        } else if (0xBA <= buffer && buffer <= 0xC3) {
            //write scratchpad (sensor value) onto the bus
            if (can_read == 1){
                int i_4 = 1;
                while (i_4 < 10) {
                    while (one_wire);
                    write_byte(scratchpad[i_4]);
                    i_4++;
                }
                can_read = 0;
            }
        }
        buffer = 0;
        current_state = WAIT_FOR_RESET;
}
 _CNIE = 1;
}

byte detect_reset(void) {
    DELAY_US(20);
    if (!one_wire){
        DELAY_US(480);
        if (one_wire){
            return 1;
        } else {
            return 0;
        }
    }
    return 0;
}

void send_presence_pulse(void) {
    pull_bus_low();
    DELAY_US(70);
    release_bus();
}

void pull_bus_low(void) {
    CONFIG_RB13_AS_DIG_OUTPUT();
    one_wire = 0;
}

void release_bus(void) {
    config_pb();
    config_cn();
}
byte read_bit (void) {
    byte read_data;
    DELAY_US(25);
    read_data = one_wire;
    DELAY_US(20);
    if (one_wire){
        return read_data;
    }
    DELAY_US(25);
    if (one_wire) {
        return read_data;
    }
}

byte read_byte (void) {
	// I unfold this and some other loops to meet very strict time limits
	byte result=0;
	if (read_bit())
		result |= 0x80;				// if result is one, then set MS-bit
	while(one_wire);
	result >>= 1; 				    // shift the result to get it ready for the next bit to receive
	if (read_bit())
		result |= 0x80;
	while(one_wire);
	result >>= 1;
	if (read_bit())
		result |= 0x80;
	while(one_wire);
	result >>= 1;
	if (read_bit())
		result |= 0x80;
	while(one_wire);
	result >>= 1;
	if (read_bit())
		result |= 0x80;
	while(one_wire);
	result >>= 1;
	if (read_bit())
		result |= 0x80;
	while(one_wire);
	result >>= 1;
	if (read_bit())
		result |= 0x80;
	while(one_wire);
	result >>= 1;
	if (read_bit())
		result |= 0x80;
	return result;
}


void write_bit(byte write_bitt) {
    if (write_bitt) {
        DELAY_US(60);
    } else {
        pull_bus_low();
        DELAY_US(60);
        release_bus();
    }
}

byte match_bits (byte read_bitt) {
	byte result=0;
	if (read_bit() == read_bitt)		// read bit on 1-wire line and compare with current one
		result = 1;						// match
	return result;
}

byte match_search (byte write_bitt) {
    byte res = 0;
    write_bit(write_bitt);
    while(one_wire);
    write_bit(write_bitt ^ 0x01);
    while(one_wire);
    if (read_bit() == write_bitt) {
        res = 1;
    } else {
        res = 0;
    }
    return res;
}

void write_byte (byte write_data)
{
		write_bit(write_data & 0x01); 	// sending LS-bit first
		while(one_wire);							// wait for master set bus low
		write_data >>= 1;					// shift the data byte for the next bit to send
		write_bit(write_data & 0x01);
		while(one_wire);
		write_data >>= 1;
		write_bit(write_data & 0x01);
		while(one_wire);
		write_data >>= 1;
		write_bit(write_data & 0x01);
		while(one_wire);
		write_data >>= 1;
		write_bit(write_data & 0x01);
		while(one_wire);
		write_data >>= 1;
		write_bit(write_data & 0x01);
		while(one_wire);
		write_data >>= 1;
		write_bit(write_data & 0x01);
		while(one_wire);
		write_data >>= 1;
		write_bit(write_data & 0x01);
}
// Main
// ====
int main(void) {
  configBasic(HELLO_MSG);
   //configClockFRCPLL_FCY40MHz();
  config_pb();
  config_cn();
  LED1 = 0;
  while (1) {
    // Enter a low-power state, which still keeps timer3 and uart1 running.
    // Enter code to do stuff here, communications are handled via interrupts.
    IDLE();
  }
}
