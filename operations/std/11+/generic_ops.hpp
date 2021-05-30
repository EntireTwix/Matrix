#pragma once
#include "copy_fast.hpp"

namespace mat
{
    template <typename M, typename M2, typename F>
    constexpr M Operation(const M &a, const M2 &b, F &&func)
    {
        if (b.Area() != a.Area())
        {
            throw std::invalid_argument("arg a size must match b");
        }
        M res(a.SizeCopy());
        for (size_t i = 0; i < b.Area(); ++i)
        {
            res.FastAt(i) = func(a.FastAt(i), b.FastAt(i));
        }
        return res;
    }
    template <typename M, typename M2, typename F>
    constexpr void OperationMut(M &a, const M2 &b, F &&func)
    {
        if (b.Area() != a.Area())
        {
            throw std::invalid_argument("arg a size must match b");
        }
        for (size_t i = 0; i < b.Area(); ++i)
        {
            func(a.FastAt(i), b.FastAt(i));
        }
    }
    template <typename M, typename F, typename T = typename M::type>
    constexpr M ScalarOperation(const M &mat, copy_fast_cv_t<T> v, F &&func)
    {
        M res(mat.SizeCopy());
        for (size_t i = 0; i < mat.Area(); ++i)
        {
            res.FastAt(i) = func(mat.FastAt(i), v);
        }
        return res;
    }
    template <typename M, typename F, typename T = typename M::type>
    constexpr void ScalarOperationMut(M &mat, copy_fast_cv_t<T> v, F &&func)
    {
        for (T &e : mat)
        {
            func(e, v);
        }
    }
};
