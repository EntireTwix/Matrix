#pragma once
#include "dependencies/copy_fast.hpp"
#include "dependencies/cmat.hpp"

namespace mat
{
    template <MATRIX_TYPENAME M, MATRIX_TYPENAME M2, typename F>
    constexpr M operation(const M &a, const M2 &b, F &&func)
    {
        EXEC_IF_NOT_20(static_assert(CONSTEXPR_MATRIX(M) || RUNTIME_MATRIX(M), "operation: M must be a CONSTEXPR_MATRIX or RUNTIME_MATRIX"));
        M res(a);
        for (size_t i = 0; i < b.get_area(); ++i)
        {
            res.fast_at(i) = func(a.fast_at(i), b.fast_at(i));
        }
        return res;
    }
    template <MATRIX_TYPENAME M, MATRIX_TYPENAME M2, typename F>
    constexpr void operation_mut(M &a, const M2 &b, F &&func)
    {
        EXEC_IF_NOT_20(static_assert(CONSTEXPR_MATRIX(M) || RUNTIME_MATRIX(M), "operation_mut: M must be a CONSTEXPR_MATRIX or RUNTIME_MATRIX"));
        for (size_t i = 0; i < b.get_area(); ++i)
        {
            func(a.fast_at(i), b.fast_at(i));
        }
    }
    template <MATRIX_TYPENAME M, typename F, typename T = typename M::value_type>
    constexpr M scalar_operation(const M &mat, copy_fast_t<T> v, F &&func)
    {
        EXEC_IF_NOT_20(static_assert(CONSTEXPR_MATRIX(M) || RUNTIME_MATRIX(M), "scalar_operation: M must be a CONSTEXPR_MATRIX or RUNTIME_MATRIX"));
        M res(mat);
        for (size_t i = 0; i < mat.get_area(); ++i)
        {
            res.fast_at(i) = func(mat.fast_at(i), v);
        }
        return res;
    }
    template <MATRIX_TYPENAME M, typename F, typename T = typename M::value_type>
    constexpr void scalar_operation_mut(M &mat, copy_fast_t<T> v, F &&func)
    {
        EXEC_IF_NOT_20(static_assert(CONSTEXPR_MATRIX(M) || RUNTIME_MATRIX(M), "scalar_operation_mut: M must be a CONSTEXPR_MATRIX or RUNTIME_MATRIX"));
        for (T &e : mat)
        {
            func(e, v);
        }
    }
};
