/* Program Example 12.8 : Ethernet read 
*/
#include "mbed.h" 
Ethernet eth; // Ethernet object 
Serial pc(USBTX, USBRX); // tx, rx for host terminal coms 
char buf[0xFF]; // create a large buffer to store data 
int main() 
{ 
	pc.printf("Ethernet data read and display\n\r"); 
	while (1) 
	{ 
		int size = eth.receive(); // get size of incoming data packet 
		if (size > 0) 
		{ // if packet received 
			eth.read (buf,size) ; // read packet to data buffer 
			pc.printf("size = %d data = ", size); // print to screen 
			for (int i = 0; i < size; i++) 
			{ // loop for each data byte 
				pc.printf("%02X" ,buf[i]); // print data to screen 
			} 
			pc.printf("\n\r"); 
		} 
	} 
}
