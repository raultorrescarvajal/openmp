---
layout: page
title:  "Cláusula Lastprivate"
---
[Anterior](firstprivate-000.html) | [Siguiente](schedule-000.html)

Al volver de un bucle compartido por los hilos, a veces se requiere obtener el valor de una variable en la última iteración del bucle. Esto se logra adicionando la cláusula **lastprivate** a la directiva paralela. 

## Sintaxis básica
```c
#pragma omp parallel for lastprivate(<var1[,var2,var3]>)
for(...){
    <loop body>
}// implicit barrier here
``` 
## Ejemplo
Vamos a modificar la variable `p` dentro del bucle y obtener su valor en la última iteración:
```c
#include <stdio.h>
#include <omp.h>

int main(){
    int m = omp_get_thread_num();
    printf("master thread=%d in serial region\n", m);
    
    int p = -1;
    printf("p=%d in serial region\n", p);

    #pragma omp parallel for lastprivate(p)
    for(int i=0; i<16 ; i++){
        int f = omp_get_thread_num();
        p = f;
        printf("p=%d modified by thread=%d\n", p, f);
    } // implicit barrier here
    
    printf("master thread=%d in serial region\n", m);
    printf("p=%d in serial region\n", p);
}
```
[Descarga el código aquí](../codigo/lastprivate-000.c).

### ¿Cómo compilar?
```bash
clang -fopenmp -I/home/user/llvm/llvm-build/projects/openmp/runtime/src/ 
     -o lastprivate-000 lastprivate-000.c
```
### ¿Cómo ejecutar?
```bash
./lastprivate-000 
```
### Salida
```bash
p=-1 in serial region
p=0 modified by thread=0
p=0 modified by thread=0
p=0 modified by thread=0
p=0 modified by thread=0
p=3 modified by thread=3
p=3 modified by thread=3
p=3 modified by thread=3
p=3 modified by thread=3
p=1 modified by thread=1
p=1 modified by thread=1
p=1 modified by thread=1
p=1 modified by thread=1
p=2 modified by thread=2
p=2 modified by thread=2
p=2 modified by thread=2
p=2 modified by thread=2
master thread=0 in serial region
p=3 in serial region

```
Cada hilo recibe una contiene una copia de la variable `p` y le hace modificaciones . Al terminar el bucle, como la última iteración estuvo a cargo del hilo 3, la  variable `p` tiene como valor 3.

## Preguntas

* _Separa el parallel del for y utiliza lastprivate en la clásula parallel._
* _¿Qué sucede?_

[Anterior](firstprivate-000.html) | [Siguiente](schedule-000.html)

<div class=coursetitle>Estás en el Nivel 2: Bucles paralelos y tareas concurrentes con OpenMP. <a href="main.html">¿Deseas volver al inicio?</a> </div>