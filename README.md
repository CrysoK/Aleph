# Aleph

[![build-windows](https://github.com/CrysoK/Aleph/actions/workflows/build-windows.yml/badge.svg)](https://github.com/CrysoK/Aleph/actions/workflows/build-windows.yml)
[![test-windows](https://github.com/CrysoK/Aleph/actions/workflows/test-windows.yml/badge.svg)](https://github.com/CrysoK/Aleph/actions/workflows/test-windows.yml)
[![doxygen-deploy](https://github.com/CrysoK/Aleph/actions/workflows/doxygen.yml/badge.svg)](https://github.com/CrysoK/Aleph/actions/workflows/doxygen.yml)

## Introducción

*Aleph* es un lenguaje de programación experimental diseñado como una herramienta
educativa para aprender los fundamentos del diseño de lenguajes de programación.

Está orientado a estudiantes y desarrolladores interesados en entender los
conceptos fundamentales detrás de los intérpretes y la teoría de lenguajes
formales.

Para obtener más información sobre la sintaxis, la semántica y las
características de *Aleph*, consulta la [documentación](doc/README.md).

## Instalación

### Pre-compilado

Puedes descargar el intérprete listo para usar en Windows [aquí](https://github.com/CrysoK/Aleph/releases).

### Compilar

El único requisito para compilar el intérprete es tener un compilador de C
(recomendado: `gcc`).

Clona o descarga el repositorio. Luego ejecuta el comando del archivo
[`_gcc.cmd`](https://github.com/CrysoK/Aleph/blob/main/_gcc.cmd).

Si se modifican los archivos
[`scanner.l`](https://github.com/CrysoK/Aleph/blob/main/src/flex/scanner.l) o
[`parser.y`](https://github.com/CrysoK/Aleph/blob/main/src/bison/parser.y) se
debe ejecutar `flex` o `bison` respectivamente. Para facilitar la compilación se
puede usar `make`.

## Ejemplos

```rust
print("Hola mundo!")
// Python?
```

```rust
// Funciones recursivas
fn Fib(n) {
  if n <= 1 { return n }
  else { return Fib(n - 2) + Fib(n - 1) }
}
println(Fib(20))
```

```rust
// Funciones como argumento
fn map(f, iter) {
  let new = []
  for e in iter {
    new += [f(e)]
  }
  return new
}
fn doble(elem) { return elem * 2 }
let lista = [1, 2, 3, 4]
let dobles = map(doble, lista)
println(dobles)
```
