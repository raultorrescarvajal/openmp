---
layout: page
title:  "Pre-requisitos"
---
[Anterior](para-que-000.html) | [Siguiente](instalacion-001.html)

Para este taller vamos a utilizar la versión de OpenMP del compilador **LLVM** y su frontend para **C/C++** llamado **Clang**. Como sistema operativo utilizaremos **Ubuntu**. Y antes de poder instalar el kit de compilación de LLVM, necesitaremos instalar los siguientes paquetes desde la terminal:

* Bibliotecas que permiten compilar un acelerador de prueba:
```bash
sudo apt install libefi
sudo apt install libffi
```
* Compilador base de C/C++
```bash
sudo apt install build-essential
```
* Generador de proyectos de compilación:
```bash
sudo apt install cmake
```
* Orquestrador de compilación
```bash
sudo apt install ninja
```
* Sistema de control de versiones
```bash
sudo apt install git
```
## Preguntas
* _Describe qué tipo de experiencia tienes con los paquetes anteriormente mencionados o similares._


[Anterior](para-que-000.html) | [Siguiente](instalacion-001.html)

<div class=coursetitle>Estás en el Nivel 1: Introducción a la programación paralela con OpenMP. <a href="main.html">¿Deseas volver al inicio?</a> </div>