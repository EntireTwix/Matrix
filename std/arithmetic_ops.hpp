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
template <typename T, typename T2>
concept Powable = requires(T a, T2 b)
{
    { a = 1 };
    { 0 < b } -> std::same_as<bool>;
    { a *= a };
    { a = a};
};
#endif


namespace mat
{
    //Add
    template <MATRIX_TYPENAME M, MATRIX_TYPENAME M2>
    #ifdef HAS_CONCEPTS 
    requires Addable<typename M::value_type, typename M2::value_type>
    #endif
    constexpr M add_mat(const M& a, const M2&b) { EXEC_IF_NOT_20(static_assert(CONSTEXPR_MATRIX(M) || RUNTIME_MATRIX(M), "AddMat: M must be a CONSTEXPR_MATRIX or RUNTIME_MATRIX")); return operation(a,b,[](copy_fast_t<typename M::value_type> a, copy_fast_t<typename M2::value_type> b){ return a+b; }); }
    template <MATRIX_TYPENAME M, MATRIX_TYPENAME M2>
    #ifdef HAS_CONCEPTS 
    requires AddableAs<typename M::value_type, typename M2::value_type>
    #endif
    constexpr void add_mat_mut(M& a, const M2&b) { EXEC_IF_NOT_20(static_assert(CONSTEXPR_MATRIX(M) || RUNTIME_MATRIX(M), "AddMatMut: M must be a CONSTEXPR_MATRIX or RUNTIME_MATRIX")); operation_mut(a, b, [](typename M::value_type& a, copy_fast_t<typename M2::value_type> b){ a+=b; }); }
    template <MATRIX_TYPENAME M, typename T = typename M::value_type>
    #ifdef HAS_CONCEPTS 
    requires Addable<typename M::value_type, T>
    #endif
    constexpr M add(const M& mat, copy_fast_t<T> v) { EXEC_IF_NOT_20(static_assert(CONSTEXPR_MATRIX(M) || RUNTIME_MATRIX(M), "Add: M must be a CONSTEXPR_MATRIX or RUNTIME_MATRIX")); return scalar_operation(mat, std::move(v), [](copy_fast_t<typename M::value_type> a, copy_fast_t<T> b){ return a+b; }); }
    template <MATRIX_TYPENAME M, typename T = typename M::value_type>
    #ifdef HAS_CONCEPTS 
    requires AddableAs<typename M::value_type, T>
    #endif
    constexpr void add_mut(M& mat, copy_fast_t<T> v)  { EXEC_IF_NOT_20(static_assert(CONSTEXPR_MATRIX(M) || RUNTIME_MATRIX(M), "AddMut: M must be a CONSTEXPR_MATRIX or RUNTIME_MATRIX")); scalar_operation_mut(mat, std::move(v), [](typename M::value_type& a, copy_fast_t<T> b){ a+=b; }); }

    //Sub
    template <MATRIX_TYPENAME M, MATRIX_TYPENAME M2>
    #ifdef HAS_CONCEPTS 
    requires Subtractable<typename M::value_type, typename M2::value_type>
    #endif
    constexpr M sub_mat(const M& a, const M2&b) { EXEC_IF_NOT_20(static_assert(CONSTEXPR_MATRIX(M) || RUNTIME_MATRIX(M), "sub_mat: M must be a CONSTEXPR_MATRIX or RUNTIME_MATRIX")); return operation(a,b,[](copy_fast_t<typename M::value_type> a, copy_fast_t<typename M2::value_type> b){ return a-b; }); }
    template <MATRIX_TYPENAME M, MATRIX_TYPENAME M2>
    #ifdef HAS_CONCEPTS 
    requires SubtractableAs<typename M::value_type, typename M2::value_type>
    #endif
    constexpr void sub_mat_mut(M& a, const M2&b) { EXEC_IF_NOT_20(static_assert(CONSTEXPR_MATRIX(M) || RUNTIME_MATRIX(M), "sub_mat_mut: M must be a CONSTEXPR_MATRIX or RUNTIME_MATRIX")); operation_mut(a, b, [](typename M::value_type& a, copy_fast_t<typename M2::value_type> b){ a-=b; }); }
    template <MATRIX_TYPENAME M, typename T = typename M::value_type>
    #ifdef HAS_CONCEPTS 
    requires Subtractable<typename M::value_type, T>
    #endif
    constexpr M Sub(const M& mat, copy_fast_t<T> v) { EXEC_IF_NOT_20(static_assert(CONSTEXPR_MATRIX(M) || RUNTIME_MATRIX(M), "Sub: M must be a CONSTEXPR_MATRIX or RUNTIME_MATRIX")); return scalar_operation(mat, std::move(v), [](copy_fast_t<typename M::value_type> a, copy_fast_t<T> b){ return a-b; }); }
    template <MATRIX_TYPENAME M, typename T = typename M::value_type>
    #ifdef HAS_CONCEPTS 
    requires SubtractableAs<typename M::value_type, T>
    #endif
    constexpr void sub_mut(M& mat, copy_fast_t<T> v)  { EXEC_IF_NOT_20(static_assert(CONSTEXPR_MATRIX(M) || RUNTIME_MATRIX(M), "sub_mut: M must be a CONSTEXPR_MATRIX or RUNTIME_MATRIX")); scalar_operation_mut(mat, std::move(v), [](typename M::value_type& a, copy_fast_t<T> b){ a-=b; }); }

