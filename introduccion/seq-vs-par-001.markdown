---
layout: page
title:  "Ejecución secuencial vs Ejecución paralela"
---
[Anterior](seq-vs-par-000.html) | [Siguiente](para-que-000.html)

## Ejemplo de programa secuencial
El siguiente es un programa que se ejecuta de manera secuencial:
```c
#include <stdio.h>

int main(){
    printf("Step 1\n");
    printf("Step 2\n");
    printf("Step 3\n");
    printf("Step 4\n");
}
```
[Descarga el código aquí](../codigo/sequential-000.c).

### ¿Cómo compilar?
Usamos la sintaxis básica de Clang: `-o` para indicar el nombre del executable, seguido por el nombre del archivo que queremos compilar.
```bash
clang -o sequential-000 sequential-000.c
```
### ¿Cómo ejecutar?
Desde la consola, llamamos al ejecutable, anteponiendo la referencia al directorio actual (`./`):
```bash
./sequential-000 
```
### Salida
```bash
Step 1
Step 2
Step 3
Step 4
```
Se ve cómo cada paso se ejecuta en el mismo orden en el que fue escrito.
Y si volvemos a ejecutar le programa, veremos exactamente la misma salida todas las veces que lo hagamos.

## Ejemplo de programa paralelo inservible
El siguiente es un programa que se ejecuta de manera paralela.
Simplemente adicionamos la directiva **parallel** alrededor del código que queremos paralelizar:
```c
#include <stdio.h>

int main(){
    #pragma omp parallel
    {
        printf("Step 1\n");
        printf("Step 2\n");
        printf("Step 3\n");
        printf("Step 4\n");
    }
}
```
[Descarga el código aquí](../codigo/replicated-000.c).

### ¿Cómo compilar?
Para decirle a Clang que queremos compilar código paralelo escrito con OpenMP, debemos adicionar la opción `-fopenmp`:
```bash
clang -fopenmp -o replicated-000 replicated-000.c
```
### ¿Cómo ejecutar?
```bash
./replicated-000 
```
### Salida
```bash
Step 1
Step 2
Step 3
Step 4
Step 1
Step 2
Step 3
Step 1
Step 2
Step 3
Step 4
Step 4
Step 1
Step 2
Step 3
Step 4
```
Lo único que hemos logrado es ejecutar cuatro veces el mismo código.

## Ejemplo de programa paralelo que sirve
Lo que queremos es que cada paso se ejecute independiente de los demás.
Para esto, podemos invocar una función del runtime de OpenMP (el runtime es la biblioteca compilada de OpenMP que provee la paralelización del binario que generamos en tiempo de ejecución).
Dicha función es `omp_get_thread_num()`, la cual pregunta a cada recurso paralelo disponible (llamado hilo) cuál es su identificador.
Con ese identificador decidimos qué paso es ejecutado por cada hilo.
Para usar esta función debemos adicionar la cabecera `omp.h` en el código, :
```c
#include <stdio.h>
#include <omp.h>

int main(){
    #pragma omp parallel
    {
        if(omp_get_thread_num()==0){
            printf("Step 1\n");
        }
        if(omp_get_thread_num()==1){
            printf("Step 2\n");
        }
        if(omp_get_thread_num()==2){
            printf("Step 3\n");
        }
        if(omp_get_thread_num()==3){
            printf("Step 4\n");
        }
    }
}
```
[Descarga el código aquí](../codigo/parallelized-000.c).

### ¿Cómo compilar?
Debemos ahora indicarle a Clang con la opción `-I` la ruta a la carpeta donde se encuentra `omp.h`: 
```bash
clang -fopenmp -I/home/user/llvm/llvm-build/projects/openmp/runtime/src/
    -o replicated-000 replicated-000.c
```
### ¿Cómo ejecutar?
```bash
./replicated-000 
```
### Salida 1
```bash
Step 2
Step 4
Step 1
Step 3
```
Observamos que la ejecución no se da en el orden en el que fueron escritos los pasos.
Cada nueva ejecución nos da una secuencia diferente, lo cual nos permite inferir que los pasos son ejecutados ahora de manera independiente: 
### Salida 2
```bash
Step 1
Step 4
Step 3
Step 2
```

### Salida 3
```bash
Step 4
Step 3
Step 2
Step 1
```

Los anteriores fueron solo ejemplos simplificados de programas secuenciales y paralelos.
En la práctica, OpenMP ofrece maneras mucho más elegantes de adquirir la paralelización de nuestros programas, y es lo que abordaremos en las siguientes secciones progresivamente.

## Preguntas 
* _¿Qué le adicionarías a la directiva 'parallel' para hacerla más poderosa?_

[Anterior](seq-vs-par-000.html) | [Siguiente](para-que-000.html)

<div class=coursetitle>Estás en el Nivel 1: Introducción a la programación paralela con OpenMP. <a href="main.html">¿Deseas volver al inicio?</a> </div>