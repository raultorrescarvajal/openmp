---
layout: page
title:  "Directiva Task"
---
[Anterior](tasking-000.html) | [Siguiente](taskwait-000.html)

Las tareas pueden ser desplegadas dentro de diferentes contextos:
* Región paralela:
    * Por cada ocurrencia se crean tantas tareas como hilos.
* Región single
    * Por cada ocurrencia se crea una sola tarea.
    * Al final de la región hay una barrera implícita.
* Región master
    * Por cada ocurrencia se crea una sola tarea.
    * No hay una barrera implícita al final de la tarea.

## Sintaxis básica
```c
#pragma omp parallel
{
    <parallel region code>

    #pragma omp task
    {
        <task code>
    }
    
    <parallel region code>
    
    #pragma omp single
    {
        #pragma omp task
        {
            <task code>
        }
    } // implicit barrier here

    <parallel region code>
    
    #pragma omp master
    {
        #pragma omp task
        {
            <task code>
        }
    } // no barrier here

    <parallel region code>
} // implicit barrier here
```

## Ejemplo 1
El siguiente código va a imprimir el número del hilo que está ejecutando la tarea:
```c
#include <stdio.h>
#include <omp.h>

int main(){
    int m = omp_get_thread_num();
    printf("thread=%d in serial region\n", m);
    
    #pragma omp parallel 
    {
        int p = omp_get_thread_num();
        printf("thread=%d in parallel region is creating tasks\n", p);

        #pragma omp task
        {
            int t = omp_get_thread_num();
            printf("thread=%d executed this task\n", t);
        }
    } // implicit barrier here
    
    m = omp_get_thread_num();
    printf("thread=%d in serial region\n", m);
}
```
[Descarga el código aquí](../codigo/task-000.c).

### ¿Cómo compilar?
```bash
clang -fopenmp -I/home/user/llvm/llvm-build/projects/openmp/runtime/src/ 
     -o task-000 task-000.c
```
### ¿Cómo ejecutar?
```bash
./task-000 
```
### Salida
```bash
thread=0 in serial region
thread=0 in parallel region is creating tasks
thread=1 in parallel region is creating tasks
thread=2 in parallel region is creating tasks
thread=0 executed this task
thread=0 executed this task
thread=0 executed this task
thread=3 in parallel region is creating tasks
thread=2 executed this task
thread=0 in serial region
```
Todos los hilos crean una tarea pero solo 3 las ejecutan.

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

            #pragma omp task
            {
                int t = omp_get_thread_num();
                printf("thread=%d executed task A\n", t);
            }

            #pragma omp task
            {
                int t = omp_get_thread_num();
                printf("thread=%d executed task B\n", t);
            }
        } // implicit barrier here
    } // implicit barrier here
    
    m = omp_get_thread_num();
    printf("thread=%d in serial region\n", m);
}
```
[Descarga el código aquí](../codigo/task-001.c).

### ¿Cómo compilar?
```bash
clang -fopenmp -I/home/user/llvm/llvm-build/projects/openmp/runtime/src/ 
     -o task-001 task-001.c
```
### ¿Cómo ejecutar?
```bash
./task-001
```
### Salida
```bash
thread=0 in serial region
thread=0 in single region is creating tasks
thread=3 executed task A
thread=2 executed task B
thread=0 in serial region
```
Solo 1 hilo crea las tareas, mientras que otros 2 hilos las ejecutan.

## Ejemplo 3
El siguiente código va a crear tareas de manera secuencial en el hilo maestro:
```c
#include <stdio.h>
#include <omp.h>

int main(){
    int m = omp_get_thread_num();
    printf("thread=%d in serial region\n", m);
    
    #pragma omp parallel 
    {
        #pragma omp master
        {
            int s = omp_get_thread_num();
            printf("thread=%d in master region is creating tasks\n", s);

            #pragma omp task
            {
                int t = omp_get_thread_num();
                printf("thread=%d executed task A\n", t);
            }

            #pragma omp task
            {
                int t = omp_get_thread_num();
                printf("thread=%d executed task B\n", t);
            }
        } // no barrier here
        
        int p = omp_get_thread_num();
        printf("thread=%d has arrived\n", p);
    } // implicit barrier here
    
    m = omp_get_thread_num();
    printf("thread=%d in serial region\n", m);
}
```
[Descarga el código aquí](../codigo/task-002.c).

### ¿Cómo compilar?
```bash
clang -fopenmp -I/home/user/llvm/llvm-build/projects/openmp/runtime/src/ 
     -o task-002 task-002.c
```
### ¿Cómo ejecutar?
```bash
./task-002
```
### Salida
```bash
thread=0 in serial region
thread=0 in master region is creating tasks
thread=2 has arrived
thread=1 has arrived
thread=3 has arrived
thread=1 executed task A
thread=0 has arrived
thread=2 executed task B
thread=0 in serial region
```
Solo el hilo maestro crea las tareas, mientras que otros 2 hilos las ejecutan.
La ejecución paralela continúa después de la región máster, independientemente de si las tareas han terminado su ejecución o no.

## Preguntas
* _Reemplaza el mecanismo de tareas por el mecanismo de secciones._
* _¿Qué dificultades encontraste?_

[Anterior](tasking-000.html) | [Siguiente](taskwait-000.html)

<div class=coursetitle>Estás en el Nivel 2: Bucles paralelos y tareas concurrentes con OpenMP. <a href="main.html">¿Deseas volver al inicio?</a> </div>