    //Mul
    template <MATRIX_TYPENAME M, MATRIX_TYPENAME M2>
    #ifdef HAS_CONCEPTS 
    requires Multipliable<typename M::value_type, typename M2::value_type>
    #endif
    constexpr M mul_mat(const M& a, const M2&b) { EXEC_IF_NOT_20(static_assert(CONSTEXPR_MATRIX(M) || RUNTIME_MATRIX(M), "mul_mat: M must be a CONSTEXPR_MATRIX or RUNTIME_MATRIX")); return operation(a,b,[](copy_fast_t<typename M::value_type> a, copy_fast_t<typename M2::value_type> b){ return a*b; }); }
    template <MATRIX_TYPENAME M, MATRIX_TYPENAME M2>
    #ifdef HAS_CONCEPTS 
    requires MultipliableAs<typename M::value_type, typename M2::value_type>
    #endif
    constexpr void mul_mat_mut(M& a, const M2&b) { EXEC_IF_NOT_20(static_assert(CONSTEXPR_MATRIX(M) || RUNTIME_MATRIX(M), "mul_mat_mut: M must be a CONSTEXPR_MATRIX or RUNTIME_MATRIX")); operation_mut(a, b, [](typename M::value_type& a, copy_fast_t<typename M2::value_type> b){ a*=b; }); }
    template <MATRIX_TYPENAME M, typename T = typename M::value_type>
    #ifdef HAS_CONCEPTS 
    requires Multipliable<typename M::value_type, T>
    #endif
    constexpr M Mul(const M& mat, copy_fast_t<T> v) { EXEC_IF_NOT_20(static_assert(CONSTEXPR_MATRIX(M) || RUNTIME_MATRIX(M), "Mul: M must be a CONSTEXPR_MATRIX or RUNTIME_MATRIX")); return scalar_operation(mat, std::move(v), [](copy_fast_t<typename M::value_type> a, copy_fast_t<T> b){ return a*b; }); }
    template <MATRIX_TYPENAME M, typename T = typename M::value_type>
    #ifdef HAS_CONCEPTS 
    requires MultipliableAs<typename M::value_type, T>
    #endif
    constexpr void mul_mut(M& mat, copy_fast_t<T> v)  { EXEC_IF_NOT_20(static_assert(CONSTEXPR_MATRIX(M) || RUNTIME_MATRIX(M), "mul_mut: M must be a CONSTEXPR_MATRIX or RUNTIME_MATRIX")); scalar_operation_mut(mat, std::move(v), [](typename M::value_type& a, copy_fast_t<T> b){ a*=b; }); }

