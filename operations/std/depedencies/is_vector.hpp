#pragma once
#include <cassert>
#include "v_sep.hpp"
#include EXCLU_C20_ELSE("cmat.hpp", "is_constexpr_mat.hpp")
#include "copy_fast.hpp"

namespace mat
{
    template <MATRIX_TYPENAME M>
    constexpr void IsVector(copy_fast_cv_t<M> mat)
    {
        if constexpr (EXCLU_C20_ELSE(ConstexprMatrix<M>, is_constexpr_matrix_v<M>))
        {
            static_assert(mat.Width() == 1 || mat.Height() == 1);
        }
        else
        {
            assert(mat.Width() == 1 || mat.Height() == 1);
        }
    }
};