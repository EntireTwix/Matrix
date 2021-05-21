#pragma once
#include "generic_ops.hpp"

template <typename T, typename T2> 
concept Addable = requires(T a, T2 b) { {a+b}->std::convertible_to<T>; };
template <typename T, typename T2> 
concept AddableAs = requires(T a, T2 b) { {a+=b}->std::convertible_to<T>; };
template <typename T, typename T2>
concept Subtractable = requires(T a, T2 b) { {a-b}->std::convertible_to<T>; };
template <typename T, typename T2> 
concept SubtractableAs = requires(T a, T2 b) { {a-=b}->std::convertible_to<T>; };
template <typename T, typename T2>
concept Multipliable = requires(T a, T2 b) { {a*b}->std::convertible_to<T>; };
template <typename T, typename T2>
concept MultipliableAs = requires(T a, T2 b) { {a*=b}->std::convertible_to<T>; };
template <typename T, typename T2>
concept Divideable = requires(T a, T2 b) { {a/b}->std::convertible_to<T>; };
template <typename T, typename T2>
concept DivideableAs = requires(T a, T2 b) { {a/=b}->std::convertible_to<T>; };

namespace mat
{
    //Add
    template <Matrix M, Matrix M2>
    requires Addable<typename M::type, typename M2::type>
    constexpr M operator+(const M& a, const M2& b) { return Operation(a,b,[](copy_fast_cv_t<typename M::type> a, copy_fast_cv_t<typename M::type> b){ return a+b; }); }
    template <Matrix M, Matrix M2>
    requires AddableAs<typename M::type, typename M2::type>
    constexpr void operator+=(M& a, const M2& b) { OperationMut(a, b, [](typename M::type& a, copy_fast_cv_t<typename M::type> b){ a+=b; }); }
    template <Matrix M, typename T = typename M::type>
    requires Addable<typename M::type, T>
    constexpr M operator+(const M& mat, copy_fast_cv_t<T> v) noexcept { return ScalarOperation(mat, v, [](copy_fast_cv_t<typename M::type> a, copy_fast_cv_t<T> b){ return a+b; }); }
    template <Matrix M, typename T = typename M::type>
    requires AddableAs<typename M::type, T>
    constexpr void operator+=(M& mat, copy_fast_cv_t<T> v)  noexcept { ScalarOperationMut(mat, v, [](typename M::type& a, copy_fast_cv_t<typename M::type> b){ a+=b;; }); }

    //Sub
    template <Matrix M, Matrix M2>
    requires Subtractable<typename M::type, typename M2::type>
    constexpr M operator-(const M& a, const M2& b) { return Operation(a,b,[](copy_fast_cv_t<typename M::type> a, copy_fast_cv_t<typename M::type> b){ return a-b; }); }
    template <Matrix M, Matrix M2>
    requires SubtractableAs<typename M::type, typename M2::type>
    constexpr void operator-=(M& a, const M2& b) { OperationMut(a, b, [](typename M::type& a, copy_fast_cv_t<typename M::type> b){ a-=b; }); }
    template <Matrix M, typename T = typename M::type>
    requires Subtractable<typename M::type, T>
    constexpr M operator-(const M& mat, copy_fast_cv_t<T> v) noexcept { return ScalarOperation(mat, v, [](copy_fast_cv_t<typename M::type> a, copy_fast_cv_t<T> b){ return a-b; }); }
    template <Matrix M, typename T = typename M::type>
    requires SubtractableAs<typename M::type, T>
    constexpr void operator-=(M& mat, copy_fast_cv_t<T> v)  noexcept { ScalarOperationMut(mat, v, [](typename M::type& a, copy_fast_cv_t<typename M::type> b){ a-=b;; }); }

    //Mul
    template <Matrix M, Matrix M2>
    requires Multipliable<typename M::type, typename M2::type>
    constexpr M operator*(const M& a, const M2& b) { return Operation(a,b,[](copy_fast_cv_t<typename M::type> a, copy_fast_cv_t<typename M::type> b){ return a*b; }); }
    template <Matrix M, Matrix M2>
    requires MultipliableAs<typename M::type, typename M2::type>
    constexpr void operator*=(M& a, const M2& b) { OperationMut(a, b, [](typename M::type& a, copy_fast_cv_t<typename M::type> b){ a*=b; }); }
    template <Matrix M, typename T = typename M::type>
    requires Multipliable<typename M::type, T>
    constexpr M operator*(const M& mat, copy_fast_cv_t<T> v) noexcept { return ScalarOperation(mat, v, [](copy_fast_cv_t<typename M::type> a, copy_fast_cv_t<T> b){ return a*b; }); }
    template <Matrix M, typename T = typename M::type>
    requires MultipliableAs<typename M::type, T>
    constexpr void operator*=(M& mat, copy_fast_cv_t<T> v)  noexcept { ScalarOperationMut(mat, v, [](typename M::type& a, copy_fast_cv_t<typename M::type> b){ a*=b;; }); }

    //Div
    template <Matrix M, Matrix M2>
    requires Divideable<typename M::type, typename M2::type>
    constexpr M operator/(const M& a, const M2& b) { return Operation(a,b,[](copy_fast_cv_t<typename M::type> a, copy_fast_cv_t<typename M::type> b){ return a/b; }); }
    template <Matrix M, Matrix M2>
    requires DivideableAs<typename M::type, typename M2::type>
    constexpr void operator/=(M& a, const M2& b) { OperationMut(a, b, [](typename M::type& a, copy_fast_cv_t<typename M::type> b){ a/=b; }); }
    template <Matrix M, typename T = typename M::type>
    requires Divideable<typename M::type, T>
    constexpr M operator/(const M& mat, copy_fast_cv_t<T> v) noexcept { return ScalarOperation(mat, v, [](copy_fast_cv_t<typename M::type> a, copy_fast_cv_t<T> b){ return a/b; }); }
    template <Matrix M, typename T = typename M::type>
    requires DivideableAs<typename M::type, T>
    constexpr void operator/=(M& mat, copy_fast_cv_t<T> v)  noexcept { ScalarOperationMut(mat, v, [](typename M::type& a, copy_fast_cv_t<typename M::type> b){ a/=b;; }); }
};
