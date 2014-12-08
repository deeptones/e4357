/* Use mbed timeout to communicate with ZigBee module connected serially to p9,p10 (tx,rx). 
Using Coolterm terminal to test. 
Timeout is called every TIMEOUT seconds */

#include "mbed.h" 
#include <stdio.h>
#define TIMEOUT 0.25 // Max time to wait for checking if any response from ZigBee. 

Serial pc( USBTX, USBRX); // Serial port for USB (Terminal) communication.
Serial zigBee(p9,p10);    // Serial port for mbed to ZigBee communication.
DigitalOut myled(LED1); // LED1 lights up when ISR is accessed every TIMEOUT.

Timeout checkResponse;  // Timer-generated interrupt to check for response from zigBee.
int timeoutAttached=0;  // Gets set in main.  Gets unset after calling ISR.

// zBeeRespond() - interrupt service routine for timer interrupt
void zBeeRespond() {
    // unset timeoutAttached since no longer attached since this ISR was called.
    timeoutAttached=0;
    char zBOut;
    if(zigBee.readable()==1) 
    {
//        pc.printf("\n\r"); // Put ZigBee response on its own new line.
        while(zigBee.readable()==1) {
            zBOut = zigBee.getc();
            pc.putc(zBOut);  // Transfer ZigBee response to terminal output.
        } // end of while readable
        // output new line for typed characters...
   //     pc.printf("\n\r");
    } // end of if readable block
    // Switch LED
    wait(0.1);
    myled=!myled;
} // End of ZBeeRespond method.

int main() 
{ 
    char pcTx;
    checkResponse.attach(&zBeeRespond, TIMEOUT);
    while(1) {
        // Attach ISR to timeout if not already attached.
        if(timeoutAttached == 0) {
            checkResponse.attach(&zBeeRespond, TIMEOUT);  // Should check every 0.25 seconds for output.
            timeoutAttached=1; // only attach once for every timeout event.
        } // end if timeoutAttached.
        // if I entered data into terminal, transfer to ZigBee and echo to terminal.
        while(pc.readable()==1) {
            // Write char to ZigBee:
            pcTx=pc.getc();
            zigBee.putc(pcTx);
            // Echo char to terminal:
            pc.putc(pcTx);
        } // end while(pc.readable()==1)
    } // end while(1)
}
