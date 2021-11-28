#pragma once
#include "dependencies/copy_fast.hpp"
#include "dependencies/cmat.hpp"

namespace mat
{
    template <MATRIX_TYPENAME M, MATRIX_TYPENAME M2, typename F>
    constexpr M Operation(const M &a, const M2 &b, F &&func)
    {
        M res(a);
        for (size_t i = 0; i < b.Area(); ++i)
        {
            res.FastAt(i) = func(a.FastAt(i), b.FastAt(i));
        }
        return res;
    }
    template <MATRIX_TYPENAME M, MATRIX_TYPENAME M2, typename F>
    constexpr void OperationMut(M &a, const M2 &b, F &&func)
    {
        for (size_t i = 0; i < b.Area(); ++i)
        {
            func(a.FastAt(i), b.FastAt(i));
        }
    }
    template <MATRIX_TYPENAME M, typename F, typename T = typename M::type>
    constexpr M ScalarOperation(const M &mat, copy_fast_cv_t<T> v, F &&func)
    {
        M res(mat);
        for (size_t i = 0; i < mat.Area(); ++i)
        {
            res.FastAt(i) = func(mat.FastAt(i), v);
        }
        return res;
    }
    template <MATRIX_TYPENAME M, typename F, typename T = typename M::type>
    constexpr void ScalarOperationMut(M &mat, copy_fast_cv_t<T> v, F &&func)
    {
        for (T &e : mat)
        {
            func(e, v);
        }
    }
};
