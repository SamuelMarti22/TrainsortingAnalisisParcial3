#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Imprime una matriz (vector de vectores) por filas.
// Cada fila se imprime en una línea y los elementos se separan por un espacio.
// Parámetros:
//  - mat: referencia constante a la matriz a imprimir.
// Nota: función auxiliar para depuración/visualización; no modifica la matriz.
void printMatrix(const vector<vector<int>> &mat)
{
    for (const auto &row : mat)
    {
        for (size_t j = 0; j < row.size(); ++j)
        {
            cout << row[j];
            if (j + 1 < row.size())
                cout << ' ';
        }
        cout << '\n';
    }
    cout << "-------------------------------------" << endl;
}

// Devuelve el valor máximo entre los elementos de la última fila y la última columna.
// Precondición: la matriz debe tener al menos una fila/columna (mat.size() > 0).
// Si la matriz no es cuadrada, la función asume que la última columna existe (índice n-1
// para cada fila). Se usa en el algoritmo para obtener el mayor valor acumulado en
// los bordes/sentíneles de la matriz de organización.
int maxUltimaFilaColumna(const vector<vector<int>> &mat)
{
    size_t n = mat.size();
    int maxv = 0;
    // recorrer última fila (índice n-1)
    for (size_t j = 0; j < n; ++j)
        maxv = max(maxv, mat[n - 1][j]);
    // recorrer última columna (índice n-1)
    for (size_t i = 0; i < n; ++i)
        maxv = max(maxv, mat[i][n - 1]);
    return maxv;
}

vector<int> ultimaColumna(const vector<vector<int>> &mat)
{
    if (mat.empty()) return {};
    size_t n = mat.size();
    vector<int> col(n);
    for (size_t i = 0; i < n; ++i)
    {
        // toma el elemento de la última columna (índice n-1)
        col[i] = mat[i][n - 1];
    }
    return col;
}

// ------------------------------------------------------------------
// Función auxiliar: ultimaColumna
// Devuelve un vector con los valores de la última columna de la matriz `mat`.
// - Si `mat` está vacía, devuelve un vector vacío.
// Uso: facilita pasar la última columna a otras funciones sin exponer la matriz completa.
// ------------------------------------------------------------------

// Busca el índice (posición) del elemento candidato con mayor "valor" entre
// las posiciones [0..contador].
// Parámetros:
// - carros: vector con los pesos/valores principales (ej. tamaños de carros)
// - valores: vector paralelo con valores acumulados/auxiliares usados para comparar
// - contador: índice límite (se busca entre 0..contador)
// - fila: si true, se aplica la condición de búsqueda para "fila" (carros[i] > carros[contador]);
//         si false, se aplica la condición contraria (carros[i] < carros[contador]).
// Retorna:
// - el índice del elemento elegido o -1 si no existe ninguno que cumpla la condición.
// Nota: `valores` se pasa por referencia no-const porque el código original lo utiliza así;
// si `valores` no se modifica en la función, se puede cambiar a `const vector<int>&`.
int indiceMayor(vector<int> &carros, vector<int> &valores, int contador, bool fila)
{
    int indiceMayor = -1;
    int valorMayor = -1;
    int valorActual;
    for (int i = contador; i >= 0; i--)
    {
        if (fila)
        {
            if (carros[i] > carros[contador])
            {
                if (valores[i] > valorMayor)
                {
                    valorMayor = valores[i];
                    indiceMayor = i;
                }
                else if (valores[i] == valorMayor)
                {
                    if (carros[indiceMayor] - carros[contador] > carros[i] - carros[contador])
                    {
                        indiceMayor = i;
                    }
                }
            }
        }
        else
        {
            if (carros[i] < carros[contador])
            {
                if (valores[i] > valorMayor)
                {
                    valorMayor = valores[i];
                    indiceMayor = i;
                }
                else if (valores[i] == valorMayor)
                {
                    if (carros[contador] - carros[indiceMayor] > carros[contador] - carros[i])
                    {
                        indiceMayor = i;
                    }
                }
            }
        }
    }
    return indiceMayor;
}

// vector<int> menorDistancia(int contador, vector<int> &carros)
// {
//     int indiceX, indiceY, minimaRestaY, minimaRestaX;
//     indiceX = -1;
//     indiceY = -1;
//     minimaRestaY = max(carros.begin(), carros.end()) - min(carros.begin(), carros.end());
//     minimaRestaX = max(carros.begin(), carros.end()) - min(carros.begin(), carros.end());
//     for (int i = contador; i >= 0; i--)
//     {
//         int resta = carros[contador] - carros[i];
//         if (resta < 0 && abs(resta) < minimaRestaY)
//         {
//             minimaRestaY = abs(resta);
//             indiceY = i;
//         }
//         else if (resta > 0 && resta < minimaRestaX)
//         {
//             minimaRestaX = resta;
//             indiceX = i;
//         }
//     }
//     vector<int> retorno = {indiceX, indiceY};
//     return retorno;
// }

