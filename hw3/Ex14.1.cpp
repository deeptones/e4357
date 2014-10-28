// Program Example 14.1 : Sets up a digital output pin using control 
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







int main() 
{  
    FIO1DIR2 = 0xFF;
    // PINSEL3 =  0x00000000; // This should be the reset value but just to be sure...
    // PINMODE3 = 0x00000A20; // Ensure pull-up resistor enabled on all port1[31:16] pins
// set port 2, lowest byte to output 
        while(1) 
        {
            // FIO2PIN0 |= 0x01;  // OR bit 0 with 1 to set pin high
            FIO1PIN2 |= 0x80; 
            delay(); 
                
           // FIO2PIN0 &= ~0x01; // AND bit 0 with 0 to set pin low
            FIO1PIN2 &= ~0x80;
            delay(); 
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
