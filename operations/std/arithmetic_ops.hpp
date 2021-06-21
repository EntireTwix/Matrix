#pragma once
#include "generic_ops.hpp"

#ifdef __cpp_concepts 
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
    #ifdef __cpp_concepts 
    requires Addable<typename M::type, typename M2::type>
    #endif
    constexpr M operator+(const M& a, const M2&b) { return Operation(a,b,[](copy_fast_cv_t<typename M::type> a, copy_fast_cv_t<typename M::type> b){ return a+b; }); }
    template <MATRIX_TYPENAME M, MATRIX_TYPENAME M2>
    #ifdef __cpp_concepts 
    requires AddableAs<typename M::type, typename M2::type>
    #endif
    constexpr void operator+=(M& a, const M2&b) { OperationMut(a, b, [](typename M::type& a, copy_fast_cv_t<typename M::type> b){ a+=b; }); }
    template <MATRIX_TYPENAME M, typename T = typename M::type>
    #ifdef __cpp_concepts 
    requires Addable<typename M::type, T>
    #endif
    constexpr M operator+(const M& mat, T&& v) noexcept { return ScalarOperation(mat, v, [](copy_fast_cv_t<typename M::type> a, copy_fast_cv_t<T> b){ return a+b; }); }
    template <MATRIX_TYPENAME M, typename T = typename M::type>
    #ifdef __cpp_concepts 
    requires AddableAs<typename M::type, T>
    #endif
    constexpr void operator+=(M& mat, T&& v)  noexcept { ScalarOperationMut(mat, v, [](typename M::type& a, copy_fast_cv_t<typename M::type> b){ a+=b; }); }

    //Sub
    template <MATRIX_TYPENAME M, MATRIX_TYPENAME M2>
    #ifdef __cpp_concepts 
    requires Subtractable<typename M::type, typename M2::type>
    #endif
    constexpr M operator-(const M& a, const M2&b) { return Operation(a,b,[](copy_fast_cv_t<typename M::type> a, copy_fast_cv_t<typename M::type> b){ return a-b; }); }
    template <MATRIX_TYPENAME M, MATRIX_TYPENAME M2>
    #ifdef __cpp_concepts 
    requires SubtractableAs<typename M::type, typename M2::type>
    #endif
    constexpr void operator-=(M& a, const M2&b) { OperationMut(a, b, [](typename M::type& a, copy_fast_cv_t<typename M::type> b){ a-=b; }); }
    template <MATRIX_TYPENAME M, typename T = typename M::type>
    #ifdef __cpp_concepts 
    requires Subtractable<typename M::type, T>
    #endif
    constexpr M operator-(const M& mat, T&& v) noexcept { return ScalarOperation(mat, v, [](copy_fast_cv_t<typename M::type> a, copy_fast_cv_t<T> b){ return a-b; }); }
    template <MATRIX_TYPENAME M, typename T = typename M::type>
    #ifdef __cpp_concepts 
    requires SubtractableAs<typename M::type, T>
    #endif
    constexpr void operator-=(M& mat, T&& v)  noexcept { ScalarOperationMut(mat, v, [](typename M::type& a, copy_fast_cv_t<typename M::type> b){ a-=b; }); }

    //Mul
    template <MATRIX_TYPENAME M, MATRIX_TYPENAME M2>
    #ifdef __cpp_concepts 
    requires Multipliable<typename M::type, typename M2::type>
    #endif
    constexpr M operator*(const M& a, const M2&b) { return Operation(a,b,[](copy_fast_cv_t<typename M::type> a, copy_fast_cv_t<typename M::type> b){ return a*b; }); }
    template <MATRIX_TYPENAME M, MATRIX_TYPENAME M2>
    #ifdef __cpp_concepts 
    requires MultipliableAs<typename M::type, typename M2::type>
    #endif
    constexpr void operator*=(M& a, const M2&b) { OperationMut(a, b, [](typename M::type& a, copy_fast_cv_t<typename M::type> b){ a*=b; }); }
    template <MATRIX_TYPENAME M, typename T = typename M::type>
    #ifdef __cpp_concepts 
    requires Multipliable<typename M::type, T>
    #endif
    constexpr M operator*(const M& mat, T&& v) noexcept { return ScalarOperation(mat, v, [](copy_fast_cv_t<typename M::type> a, copy_fast_cv_t<T> b){ return a*b; }); }
    template <MATRIX_TYPENAME M, typename T = typename M::type>
    #ifdef __cpp_concepts 
    requires MultipliableAs<typename M::type, T>
    #endif
    constexpr void operator*=(M& mat, T&& v)  noexcept { ScalarOperationMut(mat, v, [](typename M::type& a, copy_fast_cv_t<typename M::type> b){ a*=b; }); }

    //Div
    template <MATRIX_TYPENAME M, MATRIX_TYPENAME M2>
    #ifdef __cpp_concepts 
    requires Divideable<typename M::type, typename M2::type>
    #endif
    constexpr M operator/(const M& a, const M2&b) { return Operation(a,b,[](copy_fast_cv_t<typename M::type> a, copy_fast_cv_t<typename M::type> b){ return a/b; }); }
    template <MATRIX_TYPENAME M, MATRIX_TYPENAME M2>
    #ifdef __cpp_concepts 
    requires DivideableAs<typename M::type, typename M2::type>
    #endif
    constexpr void operator/=(M& a, const M2&b) { OperationMut(a, b, [](typename M::type& a, copy_fast_cv_t<typename M::type> b){ a/=b; }); }
    template <MATRIX_TYPENAME M, typename T = typename M::type>
    #ifdef __cpp_concepts 
    requires Divideable<typename M::type, T>
    #endif
    constexpr M operator/(const M& mat, T&& v) noexcept { return ScalarOperation(mat, v, [](copy_fast_cv_t<typename M::type> a, copy_fast_cv_t<T> b){ return a/b; }); }
    template <MATRIX_TYPENAME M, typename T = typename M::type>
    #ifdef __cpp_concepts 
    requires DivideableAs<typename M::type, T>
    #endif
    constexpr void operator/=(M& mat, T&& v)  noexcept { ScalarOperationMut(mat, v, [](typename M::type& a, copy_fast_cv_t<typename M::type> b){ a/=b; }); }
};
