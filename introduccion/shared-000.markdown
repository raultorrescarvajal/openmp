---
layout: page
title:  "Variables compartidas con la cláusula Shared"
---
[Anterior](datos-000.html) | [Siguiente](private-000.html)

Para denotar explícitamente una variable como compartida, usamos la cláusula `shared`. Las cláusulas actúan como modificadores de las directivas.

## Sintaxis básica
En el caso de la directiva `parallel`, la sintaxis es la siguiente:
```c
#pragma omp parallel shared(<var1[,var2,var3,...]>)
{
    <parallel region code>
}
``` 
## Ejemplo
Dentro de la región paralela compararemos una variable compartida y una interna para determinar cuál es el hilo maestro:
```c
#include <stdio.h>
#include <omp.h>

int main(){
    int m = omp_get_thread_num();
    printf("master thread=%d in serial region\n", m);
    
    #pragma omp parallel shared(m)
    {
        int t = omp_get_thread_num();
        if(t==m)
            printf("master thread=%d in parallel region\n", m);
        else
            printf("thread=%d in parallel region\n", t);
    }
    
    printf("master thread=%d in serial region\n", m);
}
```
[Descarga el código aquí](../codigo/shared-000.c).

### ¿Cómo compilar?
```bash
clang -fopenmp -I/home/user/llvm/llvm-build/projects/openmp/runtime/src/ 
     -o shared-000 shared-000.c
```
### ¿Cómo ejecutar?
```bash
./shared-000 
```
### Salida
```bash
master thread=0 in serial region
thread=2 in parallel region
master thread=0 in parallel region
thread=3 in parallel region
thread=1 in parallel region
master thread=0 in serial region
```
## Preguntas
* _¿Qué pasaría si no usáramos la cláusula shared?_
* _Modifica el programa de tal manera que haya una condición de carrera al usar la variable compartida_
* _¿Cómo resolverías ese conflicto?_
* _¿Cuándo recomendarías usar variables compartidas?_


[Anterior](datos-000.html) | [Siguiente](private-000.html)

<div class=coursetitle>Estás en el Nivel 1: Introducción a la programación paralela con OpenMP. <a href="main.html">¿Deseas volver al inicio?</a> </div>