#pragma once
#include "dependencies/cmat.hpp"

namespace mat
{
    template <MATRIX_TYPENAME M, MATRIX_TYPENAME M2>
    constexpr void TruncCopy(const M &src, M2 &dest)
    {
        EXEC_IF_NOT_20(static_assert( (CONSTEXPR_MATRIX(M) || RUNTIME_MATRIX(M)) && (CONSTEXPR_MATRIX(M2) || RUNTIME_MATRIX(M2)), "TruncCopy: M and M2 must be a CONSTEXPR_MATRIX or RUNTIME_MATRIX"));
        for (size_t i = 0; i < dest.height(); ++i)
        {
            for (size_t j = 0; j < dest.width(); ++j)
            {
                if (j < src.width() && i < src.height())
                {
                    dest.at(j, i) = src.at(j, i);
                }
            }
        }
    }

    template <MATRIX_TYPENAME M>
    constexpr auto* Safefast_at(size_t index, M& mat)
    {
        EXEC_IF_NOT_20(static_assert(CONSTEXPR_MATRIX(M) || RUNTIME_MATRIX(M), "SafeFastAt: M must be a CONSTEXPR_MATRIX or RUNTIME_MATRIX"));
        return (index < mat.area())? &mat.fast_at(index):(typename M::value_type*)nullptr;
    }

    template <MATRIX_TYPENAME M>
    constexpr auto* Safeat(size_t x, size_t y, M& mat) 
    { 
        EXEC_IF_NOT_20(static_assert(CONSTEXPR_MATRIX(M) || RUNTIME_MATRIX(M), "SafeAt: M must be a CONSTEXPR_MATRIX or RUNTIME_MATRIX"));
        return (x < mat.width() && y < mat.height())? &mat.at(x, y):(typename M::value_type*)nullptr;
    }
};
