/* Program Example 12.7 : Ethernet write 
*/
#include "mbed.h" 
#include "Ethernet.h" 
Ethernet eth; // The Ethernet object 
char data[] ={ 0xB9,0x46}; // Define the data values 
int main() { 
	while (1) 
	{ 
		eth.write( data, 0x02); // Write the package 
		eth.send(); // Send the package 
		wait( 0.2); // wait 200 ms 
	} 
}
