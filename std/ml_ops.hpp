#pragma once
#include <cmath>
#include <type_traits>
#include "smat.hpp"
#include "arithmetic_ops.hpp"
#include "dependencies/pow.hpp"

template <size_t W, size_t H>
using MLMat = mat::sMat<float, W, H>;

template <typename T>
constexpr void SoftMaxMut(T first, T end)
{
    std::remove_reference_t<decltype(*first)> sum{};
    T ptr(first);
    for (;ptr != end; ++ptr)
    {
        if (*ptr > 0)
        {
            sum += *ptr;
        }
    }
    ptr = first;
    for (;ptr != end; ++ptr)
    {
        if (*ptr > 0)
        {
            *ptr /= sum;
        }
        else
        {
            *ptr = 0;
        }
    }
}

// TODO: faster matrix multiplications via SIMD and GPU
template <size_t W2, size_t H, size_t S>
constexpr MLMat<W2, H> MatMult(const MLMat<S, H>& a, const MLMat<W2, S>& b)
{
    MLMat<W2, H> res;
    for (size_t i = 0; i < H; ++i) 
    {
        for (size_t j = 0; j < W2; ++j) 
        {
            for (size_t k = 0; k < S; ++k) 
            {
                res.At(j, i) += a.At(k, i) * b.At(j, k);
            }
        }
    }
    return res;
}

// Wrapper
template <MATRIX_TYPENAME M>
class Transpose
{ 
private:
    M& _ref;
public:
    Transpose() noexcept = delete;
    Transpose(M& mat) noexcept : _ref(mat) {}

    using value_type = typename M::value_type;

    //Iterators
    constexpr value_type *begin() noexcept { return _ref.begin(); }
    constexpr value_type *end() noexcept { return _ref.end(); }
    constexpr const value_type *begin() const noexcept { return _ref.begin(); }
    constexpr const value_type *end() const noexcept { return _ref.end(); }

    //Size
    constexpr size_t Area() const noexcept { return _ref.Area(); }
    constexpr size_t Width() const noexcept { return _ref.Height(); }
    constexpr size_t Height() const noexcept { return _ref.Width(); }

    //Indexing
    constexpr value_type &At(size_t x, size_t y) noexcept { return _ref.At(y, x); }
    constexpr copy_fast_t<value_type> At(size_t x, size_t y) const noexcept { return _ref.At(y, x); }
    constexpr value_type &FastAt(size_t index) noexcept { return _ref.At(index / _ref.Height(), index % _ref.Height()); }
    constexpr copy_fast_t<value_type> FastAt(size_t index) const noexcept { return _ref.At(index / _ref.Height(), index % _ref.Height()); }
};

// Initializations
template <MATRIX_TYPENAME M, typename T>
constexpr void GenInit(M& mat, T&& func) 
{ 
    EXEC_IF_NOT_20(static_assert(CONSTEXPR_MATRIX(M) || RUNTIME_MATRIX(M), "GenInit: M must be a CONSTEXPR_MATRIX or RUNTIME_MATRIX"));
    for (auto& f : mat) { f = func(); } 
}

// Loss Functions
//     Regression
template <size_t W>
constexpr float MeanSquare(MLMat<W, 1> guess, MLMat<W, 1> actual) 
{   
    float sum = 0.0f;
    for (size_t i = 0; i < W; ++i) { sum += pow2(guess.FastAt(i) - actual.FastAt(i)); }
    return sum /= W;  
}
template <size_t W>
constexpr float MeanSquarePrime(MLMat<W, 1> guess, MLMat<W, 1> actual) 
{
    float sum = 0.0f;
    for (size_t i = 0; i < W; ++i) { sum += guess.FastAt(i) - actual.FastAt(i); }
    return sum /= W;  
}

// Forward Prop
template <size_t S, size_t W, size_t H>
constexpr MLMat<W, H> WeightForward(const MLMat<S, H>& inputs, const MLMat<W, S>& weights, const MLMat<W, 1>& biases)
{
    // TODO: optimize this to be added while matrix mult
    MLMat<W, H> res(MatMult(inputs, weights));
    if constexpr (H == 1) { AddMatMut(res, biases); }
    else
    {
        for (size_t i = 0; i < H; ++i)
        {
            for (size_t j = 0; j < W; ++j)
            {
                res.At(j, i) += biases.At(j, 0);
            }
        }
    }
    return res;
}
template <size_t W, size_t H, typename T>
constexpr MLMat<W, H> HiddenForward(const MLMat<W, H>& input, T&& activation_func) 
{
    MLMat<W, H> res;
    for (size_t i = 0; i < (W * H); ++i)
    {
        res.FastAt(i) = activation_func(input.FastAt(i));
    }
    return res;
}

// Backward Prop
