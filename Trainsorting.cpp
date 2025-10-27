#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void trainSorting(vector<int> &carros)
{
    vector<vector<int>> organizacionCarros(carros.size(), vector<int>(carros.size(), 0));
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
    int contador = 1;
    while (contador < carros.size())
    {
        int filaComparar, columnaComparar, indiceX, indiceY, minimaRestaY, minimaRestaX;
        indiceX = -1;
        indiceY = -1;
        minimaRestaY = max(carros.begin(), carros.end()) - min(carros.begin(), carros.end());
        minimaRestaX = max(carros.begin(), carros.end()) - min(carros.begin(), carros.end());
        for (int i = contador; i >= 0; i--)
        {
            int resta = carros[contador] - carros[i];
            if (resta < 0 && abs(resta) < minimaRestaY)
            {
                minimaRestaY = abs(resta);
                indiceY = i;
            }
            else if (resta > 0 && resta < minimaRestaX)
            {
                minimaRestaX = resta;
                indiceX = i;
            }
        }
        contador++;
    }
}

int main()
{
    vector<int> carros = {5, 3, 8, 6, 2};
    trainSorting(carros);
    return 0;
}