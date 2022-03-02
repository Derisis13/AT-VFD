//
// Created by lacko on 02/03/2022.
//
#include <avr/io.h>
#include <util/delay.h>
#include "PT6302.h"

void PT6302_startup (void)
{
  PORTB |= (CSBpin | CLKBpin);
  PORTB &= ~DINpin;
  PORTC |= RSTpin;
  DDRB |= (CSBpin | CLKBpin | DINpin);
  DDRC |= RSTpin;
  _delay_us (TPRZ);
  PORTC &= ~RSTpin;
  _delay_us (TWRSTB);
};

void transmit_bytes (const uint8_t *payload, const uint8_t size)
{
  PORTB &= ~CSBpin;
  for (int i = 0; i < size; ++i)
    {
      uint8_t data = payload[i];
      for (int j = 0; j < 8; ++j)
        {
          PORTB &= ~CLKBpin;
          if ((data & 0x01) == 0)
            {
              PORTB |= DINpin;
            }
          else
            {
              PORTB &= ~DINpin;
            }
          _delay_us (TCW);
          PORTB |= CLKBpin;
          _delay_us (TCW);
          data >> 1;
        }
      _delay_us (TDOFF);
    }
  _delay_us (DTCSH);
  PORTB |= CSBpin;
}


void set_display_brightness (uint8_t level)
{
  switch (level)
    {
      case 0:transmit_bytes (0x0A, 1);
      break;
      case 1:transmit_bytes (0x2A, 1);
      break;
      case 2:transmit_bytes (0x4A, 1);
      break;
      case 3:transmit_bytes (0x6A, 1);
      break;
      case 4:transmit_bytes (0x8A, 1);
      break;
      case 5:transmit_bytes (0xAA, 1);
      break;
      case 6:transmit_bytes (0xCA, 1);
      default:transmit_bytes (0xEA, 1);
    }
}
