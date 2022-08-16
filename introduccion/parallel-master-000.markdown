---
layout: page
title:  "Directiva combinada Parallel Master"
---
[Anterior](master-000.html) | [Siguiente](critical-000.html)

A veces es necesario que, de entrada, en una región paralela, el hilo maestro asuma el control y despache **tareas** de manera asíncrona a los demás hilos.Todos los hilos se sincronizan al finalizar la región (barrera implícita). Veremos el despacho de tareas más adelante en el taller.

## Sintaxis básica
```c
#pragma omp parallel master
{
    <serial region code with task dispatching>
}
``` 
## Ejemplo
El hilo maestro se encarga de despachar tareas a los demás hilos:
```c
#include <stdio.h>
#include <omp.h>

int main(){
    int m = omp_get_thread_num();
    printf("master thread=%d in serial region\n", m);
    
    #pragma omp parallel master
    {
        int t = omp_get_thread_num();
        printf("thread=%d in parallel region\n", t);
        
        #pragma omp task
        {
            int s = omp_get_thread_num();
            printf("thread=%d in task region\n", s);
        }
        #pragma omp task
        {
            int s = omp_get_thread_num();
            printf("thread=%d in task region\n", s);
        }
        #pragma omp task
        {
            int s = omp_get_thread_num();
            printf("thread=%d in task region\n", s);
        }
    } // implicit barrier here
    
    printf("master thread=%d in serial region\n", m);
}
```
[Descarga el código aquí](../codigo/parallel-master-000.c).

### ¿Cómo compilar?
```bash
clang -fopenmp -I/home/user/llvm/llvm-build/projects/openmp/runtime/src/ 
     -o parallel-master-000 parallel-master-000.c
```
### ¿Cómo ejecutar?
```bash
./parallel-master-000 
```
### Salida
```bash
master thread=0 in serial region
thread=0 in parallel region
thread=3 in task region
thread=0 in task region
thread=1 in task region
master thread=0 in serial region
```
En este caso el hilo maestro asumió el control de la región, y despachó tareas a todos los hilos, incluido a sí mismo. Por eso, hilo 2 no participó. 

## Preguntas

* _¿A qué directiva de las ya estudiadas se asemeje la directiva task?_

[Anterior](master-000.html) | [Siguiente](critical-000.html)

<div class=coursetitle>Estás en el Nivel 1: Introducción a la programación paralela con OpenMP. <a href="main.html">¿Deseas volver al inicio?</a> </div>