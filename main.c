/*
 * AT-VFD - example project
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

#define F_CPU 8000000UL
#define DISPLAY_DIGITS 12

#include <avr/io.h>
#include <util/delay.h>
#include "PT6302.h"

/* PT6302 commands */
static const uint8_t lighton = 0x72;
static const uint8_t lightoff = 0x71;


int main ()
{
  static const uint8_t digitstates[] =
    {0b11, 0b11, 0b11, 0b11, 0b11, 0b11, 0b11, 0b11, 0b11, 0b11, 0b11, 0b11};
  static const uint8_t custom_chars[8*5] = {0};
  static const uint8_t characters[] =
    {0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff};
  PT6302_startup ();
  set_ports (1, 1);
  set_digits (DISPLAY_DIGITS);
  set_duty (7);
  set_ADRAM (0, digitstates, DISPLAY_DIGITS);
  set_CGRAM (0,custom_chars, 8);
  set_DCRAM (0, characters, DISPLAY_DIGITS);
  while (1)
    {
      transmit_bytes (&lighton, 1);
      _delay_us (1000);
      transmit_bytes (&lightoff, 1);
      _delay_us (1000);
    }
}
