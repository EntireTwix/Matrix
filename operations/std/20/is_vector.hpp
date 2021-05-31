#pragma once
#include <cassert>
#include "cmat.hpp"

namespace mat
{
    template <Matrix M>
    void IsVector(const M &mat)
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