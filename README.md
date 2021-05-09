# Matrix 
a collection of zero cost matrix implementations for C++20.

Zero cost meaning the matrix abstraction provides programmatic utility without differing in performance from a hand written array manipulation. In

## [sMat](smat.hpp)
`STACK` based Matrix, use this where you would std::array. This implementation has the advantage of having constexpr support so that when applicable it can be done compile time

## [hMat](hmat.hpp)
`HEAP` based Matrix, use this where you would std::vector

## [Matrix Concept](cmat.hpp)
a concept to avoid the cost of vtable lookup, also allows for generic operations and matrix implementations being interchangable, if the requirements for the concept are implemented it can mesh with any existing matrix operation.

## [Operations](mat_ops.hpp)
a set of generic operations that work with any type that qualifies as a Matrix via the concept. Future devolopment may include support for CUDA operations. 

arithmetic operators are hand written to remove overhead, and generic operation functions are avaliable for anything else 
* `M` `Operation` for taking two matrices and applying a function to each index of both `func(a[0], b[1])`
* `void` `OperationMut` the same as above but intended to mutate `a` or `b` instead of using the returned value to form the resulting matrix
* `M` `ScalarOperation` the `Operation` function but with a value instead of another matrix
* `void` `ScalarOperationMut` scalar variant of OperationMut

if u want to do an operation that does not conform to the above then I recommend using `begin()`, `end()`, and `data()` methods with an existing std alg
