---
layout: page
title:  "Directiva Single"
---
[Anterior](default-000.html) | [Siguiente](master-000.html)

A veces es necesario que solo uno de los threads de la región paralela ejecute una parte del código. Esto se logra creando una región interna  de ejecución secuencial con la directiva `single`. Cualquiera de los hilos de la región paralela puede asumir el control de esa región secuencial. Todos los hilos se sincronizan al final de la región `single` (barrera implícita), a menos que se use la cláusula `nowait`.

## Sintaxis básica
```c
#pragma omp parallel 
{
    <parallel region code>
    #pragma omp single 
    {
        <serial region code>
    } // implicit barrier here
    <parallel region code>
} // implicit barrier here
``` 
## Ejemplo 1
Dentro de la región paralela creamos una región secuencial y vemos cuál de los hilos la asumió:
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
        
        #pragma omp single
        {
            int s = omp_get_thread_num();
            printf("thread=%d in single region\n", s);
        } // implict barrier here

        printf("thread=%d says goodbye\n", t);
    }
    
    printf("master thread=%d in serial region\n", m);
}
```
[Descarga el código aquí](../codigo/single-000.c).

### ¿Cómo compilar?
```bash
clang -fopenmp -I/home/user/llvm/llvm-build/projects/openmp/runtime/src/ 
     -o single-000 single-000.c
```
### ¿Cómo ejecutar?
```bash
./single-000 
```
### Salida
```bash
master thread=0 in serial region
thread=0 in parallel region
thread=0 in single region
thread=2 in parallel region
thread=3 in parallel region
thread=1 in parallel region
thread=0 says goodbye
thread=2 says goodbye
thread=3 says goodbye
thread=1 says goodbye
master thread=0 in serial region
```
En este caso el hilo 2 asumió el control de la región interna, pero podría ser cualquiera de los 4. Los 4 hilos se despiden en bloque, y siempre después de que la región `single`haya terminado.

## Ejemplo 2
Dentro de la región paralela creamos una región secuencial con `nowait` y vemos el orden de impresión de las despedidas:
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
        
        #pragma omp single nowait
        {
            int s = omp_get_thread_num();
            printf("thread=%d in single region\n", s);
        } // no barrier here

        printf("thread=%d says goodbye\n", t);
    }
    
    printf("master thread=%d in serial region\n", m);
}
```
[Descarga el código aquí](../codigo/single-001.c).

### ¿Cómo compilar?
```bash
clang -fopenmp -I/home/user/llvm/llvm-build/projects/openmp/runtime/src/ 
     -o single-001 single-001.c
```
### ¿Cómo ejecutar?
```bash
./single-001
```
### Salida
```bash
master thread=0 in serial region
thread=0 in parallel region
thread=0 in single region
thread=0 says goodbye
thread=3 in parallel region
thread=3 says goodbye
thread=2 in parallel region
thread=2 says goodbye
thread=1 in parallel region
thread=1 says goodbye
master thread=0 in serial region
```
En este caso el hilo 0 asumió el control de la región interna. Cada  hilo se despide inmediatamente, sin esperar a que la región secuencial haya terminado.

## Preguntas
* _Modifica el programa de tal manera que se fuerce al hilo 3 a ejecutar la región single._
* _¿Por qué el programa no termina de ejecutarse?_
* _Si no tuviésemos la directiva single, ¿cómo lograríamos el mismo propósito?_
* _¿Qué aplicaciones le darías a esta directiva?_

[Anterior](default-000.html) | [Siguiente](master-000.html)

<div class=coursetitle>Estás en el Nivel 1: Introducción a la programación paralela con OpenMP. <a href="main.html">¿Deseas volver al inicio?</a> </div>