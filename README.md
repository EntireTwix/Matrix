# Matrix 
A header only zero overhead matrix library for C++20 or C++17 w/CUDA 

Zero overhead meaning the matrix abstraction provides programmatic utility without differing in performance from a hand written array manipulation.

A nice side effect of making operations very generic is any matrix implementation can interact with any other, you can use `stack` based matrices when size is known, recieving the performance advantages, and have them interact with `heap` based matrices with no consequence

## Usage

The recommended way to use Matrix in your project is as a subproject with the meson build system. Get the dependency object like this:
```meson
matrix_dep = subproject('matrix').get_variable('matrix_dep')
```

#### Optional CUDA usage
for CUDA you can set the `matrix_use_cuda` meson feature option to `enabled`.

**DISCLAIMER: CUDA is annoying in that its highest version is C++17**

## Implementation 

#### [sMat](smat.hpp)
`STACK` based Matrix, use this where you would `std::array`. This implementation has the advantage of having constexpr support so that when applicable it can be done compile time

#### [hMat](hmat.hpp)
`HEAP` based Matrix, use this where you would `std::vector`

#### [Matrix Concept](cmat.hpp) (C++20)
A concept to avoid the cost of vtable lookup, also allows for generic operations and matrix implementations being interchangable, if the requirements for the concept are implemented it can mesh with any existing matrix operation. The only downside to this approach vs inheritance is there is a lot of implementation overlap that usually a parent class would implement.

#### [Operations](operations/std)
A set of generic operations that work with any type that qualifies as a Matrix via the concept (if compiling with C++20)

Generic operation functions supplied with lambdas are avaliable, they come with no overhead
* `M Operation` for taking two matrices and applying a function to each index of both `func(a[0], b[1])`
* `void OperationMut` the same as above but intended to mutate `a` or `b` instead of using the returned value to form the resulting matrix
* `M ScalarOperation` the `Operation` function but with a value instead of another matrix `func(a[0], v)`
* `void ScalarOperationMut` scalar variant of OperationMut

if you want to do an operation that does not conform to the above then I recommend making and then performing a PR so I can merge it in

#### [CUDA Operations](operations/cuda)
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
    Fill(a, 3);
    Fill(b, 5);

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
    Fill(a, 3);
    Fill(b, 5);
    AddMatMut(a, b);
}
```
`+=` being a call to the generic operation `OperationMut`
```cpp
template <MATRIX_TYPENAME M, MATRIX_TYPENAME M2>
#ifdef HAS_CONCEPTS 
requires AddableAs<typename M::type, typename M2::type>
#endif
constexpr void AddMatMut(M& a, const M2&b) 
{ 
    OperationMut(a, b, [](typename M::type& a, copy_fast_cv_t<typename M::type> b){ 
        a+=b; 
    }); 
}
```
```cpp
template <MATRIX_TYPENAME M, MATRIX_TYPENAME M2, typename F>
constexpr void OperationMut(M &a, const M2& b, F &&func)
{
    for (size_t i = 0; i < b.Area(); ++i)
    {
        func(a.FastAt(i), b.FastAt(i));
    }
}
```
