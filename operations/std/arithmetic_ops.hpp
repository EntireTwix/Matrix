#pragma once
#include "generic_ops.hpp"

#ifdef HAS_CONCEPTS 
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
#endif


namespace mat
{
    //Add
    template <MATRIX_TYPENAME M, MATRIX_TYPENAME M2>
    #ifdef HAS_CONCEPTS 
    requires Addable<typename M::type, typename M2::type>
    #endif
    constexpr M operator+(const M& a, const M2&b) { return Operation(a,b,[](copy_fast_cv_t<typename M::type> a, copy_fast_cv_t<typename M::type> b){ return a+b; }); }
    template <MATRIX_TYPENAME M, MATRIX_TYPENAME M2>
    #ifdef HAS_CONCEPTS 
    requires AddableAs<typename M::type, typename M2::type>
    #endif
    constexpr void operator+=(M& a, const M2&b) { OperationMut(a, b, [](typename M::type& a, copy_fast_cv_t<typename M::type> b){ a+=b; }); }
    template <MATRIX_TYPENAME M, typename T = typename M::type>
    #ifdef HAS_CONCEPTS 
    requires Addable<typename M::type, T>
    #endif
    constexpr M operator+(const M& mat, T&& v) { return ScalarOperation(mat, std::move(v), [](copy_fast_cv_t<typename M::type> a, copy_fast_cv_t<T> b){ return a+b; }); }
    template <MATRIX_TYPENAME M, typename T = typename M::type>
    #ifdef HAS_CONCEPTS 
    requires AddableAs<typename M::type, T>
    #endif
    constexpr void operator+=(M& mat, T&& v)  { ScalarOperationMut(mat, std::move(v), [](typename M::type& a, copy_fast_cv_t<T> b){ a+=b; }); }

    //Sub
    template <MATRIX_TYPENAME M, MATRIX_TYPENAME M2>
    #ifdef HAS_CONCEPTS 
    requires Subtractable<typename M::type, typename M2::type>
    #endif
    constexpr M operator-(const M& a, const M2&b) { return Operation(a,b,[](copy_fast_cv_t<typename M::type> a, copy_fast_cv_t<typename M::type> b){ return a-b; }); }
    template <MATRIX_TYPENAME M, MATRIX_TYPENAME M2>
    #ifdef HAS_CONCEPTS 
    requires SubtractableAs<typename M::type, typename M2::type>
    #endif
    constexpr void operator-=(M& a, const M2&b) { OperationMut(a, b, [](typename M::type& a, copy_fast_cv_t<typename M::type> b){ a-=b; }); }
    template <MATRIX_TYPENAME M, typename T = typename M::type>
    #ifdef HAS_CONCEPTS 
    requires Subtractable<typename M::type, T>
    #endif
    constexpr M operator-(const M& mat, T&& v) { return ScalarOperation(mat, std::move(v), [](copy_fast_cv_t<typename M::type> a, copy_fast_cv_t<T> b){ return a-b; }); }
    template <MATRIX_TYPENAME M, typename T = typename M::type>
    #ifdef HAS_CONCEPTS 
    requires SubtractableAs<typename M::type, T>
    #endif
    constexpr void operator-=(M& mat, T&& v)  { ScalarOperationMut(mat, std::move(v), [](typename M::type& a, copy_fast_cv_t<T> b){ a-=b; }); }

    //Mul
    template <MATRIX_TYPENAME M, MATRIX_TYPENAME M2>
    #ifdef HAS_CONCEPTS 
    requires Multipliable<typename M::type, typename M2::type>
    #endif
    constexpr M operator*(const M& a, const M2&b) { return Operation(a,b,[](copy_fast_cv_t<typename M::type> a, copy_fast_cv_t<typename M::type> b){ return a*b; }); }
    template <MATRIX_TYPENAME M, MATRIX_TYPENAME M2>
    #ifdef HAS_CONCEPTS 
    requires MultipliableAs<typename M::type, typename M2::type>
    #endif
    constexpr void operator*=(M& a, const M2&b) { OperationMut(a, b, [](typename M::type& a, copy_fast_cv_t<typename M::type> b){ a*=b; }); }
    template <MATRIX_TYPENAME M, typename T = typename M::type>
    #ifdef HAS_CONCEPTS 
    requires Multipliable<typename M::type, T>
    #endif
    constexpr M operator*(const M& mat, T&& v) { return ScalarOperation(mat, std::move(v), [](copy_fast_cv_t<typename M::type> a, copy_fast_cv_t<T> b){ return a*b; }); }
    template <MATRIX_TYPENAME M, typename T = typename M::type>
    #ifdef HAS_CONCEPTS 
    requires MultipliableAs<typename M::type, T>
    #endif
    constexpr void operator*=(M& mat, T&& v)  { ScalarOperationMut(mat, std::move(v), [](typename M::type& a, copy_fast_cv_t<T> b){ a*=b; }); }

    //Div
    template <MATRIX_TYPENAME M, MATRIX_TYPENAME M2>
    #ifdef HAS_CONCEPTS 
    requires Divideable<typename M::type, typename M2::type>
    #endif
    constexpr M operator/(const M& a, const M2&b) { return Operation(a,b,[](copy_fast_cv_t<typename M::type> a, copy_fast_cv_t<typename M::type> b){ return a/b; }); }
    template <MATRIX_TYPENAME M, MATRIX_TYPENAME M2>
    #ifdef HAS_CONCEPTS 
    requires DivideableAs<typename M::type, typename M2::type>
    #endif
    constexpr void operator/=(M& a, const M2&b) { OperationMut(a, b, [](typename M::type& a, copy_fast_cv_t<typename M::type> b){ a/=b; }); }
    template <MATRIX_TYPENAME M, typename T = typename M::type>
    #ifdef HAS_CONCEPTS 
    requires Divideable<typename M::type, T>
    #endif
    constexpr M operator/(const M& mat, T&& v) { return ScalarOperation(mat, std::move(v), [](copy_fast_cv_t<typename M::type> a, copy_fast_cv_t<T> b){ return a/b; }); }
    template <MATRIX_TYPENAME M, typename T = typename M::type>
    #ifdef HAS_CONCEPTS 
    requires DivideableAs<typename M::type, T>
    #endif
    constexpr void operator/=(M& mat, T&& v)  { ScalarOperationMut(mat, std::move(v), [](typename M::type& a, copy_fast_cv_t<T> b){ a/=b; }); }
};
