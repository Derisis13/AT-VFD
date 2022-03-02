#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>

/* PT6302 timing constants, all in usec */
static const uint8_t TCW = 1;     //CLKB pulse width
static const uint8_t TDOFF = 8;   //Data processing time
static const uint8_t DTCSH = 16;  //time difference between tDOFF and tCSH
static const uint8_t TPRZ = 100;  //VDD rise time
static const uint8_t TWRSTB = 1;  //RSTB pulse width

enum pins {
  RSTpin = (1 << PC2),
  CSBpin = (1 << PB0),
  CLKBpin = (1 << PB6),
  DINpin = (1 << PB7),
};

static inline void PT6302_startup (void)
{
  DDRB |= (CSBpin | CLKBpin | DINpin);
  DDRC |= RSTpin;
  PORTB |= (CSBpin | CLKBpin);
  PORTB &= ~DINpin;
  PORTC |= RSTpin;
  _delay_us (TPRZ);
  PORTC &= ~RSTpin;
  _delay_us (TWRSTB);
}

static void transmit_bytes (const uint8_t *payload, const uint8_t size)
{
  PORTB &= ~CSBpin;
  for (int i = 0; i < size; ++i)
    {
      uint8_t data = payload[i];
      for (int j = 0; j < 8; ++j, data >>= 1)
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
        }
      _delay_us (TDOFF);
    }
  _delay_us (DTCSH);
  PORTB |= CSBpin;
}

int main ()
{
  PT6302_startup ();
  DDRC |= (1 << PC4);
  while (1)
    {
      PORTC |= (1 << PC4);
      _delay_ms (1000);
      PORTC &= ~(1 << PC4);
      _delay_ms (1000);
    }
}
