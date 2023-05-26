#pragma once
#include <cassert>
#include "cmat.hpp"

namespace mat
{
    template <MATRIX_TYPENAME M>
    constexpr void is_vector(const M &mat)
    {
        EXEC_IF_NOT_20(static_assert(CONSTEXPR_MATRIX(M) || RUNTIME_MATRIX(M), "is_vector: M must be a CONSTEXPR_MATRIX or RUNTIME_MATRIX"));
        if constexpr (CONSTEXPR_MATRIX(M))
        {
            static_assert(mat.get_width() == 1 || mat.get_height() == 1);
        }
        else
        {
            assert(mat.get_width() == 1 || mat.get_height() == 1);
        } 
    }
};
