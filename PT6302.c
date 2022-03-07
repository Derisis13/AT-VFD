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
  uint8_t command = 0x50 | brightness;
  transmit_bytes (&command, 1);
}
