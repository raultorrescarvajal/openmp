/* Copyright (C) 2022 Raul Torres raultorrescarvajal@gmail.com */

#include <stdio.h>
#include <omp.h>

int main(){
    int m = omp_get_thread_num();
    printf("thread=%d in serial region\n", m);
    
    #pragma omp parallel 
    {
        #pragma omp single
        {
            int s = omp_get_thread_num();
            printf("thread=%d in single region is creating tasks\n", s);
            
            #pragma omp taskloop
            for(int i=0; i<16; i++)
            {
                int t = omp_get_thread_num();
                printf("thread=%d executed iteration %d\n", t, i);
                
            } // implicit barrier here

            #pragma omp task
            {
                int t = omp_get_thread_num();
                printf("thread=%d executed final task\n", t);
            }
        } // implicit barrier here
    } // implicit barrier here
    
    m = omp_get_thread_num();
    printf("thread=%d in serial region\n", m);
}