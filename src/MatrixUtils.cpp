#include "MatrixUtils.h"

// 상관관계 행렬 대칭 복원
std::vector<std::vector<double>> MatrixUtils::buildSymmetricMatrix(const std::vector<std::vector<double>>& lowerTriangle) {
    int size = lowerTriangle.size();
    std::vector<std::vector<double>> matrix(size, std::vector<double>(size, 0.0));

    // 하삼각행렬을 대칭 복사하여 전체 상관관계 행렬을 만듬
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j <= i; ++j) {
            matrix[i][j] = lowerTriangle[i][j];
            matrix[j][i] = lowerTriangle[i][j];
        }
    }

    return matrix;
}
