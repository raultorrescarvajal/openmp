---
layout: page
title:  "Práctica 1"
---
[Anterior](reduction-000.html) | [Siguiente](tasking-000.html)

Es hora de poner en práctica lo que hemos aprendido acerca de las directivas de OpenMP que nos permiten paralelizar nuestros bucles.
Los siguientes bucles está escritos de manera secuencial.
Tu misión es paralelizarlos utilizando las directivas aprendidas.

## Programa secuencial 1:
Calcula C como la suma de los vectores A y B, y luego suma todos los elementos de C.
* Distribuye las iteraciones del bucle en bloques de 3 elementos de manera estática.
* Imprime en pantalla el número de hilo con cada resultado.

```c
#include <stdio.h>
// pista: se debe incluir una cabecera que permita
// enlazar las funciones del runtime

int main(){
    /* calcula C como la suma de los vectores A y B, y luego
       suma todos los elementos de C.
       (- distribuye las iteraciones del bucle en bloques de 
          4 elementos de manera estática
        - imprime en pantalla el número de hilo con cada resultado) */

    // pista: las siguientes variables pueden accederse 
    // desde cualquier hilo
    int A[16]= {0 , 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,14,15};
    int B[16]= {15,14,13,12,11,10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
    int C[16]= {};

    // pista: esta variable acumula el valor de la operación +
    // en cada iteración
    int total=0;

    // pista: podemos usar una directiva combinada 
    // para paralelizar este bucle sin escribir mucho código
    for(int i=0;i<16;i++){
        C[i] = A[i] + B[i];
        printf("C[%d]=%d\n", i, C[i]);
        total += C[i];
    }

    printf("total=%d\n", total);
}
```
[Descarga el código aquí](../codigo/prof-practice-sequential-000.c).

### ¿Cómo compilar?
```bash
clang -o prof-practice-sequential-000 prof-practice-sequential-000.c
```
### ¿Cómo ejecutar?
```bash
./prof-practice-sequential-000
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

## Programa paralelo 1:
Apóyate en las pistas dejadas en el código secuencial para crear tu propia versión paralela:
```bash
    Aquí va tu código ...
```

### ¿Cómo compilar?
```bash
clang -fopenmp -I/home/user/llvm/llvm-build/projects/openmp/runtime/src/ 
     -o prof-practice-parallel-000 prof-practice-parallel-000.c
```
### ¿Cómo ejecutar?
```bash
./prof-practice-parallel-000 
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
Calcula C como la resta de los vectores A y B más un offset.
* Distribuye las iteraciones del bucle en bloques de 5 elementos de manera estática.
* Imprime en pantalla el número de hilo con cada resultado.

```c
#include <stdio.h>
// pista: se debe incluir una cabecera que permita
// enlazar las funciones del runtime

int main(){
    /* calcula C como la resta de los vectores A y B más un offset.
       (- distribuye las iteraciones del bucle en bloques de 
          5 elementos de manera estática
        - imprime en pantalla el número de hilo con cada resultado) */

    // pista: las siguientes variables pueden accederse 
    // desde cualquier hilo
    int A[16]= {0 , 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,14,15};
    int B[16]= {15,14,13,12,11,10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
    int C[16]= {};

    // pista: cada iteración debe tener su propia copia de offset
    int offset=33;

    // pista: debemos imprimir el valor de thisOffset de la última iteración
    int thisOffset=0;

    // pista: podemos usar una directiva combinada 
    // para paralelizar este bucle sin escribir mucho código
    for(int i=0;i<16;i++){
        thisOffset = offset * i;  
        C[i] = A[i] - B[i] + thisOffset;
        printf("C[%d]=%d, thisOffset=%d\n", i, C[i], thisOffset);
    }

    printf("thisOffset=%d\n", thisOffset);
}
```
[Descarga el código aquí](../codigo/prof-practice-sequential-001.c).

### ¿Cómo compilar?
```bash
clang -o prof-practice-sequential-001 prof-practice-sequential-001.c
```
### ¿Cómo ejecutar?
```bash
./prof-practice-sequential-001
```
### Salida
```bash
C[0]=-15, thisOffset=0
C[1]=20, thisOffset=33
C[2]=55, thisOffset=66
C[3]=90, thisOffset=99
C[4]=125, thisOffset=132
C[5]=160, thisOffset=165
C[6]=195, thisOffset=198
C[7]=230, thisOffset=231
C[8]=265, thisOffset=264
C[9]=300, thisOffset=297
C[10]=335, thisOffset=330
C[11]=370, thisOffset=363
C[12]=405, thisOffset=396
C[13]=440, thisOffset=429
C[14]=475, thisOffset=462
C[15]=510, thisOffset=495
thisOffset=495
```
### Pregunta
¿Qué sucede si las variables `offset` and `thisOffset` se mantienen privadas?

