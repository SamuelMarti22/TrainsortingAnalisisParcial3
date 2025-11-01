#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


/*
* Nombre: trainSorting
* Parametros: 
*   - vector<int> &carros: Vector que contiene los pesos/números de los vagones
* Tipo de retorno: void
* Excepciones que produce: No maneja excepciones
* Descipción: Esta función resuelve el problema de ordenamiento de trenes donde necesitamos encontrar
* la secuencia más larga posible de vagones que pueden ser organizados para formar tanto
* una secuencia creciente como decreciente. Esto se logra calculando dos arreglos auxiliares que contienen
* las longitudes máximas de subsecuencias crecientes y decrecientes desde cada posición del vector original.
*/
void trainSorting(vector<int> &carros)
{
    // Definición de variables
    int tamano = carros.size();
    int mayorSolucion = 0; // Variable para almacenar la solución máxima encontrada
    int solucionParcial; 
    vector<int> MayoresCrecientes(tamano, 1); // Vector auxiliar para almacenar longitudes de subsecuencias decrecientes
    vector<int> MayoresDecrecientes(tamano, 1); // Vector auxiliar para almacenar longitudes de subsecuencias crecientes

    // Bucle principal para calcular las subsecuencias crecientes y decrecientes
    for (int i = tamano - 1; i >= 0; i--)
    {
        // variales para almacenar las longitudes máximas encontradas en cada iteración
        // con cada posición anteriormente calculada
        int maxCreciente = 1;
        int maxDecreciente = 1;

        // Bucle interno para comparar el elemento actual con los elementos posteriores
        for (int j = tamano - 1; j > i; j--)
        {
            // Comparar y actualizar las longitudes máximas según la relación entre los elementos
            if (carros[i] < carros[j])
            {
                if (MayoresCrecientes[j] + 1 > maxCreciente)
                {
                    maxCreciente = MayoresCrecientes[j] + 1;
                }
            }
            else
            {
                if (MayoresDecrecientes[j] + 1 > maxDecreciente)
                {
                    maxDecreciente = MayoresDecrecientes[j] + 1;
                }
            }
        }

        // Actualizar los vectores auxiliares con las longitudes máximas encontradas
        MayoresCrecientes[i] = maxCreciente;
        MayoresDecrecientes[i] = maxDecreciente;
        solucionParcial = maxCreciente + maxDecreciente - 1;

        // Actualizar la solución máxima si la parcial es mayor
        if (solucionParcial > mayorSolucion)
        {
            mayorSolucion = solucionParcial;
        }
    }

    // Imprimir la solución máxima encontrada
    cout << mayorSolucion << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Lee `casosDePrueba` casos; para cada caso lee `numeroCarros` y la lista de carros
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
        trainSorting(carros);
        i++;
    }
    return 0;
}