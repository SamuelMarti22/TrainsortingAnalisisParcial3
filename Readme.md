[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/lZPRGWOz)
# UVA-11456-Trainsorting

## Tercera Práctica: Programación Dinámica
Problema que consiste en identificar cuál es el número máximo de vagones que se pueden acomodar en un tren de manera que esten ordenados de mayor a menor, procesandolos en el orden en que llegan.

## Objetivo
El objetivo de esta práctica es resolver un problema utilizando programación dinámica. Como recordarán, la programación dinámica es una optimización de dividir para conquistar en la cual, cuando en la evaluación recursiva se repiten muchos cálculos, se mejora la eficiencia cambiando el orden de evaluación del árbol comenzando por las hojas y terminando en la raíz. Puede ser visto como adicionar memoria a la función recursiva, de manera que si se llama nuevamente con un parámetro ya evaluado, en lugar de ejecutar la función con  ese parámetro, se retorna el valor previamente calculado. 

## Problema
El problema a resolver se denomina *Trainsorting*. El enunciado lo encuentra anexo y también lo pueden consultar acá: [Online Judge - 11456 Trainsorting](https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=26&page=show_problem&problem=2451). Deben implementar la solución en cualquier lenguaje de programación aceptado por el juez en línea de UVA:

- ANSI C 5.3.0 - GNU C Compiler with options: -lm -lcrypt -O2 -pipe -ansi -DONLINE_JUDGE
- JAVA 1.8.0 - OpenJDK Java
- C++ 5.3.0 - GNU C++ Compiler with options: -lm -lcrypt -O2 -pipe -DONLINE_JUDGE
- PASCAL 3.0.0 - Free Pascal Compiler
- C++11 5.3.0 - GNU C++ Compiler with options: -lm -lcrypt -O2 -std=c++11 -pipe -DONLINE_JUDGE
- PYTH3 3.5.1 - Python 3

### Traducción del enunciado
# 11456 – Clasificación de Trenes (Trainsorting)

Erin es ingeniera. Conduce trenes.
También organiza los vagones dentro de cada tren. Prefiere colocar los vagones en **orden decreciente de peso**, con el vagón más pesado al frente del tren.

Desafortunadamente, ordenar vagones de tren **no es sencillo**. No se puede simplemente levantar un vagón y colocarlo en otro lugar. Es poco práctico insertar un vagón en medio de un tren existente.
Un vagón solo se puede agregar **al inicio** o **al final** del tren.

Los vagones llegan a la estación de tren en un **orden predeterminado**.
Cuando cada vagón llega, Erin puede:

- Agregarlo al inicio de su tren,
- Agregarlo al final, o
- Rechazarlo.

El tren resultante debe ser lo más largo posible, pero los vagones dentro de él deben estar ordenados por peso de forma **estrictamente decreciente** (de más pesado a más liviano de adelante hacia atrás).

Dado el peso de los vagones en el orden en que llegan, ¿cuál es la **longitud máxima** del tren que Erin puede formar?

---

## Entrada

- La primera línea contiene el número de casos de prueba.
- Los casos de prueba se presentan uno tras otro y tienen el siguiente formato:

- La primera línea contiene un entero `0 ≤ n ≤ 2000`, que representa el número de vagones.
- Cada una de las siguientes `n` líneas contiene un entero no negativo que representa el peso de un vagón.
- No hay dos vagones con el mismo peso.

---

## Salida

- La salida consiste en un solo número entero que indica **el número máximo de vagones** en el tren más largo que puede construirse con las restricciones dadas.

---

## Entrada de ejemplo

```
1
3
1
2
3
```

## Salida de ejemplo

```
3
```


## Evaluación

La evaluación está organizada de la siguiente manera:

