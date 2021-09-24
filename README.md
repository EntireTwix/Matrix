# Matrix 
A header only zero overhead matrix library for C++20 or C++17 w/CUDA 

Zero overhead meaning the matrix abstraction provides programmatic utility without differing in performance from a hand written array manipulation.

A nice side effect of making operations very generic is any matrix implementation can interact with any other, you can use `stack` based matrices when size is known, recieving the performance advantages, and have them interact with `heap` based matrices with no consequence

## Usage

As this is header only, simply include the implementation(s) of your choice
```cpp
#include "hmat.hpp"
```
and/or
```cpp
#include "smat.hpp"
```

### Optional CUDA usage
#### Meson
```meson
matrix_dep = subproject('matrix').get_variable('matrix_dep')
```
for CUDA you can set the `matrix_use_cuda` meson feature option to `enabled`.

#### CMake
or with CMake
```cmake
add_subdirectory(Matrix)
target_link_libraries(${PROJECT_NAME} matrix_cuda)
```
aswell as 
`-DUSE_CUDA=true` when constructing your project.

**DISCLAIMER: CUDA is annoying in that its highest version is C++17**

## Implementation 

#### [sMat](smat.hpp)
`STACK` based Matrix, use this where you would `std::array`. This implementation has the advantage of having constexpr support so that when applicable it can be done compile time.

#### [hMat](hmat.hpp)
`HEAP` based Matrix, use this where you would `std::vector`

#### [Matrix Concept](matrix/std/dependencies/cmat.hpp) (C++20)
A concept that allows for generic operations and matrix implementations being interchangable, if the requirements for the concept are implemented it can mesh with any existing matrix operation

#### [Operations](matrix/std)
A set of generic zero overhead operations that work with any type that qualifies as a Matrix via the concept (if compiling with C++20). Use these operations if they exist for your purposes, otherwise look for an [STL alg](https://en.cppreference.com/w/cpp/algorithm), lastly if that too fails resort to implementing the function.

#### [CUDA Operations](subprojects/cuda)
**In Development**
GPU accelerated Matrix operations

### Overhead
the binaries were compared and no differences were found, meaning no overhead. This cannot be garaunteed for all operations however ideally it should hold.

hand written
```cpp
int main()
{
    using namespace mat;

    hMat<int> a(100,100);
    hMat<int> b(100,100);
    std::fill(a.begin(), a.end(), 3);
    std::fill(b.begin(), b.end(), 8);

    for(size_t i = 0; i < 10000; ++i)
    {
        a.FastAt(i) += b.FastAt(i);
    }
}
```
generic
```cpp
int main()
{
    using namespace mat;

    hMat<int> a(100,100);
    hMat<int> b(100,100);
    std::fill(a.begin(), a.end(), 3);
    std::fill(b.begin(), b.end(), 8);
    AddMatMut(a, b);
}
```
`AddMatMut` being a call to the generic operation `OperationMut`
```cpp
template <MATRIX_TYPENAME M, MATRIX_TYPENAME M2>
#ifdef HAS_CONCEPTS
requires AddableAs<typename M::type, typename M2::type>
#endif
constexpr void AddMatMut(M & a, const M2 &b)
{
    OperationMut(a, b, [](typename M::type &a, copy_fast_cv_t<typename M2::type> b) {
        a += b;
    });
}
```
```cpp
template <MATRIX_TYPENAME M, MATRIX_TYPENAME M2, typename F>
constexpr void OperationMut(M & a, const M2 &b, F &&func)
{
    for (size_t i = 0; i < b.Area(); ++i)
    {
        func(a.FastAt(i), b.FastAt(i));
    }
}
```
