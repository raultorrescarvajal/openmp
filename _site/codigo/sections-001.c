/* Copyright (C) 2022 Raul Torres raultorrescarvajal@gmail.com */

#include <stdio.h>
#include <omp.h>

int main(){
    int m = omp_get_thread_num();
    printf("thread=%d in serial region\n", m);
    
    #pragma omp parallel 
    {
        #pragma omp sections
        {
            int num_threads = omp_get_num_threads();
            for(int i=0; i<num_threads; i++)
            {
                #pragma omp section
                {
                    int t = omp_get_thread_num();
                    printf("Section %d executed by thread=%d\n", i, t);
                }
            }
        } // implicit barrier here
    } 
    
    m = omp_get_thread_num();
    printf("thread=%d in serial region\n", m);
}