20% - El programa debe pasar todos los casos de prueba de udebug [uDebug - UVA 11456 Trainsorting](https://www.udebug.com/Uva/11456). Recuerden que si se registran en udebug, tienen acceso a sugerencias sobre el problema.

40% - El programa debe para los casos de prueba del onlinejudge de UVA ([Online Judge - 11456 Trainsorting](https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=26&page=show_problem&problem=2451))

40% - La explicación de la solución utilizada y la calidad del código. Esto incluye:
1. Descripción del algoritmo. ¿Por qué funciona?

El algoritmo busca determinar la cantidad máxima de vagones que pueden formar un tren ordenado estrictamente decreciente de frente a cola, a partir de una secuencia de vagones carros que llegan en cierto orden.

Para resolverlo, se observa que la estructura óptima del tren es bitónica en valores: primero los vagones deben organizarse de forma creciente (al ir construyendo desde atrás hacia el frente), y luego decreciente (al descender hacia la cola). Esta idea se traduce en dos cálculos principales que se realizan para cada posición i dentro de la lista de carros.

En primer lugar, se calcula MayoresCrecientes[i], que representa la longitud de la mejor subsecuencia estrictamente creciente que termina en la posición i. Es decir, mide cuántos carros pueden colocarse antes de carros[i] siguiendo un orden de pesos ascendente.

Luego, se calcula MayoresDecrecientes[i], que corresponde a la longitud de la mejor subsecuencia estrictamente decreciente que parte desde la posición i hacia el final. Esto refleja cuántos carros pueden colocarse después de carros[i] siguiendo un orden descendente.

Cada índice i del arreglo se interpreta como un posible punto máximo o “pico” del tren, combinando la mejor subsecuencia creciente que llega a ese punto con la mejor subsecuencia decreciente que parte de él. La suma de ambas longitudes (MayoresCrecientes[i] + MayoresDecrecientes[i]) representa el tamaño del tren posible con ese pico. Dado que el carro en la posición i se cuenta dos veces, una al final de la parte creciente y otra al inicio de la decreciente, se resta uno para obtener el total real.

El resultado final del algoritmo es el máximo valor obtenido entre todos los índices i, es decir, el tamaño del tren más largo que puede formarse respetando las condiciones del problema.

Este enfoque funciona porque la propiedad de optimalidad se conserva por índice, no de manera global. Cada posición almacena la mejor solución parcial que termina o empieza en ese punto, garantizando que las subsecuencias construidas localmente puedan combinarse de manera óptima en el resultado final. Así se evita el error común de intentar construir el tren eligiendo un único “mejor carro previo” o un par global de mínimos y máximos, que descarta combinaciones válidas y puede perder la mejor configuración total.

2. Descripción del mecanismo recursivo: ¿Cuál es la variable que determina el tamaño del problema? ¿Cuáles son los casos triviales? ¿Cuál es la relación de recurrencia?

El tamaño del problema está determinado por la cantidad total de carros n, es decir, el número de vagones que llegan y deben organizarse para formar el tren. Cada carro representa una posible posición dentro de la secuencia final, y por lo tanto el problema completo puede verse como la combinación de todos los subproblemas definidos por cada índice i del vector carros.

Para cada uno de estos subproblemas se consideran dos aspectos:

La subsecuencia creciente que llega hasta el carro i, representada por MayoresCrecientes[i].

La subsecuencia decreciente que parte desde el mismo carro i, representada por MayoresDecrecientes[i].

El caso base ocurre cuando un carro no puede conectarse con ningún otro anterior o posterior que cumpla la condición de orden. En ese escenario, tanto MayoresCrecientes[i] como MayoresDecrecientes[i] valen 1, porque el propio carro forma por sí solo una subsecuencia válida de longitud mínima. Este caso se da naturalmente al inicio y al final del recorrido de los bucles, y también en cualquier punto donde no existan valores que permitan extender la secuencia respetando el orden estricto.

La relación de recurrencia se basa en aprovechar soluciones previamente calculadas para construir soluciones mayores.

En el caso de MayoresCrecientes, se toma el máximo entre todas las subsecuencias crecientes que terminan en posiciones anteriores j < i, y se agrega el carro actual i siempre que su valor sea estrictamente mayor que el del carro previo (carros[j] < carros[i]).
De esta manera, MayoresCrecientes[i] se define como 1 más la mejor subsecuencia creciente que termina antes de i y puede ser extendida con el carro actual.

De forma análoga, MayoresDecrecientes[i] se construye revisando todas las posiciones posteriores k > i, tomando el máximo entre las subsecuencias decrecientes que comienzan en esas posiciones, y extendiéndolas con el carro actual cuando su valor es estrictamente mayor que el siguiente (carros[k] < carros[i]).

Estas relaciones garantizan que cada nuevo valor se apoye en resultados previamente calculados y correctos, lo cual cumple la propiedad de subestructura óptima característica de la programación dinámica.
De este modo, al recorrer todo el vector se acumulan las longitudes óptimas tanto en el sentido creciente como en el decreciente, y el valor máximo obtenido al combinar ambas (MayoresCrecientes[i] + MayoresDecrecientes[i] - 1) representa la mejor solución posible para el tamaño total n.

3. Se revisará también la calidad del código. Algunos ejemplos de cosas que se penalizan:
    * Utilizar variables globales
    * Incluir en los ciclos cálculos que no cambian en cada iteración
    * Nombres arbitrarios de variables o funciones (aleatorios o sin ninguna relación con la semántica de la variable o la función)
