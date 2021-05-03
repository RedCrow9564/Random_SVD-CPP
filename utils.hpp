#ifndef UTILS_H
#define UTILS_H

#include <blaze/Math.h>
#define VectorType blaze::DynamicVector
#define MatrixType blaze::DynamicMatrix

namespace Utils {

template <class T>
void PrintMatrix(const MatrixType<T>& a) {

  for(size_t i=0UL; i < a.rows(); ++i ) {
    for(MatrixType<T>::ConstIterator it = a.cbegin(i); it != a.cend(i); ++it ) {
        std::cout << *it << ", ";
    }
    std::cout << "\n";
  }
}

template <class T>
void PrintMatrix(const MatrixType<std::complex<T>>& a) {

  double imaginary_part, real_part;

  for(size_t i=0UL; i < a.rows(); ++i ) {
    for(MatrixType<std::complex<T>>::ConstIterator it = a.cbegin(i); it != a.cend(i); ++it ) {
        real_part = it->real();
        imaginary_part = it->imag();
        std::cout << std::noshowpos << real_part;  //Print real part of the element.

        if (imaginary_part != 0.0) {
        std::cout << std::showpos << imaginary_part << "i";
        }

        std::cout << std::noshowpos << ", ";
    }
    std::cout << "\n";
  }
}

template <class T>
void PrintVector(const VectorType<T>& a) {
  for(VectorType<T>::ConstIterator it = a.cbegin(); it != a.cend(); ++it ) {
    std::cout << *it << ", ";
  }
}

template <class T>
void PrintVector(const VectorType<std::complex<T>>& a) {

  double imaginary_part, real_part;

  for(VectorType<std::complex<T>>::ConstIterator it = a.cbegin(); it != a.cend(); ++it ) {
    real_part = it->real();
    imaginary_part = it->imag();
    std::cout << std::noshowpos << real_part;  //Print real part of the element.

    if (imaginary_part != 0.0) {
      std::cout << std::showpos << imaginary_part << "i";
    }

    std::cout << std::noshowpos << ", ";
  }
}

template <class T>
inline MatrixType<T> DiagonalMatDot(const VectorType<T>& D, const MatrixType<T>& A) {

  const size_t m = A.rows();
  const size_t n = A.columns();
  MatrixType<T> prod{m, n};

  for(size_t i = 0; i < m; ++i ) {
    for(size_t j = 0; j < n; ++j ) {
      prod(i, j) = A(i, j) * D[i];
    }
  }

  return prod;
}

template<class T>
inline MatrixType<T> GenerateRandomMatrix(const unsigned long rows, const unsigned long columns, 
const double mean = 0.0, const double std = 1.0, const unsigned int seed = 42) {

  MatrixType<T> random_mat{rows, columns};
  std::mt19937 gen{seed};;
  std::normal_distribution<> d{mean, std};

  for(size_t i = 0; i < rows; ++i ) {
    for(size_t j = 0; j < columns; ++j ) {
      random_mat(i, j) = (T)d(gen);
    }
  }

  return random_mat;
}

template<class T>
inline MatrixType<T> RandomOrthonormalMat(const unsigned long data_size, const unsigned long columns, 
const double mean = 0.0, const double std = 1.0, const unsigned int seed = 42) {

  MatrixType<T> random_mat = GenerateRandomMatrix<T>(data_size, columns, mean, std, seed);
  MatrixType<T> Q, R;
  qr(random_mat, Q, R);
  return Q;
}


template <class T>
inline MatrixType<T> diag(VectorType<T> const& vec) {
  const int k = vec.size();
  MatrixType<double> sigma(k, k);

  for(size_t i = 0UL; i < sigma.rows(); ++i ) {
    for(size_t j = 0UL; j < sigma.columns(); ++j ) {
      if(i == j) {
        sigma(i, i) = vec[i];
      }
      else {
        sigma(i, j) = 0.0;
      }
    }
  }
  return sigma;
}


}
#endif /* UTILS_H */
