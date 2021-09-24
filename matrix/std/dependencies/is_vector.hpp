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
        else
        {
            assert(mat.Width() == 1 || mat.Height() == 1);
        }
    }
};
