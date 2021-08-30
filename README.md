<div align="center">

<h1>PPM Operations</h1>
<h3>Trabajo Final de Seminario de Lenguajes C</h3>
</div>

<div align="center">

[![Build, Test and Memory Check Status][workflowbadge]][workflowurl]
[![License: MIT][licensebadge]][licenseurl]

</div>

Este programa es un gestor de imágenes en formato [PPM de tipo P6](http://netpbm.sourceforge.net/doc/ppm.html).
Para poder operar con estas imágenes se implementó una versión simplificada y
básica de **ppm** que básicamente permite crear nuevas imágenes, leerlas desde
el disco o guardarlas en el disco.

La implementación de ppm, puede verse en los archivos `src/ppm.c` y `include/ppm.h`. Para
poder realizar operaciones sobre las imágenes, existe otra librería llamada
**ppm-operations**. Esta librería ofrece funciones de transformación de imágenes
respetando siempre la idea de devolver una nueva imagen transformada a partir de
la imagen original.

## Quickstart

Para compilar y ejecutar el programa:

```sh
$ git clone https://github.com/Maqui-LP/ppm-operations.git
$ cd ./ppm-operations
$ make
$ ./bin/ppm --help
```

## Operaciones

Para realizar operaciones sobre las imagenes, el programa cuenta con los siguientes flags:

- `-i entrada.ppm`: archivo origen. Opción requerida
- `-o salida.ppm` o `--output salida.ppm`: archivo salida. Opción requerida
- `-n` o `--negative`: calcula el negativo
- `-r` o `--rotate`: rota a 90 grados
- `-h` o `--horizontal`: espejo horizontal
- `-v` o `--vertical`: espejo vertical
- `-s` o `--sepia`: filtro sepia
- `-g` o `--grayscale`: filtro escala de grises
- `-w` o `--black-white`: filtro blanco y negro
- `-b NUM` o `--blur NUM`: desenfoque con radio NUM
- `-?` o `--help`: ayuda del programa

## Ejemplos de uso

### Copia de una imagen

```sh
$ ./bin/ppm -i input.ppm -o output.ppm
```

### Calcula el negativo del origen

```sh
$ ./bin/ppm -i input.ppm -o output.ppm -n
```

### Rota una imagen, luego hace el espejo horizontal y luego el desenfoque

```sh
$ ./bin/ppm -i input.ppm -h -o output.ppm -b 2
```

### Ejemplos de imagenes

El directorio `./samples` tiene ejemplos de PPMs

## Tests

Para validar que el programa funciona correctamente, se cuenta con un GitHub Action que ejecutan tests de integración. Los mismos se pueden ejecutar localmente con el siguiente comando:

```sh
$ make test
```

## Memory Check

Para asegurar que el programa no cuenta con memory leaks, se cuenta con un Github Action que ejecuta pruebas de memoria utilizando Valgrind. Estas pruebas pueden ejecutarse localmente con el siguiente comando:

```sh
$ make valgrind
```

[workflowbadge]: https://github.com/Maqui-LP/ppm-operations/actions/workflows/ci.yml/badge.svg
[licensebadge]: https://img.shields.io/badge/License-MIT-blue.svg
[workflowurl]: https://github.com/Maqui-LP/ppm-operations/commits/main
[licenseurl]: https://github.com/Maqui-LP/ppm-operations/blob/main/LICENSE
