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

    //Ordeno las distancias de menor a mayor
    vector<unsigned int> ordenado;
    for (int i = 0; i < dist.size(); ++i) {
        ordenado[i] = dist(i);
    }
    sort(ordenado.begin(), ordenado.end()); //Los ordeno ascendentemente

    //Me quedo con los primeros 'k' indices ordenados
    // (el primer elemento de la tupla es la # de apariciones del tag)
    vector< pair<double,unsigned int> > tags(k_);
    for (unsigned int i = 0; i < k_; ++i) {
        tags[i] = make_pair(1, ordenado[i]); //Seteo las apariciones en 1 y abajo las completo
    }

    /** Hasta aca creo que va ok **/

    // Itero sobre mi vector para ver cuantas veces aparece cada tag
    // Tambien elimino indices con tags repetidos
    for (unsigned int i = 0; i < tags.size(); ++i) {
        for (unsigned int j = i + 1; j < tags.size(); ++j) {
            //Sii mi elemento se repite
            if ( tags[j].second == tags[i].second) {
                //Sumo su cantidad de apariciones, y borro el indice repetido
                tags[i] = make_pair(tags[i].first++, tags[i].second);
                //Como mi vector tendra un indice menos, hago que el 'j' no cambie
                j--;
            }
        }
    }

    //Me quedo con la moda
    unsigned int modaIndice = 0; //Inicio lo que sera el indice del tag que mas aparece
    for (unsigned int i = 1; i < tags.size(); ++i) {
        if (tags[i].first > tags[modaIndice].first) {
            modaIndice = i;
        }
    }
    double moda = tags[modaIndice].second; //Me quedo con el tag de mas apariciones
    return moda;
}

Vector KNNClassifier::predict(Matrix X)
{
    // Creamos vector columna a devolver
    auto ret = Vector(X.rows());

    for (unsigned k = 0; k < X.rows(); ++k)
    {
        ret(k) = predictRow(X.row(k));
    }

    return ret;
}
