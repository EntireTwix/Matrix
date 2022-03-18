#pragma once
#include <type_traits>
#include "smat.hpp"

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

// possibly suboptimal
template <size_t W2, size_t H, size_t S>
constexpr MLMat<W2, H> Dot(const MLMat<S, H>& a, const MLMat<W2, S>& b)
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

template <MATRIX_TYPENAME M, typename T>
constexpr void GenInit(M& mat, T&& func) { for(auto& f : mat) { f = func(); } }
