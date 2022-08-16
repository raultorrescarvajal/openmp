---
layout: page
title:  "Cláusula firstprivate"
---
[Anterior](parallel-for-000.html) | [Siguiente](lastprivate-000.html)

Al compartir el trabajo, a veces se requiere que todos los hilos reciban una copia de una variable inicializada con el mismo valor, principalmente si se piensa hacer cambios sobre esa variable. Esto se logra adicionando la cláusula **firstprivate** a la directiva paralela. 

## Sintaxis básica
```c
#pragma omp parallel for firstprivate(<var1[,var2,var3]>)
for(...){
    <loop body>
}// implicit barrier here
``` 
## Ejemplo
Vamos a modificar la variable `p` dentro del bucle:
```c
#include <stdio.h>
#include <omp.h>

int main(){
    int m = omp_get_thread_num();
    printf("master thread=%d in serial region\n", m);
    
    int p = 4;
    printf("p=%d in serial region\n", p);

    #pragma omp parallel for firstprivate(p)
    for(int i=0; i<16 ; i++){
        int f = omp_get_thread_num();
        p = p + f;
        printf("p=%d modified by thread=%d\n", p, f);
    } // implicit barrier here
    
    printf("master thread=%d in serial region\n", m);
    printf("p=%d in serial region\n", p);
}
```
[Descarga el código aquí](../codigo/firstprivate-000.c).

### ¿Cómo compilar?
```bash
clang -fopenmp -I/home/user/llvm/llvm-build/projects/openmp/runtime/src/ 
     -o firstprivate-000 firstprivate-000.c
```
### ¿Cómo ejecutar?
```bash
./firstprivate-000 
```
### Salida
```bash
master thread=0 in serial region
p=4 in serial region
p=6 modified by thread=2
p=8 modified by thread=2
p=10 modified by thread=2
p=12 modified by thread=2
p=5 modified by thread=1
p=4 modified by thread=0
p=4 modified by thread=0
p=4 modified by thread=0
p=4 modified by thread=0
p=6 modified by thread=1
p=7 modified by thread=1
p=8 modified by thread=1
p=7 modified by thread=3
p=10 modified by thread=3
p=13 modified by thread=3
p=16 modified by thread=3
master thread=0 in serial region
p=4 in serial region
```
Cada hilo recibe una copia de la variable `p` inicializada en 4 y le hace modificaciones . Sin embargo, al terminar el bucle, la variable `p` mantiene su valor original.

## Preguntas
* _Modifica el programa y utiliza la cláusula shared en lugar de firstprivate._
* _¿Qué puede suceder?_

[Anterior](parallel-for-000.html) | [Siguiente](lastprivate-000.html)

<div class=coursetitle>Estás en el Nivel 2: Bucles paralelos y tareas concurrentes con OpenMP. <a href="main.html">¿Deseas volver al inicio?</a> </div>