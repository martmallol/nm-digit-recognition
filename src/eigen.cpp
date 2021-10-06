#include <algorithm>
#include <chrono>
#include <iostream>
#include "eigen.h"

using namespace std;


pair<double, Vector> power_iteration(const Matrix& X, unsigned num_iter, double eps)
{
    Vector b = Vector::Random(X.cols());
    double eigenvalue;
    /***********************
     * COMPLETAR CODIGO
     **********************/
     Vector bOld(X.cols());
    for (int i = 0; i < num_iter; ++i) {
        bOld = b;
        b = bOld / bOld.squaredNorm();

        //Termino la iteracion si encontre el vector
        double cosAngle = b.transpose() * bOld;
        if ((1.0 - eps) < cosAngle <= 1.0) {
            i = num_iter;
        }
    }

    return make_pair(eigenvalue, b / b.norm());
}

pair<Vector, Matrix> get_first_eigenvalues(const Matrix& X, unsigned num, unsigned num_iter, double epsilon)
{
    Matrix A(X);
    Vector eigvalues(num); //Vector de autovalores
    Matrix eigvectors(A.rows(), num); //Matriz de autovectores (puesots en columna)

    /***********************
     * COMPLETAR CODIGO
     **********************/
    for (int i = 0; i < num; ++i) {
        pair<double, Vector> metodoPotencia = power_iteration(X, num_iter, epsilon);
        double eigenvalue = metodoPotencia.first; //Autovalor_i
        Vector v = metodoPotencia.second; //Autovector_i

        eigvalues(i) = eigenvalue; //Agrego autovalor_i
        eigvectors.col(i) = v; //Agrego autovector_i
        A = A - eigenvalue * (v * v.transpose());
    }

    return make_pair(eigvalues, eigvectors);
}
