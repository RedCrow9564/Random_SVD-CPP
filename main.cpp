#include <iostream>
#include <chrono>
#include <complex>
#include <cmath>
#include <blaze/Math.h>
#include "utils.hpp"
#include "Matrices/matrices_forms.hpp"
#include "random_svd.hpp"


using namespace std::chrono;

 
int main()
{
  const unsigned long rank = 14;
  const unsigned long k = 5;
  const unsigned long increment = 7;
  const unsigned long m = 20UL;
  const unsigned long n = 20UL;

  auto start = high_resolution_clock::now(); 
  const auto& a = Matrices::Matrix<double>::GenerateRandomMatrix(m, n, rank);
  auto end = high_resolution_clock::now();
  auto duration = duration_cast<microseconds>(end - start);
  std::cout << "Random Generation Duration: " << duration.count() << " microseconds" << std::endl; 

  start = high_resolution_clock::now();
  auto& [U, s, V_T] = RandomSVD::RandomSVD(a, k, increment);

  end = high_resolution_clock::now();
  duration = duration_cast<microseconds>(end - start);
  std::cout << "Random SVD Duration: " << duration.count() << " microseconds" << std::endl; 

  std::cout << "U: " << std::endl; 
  std::cout << U << std::endl;
  std::cout << "V_T: " << std::endl; 
  std::cout << V_T << std::endl;
  std::cout << "sigma:\n " << std::endl;
  std::cout << s << std::endl;
  

  std::cout << "\nError:\n " << std::endl; 
  std::cout << norm(U * Utils::DiagonalMatDot(s, V_T) - a.reconstruct()) << std::endl;
  return 0;
}
 