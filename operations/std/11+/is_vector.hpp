#pragma once
#include "depedencies//is_constexpr_mat.hpp"

namespace mat
{
    template <typename M>
    void IsVector(const M &mat)
    {
        if constexpr (is_constexpr_matrix_v<M>)
        {
            static_assert(mat.Width() == 1 || mat.Height() == 1);
        }
        else
        {
            assert(mat.Width() == 1 || mat.Height() == 1);
        }
    }
};