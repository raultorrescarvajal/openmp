---
layout: page
title:  "Modelo fork-join"
---
[Anterior](prueba-000.html) | [Siguiente](parallel-000.html)

Un programa de OpenMP consiste generalmente de partes secuenciales y paralelas.
OpenMP utiliza el modelo de ejecución **fork-join**, donde un hilo, llamado el hilo maestro (master thread),
se encarga de la ejecución secuencial hasta encontrar una región paralela. Al encontrarla, se crean nuevos hilos que ejecutan la región paralela al mismo tiempo, pero se unen nuevamente en cierto punto del programa (una barrera), desde donde el hilo maestro continúa con la ejecución secuencial hasta encontrar la siguiente región paralela. El siguiente gráfico ilustra el proceso:

![Modelo fork-join](../graficos/fork-join-000.png) 

Al conjunto que conforman el hilo maestro y los demás hilos se lo denomina como **equipo** (team).
Cabe anotar que el hilo maestro también participa en la ejecución de la región paralela.

Los hilos son unidades de ejecución que se asignan a los procesadores o núcleos disponibles de la máquina.
Aunque generalmente el número de hilos suele corresponder al número de núcleos físicos, puede suceder que se creen más o menos hilos:
* Tener menos hilos puede ser útil cuando queremos limitar los recursos que va a requerir nuestro programa, especialmente si tiene que compartirlos con otras aplicaciones.
* Tener más hilos es un caso menos práctico, pero puede servir para simular la posesión de más procesadores físicos, por ejemplo.
En ese caso, algunos de los procesadores físicos tendrán que hacerse cargo de más de un solo hilo y su ejecución internamente sería secuencial.

Por tanto, es válido afirmar que los hilos son unidades lógicas de procesamiento que nos permiten abstraer las unidades físicas disponibles, de tal manera que podamos diseñar nuestros programas para que sean portables entre diferentes configuraciones de hardware.

## Preguntas
* _¿Qué alternativa propondrías en lugar del modelo fork-join?_

[Anterior](prueba-000.html) | [Siguiente](parallel-000.html)

<div class=coursetitle>Estás en el Nivel 1: Introducción a la programación paralela con OpenMP. <a href="main.html">¿Deseas volver al inicio?</a> </div>