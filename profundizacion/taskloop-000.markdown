---
layout: page
title:  "Directiva Taskloop"
---
[Anterior](taskgroup-000.html) | [Siguiente](depend-000.html)

Esta directiva se usa para emitir tareas basadas en un bucle.
El cuerpo del bucle constituye el cuerpo de cada tarea emitida.
Por defecto, cada iteración es una tarea.

## Sintaxis básica
```c
#pragma omp parallel
{ 
    <parallel region code>

    #pragma omp single
    {
        #pragma omp taskloop
        for(...)
        {
            <loop body>
        } // implicit barrier here

        #pragma omp taskloop nogroup
        for(...)
        {
            <loop body>
        } // no barrier here
    } // implicit barrier here

    <parallel region code>
} // implicit barrier here
```
## Ejemplo 1
El siguiente código va a crear tareas de manera secuencial:
```c
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
```
[Descarga el código aquí](../codigo/taskloop-000.c).

### ¿Cómo compilar?
```bash
clang -fopenmp -I/home/user/llvm/llvm-build/projects/openmp/runtime/src/ 
     -o taskloop-000 taskloop-000.c
```
### ¿Cómo ejecutar?
```bash
./taskloop-000
```
### Salida
```bash
thread=0 in serial region
thread=0 in single region is creating tasks
thread=1 executed iteration 0
thread=0 executed iteration 15
thread=0 executed iteration 14
thread=2 executed iteration 1
thread=2 executed iteration 4
thread=2 executed iteration 5
thread=2 executed iteration 6
thread=2 executed iteration 7
thread=2 executed iteration 8
thread=1 executed iteration 3
thread=3 executed iteration 2
thread=3 executed iteration 11
thread=3 executed iteration 12
thread=0 executed iteration 13
thread=2 executed iteration 9
thread=1 executed iteration 10
thread=3 executed final task
thread=0 in serial region
```
Se crean 16 tareas, una por cada iteración, asignadas al primer hilo disponible en ese momento.
La tarea final siempre se ejecuta después del taskloop, dado la barrera implícita.

## Ejemplo 2
El siguiente código va a crear tareas de manera secuencial:
```c
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
            
            #pragma omp taskloop nogroup
            for(int i=0; i<16; i++)
            {
                int t = omp_get_thread_num();
                printf("thread=%d executed iteration %d\n", t, i);
                
            } // no barrier here anymore

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
```
[Descarga el código aquí](../codigo/taskloop-001.c).

### ¿Cómo compilar?
```bash
clang -fopenmp -I/home/user/llvm/llvm-build/projects/openmp/runtime/src/ 
     -o taskloop-001 taskloop-001.c
```
### ¿Cómo ejecutar?
```bash
./taskloop-001
```
### Salida
```bash
thread=0 in serial region
thread=0 in single region is creating tasks
thread=3 executed iteration 0
thread=2 executed iteration 1
thread=3 executed iteration 3
thread=0 executed final task
thread=2 executed iteration 4
thread=3 executed iteration 5
thread=3 executed iteration 7
thread=1 executed iteration 2
thread=1 executed iteration 9
thread=1 executed iteration 10
thread=1 executed iteration 11
thread=1 executed iteration 12
thread=3 executed iteration 8
thread=3 executed iteration 14
thread=2 executed iteration 6
thread=1 executed iteration 13
thread=0 executed iteration 15
thread=0 in serial region
```
Se crean 16 tareas, una por cada iteración, asignadas al primer hilo disponible en ese momento.
La tarea final se ejecuta asíncronamente junto con las del taskloop, dado la cláusula `nogroup`.

## Ejemplo 3
El siguiente código va a crear tareas de manera secuencial:
```c
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
            
            #pragma omp taskloop num_tasks(3)
            for(int i=0; i<16; i++)
            {
                int t = omp_get_thread_num();
                printf("thread=%d executed iteration %d\n", t, i);
                
            } // implicit barrier here
        } // implicit barrier here
    } // implicit barrier here
    
    m = omp_get_thread_num();
    printf("thread=%d in serial region\n", m);
}
```
[Descarga el código aquí](../codigo/taskloop-002.c).

### ¿Cómo compilar?
```bash
clang -fopenmp -I/home/user/llvm/llvm-build/projects/openmp/runtime/src/ 
     -o taskloop-002 taskloop-002.c
```
### ¿Cómo ejecutar?
```bash
./taskloop-002
```
### Salida
```bash
thread=0 in serial region
thread=2 in single region is creating tasks
thread=0 executed iteration 0
thread=1 executed iteration 6
thread=1 executed iteration 7
thread=1 executed iteration 8
thread=1 executed iteration 9
thread=1 executed iteration 10
thread=2 executed iteration 11
thread=2 executed iteration 12
thread=2 executed iteration 13
thread=2 executed iteration 14
thread=2 executed iteration 15
thread=0 executed iteration 1
thread=0 executed iteration 2
thread=0 executed iteration 3
thread=0 executed iteration 4
thread=0 executed iteration 5
thread=0 in serial region
```
Se crean solo 3 tareas al tiempo, una por cada iteración, asignadas al primer hilo disponible en ese momento.

## Ejemplo 4
```c
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
            
            #pragma omp taskloop grainsize(4)
            for(int i=0; i<16; i++)
            {
                int t = omp_get_thread_num();
                printf("thread=%d executed iteration %d\n", t, i);
                
            } // implicit barrier here
        } // implicit barrier here
    } // implicit barrier here
    
    m = omp_get_thread_num();
    printf("thread=%d in serial region\n", m);
}
```
[Descarga el código aquí](../codigo/taskloop-003.c).

### ¿Cómo compilar?
```bash
clang -fopenmp -I/home/user/llvm/llvm-build/projects/openmp/runtime/src/ 
     -o taskloop-003 taskloop-003.c
```
### ¿Cómo ejecutar?
```bash
./taskloop-003
```
### Salida
```bash
thread=0 in serial region
thread=0 in single region is creating tasks
thread=1 executed iteration 0
thread=1 executed iteration 1
thread=1 executed iteration 2
thread=1 executed iteration 3
thread=2 executed iteration 4
thread=2 executed iteration 5
thread=2 executed iteration 6
thread=2 executed iteration 7
thread=0 executed iteration 12
thread=0 executed iteration 13
thread=0 executed iteration 14
thread=0 executed iteration 15
thread=3 executed iteration 8
thread=3 executed iteration 9
thread=3 executed iteration 10
thread=3 executed iteration 11
thread=0 in serial region
```
Se crean 4 tareas de 4 iteraciones cada una, asignadas al primer hilo disponible en ese momento.

## Preguntas 
* _Experimenta con diferentes valores de grainsize y num_tasks_

[Anterior](taskgroup-000.html) | [Siguiente](depend-000.html)

<div class=coursetitle>Estás en el Nivel 2: Bucles paralelos y tareas concurrentes con OpenMP. <a href="main.html">¿Deseas volver al inicio?</a> </div>