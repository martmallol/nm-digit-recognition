#include <algorithm>
//#include <chrono>
#include <iostream>
#include "knn.h"

using namespace std;


KNNClassifier::KNNClassifier(unsigned int n_neighbors)
{
    k_ = n_neighbors;
}

void KNNClassifier::fit(Matrix X, Matrix y)
{
    x_ = X;
    y_ = y;
}


// Para calcular los 'k' vecinos mas cercanos voy a necesitar lo siguiente:
// 1 - Calculo la distancia entre mi vector y el resto.
// 2 - Agrego la distancia a un array
// 3 - Ordeno el array de distancias de menor a mayor.
// 4 - Me quedo con los primeros k indices ordenados
// 5 - Chequeo a que clase pertenece cada uno, y me quedo con la clase mas popular (la moda)
// 6 - Asigno dicha clase a la matriz pasada como parametro
double KNNClassifier::predictRow(Vector z) {
    //Calculo la distancia entre mi vector y el resto.
    Vector dist(x_.rows());
    for (int i = 0; i < x_.rows(); ++i) {
        dist(i) = (x_.row(i) - z).squaredNorm();
    }

    vector<unsigned int> ordenado;

    Vector tags(k_);

    //Me quedo con los primeros k indices ordenados
    for (int i = 0; i < k_; ++i) {
        tags(i) = ordenado[i];
    }

    // Hago un counting sort para ver cual tag tiene mas votos
    Vector countingSort(k_);
    for (int i = 0; i < k_; ++i) {
        countingSort[tags(i)]++;
    }

    //Me quedo con la moda
    double moda = countingSort(0);
    for (int i = 1; i < k_; ++i) {

    }
}

Vector KNNClassifier::predict(Matrix X)
{
    // Creamos vector columna a devolver
    auto ret = Vector(X.rows());

    for (unsigned k = 0; k < X.rows(); ++k)
    {
        ret(k) = 0;
    }

    return ret;
}
