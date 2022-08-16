/* Copyright (C) 2022 Raul Torres raultorrescarvajal@gmail.com */

#include <stdio.h>
#include <omp.h>

int main(){
    int A[4][4]= { {0 , 1, 2, 3},{ 4, 5, 6, 7},{8, 9,10,11},{12,13,14,15} };
    int B[4][4]= { {15,14,13,12},{11,10, 9, 8},{7, 6, 5, 4},{ 3, 2, 1, 0} };
    int C[4][4]= { {},{},{},{} };

    int offset=33;

    int thisOffset=0;

    #pragma omp parallel for collapse(2) shared(A, B, C) firstprivate(offset) lastprivate(thisOffset) schedule(static,5)
    for(int i=0;i<4;i++){
    	for(int j=0;j<4;j++){
            thisOffset = offset * (i*4 + j);  
            C[i][j] = A[i][j] - B[i][j] + thisOffset;
            printf("C[%d][%d]=%d, thisOffset=%d, thread=%d\n", i, j, C[i][j], thisOffset, omp_get_thread_num());
            }
    }

    printf("thisOffset=%d\n", thisOffset);
}
