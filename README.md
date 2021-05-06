# Matrix 
a collection of zero cost matrix implementations for C++20

## sMat (smat.hpp)
STACK based Matrix, use this where you would std::array

## hMat (hmat.hpp)
HEAP based Matrix, use this where you would std::vector

## Matrix Concept (cmat.hpp)
a concept to avoid the cost of vtable lookup, also allows for generic operations and matrix implementations being interchangable

## Operations (mat_ops.hpp)
a set of generic operations that work with any type that qualifies as a Matrix via the concept