#pragma once
#include "generic_ops.hpp"

namespace mat
{
    //Add
    template <typename M, typename M2>
    constexpr M operator+(const M& a, const M2& b) { return Operation(a,b,[](copy_fast_cv_t<typename M::type> a, copy_fast_cv_t<typename M::type> b){ return a+b; }); }
    template <typename M, typename M2>
    constexpr void operator+=(M& a, const M2& b) { OperationMut(a, b, [](typename M::type& a, copy_fast_cv_t<typename M::type> b){ a+=b; }); }
    template <typename M, typename T = typename M::type>
    constexpr M operator+(const M& mat, copy_fast_cv_t<T> v) noexcept { return ScalarOperation(mat, v, [](copy_fast_cv_t<typename M::type> a, copy_fast_cv_t<T> b){ return a+b; }); }
    template <typename M, typename T = typename M::type>
    constexpr void operator+=(M& mat, copy_fast_cv_t<T> v)  noexcept { ScalarOperationMut(mat, v, [](typename M::type& a, copy_fast_cv_t<typename M::type> b){ a+=b;; }); }

    //Sub
    template <typename M, typename M2>
    constexpr M operator-(const M& a, const M2& b) { return Operation(a,b,[](copy_fast_cv_t<typename M::type> a, copy_fast_cv_t<typename M::type> b){ return a-b; }); }
    template <typename M, typename M2>
    constexpr void operator-=(M& a, const M2& b) { OperationMut(a, b, [](typename M::type& a, copy_fast_cv_t<typename M::type> b){ a-=b; }); }
    template <typename M, typename T = typename M::type>
    constexpr M operator-(const M& mat, copy_fast_cv_t<T> v) noexcept { return ScalarOperation(mat, v, [](copy_fast_cv_t<typename M::type> a, copy_fast_cv_t<T> b){ return a-b; }); }
    template <typename M, typename T = typename M::type>
    constexpr void operator-=(M& mat, copy_fast_cv_t<T> v)  noexcept { ScalarOperationMut(mat, v, [](typename M::type& a, copy_fast_cv_t<typename M::type> b){ a-=b;; }); }

    //Mul
    template <typename M, typename M2>
    constexpr M operator*(const M& a, const M2& b) { return Operation(a,b,[](copy_fast_cv_t<typename M::type> a, copy_fast_cv_t<typename M::type> b){ return a*b; }); }
    template <typename M, typename M2>
    constexpr void operator*=(M& a, const M2& b) { OperationMut(a, b, [](typename M::type& a, copy_fast_cv_t<typename M::type> b){ a*=b; }); }
    template <typename M, typename T = typename M::type>
    constexpr M operator*(const M& mat, copy_fast_cv_t<T> v) noexcept { return ScalarOperation(mat, v, [](copy_fast_cv_t<typename M::type> a, copy_fast_cv_t<T> b){ return a*b; }); }
    template <typename M, typename T = typename M::type>
    constexpr void operator*=(M& mat, copy_fast_cv_t<T> v)  noexcept { ScalarOperationMut(mat, v, [](typename M::type& a, copy_fast_cv_t<typename M::type> b){ a*=b;; }); }

    //Div
    template <typename M, typename M2>
    constexpr M operator/(const M& a, const M2& b) { return Operation(a,b,[](copy_fast_cv_t<typename M::type> a, copy_fast_cv_t<typename M::type> b){ return a/b; }); }
    template <typename M, typename M2>
    constexpr void operator/=(M& a, const M2& b) { OperationMut(a, b, [](typename M::type& a, copy_fast_cv_t<typename M::type> b){ a/=b; }); }
    template <typename M, typename T = typename M::type>
    constexpr M operator/(const M& mat, copy_fast_cv_t<T> v) noexcept { return ScalarOperation(mat, v, [](copy_fast_cv_t<typename M::type> a, copy_fast_cv_t<T> b){ return a/b; }); }
    template <typename M, typename T = typename M::type>
    constexpr void operator/=(M& mat, copy_fast_cv_t<T> v)  noexcept { ScalarOperationMut(mat, v, [](typename M::type& a, copy_fast_cv_t<typename M::type> b){ a/=b;; }); }
};
