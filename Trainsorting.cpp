#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void printMatrix(const vector<vector<int>> &mat)
{
    for (const auto &row : mat)
    {
        for (size_t j = 0; j < row.size(); ++j)
        {
            cout << row[j];
            if (j + 1 < row.size()) cout << ' ';
        }
        cout << '\n';
    }
    cout << "-------------------------------------" << endl;
}

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

int trainSorting(vector<int> &carros)
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
        
        // cout << "Número a procesar: " << carros[contador] << "  // Indice X: " << indiceX << " // Indice Y: " << indiceY << endl;
        for(int i = 0; i < contador; i++){
            if (indiceX == -1 || organizacionCarros[i][indiceX] == 0){
                organizacionCarros[i][contador] = 0;//Misma columna
            } else {
                organizacionCarros[i][contador] = 1 + organizacionCarros[i][indiceX];//Misma columna
            }
            if (indiceY == -1 || organizacionCarros[indiceY][i] == 0){
                organizacionCarros[contador][i] = 0;//Misma fila
            } else {
                organizacionCarros[contador][i] = 1 + organizacionCarros[indiceY][i];//Misma fila
            }
        }
        
        contador++;
    }
    printMatrix(organizacionCarros);
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
    while (i < casosDePrueba){
        vector<int> carros;
        cin >> numeroCarros;
        for (int j = 0; j < numeroCarros; j++){
            cin >> carro;
            carros.push_back(carro);
        }
        resultado.push_back(trainSorting(carros));
        i++;
    }
    cout << "------" << endl; 
    for (const int res : resultado){
        cout << res << endl;
    }
    return 0;
}