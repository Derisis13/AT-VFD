//
// Created by lacko on 02/03/2022.
//

#ifndef _PT6302_H_
#define _PT6302_H_



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


#endif //_PT6302_H_
