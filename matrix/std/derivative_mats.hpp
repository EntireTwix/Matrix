#pragma once
#include "util_ops.hpp"

namespace mat
{
    template <MATRIX_TYPENAME M>
    constexpr auto FlattenCopy(const M &mat)
    {
        EXEC_IF_NOT_20(static_assert(CONSTEXPR_MATRIX(M) || RUNTIME_MATRIX(M), "Func: M must be a CONSTEXPR_MATRIX or RUNTIME_MATRIX"));
        if constexpr (CONSTEXPR_MATRIX(M))
        {
            if constexpr (M::height == 1)
            {
                return mat;   
            }
            typename M::base<M::area, 1> res;
            DirectCopy(mat, res);
            return res;
        }
        else
        {
            if (mat.Height() == 1)
            {
                return mat;
            }
            M res(mat);
            res.Flatten();
            return res;
        }
    }
}