    //Div
    template <MATRIX_TYPENAME M, MATRIX_TYPENAME M2>
    #ifdef HAS_CONCEPTS 
    requires Divideable<typename M::value_type, typename M2::value_type>
    #endif
    constexpr M div_mat(const M& a, const M2&b) { EXEC_IF_NOT_20(static_assert(CONSTEXPR_MATRIX(M) || RUNTIME_MATRIX(M), "div_mat: M must be a CONSTEXPR_MATRIX or RUNTIME_MATRIX")); return operation(a,b,[](copy_fast_t<typename M::value_type> a, copy_fast_t<typename M2::value_type> b){ return a/b; }); }
    template <MATRIX_TYPENAME M, MATRIX_TYPENAME M2>
    #ifdef HAS_CONCEPTS 
    requires DivideableAs<typename M::value_type, typename M2::value_type>
    #endif
    constexpr void div_mat_mut(M& a, const M2&b) { EXEC_IF_NOT_20(static_assert(CONSTEXPR_MATRIX(M) || RUNTIME_MATRIX(M), "div_mat_mut: M must be a CONSTEXPR_MATRIX or RUNTIME_MATRIX")); operation_mut(a, b, [](typename M::value_type& a, copy_fast_t<typename M2::value_type> b){ a/=b; }); }
    template <MATRIX_TYPENAME M, typename T = typename M::value_type>
    #ifdef HAS_CONCEPTS 
    requires Divideable<typename M::value_type, T>
    #endif
    constexpr M Div(const M& mat, copy_fast_t<T> v) { EXEC_IF_NOT_20(static_assert(CONSTEXPR_MATRIX(M) || RUNTIME_MATRIX(M), "Div: M must be a CONSTEXPR_MATRIX or RUNTIME_MATRIX")); return scalar_operation(mat, std::move(v), [](copy_fast_t<typename M::value_type> a, copy_fast_t<T> b){ return a/b; }); }
    template <MATRIX_TYPENAME M, typename T = typename M::value_type>
    #ifdef HAS_CONCEPTS 
    requires DivideableAs<typename M::value_type, T>
    #endif
    constexpr void div_mut(M& mat, copy_fast_t<T> v)  { EXEC_IF_NOT_20(static_assert(CONSTEXPR_MATRIX(M) || RUNTIME_MATRIX(M), "div_mut: M must be a CONSTEXPR_MATRIX or RUNTIME_MATRIX")); scalar_operation_mut(mat, std::move(v), [](typename M::value_type& a, copy_fast_t<T> b){ a/=b; }); }
    
    //Pow
    template <typename T, typename T2>
    constexpr T Pow(T base, T2 power) 
    {
        T res = 1;
        for (size_t i = 0; i < power; ++i) 
        {
            res *= base;
        }
        return res;
    }
    template <typename T, typename T2>
    constexpr void pow_mut(T& base, T2 power) 
    {
        T res = 1;
        for (size_t i = 0; i < power; ++i) 
        {
            res *= base;
        }
        base = res;
    }

    template <MATRIX_TYPENAME M, MATRIX_TYPENAME M2>
    #ifdef HAS_CONCEPTS 
    requires Powable<typename M::value_type, typename M2::value_type>
    #endif
    constexpr M pow_mat(const M& a, const M2&b) { EXEC_IF_NOT_20(static_assert(CONSTEXPR_MATRIX(M) || RUNTIME_MATRIX(M), "pow_mat: M must be a CONSTEXPR_MATRIX or RUNTIME_MATRIX")); return operation(a,b,[](copy_fast_t<typename M::value_type> a, copy_fast_t<typename M2::value_type> b){ return pow(a, b); }); }
    template <MATRIX_TYPENAME M, MATRIX_TYPENAME M2>
    #ifdef HAS_CONCEPTS 
    requires Powable<typename M::value_type, typename M2::value_type>
    #endif
    constexpr void pow_mat_mut(M& a, const M2&b) { EXEC_IF_NOT_20(static_assert(CONSTEXPR_MATRIX(M) || RUNTIME_MATRIX(M), "pow_mat_mut: M must be a CONSTEXPR_MATRIX or RUNTIME_MATRIX")); operation_mut(a, b, [](typename M::value_type& a, copy_fast_t<typename M2::value_type> b){ pow_mut(a, b); }); }
    template <MATRIX_TYPENAME M, typename T = typename M::value_type>
    #ifdef HAS_CONCEPTS 
    requires Powable<typename M::value_type, T>
    #endif
    constexpr M pow(const M& mat, copy_fast_t<T> v) { EXEC_IF_NOT_20(static_assert(CONSTEXPR_MATRIX(M) || RUNTIME_MATRIX(M), "pow: M must be a CONSTEXPR_MATRIX or RUNTIME_MATRIX")); return scalar_operation(mat, std::move(v), [](copy_fast_t<typename M::value_type> a, copy_fast_t<T> b){ return pow(a, b); }); }
    template <MATRIX_TYPENAME M, typename T = typename M::value_type>
    #ifdef HAS_CONCEPTS 
    requires Powable<typename M::value_type, T>
    #endif
    constexpr void pow_mut(M& mat, copy_fast_t<T> v)  { EXEC_IF_NOT_20(static_assert(CONSTEXPR_MATRIX(M) || RUNTIME_MATRIX(M), "pow_mut: M must be a CONSTEXPR_MATRIX or RUNTIME_MATRIX")); scalar_operation_mut(mat, std::move(v), [](typename M::value_type& a, copy_fast_t<T> b){ pow_mut(a, b); }); }
};
