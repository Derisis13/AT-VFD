#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "PT6302.h"

/* PT6302 commands */
static const uint8_t lighton = 0x72;
static const uint8_t lightoff = 0x71;


int main ()
{
  PT6302_startup ();
  set_ports (1, 1);
  set_duty (7);
  while (1)
    {

    }
}
