#pragma once
#include <cmath>
#include <type_traits>
#include "smat.hpp"
#include "generic_ops.hpp"

template <size_t W, size_t H>
using MLMat = mat::sMat<float, W, H>;

template <typename T>
constexpr void SoftMaxMut(T first, T end)
{
    std::remove_reference_t<decltype(*first)> sum{};
    for (T ptr = first; ptr != end; ++ptr)
    {
        if (*ptr > 0)
        {
            sum += *ptr;
        }
    }
    for (T ptr = first; ptr != end; ++ptr)
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
constexpr MLMat<W2, H> MatrixMult(const MLMat<S, H>& a, const MLMat<W2, S>& b)
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
constexpr float MeanSquare(MLMat<1, 1> guess, MLMat<1, 1> actual) { return std::pow(guess.FastAt(0) - actual.FastAt(0), 2); }
constexpr float MeanSquarePrime(MLMat<1, 1> guess, MLMat<1, 1> actual) { return guess.FastAt(0) - actual.FastAt(0); }
template <size_t W>
constexpr float MeanSquare(MLMat<1, W> guess, MLMat<1, W> actual) 
{   
    float sum = 0.0f;
    for (size_t i = 0; i < W; ++i)
    {
        sum += std::pow(guess.FastAt(i) - actual.FastAt(i), 2);
    }
    return sum /= W;  
}
template <size_t W>
constexpr float MeanSquarePrime(MLMat<1, W> guess, MLMat<1, W> actual) 
{
    float sum = 0.0f;
    for (size_t i = 0; i < W; ++i)
    {
        sum += guess.FastAt(i) - actual.FastAt(i);
    }
    return sum /= W;  
}

// Forward Prop
template <size_t W, size_t H, typename T>
constexpr MLMat<W, H> HiddenForward(const MLMat<W, H>& inputs, const MLMat<W, 1>& biases, T&& activation_func) { return Operation(inputs, biases, [activation_func](float a, float b){ return activation_func(a + b); }); }

// Backward Prop
template <size_t W, typename T>
constexpr MLMat<W, 1> OutputBackward(MLMat<W, 1> cost, const MLMat<W, 1>& output, T&& activation_func_prime)
{
    MLMat<W, 1> res;
    for (size_t i = 0; i < output.Area(); ++i)
    {
        res.FastAt(i) = activation_func_prime(output.FastAt(i)) * cost;
    } 
    return res;
}
