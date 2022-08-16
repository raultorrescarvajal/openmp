---
layout: page
title:  "Cláusula Collapse"
---
[Anterior](schedule-000.html) | [Siguiente](reduction-000.html)

Cuando se tienen bucles anidados, es posible hacerlos ver como un solo bucle y utilizar una sola estrategia de distribución para toda la construcción. 
Esto se logra con la cláusula **collapse**.
De esta manera evitamos tener que anidar una región paralela dentro de otra. 

## Sintaxis básica
```c
#pragma omp parallel for collapse(<num_levels>)
for(...){
    for(...){
        for(...){
            <loop body>
        }
    }
}// implicit barrier here
``` 

## Ejemplo
Vamos a colapsar dos bucles y distribuir las iteraciones entre los hilos de dos en dos:
```c
#include <stdio.h>
#include <omp.h>

int main(){
    int m = omp_get_thread_num();
    printf("master thread=%d in serial region\n", m);
    
    #pragma omp parallel for collapse(2) schedule(static,2)
    for(int i=0; i<4 ; i++){
        for(int j=0; j<4 ; j++){
            int f = omp_get_thread_num();
            printf("i,j=%d,%d processed by thread=%d\n", i, j, f);
        }
    } // implicit barrier here
    
    printf("master thread=%d in serial region\n", m);
}
```
[Descarga el código aquí](../codigo/collapse-000.c).

### ¿Cómo compilar?
```bash
clang -fopenmp -I/home/user/llvm/llvm-build/projects/openmp/runtime/src/ 
     -o collapse-000 collapse-000.c
```
### ¿Cómo ejecutar?
```bash
./collapse-000 
```
### Salida
```bash
master thread=0 in serial region
i,j=1,0 processed by thread=2
i,j=1,1 processed by thread=2
i,j=3,0 processed by thread=2
i,j=0,2 processed by thread=1
i,j=1,2 processed by thread=3
i,j=1,3 processed by thread=3
i,j=3,2 processed by thread=3
i,j=3,3 processed by thread=3
i,j=0,3 processed by thread=1
i,j=2,2 processed by thread=1
i,j=2,3 processed by thread=1
i,j=3,1 processed by thread=2
i,j=0,0 processed by thread=0
i,j=0,1 processed by thread=0
i,j=2,0 processed by thread=0
i,j=2,1 processed by thread=0
master thread=0 in serial region
```
Se crean bloques de 2 iteraciones dentro del loop más interior y se van rotando los hilos que reciben cada bloque.

## Preguntas
* _Experimenta con diferentes versiones del tamaño del chunk y diferentes estrategias de scheduling._
* _Intenta paralelizar los bucles sin utilizar collapse._

[Anterior](schedule-000.html) | [Siguiente](reduction-000.html)

<div class=coursetitle>Estás en el Nivel 2: Bucles paralelos y tareas concurrentes con OpenMP. <a href="main.html">¿Deseas volver al inicio?</a> </div>