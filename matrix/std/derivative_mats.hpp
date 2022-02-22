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
            typename M::base<M::area, 1> res;
            DirectCopy(mat, res);
            return res;
        }
        else
        {
            M res(mat);
            res.Flatten();
            return res;
        }
    }

    template <RUNTIME_MATRIX_TYPENAME M>
    constexpr M ResizeCopy(const M &mat, size_t w, size_t h)
    {
        EXEC_IF_NOT_20(static_assert(RUNTIME_MATRIX(M), "ResizeCopy: M must be RUNTIME_MATRIX"));
        if (mat.Width() == w && mat.Height() == h)
        {
            return mat;
        }
        else
        {
            M res(w, h);
            TruncCopy(mat, res);
            return res;
        }
    }
    template <CONSTEXPR_MATRIX_TYPENAME M, size_t W, size_t H>
    constexpr auto ResizeCopy(const M &mat)
    {
        EXEC_IF_NOT_20(static_assert(CONSTEXPR_MATRIX(M), "ResizeCopy: M must be CONSTEXPR_MATRIX"));
        if (mat.Width() == W && mat.Height() == H)
        {
            return mat;
        }
        else
        {
            typename M::base<W, H> res;
            TruncCopy(mat, res);
            return res;
        }
    }

    template <MATRIX_TYPENAME M>
    constexpr auto TransposeCopy(const M &mat)
    {
        EXEC_IF_NOT_20(static_assert(CONSTEXPR_MATRIX(M) || RUNTIME_MATRIX(M), "Func: M must be a CONSTEXPR_MATRIX or RUNTIME_MATRIX"));
        if constexpr (CONSTEXPR_MATRIX(M))
        {
            typename M::base<mat.Height(), mat.Width()> res;
            TruncCopy(mat, res);
            return res;
        }
        else
        {
            M res(mat.Height(), mat.Width());
            TruncCopy(mat, res);
            return res;
        }
    }
}
