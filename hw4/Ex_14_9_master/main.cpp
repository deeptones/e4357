/* Program Example 7.9:
Sets the mbed up for async communication,
and exchanges data with a similar node,
sending its own switch positions,
and displaying those of the other.
*/

#include "mbed.h"
Serial async_port( p9, p10); // set up TX and RX on pins 9 and 10

// Original LED outputs - don't need these since I'm using on-mbed LEDs
// DigitalOut red_led(p25); // red led
// DigitalOut green_led(p26); // green led

// Drew re-defined outputs using the GPIO definitions
#define FIO1DIR2 (*( volatile unsigned char *)(0x2009C022))
#define FIO1PIN2 (*( volatile unsigned char *)(0x2009C036))


// Define which LEDs are on for each state (LED3 = pin 21, LED4 = pin 23 for port2 = pins [23:16]
char threeonly = 0x20;;
char fouronly = 0x80;;
char threeandfour = 0xA0;
char noleds;

DigitalOut strobe(p7); // a strobe to trigger the scope
DigitalIn switch_ip1(p5);
DigitalIn switch_ip2(p6);
char switch_word ; // the word we will send
char recd_val; // the received value
int main()
{
        FIO1DIR2 = 0xFF; // port 1 byte 2 set all bits to output
        async_port.baud(9600); // set baud rate to 9600 (ie default)
        // accept default format, of 8 bits, no parity
        while (1)
        {
                // Set up the word to be sent, by testing switch inputs
                switch_word = 0xa0; // set up a recognizable output pattern
                if (switch_ip1 == 1)
                        switch_word = switch_word | 0x01; // OR in lsb
                        if (switch_ip2 == 1)
                                switch_word = switch_word | 0x02; // OR in next lsb
                        strobe = 1; // short strobe pulse
                        wait_us(10);
                        strobe = 0;
                        async_port.putc(switch_word); // transmit switch_word
                        if (async_port.readable() == 1) // is there a character to be read?
                        recd_val = async_port.getc(); // if yes, then read it
                        // set leds according to incoming word from slave
                                // red_led = 0; // preset both to 0
                                // green_led = 0;
                        FIO1PIN2 &= ~threeandfour;

                        recd_val = recd_val& 0x03; // AND out unwanted bits
                        if (recd_val == 1)
                                // red_led = 1;
                                FIO1PIN2 |= threeonly;
                        if (recd_val == 2)
                                // green_led = 1;
                                FIO1PIN2 |= fouronly;
                        if (recd_val == 3)
                        {
                                // red_led = 1;
                                // green_led = 1;
                                FIO1PIN2 |= threeandfour;
                        }
        }
}