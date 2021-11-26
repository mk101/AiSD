#include "TMatrix.h"
#include <omp.h>
#include <iomanip>

void printMatrix(int **a, size_t size) {
  for (size_t i = 0; i < size; i++) {
    std::cout << std::endl;
    for (size_t j = 0; j < size; j++) {
      std::cout << std::setw(5) << a[i][j] << ' ';
    }
  }
}

std::pair<double, double> test(size_t size) {
  int **baseMatrixA = new int*[size];
  int **baseMatrixB = new int*[size];
  int **baseResultMatrix = new int*[size];
  for (size_t i = 0; i < size; i++) {
    baseMatrixA[i] = new int[size];
    baseMatrixB[i] = new int[size];
    baseResultMatrix[i] = new int[size];
  }

  TMatrix<int> tMatrixA(size);
  TMatrix<int> tMatrixB(size);

  for (size_t i = 0; i < size; i++) {
    for (size_t j = 0; j < i; j++) {
      baseMatrixA[i][j] = 0;
      baseMatrixB[i][j] = 0;
    }
    for (size_t j = i; j < size; j++) {
      baseMatrixA[i][j] = static_cast<int>(i*42 + j*24 + 10);
      tMatrixA[i][j-i] = static_cast<int>(i*42 + j*24 + 10);

      baseMatrixB[i][j] = static_cast<int>(i*36 - j * 6 + 160);
      tMatrixB[i][j-i] = static_cast<int>(i*36 - j * 6 + 160);
    }
  }

  double start = omp_get_wtime();
  for (size_t i = 0; i < size; i++) {
    for (size_t j = 0; j < size; j++) {
      int sum = 0;
      for (size_t k = 0; k < size; k++) {
        sum += baseMatrixA[i][k] * baseMatrixB[k][j];
      }
      baseResultMatrix[i][j] = sum;
    }
  }
  double end = omp_get_wtime();
  auto baseTime = end - start;

  start = omp_get_wtime();
  auto tRes = tMatrixA*tMatrixB;
  end = omp_get_wtime();
  auto tTime = end - start;

  for (size_t i = 0; i < size; i++) {
    delete[] baseMatrixA[i];
    delete[] baseMatrixB[i];
    delete[] baseResultMatrix[i];
  }
  delete[] baseMatrixA;
  delete[] baseMatrixB;
  delete[] baseResultMatrix;
  return {baseTime, tTime};
}

int main() {
  for (size_t i = 10000; i < 10001; i++) {
    auto t = test(i);
    std::cout << i << ") " << (t.first >= t.second ? "OK" : "MISS") << "{ " << t.first << " " << t.second << " }" << std::endl;
  }

  return 0;
}
