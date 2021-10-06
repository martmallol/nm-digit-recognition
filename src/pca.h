#pragma once
#include "types.h"

class PCA {
public:
    PCA(unsigned int n_components);

    void fit(Matrix X);

    Eigen::MatrixXd transform(Matrix X);

    Matrix matrizDeCovarianza(Matrix A);

private:
    unsigned int n_;
    Matrix covarianza_;
    Vector autovalores_;
    Vector autovectores_;

    Vector media(Matrix A);
};
