//
//  CircularBuffer.cpp
//  
//
//  Created by Robert Plant on 11/18/14.
//
//
#include "mbed.h"

/**< Init Ciruclar Buffer */
#define SIZE 8

Serial pc(USBTX, USBRX);
InterruptIn button(p5);

typedef unsigned char INT8U;
typedef INT8U KeyType ;

typedef struct {
    INT8U size;
    INT8U mask;
    INT8U writePointer;
    INT8U readPointer;
    KeyType keys[0];
} CircularBuffer;



CircularBuffer* CircularBufferInit(CircularBuffer** pQue, int size)
{
    int sz = size*sizeof(KeyType)+sizeof(CircularBuffer);
    *pQue = (CircularBuffer*) malloc(sz);
    if(*pQue)
    {
        pc.printf("Init CircularBuffer: keys[%d] (%d)\n", size, sz);
        if( !(size & (size-1)) )
        { // must have size as power of 2
            // ie. 10000000 & 01111111 = 00000000
            (*pQue)->size=size;
            (*pQue)->mask=size-1;
            (*pQue)->writePointer = 0;
            (*pQue)->readPointer = 0;
        } else
        {
            printf("Error Size:%d is not power of TWO!\n", size);
        }
    }
    return *pQue;
}


inline int CircularBufferIsEmpty(CircularBuffer* que) {
    if (que->writePointer == que->readPointer) {
        return 1;
    }
    return 0;
}

inline int CircularBufferIsFull(CircularBuffer* que) {
    // If write pointer is pointing to the last empty space, then que is full
    if (( ((que->writePointer) + 1) & (que->mask) ) == (que->readPointer) ) {
        return 1;
    }
    return 0;
}

inline int CircularBufferEnqueue(CircularBuffer* que, KeyType k) {
    // Check that buffer is not full
    if (CircularBufferIsFull(que)) {
        return 0;
    }
    // else enqueue the data...
    que->keys[que->writePointer]=k;
    // increment writePointer using mask to wrap-around to 0 if at end.
    que->writePointer = ( ((que->writePointer)+1) & que->mask);
    return 1;
}

inline int CircularBufferDequeue(CircularBuffer* que, KeyType* pK) {
    // Check that buffer is not empty
    if (CircularBufferIsEmpty(que)) {
        return 0;
    }
    // else...
    // Read data at key[readPointer]
    *pK = que->keys[que->readPointer];
    // Increment readPointer using mask to wrap-around to 0 if at end.
    que->readPointer = ( ((que->readPointer)+1) & que->mask);
    return 1;
}

inline int CircularBufferPrint(CircularBuffer* que) {
    // Print warning if buffer is empty...
    if (CircularBufferIsEmpty(que) ) {
	pc.printf("Warning!  Can\'t print since buffer is empty!\n\r");
	return 0;
    }
    // Header...
    pc.printf("Printing Buffer --\n\r");
    int value;
    // readIndex is a temporary holder for que->readPointer
    KeyType readIndex = que->readPointer;
    while (readIndex != que->writePointer) {
        value=que->keys[readIndex];
        pc.printf("Address %u = 0x%02X\n\r", readIndex , value);
	readIndex=(readIndex+1) & (que->mask);
    }
    // Print out two final lines
    pc.printf("\n\n");
    return 1;
}
int main(void) {
    // Initialize pointer to cb:
    CircularBuffer** ptr2ptr;
    CircularBuffer* ptr;
    ptr2ptr = &ptr;
    
    // Initialize the circular buffer...
    CircularBufferInit(ptr2ptr, SIZE);

    // Reset screen for nice format
    pc.printf("\n\r\n\rNew Buffer Test\n\r");
    
    // Read characters from the keyboard...
    // r or R = read (deQueue mode) 
    // p or P = print buffer mode...
    KeyType keyChar;
    KeyType bufferChar;
    while (1) {
        keyChar=pc.getc();
	pc.printf("%c:  ", keyChar);
	// Echo entered key character to screen...
        switch (keyChar) {
            case 'r': case 'R': // read a character...
                if(CircularBufferDequeue(*ptr2ptr,&bufferChar)) {
                    pc.printf("popped %c off of the Buffer!\n\r", bufferChar);
                } else {
                    pc.printf("Buffer is empty!  No characters to retrieve.\n\r\n\r");
                }
                break;
            case 'p': case 'P':
                CircularBufferPrint(*ptr2ptr);
                break;
            case 'q': case 'Q':
                return 0;
            default: // Assume you want to write these char's to the Buffer
                if (CircularBufferEnqueue(*ptr2ptr,keyChar)) {
                    pc.printf("Added 0x%x to Buffer!\n\r", keyChar);
                } else { // Buffer is full
                    pc.printf("Buffer is full!  Couldn't add %c!\n\r", keyChar);
                }
                
        } // end, switch statement
        
    } // end, infinite while loop
} // end main
