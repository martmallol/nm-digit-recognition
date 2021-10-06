#include <iostream>
#include "pca.h"
#include "eigen.h"

using namespace std;


PCA::PCA(unsigned int n_components)
{

}

void PCA::fit(Matrix X)
{
}


MatrixXd PCA::transform(Matrix X)
{
  throw std::runtime_error("Sin implementar");
}

/*
 * Para realizar el metodo necesito:
 * Tenemos n muestras de m variables. LISTO
 * Calculamos el vector µ que contiene la media de cada de una las
   variables. LISTO
 * Construimos la matriz X ∈ R^n×m donde cada muestra corresponde a una
   fila de X y tienen media cero (ej:, x^(i) = (x^(i) − µ) / sqrt(n − 1)). LISTO
 * Diagonalizamos la matriz de covarianzas Mx . La matriz V (ortogonal)
   contiene los autovectores de Mx .
 */

Vector PCA::media(Matrix A) {
    int n = A.rows();
    int m = A.cols();
    Vector mu = A.row(0);; //Vector de la media

    //Sumo todas las filas de A
    for (int i = 1; i < n; ++i) {
        mu = mu + A.row(i);
    }

    //Calculo el promedio en cada indice
    for (int i = 0; i < m; ++i) {
        mu(i) = mu(i) / (double)n;
    }

    return mu;
}

Matrix PCA::matrizDeCovarianza(Matrix A) {
    Matrix X = A;
    int n = A.rows();
    Vector mu = media(A);

    //Calculo la matriz X
    for (int i = 0; i < n; ++i) {
        X.row(i) = X.row(i) - mu;
        //X.row(i) / sqrt ((double)n - 1.0);
    }

    //Calculo X^t * X / (n-1) Osea, la matriz de covarianza
    Matrix covarianza = X.transpose() * X / ((double)n - 1.0);
    return covarianza;
}