int trainSorting(vector<int> &carros)
{
    // ------------------------------------------------------------------
    // Estructura de datos principal:
    // `organizacionCarros` es una matriz (n+1)x(n+1) donde las filas/columnas
    // 0..n-1 corresponden a relaciones entre los `carros` (índices reales) y
    // la fila/columna `n` se usa como fila/columna sentinela para almacenar
    // máximos acumulados por columna/fila. Esto facilita consultas y
    // actualizaciones de valores máximos sin recorrer toda la matriz.
    // ------------------------------------------------------------------
    vector<vector<int>> organizacionCarros(carros.size() + 1, vector<int>(carros.size() + 1, 0));

    // Caso base: si no hay carros (o entrada trivial), devolvemos 0.
    // (La comprobación `carros.size()==1 && carros[0]==0` conserva la lógica
    // original que trata una entrada concreta como caso especial).
    if((carros.size()==1 && carros[0]==0)||carros.size()==0){
        return 0;
    }
    // Inicialización básica: marcar como 1 las posiciones donde los valores
    // de `carros` son iguales. Esto establece una base de comparación
    // (por ejemplo sub-secuencias de longitud 1 entre elementos iguales).
    for (int i = 0; i < carros.size(); ++i)
    {
        for (int j = 0; j < carros.size(); ++j)
        {
            if (carros[i] == carros[j])
            {
                organizacionCarros[i][j] = 1;
            }
        }
    }
    int tamano = carros.size();
    // Inicializar la fila y columna sentinela (índice `tamano`) a 1. Estas
    // posiciones actúan como valores neutros/semilla: representan que desde
    // la frontera (sentinela) la contribución mínima es 1. Durante el
    // proceso se actualizarán con valores mayores cuando se detecten
    // extensiones de secuencias.
    for (int i = 0; i < organizacionCarros.size(); i++)
    {
        organizacionCarros[tamano][i] = 1;
        organizacionCarros[i][tamano] = 1;
    }
    int contador = 0;
    // Bucle principal: para cada elemento `contador` (desde 0 hasta n-1) se
    // intenta extender secuencias (por fila y por columna) con base en los
    // mejores índices previos.
    while (contador < carros.size())
    {
        int indiceX, indiceY;

        // Obtener la última columna (valores de la columna sentinela) en un
        // vector auxiliar. Esto permite pasarla a `indiceMayor` sin exponer la
        // matriz completa (y evita trabajar con referencias a temporales).
        vector<int> UltimaColumna = ultimaColumna(organizacionCarros);

        // Buscar los mejores candidatos previos usando `indiceMayor`:
        // - indiceX: mejor candidato para extender por columna (condición
        //   `fila=false` en `indiceMayor` significa que se busca carros[i] < carros[contador]).
        //   Se pasa `organizacionCarros[tamano]` (la fila sentinela) como vector
        //   de valores acumulados por columna.
        // - indiceY: mejor candidato para extender por fila (condición
        //   `fila=true` busca carros[i] > carros[contador]). Se pasa la última
        //   columna calculada arriba como vector de valores acumulados por fila.
        indiceX = indiceMayor(carros, organizacionCarros[tamano], contador, false);
        indiceY = indiceMayor(carros, UltimaColumna, contador, true);

        // Para cada posición anterior i (< contador) actualizamos dos cosas:
        // 1) la entrada [i][contador] (extensiones por columna usando indiceX)
        // 2) la entrada [contador][i] (extensiones por fila usando indiceY)
        // Además, tras calcular dichas extensiones actualizamos las filas/columnas
        // sentinela (`organizacionCarros[tamano][*]` y `organizacionCarros[*][tamano]`)
        // con los máximos locales para permitir consultas rápidas en iteraciones
        // siguientes.
        for (int i = 0; i < contador; i++)
        {
            // Actualización por columna: si no hay candidato válido (indiceX == -1)
            // o la relación previa es 0, la extensión es 0; en caso contrario
            // la extensión vale 1 + la extensión anterior en [i][indiceX].
            if (indiceX == -1 || organizacionCarros[i][indiceX] == 0)
            {
                organizacionCarros[i][contador] = 0; // no se puede extender por columna
            }
            else
            {
                organizacionCarros[i][contador] = 1 + organizacionCarros[i][indiceX]; // Extensión válida
                // Mantener el máximo por columna en la fila sentinela
                if (organizacionCarros[i][contador] > organizacionCarros[tamano][contador])
                {
                    organizacionCarros[tamano][contador] = organizacionCarros[i][contador];
                }
                // Mantener el máximo por fila en la columna sentinela
                if (organizacionCarros[i][contador] > organizacionCarros[i][tamano])
                {
                    organizacionCarros[i][tamano] = organizacionCarros[i][contador];
                }
            }

            // Actualización por fila: análoga a la anterior pero usando indiceY
            // y la información en `organizacionCarros[indiceY][i]`.
            if (indiceY == -1 || organizacionCarros[indiceY][i] == 0)
            {
                organizacionCarros[contador][i] = 0; // no se puede extender por fila
            }
            else
            {
                organizacionCarros[contador][i] = 1 + organizacionCarros[indiceY][i]; // Extensión válida
                // Actualizar máximos en sentinelas por columna y por fila
                if (organizacionCarros[contador][i] > organizacionCarros[tamano][i])
                {
                    organizacionCarros[tamano][i] = organizacionCarros[contador][i];
                }
                if (organizacionCarros[contador][i] > organizacionCarros[contador][tamano])
                {
                    organizacionCarros[contador][tamano] = organizacionCarros[contador][i];
                }
            }
        }

        // Avanzar al siguiente elemento a procesar.
        contador++;
    }
    return maxUltimaFilaColumna(organizacionCarros);
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int casosDePrueba;
    cin >> casosDePrueba;
    int numeroCarros;
    int i = 0;
    int carro;
    vector<int> resultado;
    while (i < casosDePrueba)
    {
        vector<int> carros;
        cin >> numeroCarros;
        for (int j = 0; j < numeroCarros; j++)
        {
            cin >> carro;
            carros.push_back(carro);
        }
        resultado.push_back(trainSorting(carros));
        i++;
    }
    for (const int res : resultado)
    {
        cout << res << endl;
    }
    return 0;
}

// main:
// Lee `casosDePrueba` casos; para cada caso lee `numeroCarros` y la lista de carros
// (valores enteros). Para cada conjunto llama `trainSorting` y almacena el resultado.
// Al final imprime todos los resultados, uno por línea.