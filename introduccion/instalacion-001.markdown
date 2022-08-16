---
layout: page
title:  "Instalación manual de LLVM/Clang/OpenMP"
---
[Anterior](instalacion-000.html) | [Siguiente](instalacion-002.html)

Vamos a clonar el repositorio de LLVM directamente y lo vamos a compilar en nuestra máquina, ya que los binarios pre-compilados no llevan integrada aún la función de descarga de la ejecución en dispositivos aceleradores. Asumiremos que la raíz del home del usuario es `/home/user/`:
* Ir al home del usuario:
```bash
cd /home/user
```
* Crear una carpeta para almacenar tanto el código fuente como los binarios compilados:
```bash
mkdir llvm
cd llvm
```
* Clonar el repositorio usando git:
```bash
git clone https://github.com/llvm/llvm-project.git
```
Aparecerá una carpeta llamada `llvm-project`.
* Crear una carpeta dentro de `llvm` para almacenar los binarios compilados:
```bash
mkdir llvm-build
cd llvm-build
```
* Invocar CMake con los siguientes argumentos:
```bash
cmake -G Ninja 
    -DLLVM_ENABLE_PROJECTS="clang;clang-tools-extra;openmp" 
    -DLLVM_INSTALL_UTILS=ON -DCMAKE_BUILD_TYPE=Release 
    ../llvm-project/llvm/
```
* Compilar invocando:
```bash
ninja
```
Esto tomará un tiempo considerable pero nos asegurará disponer de una versión completa para la experimentación.
* Ahora, hay que modificar las variables de entorno que permiten invocar binarios sin ruta y ubicar las bibliotecas dinámicas. 
```bash
export LD_LIBRARY_PATH="/home/user/llvm/llvm-build/lib":
    "/home/user/llvm/llvm-build/projects/openmp/libomptarget":
    $LD_LIBRARY_PATH
```
```bash
export PATH="/home/user/llvm/llvm-build/bin":$PATH
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
* _Comenta tus experiencias en la instalación de paquetes en Linux a través de la compilación de código fuente._
* _¿Qué otros compiladores conoces?_


[Anterior](instalacion-000.html) | [Siguiente](instalacion-002.html)

<div class=coursetitle>Estás en el Nivel 1: Introducción a la programación paralela con OpenMP. <a href="main.html">¿Deseas volver al inicio?</a> </div>