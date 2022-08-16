---
layout: page
title:  "Cláusula Schedule"
---
[Anterior](lastprivate-000.html) | [Siguiente](collapse-000.html)

Es posible controlar la estrategia de distribución y el tamaño del bloque (número de iteraciones consecutivas) asignado a cada hilo. Esto se hace con la cláusula **schedule**. 

## Sintaxis básica
```c
#pragma omp parallel for schedule(static|dynamic,<chunk_size>)
for(...){
    <loop body>
}// implicit barrier here

``` 
Las estrategias fundamentales son:

### static
* La distribución se hace en tiempo de compilación a manera round-robin, es decir, asignando cada bloque consecutivo de iteraciones a un hilo diferente.
* Si no se especifica un tamaño de bloque, cada hilo recibirá un bloque de tamaño similar (chunk_size=num_iterations/num_threads).

### dynamic
* La distribución se hace en tiempo de ejecución, asignando cada bloque consecutivo de iteraciones al hilo con menos carga, de tal manera que se balancee la ejecución.
* Si no se especifica un tamaño de bloque, cada hilo recibirá una iteración (chunk_size=1).

## Ejemplo 1
Vamos a distribuir las iteraciones entre los hilos de dos en dos:
```c
#include <stdio.h>
#include <omp.h>

int main(){
    int m = omp_get_thread_num();
    printf("master thread=%d in serial region\n", m);
    
    #pragma omp parallel for schedule(static,2)
    for(int i=0; i<16 ; i++){
        int f = omp_get_thread_num();
        printf("i=%d processed by thread=%d\n", i, f);
    } // implicit barrier here
    
    printf("master thread=%d in serial region\n", m);
}
```
[Descarga el código aquí](../codigo/schedule-000.c).

### ¿Cómo compilar?
```bash
clang -fopenmp -I/home/user/llvm/llvm-build/projects/openmp/runtime/src/ 
     -o schedule-000 schedule-000.c
```
### ¿Cómo ejecutar?
```bash
./schedule-000 
```
### Salida
```bash
master thread=0 in serial region
i=0 processed by thread=0
i=1 processed by thread=0
i=8 processed by thread=0
i=9 processed by thread=0
i=2 processed by thread=1
i=3 processed by thread=1
i=10 processed by thread=1
i=11 processed by thread=1
i=6 processed by thread=3
i=7 processed by thread=3
i=14 processed by thread=3
i=15 processed by thread=3
i=4 processed by thread=2
i=5 processed by thread=2
i=12 processed by thread=2
i=13 processed by thread=2
master thread=0 in serial region
```
Se crean bloques de 2 iteraciones y se van rotando los hilos que reciben cada bloque.

## Ejemplo 2
Vamos a distribuir las iteraciones entre los hilos de dos en dos:
```c
#include <stdio.h>
#include <omp.h>

int main(){
    int m = omp_get_thread_num();
    printf("master thread=%d in serial region\n", m);
    
    #pragma omp parallel for schedule(dynamic,2)
    for(int i=0; i<16 ; i++){
        int f = omp_get_thread_num();
        printf("i=%d processed by thread=%d\n", i, f);
    } // implicit barrier here
    
    printf("master thread=%d in serial region\n", m);

```
[Descarga el código aquí](../codigo/schedule-001.c).

### ¿Cómo compilar?
```bash
clang -fopenmp -I/home/user/llvm/llvm-build/projects/openmp/runtime/src/ 
     -o schedule-001 schedule-001.c
```
### ¿Cómo ejecutar?
```bash
./schedule-001
```
### Salida
```bash
master thread=0 in serial region
i=8 processed by thread=2
i=9 processed by thread=2
i=10 processed by thread=2
i=11 processed by thread=2
i=12 processed by thread=2
i=13 processed by thread=2
i=14 processed by thread=2
i=15 processed by thread=2
i=6 processed by thread=2
i=7 processed by thread=2
i=2 processed by thread=3
i=3 processed by thread=3
i=0 processed by thread=0
i=1 processed by thread=0
i=4 processed by thread=1
i=5 processed by thread=1
master thread=0 in serial region

```
Se crean bloques de 2 iteraciones y se van asignando a los hilos que tengan menos trabajo.
Observamos que el hilo 2 se ha encargado de 5 bloques, mientras que los demás hilos solo recibieron 1 cada uno.

## Preguntas
* _Experimenta con diferentes versiones del tamaño del chunk y diferentes estrategias de scheduling._
* _Intenta escribir dentro del bucle un problema de tipo irregular._

[Anterior](lastprivate-000.html) | [Siguiente](collapse-000.html)

<div class=coursetitle>Estás en el Nivel 2: Bucles paralelos y tareas concurrentes con OpenMP. <a href="main.html">¿Deseas volver al inicio?</a> </div>