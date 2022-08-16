---
layout: page
title:  "Cláusula nowait"
---
[Anterior](for-000.html) | [Siguiente](parallel-for-000.html)

Hemos visto que ciertas directivas poseen una barrera implícita al final de la región demarcada (por ejemplo, **single**, **for**).
Sin embargo, hay situaciones en las que se requiere eliminar dicha barrera y permitir que la ejecución continúe más allá de la región en cuestión, sin esperar a que los hilos salgan de ella. 
Para tal fin se utiliza la cláusula **nowait**.

## Sintaxis básica
```c
#pragma omp parallel
{
    <parallel region code>
    
    #pragma omp for nowait
    for(...){
        <loop body code>
    } // no barrier here anymore

    <parallel region code>
} // implicit barrier here
``` 
## Ejemplo
Vamos a imprimir las iteraciones del loop:
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
        
        #pragma omp for nowait
        for(int i=0; i<16 ; i++){
            int f = omp_get_thread_num();
            printf("id=%d processed by thread=%d\n", i, f);
        } // no barrier here anymore
    
        printf("thread=%d says goodbye\n", t);
    } // implicit barrier here
    
    printf("master thread=%d in serial region\n", m);
}
```
[Descarga el código aquí](../codigo/nowait-000.c).

### ¿Cómo compilar?
```bash
clang -fopenmp -I/home/user/llvm/llvm-build/projects/openmp/runtime/src/ 
     -o nowait-000 nowait-000.c
```
### ¿Cómo ejecutar?
```bash
./nowait-000 
```
### Salida
```bash
master thread=0 in serial region
thread=0 in parallel region
id=0 processed by thread=0
id=1 processed by thread=0
id=2 processed by thread=0
id=3 processed by thread=0
thread=0 says goodbye
thread=2 in parallel region
id=8 processed by thread=2
thread=1 in parallel region
id=9 processed by thread=2
id=10 processed by thread=2
id=11 processed by thread=2
thread=2 says goodbye
thread=3 in parallel region
id=12 processed by thread=3
id=13 processed by thread=3
id=14 processed by thread=3
id=15 processed by thread=3
thread=3 says goodbye
id=4 processed by thread=1
id=5 processed by thread=1
id=6 processed by thread=1
id=7 processed by thread=1
thread=1 says goodbye
master thread=0 in serial region
```
Cada hilo entra al bucle, imprime sus iteraciones, sale del bucle sin esperar a los demás, y se despide. 
La sincronización sólo sucede al final de la región paralela.

## Preguntas
* _Modifica el programa de tal manera que hayan dos bucles anotados con la directiva for y la cláusula nowait._
* _¿Qué comportamiento se observa?_
* _¿Qué pasa si quitamos las cláusulas nowait?_

[Anterior](for-000.html) | [Siguiente](parallel-for-000.html)

<div class=coursetitle>Estás en el Nivel 2: Bucles paralelos y tareas concurrentes con OpenMP. <a href="main.html">¿Deseas volver al inicio?</a> </div>