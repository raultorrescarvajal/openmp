---
layout: page
title:  "Directiva Parallel"
---
[Anterior](modelo-000.html) | [Siguiente](sections-000.html)

La directiva Parallel es la base de OpenMP.
Sin ella, el programa seguirá siendo secuencial.

Esta es la directiva que le indica al programa que se ha llegado a una región paralela. Al encontrarla, se crean nuevos hilos que ejecutarán el código contenido dentro de la región en paralelo. 

Existe una barrera al final de la región paralela: esto significa que el hilo maestro no continuará más allá de esa región sino hasta que todos los demás hilos del equipo hayan llegado al final también.
Se dice que esta barrera es implícita, porque no está escrita de manera específica en el código.
Por tal motivo siempre es importante al aprender nuevas directivas si éstas tienen una barrera implícita o no.
En el caso de la directiva Parallel, ésta tiene una barrera implícita al final de la región.

## Sintaxis básica
```c
<serial region code>
#pragma omp parallel
{
    <parallel region code>
} // implicit barrier here
<serial region code>
```
La llave de apertura indica el inicio de la región paralela y la llave de cierre indica su fin. 
El código entre las llaves será ejecutado por todos los hilos creados.

## Ejemplo 1:
El siguiente código va a imprimir el número del hilo que está ejecutando la región correspondiente:
```c
#include <stdio.h>
#include <omp.h>

int main(){
    int m = omp_get_thread_num();
    printf("thread=%d in serial region\n", m);
    
    #pragma omp parallel 
    {
        int t = omp_get_thread_num();
        printf("thread=%d in parallel region\n", t);
    } // implicit barrier here
    
    m = omp_get_thread_num();
    printf("thread=%d in serial region\n", m);
}
```
[Descarga el código aquí](../codigo/parallel-000.c).

### ¿Cómo compilar?
```bash
clang -fopenmp -I/home/user/llvm/llvm-build/projects/openmp/runtime/src/ 
     -o parallel-000 parallel-000.c
```
### ¿Cómo ejecutar?
```bash
./parallel-000 
```
### Salida
```bash
thread=0 in serial region
thread=0 in parallel region
thread=2 in parallel region
thread=3 in parallel region
thread=1 in parallel region
thread=0 in serial region
```
* Vemos que antes de encontrar la región paralela demarcada por la anotación `#pragma omp parallel` solo el hilo maestro está participando (thread=0). 
* Dentro de la región paralela, se crean 3 hilos más, y tanto éstos cómo el hilo maestro participan en la ejecución. 
* Una vez todos los hilos han llegado al final de la región paralela, sólo el hilo maestro continúa con la ejecución de la subsiguiente región secuencial (thread=0).
* El final de la región paralela, delimitado por la llave de cierre, constituye una barrera implícita donde los hilos que ya terminaron la ejecución, esperan a los que todavía no.
* El orden de impresión dentro de la región paralela es indeterminado.

## Ejemplo 2:
Podemos controlar el número de hilos involucrados en el cálculo con la cláusula **num_threads**:
```c
#include <stdio.h>
#include <omp.h>

int main(){
    int m = omp_get_thread_num();
    printf("thread=%d in serial region\n", m);
    
    #pragma omp parallel num_threads(2)
    {
        int t = omp_get_thread_num();
        printf("thread=%d in parallel region\n", t);
    }
    
    m = omp_get_thread_num();
    printf("thread=%d in serial region\n", m);
}
```
[Descarga el código aquí](../codigo/parallel-001.c).

### ¿Cómo compilar?
```bash
clang -fopenmp -I/home/user/llvm/llvm-build/projects/openmp/runtime/src/ 
     -o parallel-001 parallel-001.c
```
### ¿Cómo ejecutar?
```bash
./parallel-001
```
### Salida
```bash
thread=0 in serial region
thread=1 in parallel region
thread=0 in parallel region
thread=0 in serial region
```
Vemos que sólo los hilos 0 y 1 participaron en la ejecución de la región paralela.

## Preguntas
* _Modifica el programa de tal manera que cada hilo ejecute una operación diferente._

[Anterior](modelo-000.html) | [Siguiente](sections-000.html)

<div class=coursetitle>Estás en el Nivel 1: Introducción a la programación paralela con OpenMP. <a href="main.html">¿Deseas volver al inicio?</a> </div>