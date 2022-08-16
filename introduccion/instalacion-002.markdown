---
layout: page
title:  "Instalación simplificada de LLVM/Clang/OpenMP"
---
[Anterior](instalacion-001.html) | [Siguiente](prueba-000.html)

Esta será mucho más rápida que la instalación manual, pero no tendremos soporte para aceleradores.
Sin embargo, para este curso todavía no lo necesitamos.

* Instalamos el compilador LLVM, sus cabeceras y su frontend para C/C++ llamado Clang:
```bash
sudo apt install llvm libomp-dev clang
```
* Luego se debe modificar las variables de entorno que permiten invocar binarios sin ruta y ubicar las bibliotecas dinámicas. 
```bash
export LD_LIBRARY_PATH="/usr/lib":$LD_LIBRARY_PATH
```
```bash
export PATH="/usr/bin":$PATH
```
* Para hacer permanentes estos cambios, hay que adicionar los comandos anteriores al final del archivo `.profile` de la carpeta `home`:
```bash
cd /home/user/
nano .profile
```
* Y para hacer efectivos los cambios en la sesión actual se debe invocar:
```bash
source .profile
```
## Preguntas
* _¿Qué prefieres: instalar binarios pre-compilados o compilar desde el código fuente?_
* _¿Por qué?_

[Anterior](instalacion-001.html) | [Siguiente](prueba-000.html)

<div class=coursetitle>Estás en el Nivel 1: Introducción a la programación paralela con OpenMP. <a href="main.html">¿Deseas volver al inicio?</a> </div>