---
layout: page
title:  "Modelo de datos"
---
[Anterior](practice1-000.html) | [Siguiente](shared-000.html)

OpenMP asume que los hilos de una región comparten la memoria. Pero a veces es necesario que cada hilo tenga datos cuyos valores sean propios de ese hilo particular. Volvamos al código del ejemplo anterior:
```c
#include <stdio.h>
#include <omp.h>

int main(){
    int m = omp_get_thread_num();
    printf("thread=%d in serial region\n", m);
    
    #pragma omp parallel 
    {
        int t = omp_get_thread_num();
        printf("thread=%d in parallel region\n", t);
    }
    
    printf("thread=%d in serial region\n", m);
}
```
[Descarga el código aquí](../codigo/parallel-000.c).

La variable `m`, definida antes del inicio de la región paralela, una vez dentro de esta última, es vista por los hilos como una variable compartida y todos la pueden acceder, mientras que la variable `t`, definida dentro de la región paralela, es vista como una variable privada, y cada hilo maneja su propia copia. La siguiente figura lo ilustra:

![Modelo de datos](../graficos/shared-private-000.png)

## Preguntas

* _¿Qué condiciones serían necesarias para un modelo de memoria distribuida?_

[Anterior](practice1-000.html) | [Siguiente](shared-000.html)

<div class=coursetitle>Estás en el Nivel 1: Introducción a la programación paralela con OpenMP. <a href="main.html">¿Deseas volver al inicio?</a> </div>