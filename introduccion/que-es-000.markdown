---
layout: page
title:  "¿Qué es OpenMP?"
---
[Anterior](main.html) | [Siguiente](seq-vs-par-000.html)

**OpenMP** es una API (Application Programming Interface - Interfaz de Programación de Aplicaciones) que permite expresar y obtener paralelismo en programas escritos en C, C++ y Fortran. 

*Open* significa que la especificación no es propiedad de ninguna compañía comercial y es mas bien mantenida por un consorcio de expertos provenientes de diferentes empresas e instituciones.
La idea es que el lenguaje evolucione con la colaboración de todos.

*MP* significa multi-processing (multi-procesamiento). 

OpenMP trabaja con un modelo de memoria compartida, es decir, se asume que todos los procesadores de la máquina tienen acceso a un mismo espacio de memoria.

El paralelismo en OpenMP se expresa a través de anotaciones en forma de directivas y cláusulas que actúan como modificadoras del código base (C, C++ o Fortran).
En C y C++, estas directivas empiezan siempre con las siguientes palabras clave:

```c
#pragma omp 
``` 

## Ejemplo
El siguiente bucle se ejecuta ahora de manera paralela debido a la anotación con directivas OpenMP:
```c
#pragma omp parallel for // OpenMP directive
for(int i=0;i<16;i++){
    printf("i=%d processed by thread=%d\n", i, omp_get_thread_num());
}
```
Las anotaciones ofrecen la ventaja de poder mantener el programa secuencial original ante la falta de un compilador que no soporte OpenMP.

## Preguntas

* _¿Qué otros lenguajes de programación paralela conoces?_
* _¿Qué otros modelos de programación paralela conoces?_

[Anterior](main.html) | [Siguiente](seq-vs-par-000.html)

<div class=coursetitle>Estás en el Nivel 1: Introducción a la programación paralela con OpenMP. <a href="main.html">¿Deseas volver al inicio?</a> </div>