/* Copyright (C) 2022 Raul Torres raultorrescarvajal@gmail.com */

#include <stdio.h>
#include <omp.h>

int main(){
    int m = omp_get_thread_num();
    printf("master thread=%d in serial region\n", m);
    int count = 0;

    #pragma omp parallel
    {
        int t = omp_get_thread_num();
        printf("thread=%d in parallel region\n", t);
        if(t<2) {
            #pragma omp critical
            {
                int s = omp_get_thread_num();
                printf("thread=%d in critical region\n", s);
                count++;
                printf("count=%d\n", count);
            }
        } else {
            #pragma omp critical
            {
                int s = omp_get_thread_num();
                printf("thread=%d in critical region\n", s);
                count--;
                printf("count=%d\n", count);
            }
        }
        
        printf("thread=%d says goodbye\n", t);
    } // implicit barrier here
    
    printf("final count=%d\n", count);
    printf("master thread=%d in serial region\n", m);
}