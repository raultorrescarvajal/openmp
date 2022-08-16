---
layout: page
title:  "Práctica 2"
---
[Anterior](barrier-000.html) | [Volver al inicio](main.html)

Es hora de poner en práctica lo que hemos aprendido acerca de las directivas de OpenMP que nos permiten paralelizar nuestro código.
Los siguientes programas está escritos de manera secuencial.
Tu misión es paralelizarlos utilizando las directivas aprendidas.

## Programa secuencial 1:
Determina el número máximo comparando entre pares de números (imprime en pantalla el número de hilo con cada resultado):
```c
#include <stdio.h>
// pista: se debe incluir una cabecera que permite enlazar las funciones del runtime

int max(int a, int b){
    return a >= b ? a : b;
}

int main(){
    /* determina el número máximo comparando entre pares de números 
       (imprime en pantalla el número de hilo con cada resultado) */

    // pista: las siguientes variables son de solo lectura
    int a=40, b=20, c=30, d=50;
    int w=25, x=73, y=99, z=5;

    // pista: las siguientes variables se escriben y se leen una sola vez 
    int max_0=0, max_1=0, max_2=0, max_3=0, max_4=0, max_5=0;
    
    // pista: la siguiente variable solo se escribe una sola vez
    int final_max=0;
    
    // pista: las siguientes 4 líneas son independientes entre sí
    max_0 = max(a, b); printf("max_0=%d\n", max_0);
    max_1 = max(c, d); printf("max_1=%d\n", max_1);
    max_2 = max(w, x); printf("max_2=%d\n", max_2);
    max_3 = max(y, z); printf("max_3=%d\n", max_3);

    // pista: las siguientes 2 líneas son independientes entre sí
    max_4 = max(max_0, max_1); printf("max_4=%d\n", max_4);
    max_5 = max(max_2, max_3); printf("max_5=%d\n", max_5);

    // pista: solo un hilo debe ejecutar la siguiente línea
    final_max = max(max_4, max_5); printf("final_max_6=%d\n", final_max);
}
```
[Descarga el código aquí](../codigo/intro-practice-sequential-001.c).

### ¿Cómo compilar?
```bash
clang -o intro-practice-sequential-001 intro-practice-sequential-001.c
```
### ¿Cómo ejecutar?
```bash
./intro-practice-sequential-001 
```
### Salida
```bash
max_0=40
max_1=50
max_2=73
max_3=99
max_4=50
max_5=99
final_max_6=99
```

## Programa paralelo 1:
Apóyate en las pistas dejadas en el código secuencial para crear tu propia versión paralela:
```bash
    Aquí va tu código ...
```

### ¿Cómo compilar?
```bash
clang -fopenmp -I/home/user/llvm/llvm-build/projects/openmp/runtime/src/ 
     -o intro-practice-parallel-001 intro-practice-parallel-001.c
```
### ¿Cómo ejecutar?
```bash
./intro-practice-parallel-001 
```
### Salida
```bash
    Aquí va la salida de tu programa paralelo ...
```

[Anterior](barrier-000.html) | [Volver al inicio](main.html)
