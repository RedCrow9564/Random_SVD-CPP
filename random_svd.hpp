#ifndef RANDOM_SVD_H
#define RANDOM_SVD_H

#include <tuple>
#include "utils.hpp"
#include "Matrices/matrices_forms.hpp"
#include <blaze/Math.h>
#define VectorType blaze::DynamicVector
#define MatrixType blaze::DynamicMatrix


namespace RandomSVD {

template <class T>
inline auto RandomSVD(const Matrices::Matrix<T>& A, const unsigned long k, 
    const unsigned long increment, const unsigned int seed = 42) {
  MatrixType<T> U, V_T;  // The matrix for the left and right singular vectors, respectively
  MatrixType<T> B, Q; // Temporary storage matrices.
  VectorType<T> s;  // The vector for the singular values
  const unsigned long m = A.rows();
  const unsigned long n = A.columns();

  //Multiplying A by a random matrix G.
  B = A * Utils::GenerateRandomMatrix<T>(n, k + increment, 0.0, 1.0, seed);
  svd(B, Q, s, V_T);  // Computing the singular values and vectors of A*G
  Q = submatrix(Q, 0UL, 0UL, m, k); // Taking only the first k left singular-vectors of A*G.
  svd(A.left_dot(trans(Q)), U, s, V_T); //Performing SVD on Q^{T} * A.
  U = Q * U; // Fixing the approximated U by multiplication with Q.
  return std::make_tuple(U, s, V_T);
}

}

#endif /* RANDOM_SVD_H */
