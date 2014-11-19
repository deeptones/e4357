//
//  CircularQueue.c
//  
//
//  Created by Robert Plant on 11/18/14.
//
//

#include "CircularQueue.h"
/**< Init Ciruclar Buffer */
#define WAIT_Time 1s
#define SIZE 8

#include "mbed.h"
Serial pc(USBTX, USBRX);
InterruptIn button(p5);

typedef unsigned char INT8U;

typedef struct {
    unsigned char size;
    unsigned char mask
    unsigned char* writePointer;
    unsigned char* readPointer;
    KeyType keys[0];
} CircularBuffer;


static INT8U newVal = 0;

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
    if (( ((que->writePointer))+ 1 && (que->mask) ) == que->readPointer ) {
        return 1;
    }
    return 0;
}

inline int CircularBufferEnque(CircularBuffer* que, KeyType k) {
    // Check that buffer is not full
    if (CircularBufferIsFull(que)) {
        return 0;
    }
    // else enqueue the data...
    que->key[que->writePointer]=k;
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
    *pK = que->key[que->readPointer];
    // Increment readPointer using mask to wrap-around to 0 if at end.
    que->readPointer = ( ((que->readPointer)+1) & que->mask);
    return 1;
}

inline int CircularBufferPrint(CircularBuffer* que) {
    int value;
    int readIndex;
    while (que->readPointer != que->writePointer) {
        
        
        readIndex=que->readPointer;
        value=que->k[readIndex];
        pc.printf("Address %u = 0x%x\n", readIndex , value);
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
    
    int mode; // 0 == read mode, 1 == write mode
    
    // Read characters from the keyboard...
    // r or R = read (deQueue mode) (mode = 0)
    // w or W = write (enQueue mode)(mode = 1)
    // p or P = print buffer mode...
    char keyChar;
    char bufferChar;
    while (1) {
        keyChar=pc.getc();
        switch (keyChar) {
            case 'r'; case 'R':
                mode=0;
                break;
            case 'w': case 'W':
                mode=1;
                break;
            case 'p': case 'P':
                CircularBufferPrint(ptr);
                break;
            case 'q': case 'Q':
                return 0;
            default:
                if (mode == 0) { // enqueue any characters..
                    if(CircularBufferDequeue(ptr,keyChar)) {
                        pc.printf("popped %s off of the Buffer!\n\r", keyChar);
                    } else {
                        pc.printf("Buffer is empty!  No characters to retrieve."\n\r\n\r);
                    }
                    
                } else { // if mode ==1 meaning write...
                    if (CircularBufferEnqueue(ptr,Character)) {
                        pc.printf("Added %s to Buffer!\n\r", Character);
                    } else { // Buffer is full
                        pc.printf("Buffer is full!  Couldn't add %s!\n\r", keyChar);
                    }
                } // end, write mode for default case
                
        } // end, switch statement
        
    } // end, infinite while loop
} // end main

        
        pc.printf(); # Write string to terminal
        pc.putc(); # write ascii code
        pc.getc(); # retrieve ascii code
        
    }
    
    
}



