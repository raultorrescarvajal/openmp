---
layout: page
title:  "Directiva Atomic"
---
[Anterior](critical-000.html) | [Siguiente](barrier-000.html)

Para evitar una condición de carrera al actualizar una variable compartida, a veces sólo es necesario (y también más eficiente) proteger del acceso paralelo a una sola instrucción que una sección con varias instrucciones. 
Un único hilo ejecuta la instrucción al tiempo y los demás esperan su turno. El hilo que termina no espera al final de la instrucción sino que continúa hasta la siguiente barrera.

## Sintaxis básica
```c
#pragma omp parallel
{
    <parallel region code>
    
    #pragma omp atomic [update|read|write|capture]
    <instruction>

    <parallel region code>
} // implicit barrier here
``` 
* **update**: es la opción por defecto; asegura que el valor no se modifique hasta que la variable se haya actualizado.
* **read**: garantiza que el valor de la variable a leer no se modifique hasta que se termine de leerla.
* **write**: asegura que el valor de la variable a escribir no se modifique hasta que se termine de escribirla.
* **capture**: asegura que se capture el valor de la variable antes de hacer una actualización.

## Ejemplo
Vamos a contar cuántos hilos ejecutan la instrucción:
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
        
        #pragma omp atomic
        count++;
        
        printf("thread=%d says goodbye\n", t);
    } // implicit barrier here
    
    printf("master thread=%d in serial region\n", m);
    printf("count=%d\n", count);
}
```
[Descarga el código aquí](../codigo/atomic-000.c).

### ¿Cómo compilar?
```bash
clang -fopenmp -I/home/user/llvm/llvm-build/projects/openmp/runtime/src/ 
     -o atomic-000 atomic-000.c
```
### ¿Cómo ejecutar?
```bash
./atomic-000 
```
### Salida
```bash
master thread=0 in serial region
thread=0 in parallel region
thread=0 says goodbye
thread=3 in parallel region
thread=3 says goodbye
thread=1 in parallel region
thread=1 says goodbye
thread=2 in parallel region
thread=2 says goodbye
master thread=0 in serial region
count=4
```
La anotación atómica garantiza que el contador sea 4.

## Preguntas
* _Modifica el programa y usa read, write y capture._

[Anterior](critical-000.html) | [Siguiente](barrier-000.html)

<div class=coursetitle>Estás en el Nivel 1: Introducción a la programación paralela con OpenMP. <a href="main.html">¿Deseas volver al inicio?</a> </div>

[//]: # (Copyright (C) 2022 Raul Torres raultorrescarvajal@gmail.com)