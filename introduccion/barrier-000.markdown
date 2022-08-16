---
layout: page
title:  "Directiva Barrier"
---
[Anterior](atomic-000.html) | [Siguiente](practice2-000.html)

Hay situaciones en las que queremos controlar específicamente la sincronización de los hilos. 
Podemos insertar una barrera explícita que fuerce a todos los hilos a reunirse allí.

## Sintaxis básica
```c
#pragma omp parallel
{
    <parallel region code>
    
    #pragma omp barrier // explicit barrier here

    <parallel region code>
} // implicit barrier here
``` 
## Ejemplo
Vamos a asegurarnos de que los hilos se despidan en bloque:
```c
#include <stdio.h>
#include <omp.h>

int main(){
    int m = omp_get_thread_num();
    printf("master thread=%d in serial region\n", m);

    #pragma omp parallel
    {
        int t = omp_get_thread_num();
        printf("thread=%d in parallel region\n", t);
        
        #pragma omp barrier
    
        printf("thread=%d says goodbye\n", t);
    } // implicit barrier here
    
    printf("master thread=%d in serial region\n", m);
}
```
[Descarga el código aquí](../codigo/barrier-000.c).

### ¿Cómo compilar?
```bash
clang -fopenmp -I/home/user/llvm/llvm-build/projects/openmp/runtime/src/ 
     -o barrier-000 barrier-000.c
```
### ¿Cómo ejecutar?
```bash
./barrier-000 
```
### Salida
```bash
master thread=0 in serial region
thread=0 in parallel region
thread=3 in parallel region
thread=2 in parallel region
thread=1 in parallel region
thread=0 says goodbye
thread=3 says goodbye
thread=1 says goodbye
thread=2 says goodbye
master thread=0 in serial region
```
# Preguntas 

* _Modifica el programa de la directiva single, prescindiendo de aquella directiva pero logrando la misma funcionalidad._


[Anterior](atomic-000.html) | [Siguiente](practice2-000.html)

<div class=coursetitle>Estás en el Nivel 1: Introducción a la programación paralela con OpenMP. <a href="main.html">¿Deseas volver al inicio?</a> </div>
