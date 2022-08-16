---
layout: page
title:  "Prueba de la instalación"
---
[Anterior](instalacion-002.html) | [Siguiente](modelo-000.html)

Ahora debe estar todo listo para empezar a experimentar con OpenMP. Para comprobarlo vamos a compilar y ejecutar el siguiente código:
```c
#include <stdio.h>
#include <omp.h>

int main(){
    #pragma omp parallel for
    for(int i=0;i<16;i++){
        printf("i=%d processed by thread=%d\n", i, omp_get_thread_num());
    }
}
```
Puedes descargar este ejemplo [aquí](../codigo/prueba-000.c). 
Utiliza el editor de texto de tu preferencia.

La compilación se hace ejecutando clang, el frontend de llvm para C:
```bash
clang -fopenmp -I/home/user/llvm/llvm-build/projects/openmp/runtime/src/ 
     -o prueba-000 prueba-000.c
```
Usamos `-I` para indicar dónde encontrar el archivo `omp.h`, el cuál contiene la definición de la función `omp_get_num_thread()`.
Usamos `-fopenmp` para habilitar la compilación de un programa paralelo. Sin esta opción, los **pragmas** (anotaciones al código) de OpenMP serían ignorados y tendríamos un programa secuencial. 

Finalmente, ejecutamos el programa generado:
```bash
./prueba-000 
```

Obtendremos diferentes resultados cada vez que lo ejecutemos:
```bash
i=8 processed by thread=2
i=9 processed by thread=2
i=10 processed by thread=2
i=4 processed by thread=1
i=0 processed by thread=0
i=1 processed by thread=0
i=11 processed by thread=2
i=5 processed by thread=1
i=6 processed by thread=1
i=7 processed by thread=1
i=12 processed by thread=3
i=13 processed by thread=3
i=2 processed by thread=0
i=3 processed by thread=0
i=14 processed by thread=3
i=15 processed by thread=3
```
Progresivamente iremos aprendiendo cómo manipular el número de hilos y las opciones de compilación.

[Anterior](instalacion-002.html) | [Siguiente](modelo-000.html)

<div class=coursetitle>Estás en el Nivel 1: Introducción a la programación paralela con OpenMP. <a href="main.html">¿Deseas volver al inicio?</a> </div>