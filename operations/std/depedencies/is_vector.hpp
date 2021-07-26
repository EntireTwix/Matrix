#pragma once
#include <cassert>
#include "v_sep.hpp"
#include "cmat.hpp"
#include "copy_fast.hpp"

namespace mat
{
    template <MATRIX_TYPENAME M>
    constexpr void IsVector(copy_fast_cv_t<M> mat)
    {
        if constexpr (CONSTEXPR_MATRIX<M>)
        {
            static_assert(mat.Width() == 1 || mat.Height() == 1);
        }
        else
        {
            assert(mat.Width() == 1 || mat.Height() == 1);
        }
    }
};