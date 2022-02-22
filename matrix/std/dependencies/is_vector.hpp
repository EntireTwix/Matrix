#pragma once
#include <cassert>
#include "cmat.hpp"

namespace mat
{
    template <MATRIX_TYPENAME M>
    constexpr void IsVector(const M &mat)
    {
        if constexpr (CONSTEXPR_MATRIX(M))
        {
            static_assert(mat.Width() == 1 || mat.Height() == 1);
        }
        else if constexpr (RUNTIME_MATRIX(M))
        {
            assert(mat.Width() == 1 || mat.Height() == 1);
        }
        else 
        { 
            static_assert(false, "IsVector: M must be CONSTEXPR_MATRIX or RUNTIME_MATRIX"); 
        }
    }
};
