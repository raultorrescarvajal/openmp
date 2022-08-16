---
layout: page
title:  "Práctica 1"
---
[Anterior](sections-000.html) | [Siguiente](datos-000.html)

Es hora de poner en práctica lo que hemos aprendido acerca de las directivas **parallel**, **sections** y **section**.
El siguiente programa imprime una a una las palabras de un párrafo del Quijote de la Mancha. 
Tu misión es usar las 3 directivas aprendidas para imprimir diferentes versiones del mismo párrafo sin modificar el orden en que están escritas en el código fuente: 

## Programa secuencial:
```c
#include <stdio.h>

int main(){
    printf("Y ");
    printf(", "); 
    printf("viéndole ");
    printf("don "); 
    printf("Quijote ");
    printf("de ");
    printf("aquella ");
    printf("manera ");
    printf(", ");
    printf("con ");
    printf("muestras ");
    printf("de ");
    printf("tanta ");
    printf("tristeza ");
    printf(", ");
    printf("le ");
    printf("dijo ");
    printf(": ");
    printf("Sábete ");
    printf(", ");
    printf("Sancho ");
    printf(", ");
    printf("que ");
    printf("no ");
    printf("es ");
    printf("un ");
    printf("hombre ");
    printf("más ");
    printf("que ");
    printf("otro ");
    printf("si ");
    printf("no ");
    printf("hace ");
    printf("más ");
    printf("que ");
    printf("otro ");
    printf(". ");
    printf("Todas ");
    printf("estas ");
    printf("borrascas ");
    printf("que ");
    printf("nos ");
    printf("suceden ");
    printf("son ");
    printf("señales ");
    printf("de ");
    printf("que ");
    printf("presto ");
    printf("ha ");
    printf("de ");
    printf("serenar ");
    printf("el ");
    printf("tiempo ");
    printf("y ");
    printf("han ");
    printf("de ");
    printf("sucedernos ");
    printf("bien ");
    printf("las ");
    printf("cosas ");
    printf("; ");
    printf("porque ");
    printf("no ");
    printf("es ");
    printf("posible ");
    printf("que ");
    printf("el ");
    printf("mal ");
    printf("ni ");
    printf("el ");
    printf("bien ");
    printf("sean ");
    printf("durables ");
    printf(", ");
    printf("y ");
    printf("de ");
    printf("aquí ");
    printf("se ");
    printf("sigue ");
    printf("que ");
    printf(", ");
    printf("habiendo ");
    printf("durado ");
    printf("mucho ");
    printf("el ");
    printf("mal ");
    printf(", ");
    printf("el ");
    printf("bien ");
    printf("está ");
    printf("ya ");
    printf("cerca ");
    printf(". ");
    printf("Así ");
    printf("que ");
    printf(", ");
    printf("no ");
    printf("debes ");
    printf("congojarte ");
    printf("por ");
    printf("las ");
    printf("desgracias ");
    printf("que ");
    printf("a ");
    printf("mí ");
    printf("me ");
    printf("suceden ");
    printf(", ");
    printf("pues ");
    printf("; ");
    printf("a ");
    printf("ti ");
    printf("no ");
    printf("te ");
    printf("cabe ");
    printf("parte ");
    printf("dellas ");
    printf(". ");
    printf("\n");
}
```
[Descarga el código aquí](../codigo/intro-practice-sequential-000.c).

### ¿Cómo compilar?
```bash
clang -o intro-practice-sequential-000 intro-practice-sequential-000.c
```
### ¿Cómo ejecutar?
```bash
./intro-practice-sequential-000 
```
### Salida
```bash
Y , viéndole don Quijote de aquella manera , con muestras de tanta tristeza , 
le dijo : Sábete , Sancho , que no es un hombre más que otro si no hace más 
que otro . Todas estas borrascas que nos suceden son señales de que presto 
ha de serenar el tiempo y han de sucedernos bien las cosas ; porque no es 
posible que el mal ni el bien sean durables , y de aquí se sigue que , 
habiendo durado mucho el mal , el bien está ya cerca . Así que , no debes 
congojarte por las desgracias que a mí me suceden , pues ; a ti no te cabe 
parte dellas .
```

## Programa paralelo:
...:
```bash
    Aquí va tu código ...
```

### ¿Cómo compilar?
```bash
clang -fopenmp -I/home/user/llvm/llvm-build/projects/openmp/runtime/src/ 
     -o intro-practice-parallel-000 intro-practice-parallel-000.c
```
### ¿Cómo ejecutar?
```bash
./intro-practice-parallel-000 
```
### Salida
```bash
    Aquí va la salida de tu programa paralelo ...
```

[Anterior](sections-000.html) | [Siguiente](datos-000.html)

<div class=coursetitle>Estás en el Nivel 1: Introducción a la programación paralela con OpenMP. <a href="main.html">¿Deseas volver al inicio?</a> </div>