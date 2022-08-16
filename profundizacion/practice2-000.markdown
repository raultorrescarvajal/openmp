---
layout: page
title:  "Práctica 2"
---
[Anterior](depend-000.html) | [Volver al inicio](main.html)

Es hora de poner en práctica lo que hemos aprendido acerca de las directivas de OpenMP que nos permiten paralelizar usando tareas concurrentes.
Los siguientes programas está escritos de manera secuencial.
Tu misión es paralelizarlos utilizando tareas.

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
[Descarga el código aquí](../codigo/prof-practice-sequential-005.c).

### ¿Cómo compilar?
```bash
clang -o prof-practice-sequential-005 prof-practice-sequential-005.c
```
### ¿Cómo ejecutar?
```bash
./prof-practice-sequential-005 
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
### Pregunta
¿Cuáles son las diferencias principales de tu implementación paralela actual con aquella que realizaste en el curso anterior? ([Ver práctica anterior](../introduccion/practice2-000.html).) 

## Programa paralelo 1:
Apóyate en las pistas dejadas en el código secuencial para crear tu propia versión paralela:
```bash
    Aquí va tu código ...
```

### ¿Cómo compilar?
```bash
clang -fopenmp -I/home/user/llvm/llvm-build/projects/openmp/runtime/src/ 
     -o prof-practice-parallel-005 prof-practice-parallel-005.c
```
### ¿Cómo ejecutar?
```bash
./prof-practice-parallel-005 
```
### Salida
```bash
    Aquí va la salida de tu programa paralelo ...
```
### Respuesta 
```bash
    Aquí va tu respuesta a la pregunta ...
```

## Programa secuencial 2:
Usa tareas para calcular C como la suma de los vectores A y B, y luego suma todos los elementos de C.
* Establece un número mínimo de 3 iteraciones del bucle por cada tarea generada.
* Imprime en pantalla el número de hilo con cada resultado.

```c
#include <stdio.h>
// pista: se debe incluir una cabecera que permita
// enlazar las funciones del runtime

int main(){
    /* usa tareas para calcular C como la suma de los vectores A y B,
       y luego suma todos los elementos de C.
       (- establece un número mínimo de 3 iteraciones del bucle 
          por cada tarea generada.
        - imprime en pantalla el número de hilo con cada resultado) */

    // pista: las siguientes variables pueden accederse 
    // desde cualquier hilo
    int A[16]= {0 , 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,14,15};
    int B[16]= {15,14,13,12,11,10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
    int C[16]= {};

    // pista: esta variable acumula el valor de la operación +
    // en cada iteración
    int total=0;

    // pista: podemos usar una directiva que cree un tarea
    // por cada iteración del bucle y así
    // paralelizarlo sin escribir mucho código
    for(int i=0;i<16;i++){
        C[i] = A[i] + B[i];
        printf("C[%d]=%d\n", i, C[i]);
        total += C[i];
    }

    printf("total=%d\n", total);
}
```
[Descarga el código aquí](../codigo/prof-practice-sequential-006.c).

### ¿Cómo compilar?
```bash
clang -o prof-practice-sequential-006 prof-practice-sequential-006.c
```
### ¿Cómo ejecutar?
```bash
./prof-practice-sequential-006
```
### Salida
```bash
C[0]=15
C[1]=15
C[2]=15
C[3]=15
C[4]=15
C[5]=15
C[6]=15
C[7]=15
C[8]=15
C[9]=15
C[10]=15
C[11]=15
C[12]=15
C[13]=15
C[14]=15
C[15]=15
total=240
```
### Pregunta
¿Usando 4 hilos, cuál de los hilos realizó más iteraciones y por qué?

## Programa paralelo 2:
Apóyate en las pistas dejadas en el código secuencial para crear tu propia versión paralela:
```bash
    Aquí va tu código ...
```

### ¿Cómo compilar?
```bash
clang -fopenmp -I/home/user/llvm/llvm-build/projects/openmp/runtime/src/ 
     -o prof-practice-parallel-006 prof-practice-parallel-006.c
```
### ¿Cómo ejecutar?
```bash
./prof-practice-parallel-006
```
### Salida
```bash
    Aquí va la salida de tu programa paralelo ...
```
### Respuesta 
```bash
    Aquí va tu respuesta a la pregunta ...
```

## Programa secuencial 3:
Intenta resolver el programa secuencial 1 usando dependencias entre tareas:
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
    
    // pista: las siguientes 2 líneas son independientes entre sí
    max_0 = max(a, b); printf("max_0=%d\n", max_0);
    max_1 = max(c, d); printf("max_1=%d\n", max_1);
    
    // pista: la siguiente línea depende de los dos resultados anteriores
    max_4 = max(max_0, max_1); printf("max_4=%d\n", max_4);
    
    // pista: las siguientes 2 líneas son independientes entre sí,
    // y también lo son de las anteriores 3 operaciones con máximos 
    max_2 = max(w, x); printf("max_2=%d\n", max_2);
    max_3 = max(y, z); printf("max_3=%d\n", max_3);

    // pista: la siguiente línea depende de los dos resultados anteriores
    max_5 = max(max_2, max_3); printf("max_5=%d\n", max_5);

    // pista: la siguiente línea depende de dos máximos anteriores
    final_max = max(max_4, max_5); printf("final_max_6=%d\n", final_max);
}
```
[Descarga el código aquí](../codigo/prof-practice-sequential-007.c).

### ¿Cómo compilar?
```bash
clang -o prof-practice-sequential-007 prof-practice-sequential-007.c
```
### ¿Cómo ejecutar?
```bash
./prof-practice-sequential-007
```
### Salida
```bash
max_0=40
max_1=50
max_4=50
max_2=73
max_3=99
max_5=99
final_max_6=99
``` 
## Programa paralelo 3:
Apóyate en las pistas dejadas en el código secuencial para crear tu propia versión paralela:
```bash
    Aquí va tu código ...
```
### ¿Cómo compilar?
```bash
clang -fopenmp -I/home/user/llvm/llvm-build/projects/openmp/runtime/src/ 
     -o prof-practice-parallel-007 prof-practice-parallel-007.c
```
### ¿Cómo ejecutar?
```bash
./prof-practice-parallel-007
```
### Salida
```bash
    Aquí va la salida de tu programa paralelo ...
```

[Anterior](depend-000.html) | [Volver al inicio](main.html)
