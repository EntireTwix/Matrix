#pragma once
#include <cassert>
#include "depedencies/cmat.hpp"

namespace mat
{
    template <Matrix M>
    constexpr void IsVector(const M &mat)
    {
        if constexpr (ConstexprMatrix<M>)
        {
            static_assert(mat.Width() == 1 || mat.Height() == 1);
        }
        else
        {
            assert(mat.Width() == 1 || mat.Height() == 1);
        }
    }
};