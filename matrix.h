#ifndef UNTITLED22_MATRIX_H
#define UNTITLED22_MATRIX_H
#define MATRIX_SQUARE_MATRIX_IMPLEMENTED
#include <stdexcept>
#include <sstream>
#include <iostream>
#include <array>

class MatrixIsDegenerateError : public std::runtime_error {
  public:
  MatrixIsDegenerateError() : std::runtime_error("MatrixIsDegenerateError") {}
};
class MatrixOutOfRange : public std::out_of_range {
  public:
  MatrixOutOfRange() : std::out_of_range("MatrixOutOfRange") {}
};
template <class T, size_t N, size_t M>
class Matrix {
  public:
  T matrix_[N][M];
  T &operator()(size_t i, size_t j) {
    return matrix_[i][j];
  }
  const T &operator()(size_t i, size_t j) const {
    return matrix_[i][j];
  }
//  Matrix GetInversed() const {
//    if (Determinant() == 0) {
//      throw MatrixIsDegenerateError();
//    }
//
//  }
//  void Inverse() {
//    *this = GetInversed();
//  }
  T &At(size_t i, size_t j) {
    if (i >= N || j >= M) {
      throw MatrixOutOfRange();
    }
    return matrix_[i][j];
  }
  const T &At(size_t i, size_t j) const {
    if (i >= N || j >= M) {
      throw MatrixOutOfRange();
    }
    return matrix_[i][j];
  }
  constexpr size_t RowsNumber() const {
    return N;
  }
  constexpr size_t ColumnsNumber() const {
    return M;
  }
  Matrix &operator+=(const Matrix &matr) {
    for (size_t i = 0; i < N; ++i) {
      for (size_t j = 0; j < M; ++j) {
        matrix_[i][j] += matr.matrix_[i][j];
      }
    }
    return *this;
  }
  Matrix &operator-=(const Matrix &matr) {
    for (size_t i = 0; i < N; ++i) {
      for (size_t j = 0; j < M; ++j) {
        matrix_[i][j] -= matr.matrix_[i][j];
      }
    }
    return *this;
  }
  template<size_t K>
  Matrix<T, N, K> &operator*=(const Matrix<T, M, K> &matr) {
    Matrix<T, N, K> result;
    for (size_t i = 0; i < N; ++i) {
      for (size_t j = 0; j < K; ++j) {
        result(i, j) = 0;
        for (size_t k = 0; k < M; ++k) {
          result(i, j) += matrix_[i][k] * matr(k, j);
        }
      }
    }
    *this = result;
    return *this;
  }
  Matrix &operator*=(const T &num) {
    for (size_t i = 0; i < N; ++i) {
      for (size_t j = 0; j < M; ++j) {
        matrix_[i][j] *= num;
      }
    }
    return *this;
  }
  Matrix &operator/=(const T &num) {
    for (size_t i = 0; i < N; ++i) {
      for (size_t j = 0; j < M; ++j) {
        matrix_[i][j] /= num;
      }
    }
    return *this;
  }
  friend Matrix operator+(Matrix first, const Matrix second) {
    first += second;
    return first;
  }
  friend Matrix operator-(Matrix first, const Matrix second) {
    first -= second;
    return first;
  }
  template<size_t K>
  friend Matrix<T, N, K> operator*(const Matrix &first, const Matrix<T, M, K> &second) {
    Matrix<T, N, K> result;
    for (size_t i = 0; i < N; ++i) {
      for (size_t j = 0; j < K; ++j) {
        for (size_t k = 0; k < M; ++k) {
          result(i, j) += first.matrix_[i][k] * second.matrix_[k][j];
        }
      }
    }
    return result;
  }
  friend Matrix operator*(Matrix first, const T &num) {
    Matrix<T, N, M> result;
    for (size_t i = 0; i < N; ++i) {
      for (size_t j = 0; j < M; ++j) {
        result(i, j) = first.matrix_[i][j] * num;
      }
    }
    return result;
  }
  friend Matrix operator*(const T &num, Matrix second) {
    Matrix<T, N, M> result;
    for (size_t i = 0; i < N; ++i) {
      for (size_t j = 0; j < M; ++j) {
        result(i, j) = second.matrix_[i][j] * num;
      }
    }
    return result;
  }
  friend Matrix operator/(Matrix first, const T &num) {
    Matrix<T, N, M> result;
    for (size_t i = 0; i < N; ++i) {
      for (size_t j = 0; j < M; ++j) {
        result(i, j) = first.matrix_[i][j] / num;
      }
    }
    return result;
  }
  friend bool operator==(const Matrix &first, const Matrix &second) {
    for (size_t i = 0; i < N; ++i) {
      for (size_t j = 0; j < M; ++j) {
        if (first.matrix_[i][j] != second.matrix_[i][j]) {
          return false;
        }
      }
    }
    return true;
  }
  friend bool operator!=(const Matrix &first, const Matrix &second) {
    for (size_t i = 0; i < N; ++i) {
      for (size_t j = 0; j < M; ++j) {
        if (first.matrix_[i][j] != second.matrix_[i][j]) {
          return true;
        }
      }
    }
    return false;
  }
  friend std::ostream &operator<<(std::ostream &os, const Matrix &matrix) {
    for (size_t i = 0; i < N; ++i) {
      for (size_t j = 0; j < M; ++j) {
        os << matrix.matrix_[i][j];
        if (j < M - 1) {
          os << ' ';
        }
      }
      os << '\n';
    }
    return os;
  }
  friend std::istream &operator>>(std::istream &is, Matrix &matrix) {
    for (size_t i = 0; i < N; ++i) {
      for (size_t j = 0; j < M; ++j) {
        is >> matrix.matrix_[i][j];
      }
    }
    return is;
  }
};
template <class T, size_t N, size_t M>
Matrix<T, M, N> GetTransposed(const Matrix<T, N, M>& matrix) {
  Matrix<T, M, N> result;
  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0; j < M; ++j) {
      result(j, i) = matrix(i, j);
    }
  }
  return result;
}
template <class T, size_t N>
void Transpose(Matrix<T, N, N>& matrix) {
  for (size_t i = 0; i < N; ++i) {
    for (size_t j = i + 1; j < N; ++j) {
      std::swap(matrix(i, j), matrix(j, i));
    }
  }
}
template <class T, size_t N>
T Trace(Matrix<T, N, N>& matrix)  {
  T trace = 0;
  for (size_t i = 0; i < N; i++) {
    trace = trace + matrix(i, i);
  }
  return trace;
}
template <class T, size_t N>
T Determinant(Matrix<T, N, N>& matrix) {
  Matrix<T, N, N> temp = matrix;
  T det = 1;
  for (size_t i = 0; i < N - 1; i++) {
    if (temp(i, i) == 0) {
      size_t cur = i + 1;
      while (cur < N && temp(cur, i) == 0) {
        ++cur;
      }
      if (cur == N) {
        return 0;
      }
      for (size_t j = 0; j < N; ++j) {
        std::swap(temp(i, j), temp(cur, j));
      }
      det = -det;
    }
    for (size_t k = i + 1; k < N; k++) {
      T factor = -temp(k, i) / temp(i, i);
      for (size_t j = i; j < N; j++) {
        temp(k, j) += factor * temp(i, j);
      }
    }
  }
  for (size_t i = 0; i < N; ++i) {
    det *= temp(i, i);
  }
  return det;
}
template <class T, size_t N>
Matrix<T, N-1, N-1> Minor(const Matrix<T, N, N>& matrix, size_t row, size_t col) {
  Matrix<T, N-1, N-1> minor;
  size_t r = 0, c = 0;
  for (size_t i = 0; i < N; ++i) {
    if (i == row) continue;
    for (size_t j = 0; j < N; ++j) {
      if (j == col) continue;
      minor(r, c++) = matrix(i, j);
      if (c == N - 1) {
        c = 0;
        ++r;
      }
    }
  }
  return minor;
}

// Вычисление союзной матрицы
template <class T, size_t N>
Matrix<T, N, N> Adjoint(const Matrix<T, N, N>& matrix) {

  Matrix<T, N, N> adj;

  int sign = 1;
  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0; j < N; ++j) {
      Matrix<T, N-1, N-1> minor = Minor(matrix, i, j);
      adj(j, i) = sign * Determinant(minor);
      sign = -sign;
    }
    if (N % 2 == 0) {
      sign = -sign;
    }
  }

  return adj;
}

// Получение обратной матрицы
template <class T, size_t N>
Matrix<T, N, N> GetInversed(const Matrix<T, N, N>& matrix) {
  T det = Determinant(matrix);
  if (det == 0) {
    throw MatrixIsDegenerateError();
  }

  Matrix<T, N, N> adj = Adjoint(matrix);
  Matrix<T, N, N> inversed;

  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0; j < N; ++j) {
      inversed(i, j) = adj(i, j) / det;
    }
  }

  return inversed;
}
#endif  // UNTITLED22_MATRIX_H