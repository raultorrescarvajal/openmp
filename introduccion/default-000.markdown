---
layout: page
title:  "Cláusula Default"
---
[Anterior](private-000.html) | [Siguiente](single-000.html)

Para evitar suposiciones respecto a si una variable es privada o compartida, es recomendable utilizar la cláusula **default**, la cual ofrece dos posibilidades:
* shared: se asume que todas las variables definidas antes de la región paralela son compartidas, a menos que explícitamente se especifique otro calificativo.
* none: no se asume ningún calificativo, y toda variable referenciada debe ser explícitamente cualificada.

## Sintaxis básica
```c
#pragma omp parallel default(shared|none) 
{
    <parallel region code>
}
``` 
## Ejemplo 1
Dentro de la región paralela compararemos una variable compartida y una privada, solo con `c`  explícitamente tipificada, para determinar cuál es el hilo maestro:
```c
#include <stdio.h>
#include <omp.h>

int main(){
    int t = -1;
    int m = omp_get_thread_num();
    printf("master thread=%d in serial region\n", m);
    
    #pragma omp parallel default(shared) private(t)
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
[Descarga el código aquí](../codigo/default-000.c).

### ¿Cómo compilar?
```bash
clang -fopenmp -I/home/user/llvm/llvm-build/projects/openmp/runtime/src/ 
     -o default-000 default-000.c
```
### ¿Cómo ejecutar?
```bash
./default-000 
```
### Salida
```bash
master thread=0 in serial region
thread=2 in parallel region
master thread=0 in parallel region
thread=1 in parallel region
thread=3 in parallel region
master thread=0 in serial region
value of t=-1
```
`t` conserva su valor original una vez termina la región paralela.

## Ejemplo 2
Dentro de la región paralela compararemos una variable compartida y una privada, ambas explícitamente tipificada, para determinar cuál es el hilo maestro:
```c
#include <stdio.h>
#include <omp.h>

int main(){
    int t = -1;
    int m = omp_get_thread_num();
    printf("master thread=%d in serial region\n", m);
    
    #pragma omp parallel default(none) shared(m) private(t)
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
[Descarga el código aquí](../codigo/default-001.c).

### ¿Cómo compilar?
```bash
clang -fopenmp -I/home/user/llvm/llvm-build/projects/openmp/runtime/src/ 
     -o default-001 default-001.c
```
### ¿Cómo ejecutar?
```bash
./default-001 
```
### Salida
```bash
master thread=0 in serial region
master thread=0 in parallel region
thread=2 in parallel region
thread=3 in parallel region
thread=1 in parallel region
master thread=0 in serial region
value of t=-1
```
`t` conserva su valor original una vez termina la región paralela.

## Preguntas
* _Elimina las cláusulas shared y private en ambos ejemplos._
* _¿Qué sucede?_
* _¿Cuáles serían las ventajas de usar default(none)?_

[Anterior](private-000.html) | [Siguiente](single-000.html)

<div class=coursetitle>Estás en el Nivel 1: Introducción a la programación paralela con OpenMP. <a href="main.html">¿Deseas volver al inicio?</a> </div>