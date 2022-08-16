---
layout: page
title:  "Directiva combinada parallel for"
---
[Anterior](nowait-000.html) | [Siguiente](firstprivate-000.html)

Muchas veces lo único que queremos paralelizar es directamente un bucle. 
Con esta directiva combinada nos ahorramos el tener que crear una región paralela sin código paralelo entre el bucle y sus límites.

## Sintaxis básica
```c
#pragma omp parallel for
for(...){
    <loop body>
}// implicit barrier here
``` 
## Ejemplo
Vamos a distribuir las iteraciones del bucle entre los hilos disponibles:
```c
#include <stdio.h>
#include <omp.h>

int main(){
    int m = omp_get_thread_num();
    printf("master thread=%d in serial region\n", m);

    #pragma omp parallel for
    for(int i=0; i<16 ; i++){
        int f = omp_get_thread_num();
        printf("id=%d processed by thread=%d\n", i, f);
    } // implicit barrier here
    
    printf("master thread=%d in serial region\n", m);
}
```
[Descarga el código aquí](../codigo/parallel-for-000.c).

### ¿Cómo compilar?
```bash
clang -fopenmp -I/home/user/llvm/llvm-build/projects/openmp/runtime/src/ 
     -o parallel-for-000 for-000.c
```
### ¿Cómo ejecutar?
```bash
./parallel-for-000 
```
### Salida
```bash
id=0 processed by thread=0
id=8 processed by thread=2
id=9 processed by thread=2
id=1 processed by thread=0
id=2 processed by thread=0
id=3 processed by thread=0
id=10 processed by thread=2
id=11 processed by thread=2
id=12 processed by thread=3
id=13 processed by thread=3
id=14 processed by thread=3
id=15 processed by thread=3
id=4 processed by thread=1
id=5 processed by thread=1
id=6 processed by thread=1
id=7 processed by thread=1
master thread=0 in serial region
```
Cada hilo procesó 4 iteraciones de las 16 disponibles. 

## Preguntas
* _Toma los ejemplos que escribiste para for y nowait y adáptalos con la directiva combinada parallel for._

[Anterior](nowait-000.html) | [Siguiente](firstprivate-000.html)

<div class=coursetitle>Estás en el Nivel 2: Bucles paralelos y tareas concurrentes con OpenMP. <a href="main.html">¿Deseas volver al inicio?</a> </div>