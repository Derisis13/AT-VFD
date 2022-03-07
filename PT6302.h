//
// Created by lacko on 02/03/2022.
//

#ifndef _PT6302_H_
#define _PT6302_H_

/* PT6302 timing constants, all in usec */
static const uint8_t TCW = 1;     //CLKB pulse width
static const uint8_t TDOFF = 16;  //Data processing time
static const uint8_t DTCSH = 16;  //time difference between tDOFF and tCSH
static const uint8_t TPRZ = 100;  //VDD rise time
static const uint8_t TWRSTB = 1;  //RSTB pulse width

enum pins {
  RSTpin = (1 << PC2),
  CSBpin = (1 << PB0),
  CLKBpin = (1 << PB6),
  DINpin = (1 << PB7),
};

/* -------------------------------------------------------------
 * Initial setup for the VFD controller interface
 * Sets up the connected pins and leaves them in inactive state.
 * ------------------------------------------------------------- */
void PT6302_startup(void);


/* -------------------------------------------------------------------------------
 * Transmits size byte of data through the VFD controller's interface from payload
 * Handles CLKB, CSB and timing constraints
 * ------------------------------------------------------------------------------- */
void transmit_bytes (const uint8_t* payload, uint8_t size);


/* ---------------------------------------------------------
 * Sets GP1 and GP2 to the values given in the function call
 * Handles the entire communication
 * --------------------------------------------------------- */
void set_ports(uint8_t gp1, uint8_t gp2);

#endif //_PT6302_H_
