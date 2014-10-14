//
//  MultiplyMatrixVector.c
//  Created by Robert Plant on 10/7/14.
//

#include <stdio.h>

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
            double Val = (m[j]) * r[j];
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
    // Declare and define a matrix
    double M[][4] = {{1,2,3,4},{5,6,7,8},{9,10,11,12},{13,14,15,16}};
    double V[4]={1.5,2.5,3.5,4.5};

    // Multiply matrix x vector
    next_rank(M[0], V,4);

    // index declaration
    int val = 0;

    for (val = 0; val < 4; val++) {
       printf("Val[%d] = %.2f \n",val+1,V[val]);
    }
    
    return 0;
}
