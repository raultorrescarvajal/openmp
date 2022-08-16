---
layout: page
title:  "Directivas Sections and Section"
---
[Anterior](parallel-000.html) | [Siguiente](practice1-000.html)

Con estas directivas podemos asignar diferentes porciones del código de una región paralela a diferentes hilos.
La asignación de hilos a secciones se hace de manera rotatoria (round-robin fashion).

#### Sintaxis básica
```c
<serial region code>
#pragma omp parallel
{
    #pragma omp sections
    {
        #pragma omp section
        {
        }

        #pragma omp section
        {
        }
    } // implicit barrier here
} 
<serial region code>
```
...

#### Ejemplo:
Vamos a ejecutar 3 secciones diferentes en paralelo:
```c
#include <stdio.h>
#include <omp.h>

int main(){
    int m = omp_get_thread_num();
    printf("thread=%d in serial region\n", m);
    
    #pragma omp parallel 
    {
        #pragma omp sections
        {
            #pragma omp section
            {
                int t = omp_get_thread_num();
                printf("Section 0 executed by thread=%d\n", t);
            }

            #pragma omp section
            {
                int t = omp_get_thread_num();
                printf("Section 1 executed by thread=%d\n", t);
            }

            #pragma omp section
            {
                int t = omp_get_thread_num();
                printf("Section 2 executed by thread=%d\n", t);
            }
        } // implicit barrier here
    } 
    
    m = omp_get_thread_num();
    printf("thread=%d in serial region\n", m);
}
```
[Descarga el código aquí](../codigo/sections-000.c).

##### ¿Cómo compilar?
```bash
clang -fopenmp -I/home/user/llvm/llvm-build/projects/openmp/runtime/src/ 
     -o sections-000 sections-000.c
```
##### ¿Cómo ejecutar?
```bash
./sections-000 
```
##### Salida 1
```bash
thread=0 in serial region
Section 0 executed by thread=0
Section 2 executed by thread=2
Section 1 executed by thread=1
thread=0 in serial region
```

##### Salida 2
```bash
thread=0 in serial region
Section 2 executed by thread=2
Section 0 executed by thread=0
Section 1 executed by thread=1
thread=0 in serial region
```
* Cada sección fue ejecutada por un hilo diferente de manera paralela.
* La asignación de las secciones a los hilos del equipo se hizo de manera rotatoria, por lo que en ejecuciones diferentes, los hilos siempre se encargarán de la misma sección: hilo 0 con sección 0, hilo 1 con sección 1, etc...

## Preguntas
* _¿En qué situaciones la estrategia de asignación rotatoria puede resultar siendo ineficiente?_
* _Modifica el programa de tal manera que haya una sección para cada hilo._

[Anterior](parallel-000.html) | [Siguiente](practice1-000.html)

<div class=coursetitle>Estás en el Nivel 1: Introducción a la programación paralela con OpenMP. <a href="main.html">¿Deseas volver al inicio?</a> </div>