# Tarea 1

## Introducción
Este README da instrucciones para configurar y correr el código de la Tarea 2. Para compilar y ejecutar el código de manera correcta, se tienen que seguir las siguientes instrucciones.

## Estructura de Directorios

Asegurarse de tener los siguientes directorios y archivos (algunos sacados del [repositorio del ramo](https://github.com/jmsaavedrar/eda_cppal)) al mismo nivel:

- `ADTs`: Contiene todos los archivos que están en las carpetas `include/Lists` y `src`, dentro del directorio `lLists` del repositorio.
- `maze`: Contiene los archivos que están dentro de `laberinto` (`maze.hpp` y `maze.cpp`), a exepción del directorio `test`.
- `build`: Directorio para guardar archivos de compilación de CMake.
- `main`: Archivo de ejecución principal.

## Instrucciones

1. Ubicarse en el directorio `build`.

2. Correr el siguiente comando de linea para generar los archivos necesarios para compilar con [CMake](#Cmake):
```bash
$ cmake .. 
```

3. Compilar el código usando `make`:
```bash
$ make
```

4. Ejecutar el código con el siguiente comando:
```bash
$ ./test [dimension] [x inicial] [x final]
```

Reemplazar `[dimension]` con el tamaño del laberinto cuadrado, `[x inicial]` con la ubicación del inicio en la primera fila partiendo desde 0 hasta n-1, y `[x final]` con la ubicacipon del objetivo en la última fila, desde 0 hasta n-1. Por ejemplo:
```bash
$ ./test 21 0 20
```
Dentro de las soluciones `solve_cola` y `solve_pila`, hay una línea de código comentada (`usleep()`) la cual se puede descomentar para poder ver de mejor manera la completación de cada laberinto. Y si es que se quiere que se ejecute de manera "real", hay que comentar todas las llamadas al método `print()` y `system("clear")` de `maze` dentro de `main` y de ambos algoritmos. Si es que se corre en windows, se tiene que usar `system("cls")`.

Se puede ver el [repositorio de la tarea](https://github.com/CodeByManu/Tarea2_EDA) como ejemplo de estructura.

## CMake
```CMake
cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_COMPILER "/usr/bin/c++")

# set the project name

project(laberinto
VERSION 1.0
LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

#add_subdirectory(src)
#add_subdirectory(tests)

add_executable(test main.cpp maze/maze.cpp ADTs/linkedList.cpp ADTs/node.cpp ADTs/queue.cpp ADTs/stack.cpp)
target_include_directories(test PUBLIC ${PROJECT_SOURCE_DIR}/include)

# add the executable
```