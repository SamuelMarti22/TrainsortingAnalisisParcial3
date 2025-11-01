#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int trainSorting(vector<int> &carros)
{
    int tamano = carros.size();
    // Inicializar los vectores con tamaño `tamano` y valor base 1.
    // Cada posición i almacenará la longitud máxima de la secuencia
    // creciente/decreciente que empieza en i (considerando el algoritmo
    // que recorre desde la derecha hacia la izquierda).
    vector<int> MayoresCrecientes(tamano, 1);
    vector<int> MayoresDecrecientes(tamano, 1);
    int mayorSolucion = 0;
    int solucionParcial;
    for (int i = tamano - 1; i >= 0; i--)
    {
        int maxCreciente = 1;
        int maxDecreciente = 1;
        for (int j = tamano - 1; j > i; j--)
        {
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
        MayoresCrecientes[i] = maxCreciente;
        MayoresDecrecientes[i] = maxDecreciente;
        solucionParcial = maxCreciente+maxDecreciente-1;
        if (solucionParcial > mayorSolucion){
            mayorSolucion = solucionParcial;
        }
    }

    return mayorSolucion;
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