---
layout: page
title:  "¿Qué son las tareas en OpenMP?"
---
[Anterior](practice1-000.html) | [Siguiente](task-000.html)

Las tareas en OpenMP cumplen la misma función que las secciones (véase el Nivel 1), es decir, paralelizar la ejecución de distintas partes independientes de un bloque de código.
El problema es que en el modelo de secciones, los hilos disponibles se rotan las secciones disponibles, independientemente de lo que demore cada sección en ejecutarse.
Esto hace que algunos hilos realicen más trabajo que otros, lo que resulta en una degradación de la velocidad de ejecución de todo el programa.

En cambio, en el modelo de tareas, los hilos son más pro-activos y proceden a "robar" trabajo de otros hilos que se encuentran muy ocupados.
Esto permite balancear más adecuadamente aquellas aplicaciones cuyas secciones paralelas difieren mucho en carga computacional entre sí. 

Otra diferencia es que las secciones se empiezan a ejecutar inmediatamente son creadas, mientras que las tareas se pueden ejecutar en cualquier momento entre su creación y el siguiente punto de sincronización.
Es el runtime quien determina cuándo se ejecutan.

Como ejemplo, en la siguiente figura vemos cómo se distribuyen las secciones entre los hilos disponible. 
El hilo número 1 recibe la carga más alta de operaciones, por lo que el tiempo total de ejecución está determinado por este hilo.
Los demás hilos han terminado su trabajo con anterioridad y esperan desocupados hasta que el hilo 1 termine:

![Secciones](../graficos/sections-000.png)

En cambio, con las tareas, los hilos terminan balanceando la carga entre ellos:

![Tareas](../graficos/tasks-000.png)

## Preguntas

* _¿En qué situaciones es recomendable usar tareas?_

[Anterior](practice1-000.html) | [Siguiente](task-000.html)

<div class=coursetitle>Estás en el Nivel 2: Bucles paralelos y tareas concurrentes con OpenMP. <a href="main.html">¿Deseas volver al inicio?</a> </div>