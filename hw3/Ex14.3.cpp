// Program Example 14.3 : Sets up a digital output pin using control 
// registers, and flashes an led. 
//

// function prototypes 
void delay(void); 

// Define addresses of digital i/ o control registers, as pointers to volatile data 
// Drew:  original pin register addresses
#define FIO2DIR0 (*( volatile unsigned char *)(0x2009C040))
#define FIO2PIN0 (*( volatile unsigned char *)(0x2009C054))

// Drew:  My addresses for using registers connected to board-connected LED-1
#define FIO1DIR2 (*( volatile unsigned char *)(0x2009C022)) 
#define FIO1PIN2 (*( volatile unsigned char *)(0x2009C036))
#define PINSEL3  (*( volatile unsigned long *)(0x4002C00C))
#define PINMODE3 (*( volatile unsigned long *)(0x4002C04C))

// Added DIR and PIN ports for switch input
#define FIO0DIR0 (*( volatile unsigned char *)(0x2009C000)) 
#define FIO0PIN0 (*( volatile unsigned char *)(0x2009C014))

// some variables
char a; 
char b;
char i;

int main() 
{  
    FIO0DIR0 = 0x00; // port 0 byte 0 set all bits to inputs
    FIO1DIR2 = 0xFF; // port 1 byte 2 set all bits to output
    
    // PINSEL3 =  0x00000000; // This should be the reset value but just to be sure...
    // PINMODE3 = 0x00000A20; // Ensure pull-up resistor enabled on all port1[31:16] pins
// set port 2, lowest byte to output 
        while(1) 
        {
            if (FIO0PIN0&0x01==1) { // bit test port 0 pin 0 (mbed pin 9)
                a=0x20; // reverse the order of LED flashing...
                b=0x80; // based on the switch position
            
            } else {
                a=0x80;
                b=0x20;
            }
            
            FIO1PIN2 |= a; 
            delay(); 
                
            FIO1PIN2 &= ~a;
            delay(); 
            
            // blink the 2nd LED based on switch input position...
            for (i=1;i<=3;i++) {
                FIO1PIN2 |= b;
                delay();
                FIO1PIN2 &= ~b;
                delay();
                
                }
        } 
} 

// delay function 
void delay( void)
{
        int j; // loop variable j 
        for (j=0; j<10000000; j++) 
        { 
                j++; 
                j--; // waste time 
        } 
} 
