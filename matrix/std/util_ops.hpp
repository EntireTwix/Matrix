#pragma once
#include <optional>
#include "dependencies/is_vector.hpp"
#include "dependencies/copy_fast.hpp"
#include "dependencies/cmat.hpp"

namespace mat
{
    template <MATRIX_TYPENAME M, MATRIX_TYPENAME M2>
    constexpr void DirectCopy(const M &src, M2 &dest)
    {
        EXEC_IF_NOT_20(static_assert( (CONSTEXPR_MATRIX(M) || RUNTIME_MATRIX(M)) && (CONSTEXPR_MATRIX(M2) || RUNTIME_MATRIX(M2)), "DirectCopy: M and M2 must be a CONSTEXPR_MATRIX or RUNTIME_MATRIX"));
        if constexpr (CONSTEXPR_MATRIX(M) && CONSTEXPR_MATRIX(M2))
        {
            static_assert(M::area <= M2::area, "DirectCopy: must be same Area");
        }
        else
        {
            assert(src.Area() <= dest.Area());
        }

        for (size_t i = 0; i < src.Area(); ++i)
        {
            dest.FastAt(i) = src.FastAt(i);
        }
    }

    template <MATRIX_TYPENAME M, MATRIX_TYPENAME M2>
    constexpr void TruncCopy(const M &src, M2 &dest)
    {
        EXEC_IF_NOT_20(static_assert( (CONSTEXPR_MATRIX(M) || RUNTIME_MATRIX(M)) && (CONSTEXPR_MATRIX(M2) || RUNTIME_MATRIX(M2)), "TruncCopy: M and M2 must be a CONSTEXPR_MATRIX or RUNTIME_MATRIX"));
        for (size_t i = 0; i < dest.Height(); ++i)
        {
            for (size_t j = 0; j < dest.Width(); ++j)
            {
                if (j < src.Width() && i < src.Height())
                {
                    dest.At(j, i) = src.At(j, i);
                }
            }
        }
    }

    template <MATRIX_TYPENAME M>
    constexpr auto* SafeFastAt(size_t index, M& mat)
    {
        EXEC_IF_NOT_20(static_assert(CONSTEXPR_MATRIX(M) || RUNTIME_MATRIX(M), "SafeFastAt: M must be a CONSTEXPR_MATRIX or RUNTIME_MATRIX"));
        if(index < mat.Area())        
        {
            return &mat.FastAt(index);
        }
        else
        {
            return (typename M::type*)nullptr;
        }
    }

    template <MATRIX_TYPENAME M>
    constexpr auto* SafeAt(size_t x, size_t y, M& mat) 
    { 
        EXEC_IF_NOT_20(static_assert(CONSTEXPR_MATRIX(M) || RUNTIME_MATRIX(M), "SafeAt: M must be a CONSTEXPR_MATRIX or RUNTIME_MATRIX"));
        if(x < mat.Width() && y < mat.Height())
        {
            return &mat.At(x, y);
        }
        else
        {
            return (typename M::type*)nullptr;
        }    
    }
};
