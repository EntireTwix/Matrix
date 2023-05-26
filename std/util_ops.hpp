#pragma once
#include "dependencies/cmat.hpp"

namespace mat
{
    template <MATRIX_TYPENAME M, MATRIX_TYPENAME M2>
    constexpr void TruncCopy(const M &src, M2 &dest)
    {
        EXEC_IF_NOT_20(static_assert( (CONSTEXPR_MATRIX(M) || RUNTIME_MATRIX(M)) && (CONSTEXPR_MATRIX(M2) || RUNTIME_MATRIX(M2)), "TruncCopy: M and M2 must be a CONSTEXPR_MATRIX or RUNTIME_MATRIX"));
        for (size_t i = 0; i < dest.get_height(); ++i)
        {
            for (size_t j = 0; j < dest.get_width(); ++j)
            {
                if (j < src.get_width() && i < src.get_height())
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
        return (index < mat.get_area())? &mat.fast_at(index):(typename M::value_type*)nullptr;
    }

    template <MATRIX_TYPENAME M>
    constexpr auto* Safeat(size_t x, size_t y, M& mat) 
    { 
        EXEC_IF_NOT_20(static_assert(CONSTEXPR_MATRIX(M) || RUNTIME_MATRIX(M), "SafeAt: M must be a CONSTEXPR_MATRIX or RUNTIME_MATRIX"));
        return (x < mat.get_width() && y < mat.get_height())? &mat.at(x, y):(typename M::value_type*)nullptr;
    }
};
