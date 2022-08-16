---
layout: page
title:  "Directiva Critical"
---
[Anterior](parallel-master-000.html) | [Siguiente](atomic-000.html)

A veces es necesario que una parte del código paralelo sea ejecutada por los hilos de uno a uno, para evitar una condición de carrera al actualizar una variable compartida.
Un único hilo entra a la región crítica y los demás esperan hasta que ese hilo salga de ella. El hilo que termina no espera al final de la región crítica sino que continúa hasta la siguiente barrera.

## Sintaxis básica
```c
#pragma omp parallel
{
    <parallel region code>
    #pragma omp critical
    { // enter one by one
        <critical code>
    } // no barrier here
    <parallel region code>
} // implicit barrier here
``` 
## Ejemplo 1
Vamos a contar cuántos hilos entran a la región crítica:
```c
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
        
        #pragma omp critical
        {
            int s = omp_get_thread_num();
            printf("thread=%d in critical region\n", s);
            count++;
            printf("thread_count=%d\n", count);
        }
        
        printf("thread=%d says goodbye\n", t);
    } // implicit barrier here
    
    printf("master thread=%d in serial region\n", m);
}
```
[Descarga el código aquí](../codigo/critical-000.c).

### ¿Cómo compilar?
```bash
clang -fopenmp -I/home/user/llvm/llvm-build/projects/openmp/runtime/src/ 
     -o critical-000 critical-000.c
```
### ¿Cómo ejecutar?
```bash
./critical-000 
```
### Salida
```bash
master thread=0 in serial region
thread=0 in parallel region
thread=1 in parallel region
thread=0 in critical region
thread_count=1
thread=0 says goodbye
thread=3 in parallel region
thread=2 in parallel region
thread=1 in critical region
thread_count=2
thread=1 says goodbye
thread=3 in critical region
thread_count=3
thread=3 says goodbye
thread=2 in critical region
thread_count=4
thread=2 says goodbye
master thread=0 in serial region
```
Cada hilo entra a la sección crítica solo y actualiza el contador. La región crítica garantiza que el contador sea 4.

## Ejemplo 2
Ahora vamos a contar cuántos hilos entran a la región no crítica:
```c
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
        
        {
            int s = omp_get_thread_num();
            printf("thread=%d in non-critical region\n", s);
            count++;
            printf("thread_count=%d\n", count);
        }
        
        printf("thread=%d says goodbye\n", t);
    } // implicit barrier here
    
    printf("master thread=%d in serial region\n", m);
}
```
[Descarga el código aquí](../codigo/critical-001.c).

### ¿Cómo compilar?
```bash
clang -fopenmp -I/home/user/llvm/llvm-build/projects/openmp/runtime/src/ 
     -o critical-001 critical-001.c
```
### ¿Cómo ejecutar?
```bash
./critical-001 
```
### Salida
```bash
master thread=0 in serial region
thread=0 in parallel region
thread=0 in non-critical region
thread_count=1
thread=1 in parallel region
thread=1 in non-critical region
thread_count=2
thread=1 says goodbye
thread=3 in parallel region
thread=3 in non-critical region
thread=0 says goodbye
thread=2 in parallel region
thread=2 in non-critical region
thread_count=4
thread=2 says goodbye
thread_count=3
thread=3 says goodbye
master thread=0 in serial region
```
Los hilos pueden entrar a la sección no crítica sin restricciones y todos pueden actualiza el contador. No hay garantía de que el contador al final sea 4.

## Preguntas
* _¿Con qué otro nombre se puede describir la funcionalidad de la directiva critical?_
* _Modifica el programa de tal manera que la mitad de los hilos decrementen el contador y la otra mitad lo incrementen._
* _¿Qué valor tiene el contador al final del programa?_

[Anterior](parallel-master-000.html) | [Siguiente](atomic-000.html)

<div class=coursetitle>Estás en el Nivel 1: Introducción a la programación paralela con OpenMP. <a href="main.html">¿Deseas volver al inicio?</a> </div>