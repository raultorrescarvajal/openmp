---
layout: page
title:  "Variables privadas con la cláusula Private"
---
[Anterior](shared-000.html) | [Siguiente](default-000.html)

Para denotar explícitamente una variable como privada, usamos la cláusula `private`. La variable debe haber sido definida antes de la región paralela.

## Sintaxis básica
En el caso de la directiva `parallel`, la sintaxis es la siguiente:
```c
#pragma omp parallel private(<var1[,var2,var3,...]>)
{
    <parallel region code>
}
``` 
## Ejemplo
Dentro de la región paralela compararemos una variable compartida y una privada, ambas explícitamente tipificadas, para determinar cuál es el hilo maestro:
```c
#include <stdio.h>
#include <omp.h>

int main(){
    int t = -1;
    int m = omp_get_thread_num();
    printf("master thread=%d in serial region\n", m);
    
    #pragma omp parallel shared(m) private(t)
    {
        t = omp_get_thread_num();
        if(t==m)
            printf("master thread=%d in parallel region\n", m);
        else
            printf("thread=%d in parallel region\n", t);
    }
    
    printf("master thread=%d in serial region\n", m);
    printf("value of t=%d\n", t);
}
```
[Descarga el código aquí](../codigo/private-000.c).

### ¿Cómo compilar?
```bash
clang -fopenmp -I/home/user/llvm/llvm-build/projects/openmp/runtime/src/ 
     -o private-000 private-000.c
```
### ¿Cómo ejecutar?
```bash
./private-000 
```
### Salida
```bash
master thread=0 in serial region
master thread=0 in parallel region
thread=1 in parallel region
thread=3 in parallel region
thread=2 in parallel region
master thread=0 in serial region
value of t=-1
```
`t` conserva su valor original una vez termina la región paralela. 

## Preguntas
* _Modifica el programa y haz de t una variable compartida._
* _¿Qué pasaría en este caso?_

[Anterior](shared-000.html) | [Siguiente](default-000.html)

<div class=coursetitle>Estás en el Nivel 1: Introducción a la programación paralela con OpenMP. <a href="main.html">¿Deseas volver al inicio?</a> </div>