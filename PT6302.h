//
// Created by lacko on 02/03/2022.
//

#ifndef _PT6302_H_
#define _PT6302_H_

/* PT6302 timing constants, all in usec */
#define TCW 1     //CLKB pulse width
#define TDOFF 8   //Data processing time
#define DTCSH 16  //time difference between tDOFF and tCSH
#define TPRZ 100  //VDD rise time
#define TWRSTB 1  //RSTB pulse width

#define RSTpin (uint8_t) (1 << PC2)
#define CSBpin (uint8_t) (1 << PB0)
#define CLKBpin (uint8_t) (1 << PB6)
#define DINpin (uint8_t) (1 << PB7)


/* -------------------------------------------------------------
 * Innitial setup for the VFD controller interface
 * Sets up the connected pins and leaves them in inactive state.
 * ------------------------------------------------------------- */
void PT6302_startup(void);


/* -------------------------------------------------------------------------------
 * Transmits size byte of data through the VFD controller's interface from payload
 * Handles CLKB, CSB and timing constraints
 * ------------------------------------------------------------------------------- */
void transmit_bytes (const uint8_t* payload, uint8_t size);


/* --------------------------------------------------------------
 * Set the brightness of the VFD
 * level can be between 0-7, 7 and larger will set max brightness
 * It sets the display's duty cycle to conroll the brightness
 * -------------------------------------------------------------- */
void set_display_brightness (uint8_t level);

#endif //_PT6302_H_
