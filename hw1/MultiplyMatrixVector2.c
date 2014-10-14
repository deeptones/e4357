//
//  MultiplyMatrixVector.c
//  Created by Robert Plant on 10/7/14.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

void next_rank(double *m, /*input */

               double *r, /*input and output */
               int n) {
    double temp[n]; // For storing the answers...
    // index declarations
    int i = 0;
    int j = 0;

    for (i = 0; i < n ; i++) {
        temp[i] = 0;  // initialize...
        for (j=0; j< n; j++) {
            double Val = ( m[j]) * r[j] ;
            temp[i] += Val;
            
        }
        // Store the result
        // increment m pointer to point to next row
        // m += sizeof(double [n]);
        m += n;
        
    }
    
    // Store all results back into r vector:
    for (j=0; j<n ; j++) {
        r[j]=temp[j];
        
    }
}




int main(int argc, const char * argv[]) {
    // User input of n, and nxn matrix elements, followed by n vector elements
    // Alternate matrix representation
    // Check for correct number of inputs
    char Usage[] = "Usage:  ./a.out <n>, M[1][1], M[1][2], ...M[n][n], V[1], ...V[n]\n";
    int n = atoi(argv[1]);
    if (argc != (2+(n+1)*n)) {
       printf("Incorrect number of inputs!  You must specify n and correct number of:\n    matrix elements (nxn) and \n    vector elements (n) to do setup M x V\n");
       printf("You specified n=%d  so you need %d real arguments.\n",n,1+((n+1)*n));
       printf("%s",Usage);
       return 9;
    }
    int Index=0;
    // Declare Matrix 
    double Matrix[n*n];
    // Declare Vector
    double Vector[n];

    // Read in values for Matrix[]
    for (Index = 2; Index < argc-n; Index++) {
    	Matrix[Index-2] = strtod(argv[Index],NULL);
    }

    // Read in values for Vector[]
    for (Index = argc-n; Index < argc; Index++) {
    	Vector[Index-(argc-n)] = strtod(argv[Index],NULL);
    }

    // Perform multiplication
    next_rank(Matrix,Vector,n);
	

   // Print out nice looking Matrix x Vector = Answer

   // Declare loop indices
   int Row = 0;
   int Col = 0;

   // Row loop
   for (Row=0; Row<n; Row++) {
   	// Col loop
	// open matrix
	printf("[ ");
	for (Col=0; Col<n; Col++) {
		printf("%*.*f ",7,2,Matrix[Col+n*Row]);
	}

	// close matrix
	printf("] ");

	if (Row == (int) n/2) {
		printf("x [ ");
	} else {
		printf("  [ ");
	}

	// print Vector
	printf("%*.*f ] ",7,2, strtod(argv[2+(n*n)+Row],NULL));

   	// print Answer
   	if (Row == (int) n/2) {
   		printf("= [ ");
   	} else {
   		printf("  [ ");
   	}
   
   	printf("%*.*f ]\n", 7, 2, Vector[Row]);


   }


   

    return 0;
}
