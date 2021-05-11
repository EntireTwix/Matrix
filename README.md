# Matrix 
a collection of header only zero cost matrix implementations for **C++20**

Zero cost meaning the matrix abstraction provides programmatic utility without differing in performance from a hand written array manipulation.

a nice side effect of making operations very generic is any matrix implementation can interact with any other, you can use `stack` based matrices when size is known, recieving the performance advantages, and have them interact with `heap` based matrices with no consequence

`cmat.hpp` and `mat_ops.hpp` use concepts a **C++20** exclusive feature. But besides those, the individual matrix implementations are compatible with **C++11** and up.

## Implementation 

#### [sMat](smat.hpp)
`STACK` based Matrix, use this where you would std::array. This implementation has the advantage of having constexpr support so that when applicable it can be done compile time

#### [hMat](hmat.hpp)
`HEAP` based Matrix, use this where you would std::vector

#### [Matrix Concept](cmat.hpp)
a concept to avoid the cost of vtable lookup, also allows for generic operations and matrix implementations being interchangable, if the requirements for the concept are implemented it can mesh with any existing matrix operation. The only downside to this approach vs inheritance is there is a lot of implementation overlap that usually a parent class would implement

#### [Operations](mat_ops.hpp)
a set of generic operations that work with any type that qualifies as a Matrix via the concept. Future devolopment may include support for CUDA operations. 

generic operation functions supplied with lambdas are avaliable, they come with no overhead
* `M Operation` for taking two matrices and applying a function to each index of both `func(a[0], b[1])`
* `void OperationMut` the same as above but intended to mutate `a` or `b` instead of using the returned value to form the resulting matrix
* `M ScalarOperation` the `Operation` function but with a value instead of another matrix `func(a[0], v)`
* `void ScalarOperationMut` scalar variant of OperationMut
* `void ForEach` effectively std::for_each

if u want to do an operation that does not conform to the above then I recommend making and then doing a PR so I can merge it in

### [Benchmarking](benchmarks)
testing any generic w/lambda vs hand written results in the same time, which means there is no overhead to the generic operation. This can be found [here](https://github.com/EntireTwix/Matrix/blob/main/benchmarks/handwritten_vs_generic.cpp)(all times in nanoseconds), 

also the instructions were compared and no differences were found

generic
```cpp
int main()
{
    using namespace mat;

    hMat<int> a(100,100);
    Fill(a, 3);
    hMat<int> b(100,100);
    Fill(b, 5);
    a+=b;
}
```
hand written
```cpp
int main()
{
    using namespace mat;

    hMat<int> a(100,100);
    Fill(a, 3);
    hMat<int> b(100,100);
    Fill(b, 5);

    for(size_t i = 0; i < 10000; ++i)
    {
        a.FastAt(i)+=b.FastAt(i);
    }
}
```
![image](https://user-images.githubusercontent.com/31377881/117786562-7eaadf80-b1fa-11eb-9d6f-3d0b8eb164a9.png)

the only ASM difference being the file names

+= being a call to the generic operation `OperationMut`
```cpp
template <Matrix M, Matrix M2>
requires AddableAs<typename M::type, typename M2::type>
constexpr void operator+=(M& a, const M2& b) 
{ 
  OperationMut(a, b, [](typename M::type& a, copy_fast_cv_t<typename M::type> b){ a+=b; }); 
}    
```
