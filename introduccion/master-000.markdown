---
layout: page
title:  "Directiva Master"
---
[Anterior](single-000.html) | [Siguiente](parallel-master-000.html)

A veces es necesario que solo el hilo maestro ejecute una parte del código de la región paralela. 
Esto se logra creando una región interna  de ejecución secuencial con la directiva `master`. 
A  diferencia de `single`, los demás hilos siguen de largo hasta la siguiente barrera, sea ésta implícita o explícita. 

## Sintaxis básica
```c
#pragma omp parallel 
{
    <parallel region code>
    #pragma omp master
    {
        <serial region code>
    } // no barrier here
    <parallel region code>
} // implicit barrier here
``` 
## Ejemplo
Dentro de la región paralela creamos una región secuencial y vemos el orden de impresión:
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
        
        #pragma omp master
        {
            int s = omp_get_thread_num();
            printf("thread=%d in master region\n", s);
        } // no barrier here

        printf("thread=%d says goodbye\n", t);
    }
    
    printf("master thread=%d in serial region\n", m);
}
```
[Descarga el código aquí](../codigo/master-000.c).

### ¿Cómo compilar?
```bash
clang -fopenmp -I/home/user/llvm/llvm-build/projects/openmp/runtime/src/ 
     -o master-000 master-000.c
```
### ¿Cómo ejecutar?
```bash
./master-000 
```
### Salida
```bash
master thread=0 in serial region
thread=2 in parallel region
thread=2 says goodbye
thread=0 in parallel region
thread=0 in master region
thread=0 says goodbye
thread=1 in parallel region
thread=1 says goodbye
thread=3 in parallel region
thread=3 says goodbye
master thread=0 in serial region
```
En este caso el hilo maestro asumió el control de la región interna. Cada  hilo se despide inmediatamente, sin esperar a que la región secuencial haya terminado.

* _Modifica el programa de tal manera que se fuerce al hilo 3 a ejecutar la región master._
* _¿Por qué el programa nunca entra a la región master?_
* _Si no tuviésemos la directiva master, ¿cómo lograríamos el mismo propósito?_
* _¿Qué aplicaciones le darías a esta directiva?_

[Anterior](single-000.html) | [Siguiente](parallel-master-000.html)

<div class=coursetitle>Estás en el Nivel 1: Introducción a la programación paralela con OpenMP. <a href="main.html">¿Deseas volver al inicio?</a> </div>