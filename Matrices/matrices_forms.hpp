#ifndef MATRICES_FORMS_H
#define MATRICES_FORMS_H

#include <iostream>
#include "utils.hpp"
#include <blaze/Math.h>
#define VectorType blaze::DynamicVector
#define MatrixType blaze::DynamicMatrix


namespace Matrices {

template<class T>
class Matrix
{
  private:
    MatrixType<T> _mat;
    explicit inline Matrix(const MatrixType<T>& m) {this->_mat = m;}

  protected:
    explicit inline Matrix() {}

  public:
    static Matrix<T> GenerateRandomMatrix(const unsigned long rows, const unsigned long columns, 
        const double mean = 0.0, const double std = 1.0, const unsigned int seed = 42) {
      MatrixType<T>& m = Utils::GenerateRandomMatrix<T>(rows, columns, mean, std, seed);
      return Matrix<T>(m);
    }

    virtual size_t rows() const {
      return this->_mat.rows();
    }
    virtual size_t columns() const {
      return this->_mat.columns();
    }
    virtual MatrixType<T> operator* (const MatrixType<T>& A) const {
      return this->_mat * A;
    }
    virtual MatrixType<T> left_dot(const MatrixType<T>& A) const {
      return A * this->_mat;
    }
    virtual MatrixType<T> reconstruct() const {
      return this->_mat;
    }
};

template<class T>
class SVDForm : public Matrix<T>
{
  private:
    MatrixType<T> U, V_T;
    VectorType<double> s;

  public:
    explicit inline SVDForm(const MatrixType<T>& U, const VectorType<double>& s, const MatrixType<T>& V)
    {
      this->U = U;
      this->s = s;
      this->V_T = trans(V);
    }

    size_t rows() const override {return this->U.rows();}
    size_t columns() const override {return this->V_T.columns();}
    MatrixType<T> left_dot (const MatrixType<T>& A) const override{
      return (A * this->U) * Utils::DiagonalMatDot(this->s, this->V_T);
    }

    MatrixType<T> operator* (const MatrixType<T>& A) const override{
      return this->U *Utils::DiagonalMatDot<T>(this->s, this->V_T * A);
    }

    inline static SVDForm<T> GenerateRandomMatrix(const unsigned long rows, const unsigned long columns, 
        const unsigned long rank, const double mean = 0.0, const double std = 1.0, 
        const unsigned int seed = 42) {
      MatrixType<T> U = Utils::RandomOrthonormalMat(rows, rank, mean, std, seed);
      MatrixType<T> V = Utils::RandomOrthonormalMat(columns, rank, mean, std, seed);
      VectorType<double> s = blaze::linspace(rank, 1e-3, 1e-5);
      Utils::PrintVector(s);
      return SVDForm<T>(U, s, V);
    }

    MatrixType<T> reconstruct() const override{
      return this->U *Utils::DiagonalMatDot<T>(this->s, this->V_T);
    }
};


}
#endif /* MATRICES_FORMS_H */
