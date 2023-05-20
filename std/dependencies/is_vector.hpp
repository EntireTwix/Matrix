#pragma once
#include <cassert>
#include "cmat.hpp"

namespace mat
{
    template <MATRIX_TYPENAME M>
    constexpr void is_verctor(const M &mat)
    {
        EXEC_IF_NOT_20(static_assert(CONSTEXPR_MATRIX(M) || RUNTIME_MATRIX(M), "is_verctor: M must be a CONSTEXPR_MATRIX or RUNTIME_MATRIX"));
        if constexpr (CONSTEXPR_MATRIX(M))
        {
            static_assert(mat.width() == 1 || mat.height() == 1);
        }
        else
        {
            assert(mat.width() == 1 || mat.height() == 1);
        } 
    }
};