## Programa paralelo 2:
Apóyate en las pistas dejadas en el código secuencial para crear tu propia versión paralela:
```bash
    Aquí va tu código ...
```

### ¿Cómo compilar?
```bash
clang -fopenmp -I/home/user/llvm/llvm-build/projects/openmp/runtime/src/ 
     -o prof-practice-parallel-001 prof-practice-parallel-001.c
```
### ¿Cómo ejecutar?
```bash
./prof-practice-parallel-001
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
Calcula C como la resta de las matrices A y B más un offset.
* Distribuye las iteraciones del bucle en bloques de 5 elementos de manera estática.
* Imprime en pantalla el número de hilo con cada resultado.

```c
#include <stdio.h>
// pista: se debe incluir una cabecera que permita
// enlazar las funciones del runtime

int main(){
    /* calcula C como la resta de las matrices A y B más un offset.
       (- distribuye las iteraciones del bucle en bloques de 
          5 elementos de manera estática
        - imprime en pantalla el número de hilo con cada resultado) */

    // pista: las siguientes variables pueden accederse 
    // desde cualquier hilo
    int A[4][4]= { {0 , 1, 2, 3},{ 4, 5, 6, 7},{8, 9,10,11},{12,13,14,15} };
    int B[4][4]= { {15,14,13,12},{11,10, 9, 8},{7, 6, 5, 4},{ 3, 2, 1, 0} };
    int C[4][4]= { {},{},{},{} };

    // pista: cada iteración debe tener su propia copia de offset
    int offset=33;

    // pista: debemos imprimir el valor de thisOffset de la última iteración
    int thisOffset=0;

    // pista: podemos usar una directiva con una cláusula que paraleliza 
    // ambos bucles como si fueran uno solo
    for(int i=0;i<4;i++){
    	for(int j=0;j<4;j++){
            thisOffset = offset * (i*4 + j);  
            C[i][j] = A[i][j] - B[i][j] + thisOffset;
            printf("C[%d][%d]=%d, thisOffset=%d\n", i, j, C[i][j], thisOffset);
        }
    }

    printf("thisOffset=%d\n", thisOffset);
}
```
[Descarga el código aquí](../codigo/prof-practice-sequential-002.c).

### ¿Cómo compilar?
```bash
clang -o prof-practice-sequential-002 prof-practice-sequential-002.c
```
### ¿Cómo ejecutar?
```bash
./prof-practice-sequential-002
```
### Salida
```bash
C[0][0]=-15, thisOffset=0
C[0][1]=20, thisOffset=33
C[0][2]=55, thisOffset=66
C[0][3]=90, thisOffset=99
C[1][0]=125, thisOffset=132
C[1][1]=160, thisOffset=165
C[1][2]=195, thisOffset=198
C[1][3]=230, thisOffset=231
C[2][0]=265, thisOffset=264
C[2][1]=300, thisOffset=297
C[2][2]=335, thisOffset=330
C[2][3]=370, thisOffset=363
C[3][0]=405, thisOffset=396
C[3][1]=440, thisOffset=429
C[3][2]=475, thisOffset=462
C[3][3]=510, thisOffset=495
thisOffset=495
```
## Programa paralelo 3:
Apóyate en las pistas dejadas en el código secuencial para crear tu propia versión paralela:
```bash
    Aquí va tu código ...
```

### ¿Cómo compilar?
```bash
clang -fopenmp -I/home/user/llvm/llvm-build/projects/openmp/runtime/src/ 
     -o prof-practice-parallel-002 prof-practice-parallel-002.c
```
### ¿Cómo ejecutar?
```bash
./prof-practice-parallel-002
```
### Salida
```bash
    Aquí va la salida de tu programa paralelo ...
```

[Anterior](reduction-000.html) | [Siguiente](tasking-000.html)

<div class=coursetitle>Estás en el Nivel 2: Bucles paralelos y tareas concurrentes con OpenMP. <a href="main.html">¿Deseas volver al inicio?</a> </div>