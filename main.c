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

#define DISPLAY_DIGITS 15

#include <avr/io.h>
#include <util/delay.h>
#include "PT6302.h"

int main() {
  static const uint8_t digitstates[] =
      {0b00, 0b00, 0b00, 0b00, 0b00, 0b00, 0b00, 0b00, 0b00, 0b00, 0b00, 0b00};
  static const uint8_t custom_chars[8 * 5] =
      {
          // rainbow 1 @ address 0x00
          0b0010010, 0b0100100, 0b0010010, 0b0100100, 0b0010010,
          // rainbow 2 @ address 0x01
          0b0100100, 0b0010010, 0b0100100, 0b0010010, 0b0100100,
          // tail 1 @ address 0x02
          0b0000000, 0b0001100, 0b0010000, 0b0111100, 0b0100110,
          // tail 2 @ address 0x03
          0b0000000, 0b0000000, 0b0001000, 0b0000000, 0b0000000,
          // body @ address 0x04
          0b0100110, 0b0100100, 0b0100110, 0b0100100, 0b0100110,
          // body @ address 0x05
          0b0100110, 0b0100100, 0b0100110, 0b0100100, 0b0100110,
          // head 1 @ address 0x06
          0b0001100, 0b0110010, 0b0001010, 0b0110010, 0b0001100,
          // head 2 @ address 0x07
          0b0011000, 0b1100100, 0b0010100, 0b1100100, 0b0011000,
      };
  static const uint8_t ha5kfu[] =
      {0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x48, 0x41, 0x35, 0x4B, 0x46, 0x55, 0x20, 0x20, 0x20};
  static const uint8_t blank[] =
      {0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20};
  static const uint8_t even_frame[] =
      {0x07, 0x05, 0x03, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00};
  static const uint8_t odd_frame[] =
      {0x06, 0x04, 0x02, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01};
  PT6302_startup();
  set_ports(1, 1);
  set_digits(DISPLAY_DIGITS);
  set_duty(7);
  set_ADRAM(0, digitstates, DISPLAY_DIGITS);
  set_CGRAM(0, custom_chars, 8);
  set_DCRAM(0, ha5kfu, DISPLAY_DIGITS);
  set_display_mode(NORMAL_MODE);
  _delay_ms(1000);
  while (1)
  {
    set_DCRAM(0, blank, DISPLAY_DIGITS);
    for (int i = 0; i < DISPLAY_DIGITS - 4; ++i)
    {
      if (i % 2 == 0)
        set_DCRAM(DISPLAY_DIGITS - i, even_frame, i);
      else
        set_DCRAM(DISPLAY_DIGITS - i, odd_frame, i);
      _delay_ms(250);
    }
  }
}
