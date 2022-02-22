#pragma once
#include <cassert>
#include "cmat.hpp"

namespace mat
{
    template <MATRIX_TYPENAME M>
    constexpr void IsVector(const M &mat)
    {
        EXEC_IF_NOT_20(static_assert(CONSTEXPR_MATRIX(M) || RUNTIME_MATRIX(M), "IsVector: M must be a CONSTEXPR_MATRIX or RUNTIME_MATRIX"));
        if constexpr (CONSTEXPR_MATRIX(M))
        {
            static_assert(mat.Width() == 1 || mat.Height() == 1);
        }
        else if constexpr (RUNTIME_MATRIX(M))
        {
            assert(mat.Width() == 1 || mat.Height() == 1);
        } 
    }
};
