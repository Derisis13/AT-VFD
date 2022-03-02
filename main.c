#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>


int main ()
{
  uint8_t ledpin = (1 << PC4);
  DDRC |= ledpin;

  while (1)
    {
      PORTC |= ledpin;
      _delay_ms (1000);
      PORTC &= ~ledpin;
      _delay_ms (1000);
    }
}
