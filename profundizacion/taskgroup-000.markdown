---
layout: page
title:  "Directiva Taskgroup"
---
[Anterior](taskwait-000.html) | [Siguiente](taskloop-000.html)

Esta directiva se usa para lograr sincronizar las tareas desplegadas dentro de un bloque  específico.
A diferencia de **taskwait**, las sub-tareas desplegadas sí se sincronizan.

## Sintaxis básica
```c
#pragma omp parallel
{
    <parallel region code>
    
    #pragma omp single
    {
        #pragma omp taskgroup
        {
            #pragma omp task
            {
                <task code>
            }

            #pragma omp task
            {
                <task code>
            }
        } // implicit barrier here
        
        #pragma omp task
        {
            <task code>
        }
    } // implicit barrier here

    <parallel region code>
} // implicit barrier here
```
## Ejemplo
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
            
            #pragma omp taskgroup
            {
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

            #pragma omp task
            {
                int t = omp_get_thread_num();
                printf("thread=%d executed task C\n", t);
            }
        } // implicit barrier here
    } // implicit barrier here
    
    m = omp_get_thread_num();
    printf("thread=%d in serial region\n", m);
}
```
[Descarga el código aquí](../codigo/taskgroup-000.c).

### ¿Cómo compilar?
```bash
clang -fopenmp -I/home/user/llvm/llvm-build/projects/openmp/runtime/src/ 
     -o taskgroup-000 taskgroup-000.c
```
### ¿Cómo ejecutar?
```bash
./taskgroup-000
```
### Salida
```bash
thread=0 in serial region
thread=0 in single region is creating tasks
thread=0 executed task B
thread=0 executed task A
thread=0 executed task C
thread=0 in serial region
```
Gracias a la región taskgroup, la tarea C siempre se va a ejecutar después de A y B.

## Preguntas
* _Agrega una sub-tarea a las tareas A y B._
* _¿Las sub-tareas se sincronizaron con taskgroup?_

[Anterior](taskwait-000.html) | [Siguiente](taskloop-000.html)

<div class=coursetitle>Estás en el Nivel 2: Bucles paralelos y tareas concurrentes con OpenMP. <a href="main.html">¿Deseas volver al inicio?</a> </div>