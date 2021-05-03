# Random SVD - C++
[![MIT License](https://img.shields.io/apm/l/atomic-design-ui.svg?)](https://github.com/tterb/atomic-design-ui/blob/master/LICENSEs)![GitHub last commit](https://img.shields.io/github/last-commit/RedCrow9564/Random_SVD-CPP)


A C++ implementation of a randomized algorithm for SVD decomposition (published in [[1]](#1)). This is the same algorithm implemented [here](https://github.com/RedCrow9564/SpectralMethodsProject-RandomSVD) (in Python).

## Getting Started

The code uses the [blaze](https://bitbucket.org/blaze-lib/blaze/src/master/) package for numerical computations in C++. This package is linked to LAPACK and OpenMP, which can be fetched from the Numpy Python package (LAPACK may be replaced with any equivalent implementations, such as MKL, ATLAS etc.).
Blaze itself can be fetched using the [conan](https://docs.conan.io/en/latest/getting_started.html) package manager via:
```
conan install ..
```
This command installs all packages enlisted in [conanfile.txt](conanfile.txt) (which is only blaze, in this case).
To compile this code for Windows, using the CMake system and the MSVC (Visual C++) compiler:
```
cmake .. -G "Visual Studio 16"
cmake --build . --config Release
```
These commands compile the code, according to the instructions in [CMakeLists.txt](CMakeLists.txt).
Then a folder named 'bin' is created, and it contains the compiled program 'main.exe'.
Executing this file presents a demonstration of this randomized algorithm on some inputs.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details

## References
<a id="1">[1]</a> [P.-G. Martinsson, V. Rokhlin, and M. Tygert. A randomized al-
gorithm for the decomposition of matrices. Applied and Computa-
tional Harmonic Analysis, 30(1):47—68, 2011](https://www.sciencedirect.com/science/article/pii/S1063520310000242).
