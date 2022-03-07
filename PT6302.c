//
// Created by lacko on 02/03/2022.
//
#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "PT6302.h"

inline void PT6302_startup (void)
{
  DDRB |= (CSBpin | CLKBpin | DINpin);
  DDRC |= RSTpin;
  PORTB |= (CSBpin | CLKBpin);
  PORTB &= ~DINpin;
  PORTC &= ~RSTpin;
  _delay_us (TPRZ);
  PORTC |= RSTpin;
  _delay_us (TWRSTB);
}

void transmit_bytes (const uint8_t *payload, const uint8_t size)
{
  _delay_us (1);
  PORTB &= ~CSBpin;
  for (int i = 0; i < size; ++i)
    {
      uint8_t data = payload[i];
      for (int j = 0; j < 8; ++j, data = (data >> 1))
        {
          PORTB &= ~CLKBpin;
          if ((data & 0x01) == 0)
            PORTB &= ~DINpin;
          else
            PORTB |= DINpin;
          _delay_us (TCW);
          PORTB |= CLKBpin;
          _delay_us (TCW);
        }
      _delay_us (TDOFF);
    }
  _delay_us (DTCSH);
  PORTB |= CSBpin;
}

void set_ports (uint8_t gp1, uint8_t gp2)
{
  uint8_t command = 0x40;
  if (gp1 != 0)
    command |= 0x01;
  if (gp2 != 0)
    command |= 0x02;
  transmit_bytes (&command, 1);
}

void set_duty (uint8_t brightness)
{
  if (brightness > 7)
    {
      brightness = 7;
    }
  const uint8_t command = 0x50 | brightness;
  transmit_bytes (&command, 1);
}

void set_digits (uint8_t digit_count)
{
  if (digit_count >= 16)
    digit_count = 8; //we'll subtract 8 later from this number
  if (digit_count < 9)
    digit_count = 9;
  digit_count -= 8;
  const uint8_t command = 0x60 | digit_count;
  transmit_bytes (&command, 1);
}

void set_ADRAM (const uint8_t address, const uint8_t *data, uint8_t size)
{
  if (address > DISPLAY_DIGITS)
    return;
  if (address + size > DISPLAY_DIGITS)
    size = DISPLAY_DIGITS - address;
  uint8_t payload[++size];
  payload[0] = ADRAM | address;
  for (int i = 1; i < size; ++i)
    {
      payload[i] = data[i - 1];
    }
  transmit_bytes (payload, size);
}

void set_CGRAM (const uint8_t address, const uint8_t *data, uint8_t size)
{
  if (address > 0x08)
    return;
  if (address + size > 0x08)
    size = 0x08 - address;
  size = size * 5 + 1;
  uint8_t payload[size];
  payload[0] = CGRAM | address;
  for (int i = 1; i < size; ++i)
    {
      payload[i] = *(data + i - 1);
    }
  transmit_bytes (payload, size);
}

void set_DCRAM (const uint8_t address, const uint8_t *cg_address, uint8_t size)
{
  if (address > DISPLAY_DIGITS)
    return;
  if (address + size > DISPLAY_DIGITS)
    size = DISPLAY_DIGITS - address;
  uint8_t payload[++size];
  payload[0] = DCRAM | address;
  for (int i = 1; i < size; ++i)
    {
      payload[i] = cg_address[i - 1];
    }
  transmit_bytes (payload, size);
}