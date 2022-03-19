#pragma once
/*
 * AT-VFD
 * Copyright (C) 2022  László Párkányi
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301
 * USA
 */

#define DISPLAY_DIGITS 15
#include <inttypes.h>
#include <avr/io.h>
/* PT6302 timing constants, all in usec */
static const uint8_t TCW = 1;     //CLKB pulse width
static const uint8_t TDOFF = 16;  //Data processing time
static const uint8_t DTCSH = 16;  //time difference between tDOFF and tCSH
static const uint8_t TCSH = 32;   //Chip select hold time
static const uint8_t TPRZ = 100;  //VDD rise time
static const uint8_t TWRSTB = 1;  //RSTB pulse width

enum pins {
  RSTpin = (1 << PC2),
  CSBpin = (1 << PB0),
  CLKBpin = (1 << PB6),
  DINpin = (1 << PB7),
};

enum RAM_types {
  DCRAM = 0x10,
  CGRAM = 0x20,
  ADRAM = 0x30,
};

enum display_modes {
  NORMAL_MODE = 0x0,
  ALL_ON = 0x1,
  ALL_OFF = 0x2,
};

/* -------------------------------------------------------------
 * Initial setup for the VFD controller interface
 * Sets up the connected pins and leaves them in inactive state.
 * ------------------------------------------------------------- */
void PT6302_startup (void);

/* ----------------------------------------------
 * Resets the VFD controller trough its reset pin
 * Handles reset delays
 * ---------------------------------------------- */
void PT6302_reset (void);

/* ------------------------------------------------
 * Transmits one character (data)
 * Handles the entire communication
 * this is (mostly) intended to be used by wrappers
 * ------------------------------------------------ */
void transmit_byte (uint8_t data);

/* -------------------------------------------------------------------------------
 * Transmits size byte of data through the VFD controller's interface from payload
 * Handles CLKB, CSB and timing constraints
 * ------------------------------------------------------------------------------- */
void transmit_bytes (const uint8_t *payload, uint8_t size);

/* ---------------------------------------------------------
 * Sets GP1 and GP2 to the values given in the function call
 * Handles the entire communication
 * --------------------------------------------------------- */
void set_ports (uint8_t gp1, uint8_t gp2);

/* ---------------------------------------------------------------------------------------
 * Sets the number of digit_count the VFD has
 * digit_count below 9 are interpreted as 9 and digit_count above 16 are interpreted as 16
 * Handles the entire communication
 * --------------------------------------------------------------------------------------- */
void set_digits (uint8_t digit_count);

/* -----------------------------------------------------------
 * Sets duty cycle of controlled VFD
 * Brightness between 0 and 7 are accepted, any higher means 7
 * duty = (brightness + 8)/16 (valid between 8/16 and 15/16)
 * Handles the entire communication
 * ----------------------------------------------------------- */
void set_duty (uint8_t brightness);

/* ------------------------------------------------------------------------------------------
 * Set the content of the DCRAM - this will display a character from the CGROM/RAM at address
 * cd_address is an array of the CGROM/RAM addresses of characters to display
 * size is the number of characters to display (max DISPLAY_DIGITS - address)
 *  if exceeded, max possible number of characters will be displayed
 * address is the starting address (4 bits, max DISPLAY_DIGITS)
 *  if DISPLAY_DIGITS is exceeded, no characters will be set
 * Handles the entire communication
 * ------------------------------------------------------------------------------------------ */
void set_DCRAM (uint8_t address, const uint8_t *cg_address, uint8_t size);

/* -------------------------------------------------------------------------------
 * Set the content of the CGRAM - this will write custom characters into the CGRAM
 * data is an array of 5-byte arrays that contain the custom character data
 * size is the number of 5-byte arrays
 * address is the starting address (3 bits)
 * Handles the entire communication
 * ------------------------------------------------------------------------------- */
void set_CGRAM (uint8_t address, const uint8_t *data, uint8_t size);

/* ---------------------------------------------------------------------------------------
 * Set the content of the ADRAM - This will cause the corresponding segments to be set
 * data is an array containing sequential data of the segments (one byte for two segments)
 *  elements of the array are truncated after two bits
 * size is the number of segment pairs to be changed (max DISPLAY_DIGITS pairs - address)
 *  if exceeded, max possible number of segment pairs will be set
 * address is the starting address (4 bits, max DISPLAY_DIGITS)
 *  if DISPLAY_DIGITS is exceeded, no segment pairs will be set
 * Handles the entire communication
 * --------------------------------------------------------------------------------------- */
void set_ADRAM (uint8_t address, const uint8_t *data, uint8_t size);

/* -----------------------------------------
 * Sets the VFD operation mode
 * See operation modes in enum display_modes
 * Handles the entire communication
 * ----------------------------------------- */
void set_display_mode (enum display_modes mode);