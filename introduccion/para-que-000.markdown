---
layout: page
title:  "¿Para qué sirve OpenMP?"
---
[Anterior](seq-vs-par-001.html) | [Siguiente](instalacion-000.html)

OpenMP se usa muy frecuentemente para acelerar códigos científicos, por ejemplo, simulaciones del clima, dinámica de fluidos o acoplamiento de moléculas. 
Su uso se ha extendido en la comunidad científica debido a que facilita la programación paralela, pues esconde los detalles de implementación de bajo nivel que solo un experto debería conocer, lo que les permite enfocarse en la resolución del problema desde el dominio específico.

También ha evitado que códigos secuenciales antiguos tengan que ser portados a otros lenguajes, dado su diseño estilo anotaciones.
Por ejemplo, muchas aplicaciones de simulación del clima han sido escritas en el veterano Fortran, con la ventaja de que muchos compiladores soportan OpenMP para este lenguaje.

OpenMP también se usa en modo híbrido con MPI.
Este último se encarga de hacer programación distribuida entre los nodos de un cluster de computadores, mientras que OpenMP despliega el paralelismo dentro del nodo.

Desde la versión 4.0 de la especificación de OpenMP ya se puede usar también para programar sistemas heterogéneos, por ejemplo, aquellos que disponen de un procesador multi-núcleo más una o varios tarjetas gráficas (GPUs).

## Preguntas
* _¿Qué otro tipo de aplicaciones conoces que se puedan beneficiar de la computación en paralelo?_
* _¿Qué tipo de sistemas de computación heterogéneos conoces?_
* _¿Sabes lo que es un acelerador?_


[Anterior](seq-vs-par-001.html) | [Siguiente](instalacion-000.html)

<div class=coursetitle>Estás en el Nivel 1: Introducción a la programación paralela con OpenMP. <a href="main.html">¿Deseas volver al inicio?</a> </div>