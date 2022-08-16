---
layout: page
title:  "Cláusula reduction"
---
[Anterior](collapse-000.html) | [Siguiente](practice1-000.html)

Ciertas variables se utilizan dentro de los bucles con el fin de acumular los resultados de una operación que se extiende a través del espacio de iteraciones.
En un bucle secuencial se tiene una sola copia de este acumulador, pero en un bucle paralelo, tener una variable compartida para este fin puede generar una condición de carrera.
Para evitar esta situación, se usa la cláusula **reduction**. 

Las operaciones que se pueden reducir son, entre otras:
* +
* -
* *
* /

## Sintaxis básica
```c
#pragma omp parallel for reduction(<operator>:<var1[,var2,var3]>)
for(...){
    <loop body>
}// implicit barrier here
``` 
## Ejemplo
Vamos a acumular la suma de las iteraciones en la variable `p` dentro del bucle:
```c
#include <stdio.h>
#include <omp.h>

int main(){
    int m = omp_get_thread_num();
    printf("master thread=%d in serial region\n", m);
    
    int p = 0;
    printf("p=%d in serial region\n", p);

    #pragma omp parallel for reduction(+:p)
    for(int i=0; i<16 ; i++){
        int f = omp_get_thread_num();
        p = p + i;
        printf("p=%d modified by thread=%d\n", p, f);
    } // implicit barrier here
    
    printf("master thread=%d in serial region\n", m);
    printf("p=%d in serial region\n", p);
}
```
[Descarga el código aquí](../codigo/reduction-000.c).

### ¿Cómo compilar?
```bash
clang -fopenmp -I/home/user/llvm/llvm-build/projects/openmp/runtime/src/ 
     -o reduction-000 reduction-000.c
```
### ¿Cómo ejecutar?
```bash
./reduction-000 
```
### Salida
```bash
p=0 in serial region
p=8 modified by thread=2
p=17 modified by thread=2
p=27 modified by thread=2
p=38 modified by thread=2
p=0 modified by thread=0
p=1 modified by thread=0
p=3 modified by thread=0
p=6 modified by thread=0
p=4 modified by thread=1
p=9 modified by thread=1
p=15 modified by thread=1
p=22 modified by thread=1
p=12 modified by thread=3
p=25 modified by thread=3
p=39 modified by thread=3
p=54 modified by thread=3
master thread=0 in serial region
p=120 in serial region
```
Cada hilo acumula su valor en la variable `p`.
Al terminar el bucle, la variable `p` contiene la suma de los valores de las iteraciones, independientemente del orden en que fueron procesadas y sin condiciones de carrera.

## Preguntas
* _Experimenta con una reducción ad-hoc (sin usar la cláusula reduction)._

[Anterior](collapse-000.html) | [Siguiente](practice1-000.html)

<div class=coursetitle>Estás en el Nivel 2: Bucles paralelos y tareas concurrentes con OpenMP. <a href="main.html">¿Deseas volver al inicio?</a> </div>