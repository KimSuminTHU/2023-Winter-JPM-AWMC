#ifndef MATRIX_UTILS_H
#define MATRIX_UTILS_H

#include <vector>

class MatrixUtils {
public:
    static std::vector<std::vector<double>> buildSymmetricMatrix(const std::vector<std::vector<double>>& lowerTriangle);
};

#endif
