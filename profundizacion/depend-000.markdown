---
layout: page
title:  "Cláusula Depend"
---
[Anterior](taskloop-000.html) | [Siguiente](practice2-000.html)

Las tareas se pueden sincronizar individualmente con la cláusula **depend**.
Existen dos direcciones de sincronización:
* out: establece una dependencia para una tarea futura.
* in: establece una dependencia desde una tarea previa.

## Sintaxis básica
```c
#pragma omp parallel
{ 
    <parallel region code>

    #pragma omp single
    {
        #pragma omp task depend(out: var1[,var2,var3,...])
        {
            <task body>
        } 

        <single region code>

        #pragma omp task depend(in: var1[,var2,var3,...])
        {
            <loop body>
        } 
    } 

    <parallel region code>
}
```
## Ejemplo
...
```c
#include <stdio.h>
#include <omp.h>

int main(){
    int m = omp_get_thread_num();
    printf("thread=%d in serial region\n", m);
    
    #pragma omp parallel 
    {
        #pragma omp single
        {
            int g = omp_get_thread_num();
            printf("thread=%d in single region is creating tasks\n", g);

            int p=0,q=0,r=0,s=0,t=0;
            #pragma omp task depend(out: p)
            {
                p = omp_get_thread_num();
                printf("thread=%d executed task A\n", p);
            }

            #pragma omp task
            {
                q= omp_get_thread_num();
                printf("thread=%d executed task B\n", q);
            }

            #pragma omp task depend(out: r)
            {
                r= omp_get_thread_num();
                printf("thread=%d executed task C\n", r);
            }

            #pragma omp task depend(in: p, r)
            {
                s = omp_get_thread_num();
                printf("thread=%d executed task D\n", s);
            }

            #pragma omp task
            {
                t = omp_get_thread_num();
                printf("thread=%d executed task E\n", t);
            }
        } // implicit barrier here
    } // implicit barrier here
    
    m = omp_get_thread_num();
    printf("thread=%d in serial region\n", m);
}
```
[Descarga el código aquí](../codigo/depend-000.c).

### ¿Cómo compilar?
```bash
clang -fopenmp -I/home/user/llvm/llvm-build/projects/openmp/runtime/src/ 
     -o depend-000 depend-000.c
```
### ¿Cómo ejecutar?
```bash
./depend-000
```
### Salida
```bash
thread=0 in serial region
thread=0 in single region is creating tasks
thread=7 executed task A
thread=2 executed task C
thread=4 executed task B
thread=7 executed task E
thread=6 executed task D
thread=0 in serial region

```
Dadas las dependencias, la tarea D sólo se ejecuta después de las tareas A y C.

## Preguntas

* _Diseña un grafo complejo de ejecución de al menos 10 tareas y tradúcelo a código de OpenMP con dependencias._
* _Verifica que las dependencias se cumplan._

[Anterior](taskloop-000.html) | [Siguiente](practice2-000.html)

<div class=coursetitle>Estás en el Nivel 2: Bucles paralelos y tareas concurrentes con OpenMP. <a href="main.html">¿Deseas volver al inicio?</a> </div>