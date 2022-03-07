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
  set_digits (12);
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
