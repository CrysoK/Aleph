# Documentación

## Introducción

Un programa en _Aleph_ es una lista de sentencias. Las sentencias se delimitan
con `;` o fin de línea. Algunas sentencias requieren de un bloque, que no es más
que una lista de sentencias encerrada entre `{` y `}`.

El lenguaje es _case sensitive_ (distingue entre mayúsculas y minúsculas).

Los comentarios inician con `//` y terminan al final de la línea.

La sintaxis completa en formato EBNF se puede consultar
[aquí](Sintaxis.ebnf).

La documentación del intérprete se genera con Doxygen y puede consultarse
[aquí](https://crysok.github.io/Aleph/).

## Tipos de datos

### Enteros (`int`)

Se definen combinando los dígitos del `0` al `9`.

```rust
123
```

Sus operaciones son:

- **Opuesto**

  ```rust
  -32 // -32
  --421 // 421
  ```

- **Suma**

  ```rust
  1 + 2 // 3
  ```

- **Resta**

  ```rust
  2 - 4 // -2
  ```

- **Multiplicación**

  ```rust
  2 * 2 // 4
  ```

- **División** (entera)

  ```rust
  3 / 2 // 1
  ```

### Átomos (`atom`)

Son las cadenas de caracteres usuales pero no pueden ser operadas. Se definen
entre comillas dobles o comillas simples.

```python
'abc123"{}[]'
"abc123'{}[]"
```

### Conjuntos (`set`)

Colecciones desordenadas de elementos únicos y de cualquier tipo.

Como características principales: no mantienen un orden específico de los
elementos, no permiten elementos duplicados, son mutables (se pueden modificar
después de su creación) y son heterogéneos (pueden contener elementos de
diferentes tipos).

```rust
{'b', 'a', {['d'], 'c'}, 'b'} // {'a', 'b', {'c', ['d']}}
// - El orden de los elementos puede cambiar.
// - El elemento 'b' duplicado se elimina automáticamente.
// - Puede contener elementos de diferentes tipos, incluyendo otros conjuntos.
```

Sus operaciones son:

- **Unión**

  ```rust
  {'a', 'b'} + {'c'} // {'a', 'b', 'c'}
  ```

- **Intersección**

  ```rust
  {'a', 'b'} * {'b' ,'c'} // {'b'}
  ```

- **Diferencia**

  ```rust
  {'a', 'b', 'c'} - {'b'} // {'a', 'c'}
  ```

- **Cardinal**

  ```rust
  #{'a', 'b', 'c'} // 3
  ```

- **Pertenencia**: devuelve `1` si el elemento está en el conjunto y `0` en caso
  contrario.

  ```rust
  'a' in {'a', 'b', 'c'} // 1
  ```

  La negación `not E in S` también puede escribirse como `E not in S`.

- **Eliminar**: caso especial de la sentencia [`del`](#eliminación).

  ```rust
  del 'a' in {'a', 'b', 'c'} // {'b', 'c'}
  ```

### Listas (`list`)

Colecciones ordenadas de elementos de cualquier tipo.

A diferencia de muchos lenguajes de programación, la **primera** posición se
indica con el índice `1`.

Como características principales: mantienen un orden específico de los
elementos, permiten elementos duplicados, son mutables (se pueden modificar
después de su creación) y son heterogéneas (pueden contener elementos de
diferentes tipos).

```rust
['b', 'a', {['d'], 'c'}, 'b'] // ['b', 'a', {['d'], 'c'}, 'b']
// - El orden de los elementos se mantiene.
// - Los elementos duplicados ('b') se conservan.
// - Puede contener elementos de diferentes tipos, incluyendo otras listas.
```

Sus operaciones son:

- **Concatenación**

  ```rust
  ['a'] + ['b', 'c'] // ['a', 'b', 'c']
  ```

- **Tamaño**

  ```c
  #['a', 'b', {'c'}, ['d']] // 4
  ```

- **Pertenencia**: devuelve la posición del elemento o `0` si no está en la
lista.

  ```rust
  {'c'} in ['a', 'b', {'c'}] // 3
  ```

  La negación `not E in L` también puede escribirse como `E not in L`.

- **Obtener**: los índices negativos se cuentan desde el último elemento.

  ```rust
  ['a', 'b', {'c'}][2] // 'b'
  ['a', 'b', 'c'][-1] // 'c'
  ```

- **Insertar**: inserción en una posición específica `i` (`!i`) o a su derecha
  (`i!`), desplazando los elementos siguientes una posición a la derecha.

  ```rust
  ['b', 'c'][1] = 'a'  // ['a', 'c']
  ['b', 'c'][!1] = 'a' // ['a', 'b', 'c']
  ['b', 'c'][1!] = 'a' // ['b', 'a', 'c']
  ```

- **Eliminar**: caso especial de la sentencia [`del`](#eliminación).

  ```rust
  del ['a', 'b', 'c'][-2] // ['a', 'c']
  ```

### Funciones (`fn`)

Las funciones en _Aleph_ pueden ser asignadas a variables, pasadas como
argumentos y retornadas como valores. [Más detalles](#funciones-como-valores).

```rust
fn doble(x) { return x * 2 }
let func = doble
println(func(5)) // 10
println(doble) // Función: doble(x)
```

### Indefinido (`undef`)

Tipo de dato especial asignado automáticamente a toda variable declarada hasta
que se le asigne un valor. Puede ser usado como valor falso. No existe como
valor literal, es decir, no hay una palabra reservada que lo represente.

```rust
let indefinido
println(indefinido) // Indefinido
```

### Nulo o vacío (`void`)

Tipo de dato especial usado como resultado de funciones que no definen un valor
de retorno. Puede ser usado como valor falso. No existe como valor literal, es
decir, no hay una palabra reservada que lo represente.

```rust
// Todas devuelven nulo
fn sin_valor_1() {
    println("Hola mundo!")
}
fn sin_valor_2() {
    println("Hola mundo!")
    return
}
fn sin_valor_3() {
    println("Hola mundo!")
    return sin_valor_1()
}
let nulo = sin_valor_3()
println(nulo) // Nulo
```

### Booleanos

No existe un tipo de dato booleano como tal. Por convención, las expresiones con
operaciones lógicas y relacionales devuelven `1` como verdadero y `0` como falso
pero no son los únicos valores que se pueden usar:

```js
// Falso:
0              // Entero cero
""             // Átomo vacío
''             // Átomo vacío
[]             // Lista vacía
{}             // Conjunto vacío
let indefinido // Indefinido
sin_valor()    // Nulo
// Verdadero: cualquier otro valor
```

Los operadores lógicos son `and`, `or` y `not`.

Los operadores relacionales son `==`, `!=`, `<`, `<=`, `>`, `>=`.

#### Comparación

Dados dos valores cualquiera, la comparación funciona de la siguiente manera:

1. Si sus IDs son iguales entonces son iguales.
2. Si sus tipos son diferentes, es un error.
3. Si son listas o conjuntos, se comparan sus elementos.
4. Si son enteros, se comparan como enteros.
5. Si son cadenas, se comparan como cadenas.
6. Si son nulos o indefinidos, son iguales.

## Variables

En _Aleph_ las variables son nombres que hacen referencia a valores (similar a
Python). Deben ser declaradas explícitamente antes de su uso.

### Declaración y asignación

Las variables se declaran usando `let`. No es necesario asignarles un valor
inmediatamente.

```rust
let x, y, z = 5, 6, 7 // Asignación múltiple
let nombre
let lista = [ { "abc" }, [ "def", {} ], "g" ] + [ "h" ]
// ...
nombre = "Pepe"
x, y, z = -z, -y, -x
```

### Eliminación

Operación inversa a la declaración. Elimina la referencia al valor, pero no
necesariamente el valor en sí mismo si hay otras referencias a él.

```rust
let a = "Hola"
println(a)  // Hola
del a
println(a)  // Error: variable 'a' no definida
```

### Alcance

Las variables tienen alcance de bloque. Esto significa que una variable
declarada dentro de un bloque (como en una función o un bucle) solo es accesible
dentro de ese bloque.

```rust
let x = 5
if 1 {
    let y = 10
    println(x, " ", y)  // 5 10
}
println(x)  // 5
println(y)  // Error: símbolo 'y' no declarado
```

### Asignación "aumentada"

Asignación en la que se reemplaza `=` por `+=`, `-=`, `*=` o `/=`.

En el caso de enteros, este tipo de asignación simplemente reduce el código:

```rust
let x = 5
id(x) // A
x += 1 // Exactamente lo mismo que `x = x + 1`
id(x) // B
println(x)  // 6
```

Cuando se trata de listas y conjuntos, además de reducir el código, modifica el
valor original:

```rust
let x = [1, 2, 3]
id(x) // A
x += [4, 5] // NO es lo mismo que `x = x + [4, 5]`
id(x) // A
println(x)  // [1, 2, 3, 4, 5]
```

En el primer caso el resultado es un nuevo entero mientras que en el segundo es
la misma lista pero con los elementos de la segunda lista insertados al final.
Lo mismo sucede con el resto de operaciones.

## Estructuras de control

### Selección simple

```rust
let a = 0
if a > 0 {
    println("Positivo")
} elif a < 0 { // Opcional
    println("Negativo")
} else { // Opcional
    println("Cero")
}
// Cero
```

### Repetición sobre un iterable

Cuando el iterable (conjuntos y listas) es una lista se crea la variable
especial `_i`, que contiene el índice del elemento actual. El iterable puede ser
modificado durante la ejecución de la estructura.

```rust
for elem in ["a", "b", "c"] {
    println(_i, " ", elem)
}
// 1 a
// 2 b
// 3 c
```

### Repetición condicional

```rust
let a = 2
while a > 0 {
    print(a, " ")
    a -= 1
}
// 2 1 
```

### Interrupción

Finaliza la ejecución de una estructura de repetición.

```rust
let iter = [1, 2, 3, 4, 5]
for e in iter {
    if e == 3 { break }
    print(e, " ")
}
// 1 2 
```

### Continuación

Omite el resto del bloque y avanza a la siguiente iteración de una estructura de
repetición.

```rust
iter = [1, 2, 3, 4, 5]
for e in iter {
    if e == 2 or e == 4  { continue }
    print(e, " ")
}
// 1 3 5
```

### Terminación

Finaliza la ejecución del programa.

```rust
fn fin() {
  println("Finalizando...")
  exit
  println("Esto no se ejecuta")
}
fin()
// Finalizando...
```

## Funciones

Las funciones en _Aleph_ son bloques de código reutilizables que pueden tomar
parámetros y devolver valores. Se definen utilizando la palabra clave `fn`,
seguida del nombre de la función, parámetros entre paréntesis y un bloque de
código entre llaves.

El nombre sigue las reglas de nombres de variables. Los parámetros son
opcionales. La sentencia `return` es opcional y puede encontrarse en cualquier
lugar del bloque.

```rust
fn cuadrado(x) {
    return x * x
}
```

Las funciones se invocan usando su nombre seguido de los argumentos entre
paréntesis.

```rust
println(cuadrado(5)) // 25
println(cuadrado(cuadrado(5)) + cuadrado(2)) // 629
```

### Número de argumentos variable

El parámetro especial `...` se puede utilizar al final de la lista de parámetros
para indicar que la función puede tomar cualquier cantidad de argumentos. Estos
argumentos pueden ser accedidos en el cuerpo de la función por la variable
especial `_args`, de tipo lista.

```rust
fn promedio(...) {
    let sum = 0
    for arg in _args {
        sum += arg
    }
    return sum / #_args
}
println(promedio(1, 2, 3, 4, 5)) // 3
```

### Funciones como valores

Las funciones pueden ser asignadas a variables, pasadas como argumento y
devueltas como resultado. Serían _first-class citizens_ de no ser porque **solo
pueden definirse en el ámbito global**.

```rust
fn map(f, iter) {
  let res = []
  for e in iter {
    res += [f(e)]
  }
  return res
}
fn doble(elem) { return elem * 2 }
let lista = [1, 2, 3, 4]
let dobles = map(doble, lista)
println(dobles) // [2, 4, 6, 8]
```

## Funciones nativas

_Aleph_ cuenta con funciones predefinidas para algunas tareas comunes en otros
lenguajes de programación.

### Entrada y salida

#### `print(...) -> void`

Imprime los argumentos.

#### `println(...) -> void`

Imprime los argumentos y agrega un salto de línea.

#### `input() -> atom`

:no_entry: No implementado

Devuelve la cadena ingresada por el usuario hasta el primer fin de línea.

### Sistema

#### `time() -> int`

Devuelve el resultado de la función `time` del lenguaje **C**.

### Intérprete

#### `id(x) -> int`

Devuelve la dirección en memoria del valor de `x`.

#### `refcnt(x) -> int`

Devuelve la cantidad de referencias al valor de `x` sin contar las referencias
de la propia función.

### Útiles

#### `range(desde, paso, hasta) -> list`

Devuelve una lista de enteros desde `desde` hasta `hasta` (inclusive) con un
salto de `paso`.

```rust
range(0, 5, 1) // [0, 1, 2, 3, 4, 5]
range(5, -1, 0) // [5, 4, 3, 2, 1, 0]
range(0, 2, 10) // [0, 2, 4, 6, 8, 10]
range(1, 1, 0) // []
```

#### `type(x) -> atom`

Devuelve una cadena con el tipo del valor de `x`.

```js
type(1) // 'int'
type("1") // 'atom'
type([1]) // 'list'
type({1}) // 'set'
let uno
type(uno) // 'undef'
type(sin_valor()) // 'void'
type(type) // 'fn'
```

#### `copy(x: t) -> t`

Devuelve una copia del valor de `x` completamente independiente de la original,
es decir, sin ninguna referencia entre ellas.

### Conversión

#### `lst(x) -> list`

  :no_entry: No implementado

  ```rust
  lst(1) // [1]
  lst("{1}") // ["{1}"]
  lst("['1']") // ["['1']"]
  lst({1}) // [1]
  lst(["1"]) // ["1"]
  ```

#### `set(x) -> set`

  :no_entry: No implementado

  ```rust
  set(1) // {1}
  set("[1]") // {"[1]"}
  set("{'1'}") // {"{'1'}"}
  set([1]) // {1}
  set({"1"}) // {"1"}
  ```

#### `str(x) -> atom`

  :no_entry: No implementado

  ```rust
  str(1) // "1"
  str("[1]") // "[1]"
  str("{'1'}") // "{'1'}"
  str([1]) // "[1]"
  str({"1"}) // '{"1"}'
  ```

#### `int(x) -> int`

  :no_entry: No implementado

  ```rust
  int(1) // 1
  int("1") // 1
  int("a") // Error
  int([1]) // Error
  int({"1"}) // Error
  ```
