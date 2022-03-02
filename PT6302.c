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

void send_command (const uint8_t command)
{
  transmit_bytes (&command, 1);
}


void set_display_brightness (uint8_t level)
{
  switch (level)
    {
      case 0:send_command (0x0A);
      break;
      case 1:send_command (0x2A);
      break;
      case 2:send_command (0x4A);
      break;
      case 3:send_command (0x6A);
      break;
      case 4:send_command (0x8A);
      break;
      case 5:send_command (0xAA);
      break;
      case 6:send_command (0xCA);
      default:send_command (0xEA);
    }
}
